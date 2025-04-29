import numpy as np


def generate_random_3d_gaussians(N):
    gaussians = []

    for _ in range(N):
        position = np.random.uniform(-1, 1, size=(3,))
        color = np.random.uniform(0, 1, size=(3,))
        alpha = np.random.uniform(0.5, 1.0)

        # 3D covariance 만들기
        angle1 = np.random.uniform(0, 2*np.pi)
        angle2 = np.random.uniform(0, 2*np.pi)

        # rotation matrices (간단히 x, y축 중심으로만 회전 줄게)
        Rx = np.array([
            [1, 0, 0],
            [0, np.cos(angle1), -np.sin(angle1)],
            [0, np.sin(angle1), np.cos(angle1)]
        ])

        Ry = np.array([
            [np.cos(angle2), 0, np.sin(angle2)],
            [0, 1, 0],
            [-np.sin(angle2), 0, np.cos(angle2)]
        ])

        R = Ry @ Rx  # 회전 조합

        scale = np.random.uniform(0.01, 0.05, size=(3,))
        S = np.diag(scale**2)  # 스케일링

        covariance = R @ S @ R.T  # 3D 공분산 생성

        gaussians.append({
            'position': position,
            'color': color,
            'alpha': alpha,
            'covariance_3d': covariance
        })

    return gaussians

def create_look_at(eye, target, up):
    """
    카메라의 view matrix를 생성한다.
    eye: 카메라 위치 (3,)
    target: 카메라가 바라보는 점 (3,)
    up: 위쪽 방향 (3,)
    """
    forward = target - eye
    forward = forward.astype(np.float64)
    forward /= np.linalg.norm(forward)

    right = np.cross(forward, up)
    right /= np.linalg.norm(right)

    new_up = np.cross(right, forward)

    # View matrix 구성
    view = np.eye(4)
    view[0, :3] = right
    view[1, :3] = new_up
    view[2, :3] = -forward
    view[:3, 3] = -eye @ view[:3, :3]

    return view

def create_perspective(fov_deg, aspect, near, far):
    """
    퍼스펙티브 투영 매트릭스 생성
    fov_deg: 수직 시야각 (degree)
    aspect: 종횡비 (width / height)
    near, far: near/far clipping planes
    """
    fov_rad = np.deg2rad(fov_deg)
    f = 1.0 / np.tan(fov_rad / 2)

    proj = np.zeros((4, 4))
    proj[0, 0] = f / aspect
    proj[1, 1] = f
    proj[2, 2] = (far + near) / (near - far)
    proj[2, 3] = (2 * far * near) / (near - far)
    proj[3, 2] = -1

    return proj

def project_points(points, view_matrix, proj_matrix):
    N = points.shape[0]
    points_hom = np.concatenate([points, np.ones((N, 1))], axis=1)

    points_view = (view_matrix @ points_hom.T).T
    points_proj = (proj_matrix @ points_view.T).T

    points_proj /= points_proj[:, 3:4]

    points_2d = (points_proj[:, :2] + 1.0) / 2.0
    depth = points_proj[:, 2]

    return points_2d, depth, points_view[:, :3]  # view space position 반환

import numpy as np
import matplotlib.pyplot as plt

def project_covariance(points_view, covariances_3d):
    # points_view: view space에서의 3D 포인트 위치 (3D) (N, 3)
    # covariances_3d: 3D 공분산 (3x3) (N, 3, 3)
    projected_covariances = []

    for i in range(len(points_view)):
        x, y, z = points_view[i]
        covariance_3d = covariances_3d[i]

        # Jacobian 계산
        J = np.array([
            [1 / -z, 0, x / (z**2)],
            [0, 1 / -z, y / (z**2)]
        ])

        # 2D covariance
        covariance_2d = J @ covariance_3d @ J.T
        projected_covariances.append(covariance_2d)

    return projected_covariances

def splat_gaussians_covariance(points_2d, colors, depths, covariances, canvas_size=(512, 512)):
    H, W = canvas_size
    canvas = np.zeros((H, W, 3))
    alpha_canvas = np.zeros((H, W))

    sorted_indices = np.argsort(depths)

    for idx in sorted_indices:
        cx, cy = points_2d[idx]
        color = colors[idx]
        covariance = covariances[idx]

        px = int(cx * W)
        py = int(cy * H)

        eigvals = np.linalg.eigvals(covariance)
        max_sigma = np.sqrt(np.max(eigvals))
        r = int(3 * max_sigma * max(W, H)) # 3-sigma rule 99.7% 범위

        if np.linalg.det(covariance) == 0:
            continue
        cov_inv = np.linalg.inv(covariance)

        for dx in range(-r, r+1):
            for dy in range(-r, r+1):
                x = px + dx
                y = py + dy
                if 0 <= x < W and 0 <= y < H:
                    delta = np.array([dx / W, dy / H])
                    d2 = delta.T @ cov_inv @ delta
                    weight = np.exp(-0.5 * d2)

                    alpha = weight
                    canvas[y, x] = canvas[y, x] * (1 - alpha) + color * alpha
                    alpha_canvas[y, x] = alpha_canvas[y, x] + alpha * (1 - alpha_canvas[y, x])

    return canvas

# 테스트
gaussians = generate_random_3d_gaussians(100)
print(f"생성된 Gaussian 수: {len(gaussians)}")
print(f"첫 번째 Gaussian 예시:\n{gaussians[0]}")

# 1. 카메라 세팅
eye = np.array([0, 0, 3])   # 카메라 위치
target = np.array([0, 0, 0]) # 카메라가 바라보는 곳
up = np.array([0, 1, 0])     # 위쪽 방향

view_matrix = create_look_at(eye, target, up)
proj_matrix = create_perspective(fov_deg=60, aspect=1.0, near=0.1, far=10.0)

# 2. Gaussian 포인트 추출
points = np.array([g['position'] for g in gaussians])
colors = np.array([g['color'] for g in gaussians])
covariances_3d = np.array([g['covariance_3d'] for g in gaussians])

# 3. 중심 투영
points = np.array([g['position'] for g in gaussians])
colors = np.array([g['color'] for g in gaussians])
covariances_3d = [g['covariance_3d'] for g in gaussians]

points_2d, depths, points_view = project_points(points, view_matrix, proj_matrix)

# 4. 3D covariance → 2D covariance
covariances_2d = project_covariance(points_view, covariances_3d)

# 5. 2D splatting
result = splat_gaussians_covariance(points_2d, colors, depths, covariances_2d)


# 두 개의 이미지를 subplot으로 합치기
fig, axes = plt.subplots(1, 2, figsize=(12, 6))  # 1행 2열의 subplot 생성

# 첫 번째 이미지: Projected 2D Gaussians
axes[0].scatter(points_2d[:, 0], points_2d[:, 1], c=[g['color'] for g in gaussians], s=10)
axes[0].set_xlim(0, 1)
axes[0].set_ylim(0, 1)
axes[0].invert_yaxis()
axes[0].set_title('Projected 2D Gaussians')

# 두 번째 이미지: Splatting Gaussians
axes[1].imshow(np.clip(result, 0, 1))
axes[1].set_title('Splatting Gaussians')

# 공통 설정
for ax in axes:
    ax.axis('off')  # 축 숨기기

plt.tight_layout()
plt.savefig('combined_result.png')  # 결과 저장
plt.show()