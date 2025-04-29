import numpy as np


def generate_random_gaussians(N):
    """
    N개의 3D Gaussian을 생성한다.
    각 Gaussian은 (위치, 색상, 알파, 공분산)를 가진다.
    """
    gaussians = []

    for _ in range(N):
        # 3D 위치 (x, y, z) : [-1, 1] 범위
        position = np.random.uniform(-1, 1, size=(3,))

        # 색상 (r, g, b) : [0, 1] 범위
        color = np.random.uniform(0, 1, size=(3,))

        # 알파 (opacity) : [0.5, 1.0] 범위
        alpha = np.random.uniform(0.5, 1.0)

        # 공분산 (처음엔 isotropic Gaussian)
        scale = np.random.uniform(0.01, 0.05)  # 크기
        covariance = np.eye(3) * scale  # 동그란 모양

        gaussians.append({
            'position': position,
            'color': color,
            'alpha': alpha,
            'covariance': covariance
        })

    return gaussians

# 테스트
gaussians = generate_random_gaussians(100)
print(f"생성된 Gaussian 수: {len(gaussians)}")
print(f"첫 번째 Gaussian 예시:\n{gaussians[0]}")

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
    """
    3D 포인트를 카메라 view + projection으로 2D로 투영
    points: (N, 3) numpy array
    """
    N = points.shape[0]
    points_hom = np.concatenate([points, np.ones((N, 1))], axis=1)  # Homogeneous 좌표

    # View 변환
    points_view = (view_matrix @ points_hom.T).T

    # Projection 변환
    points_proj = (proj_matrix @ points_view.T).T

    # Homogeneous normalize (clip space → NDC)
    points_proj /= points_proj[:, 3:4]

    # NDC 좌표를 [0, 1] 범위로 변환
    points_2d = (points_proj[:, :2] + 1.0) / 2.0

    return points_2d, points_proj[:, 2]  # (x, y), depth

# 1. 카메라 세팅
eye = np.array([0, 0, 3])   # 카메라 위치
target = np.array([0, 0, 0]) # 카메라가 바라보는 곳
up = np.array([0, 1, 0])     # 위쪽 방향

view_matrix = create_look_at(eye, target, up)
proj_matrix = create_perspective(fov_deg=60, aspect=1.0, near=0.1, far=10.0)

# 2. Gaussian 포인트 추출
points = np.array([g['position'] for g in gaussians])

# 3. 투영
points_2d, depths = project_points(points, view_matrix, proj_matrix)

# 4. 2D 결과 출력
import matplotlib.pyplot as plt

plt.scatter(points_2d[:, 0], points_2d[:, 1], c=[g['color'] for g in gaussians], s=10)
plt.xlim(0, 1)
plt.ylim(0, 1)
plt.gca().invert_yaxis()
plt.title('Projected 2D Gaussians')
plt.savefig('projected_gaussians.png')

import numpy as np
import matplotlib.pyplot as plt

def splat_gaussians(points_2d, colors, depths, canvas_size=(512, 512), sigma=0.02):
    H, W = canvas_size
    canvas = np.ones((H, W, 3)) # RGB 캔버스
    alpha_canvas = np.zeros((H, W))  # alpha 채널 따로

    # 1. depth 기준으로 가까운 것부터
    sorted_indices = np.argsort(depths)

    for idx in sorted_indices:
        cx, cy = points_2d[idx]  # 중심 (0~1 범위)
        color = colors[idx]

        # 화면 좌표로 변환
        px = int(cx * W)
        py = int(cy * H)

        # 주변 픽셀 범위
        r = int(3 * sigma * W)  # 3 sigma 정도 범위만
        for dx in range(-r, r+1):
            for dy in range(-r, r+1):
                x = px + dx
                y = py + dy
                if 0 <= x < W and 0 <= y < H:
                    # 2D Gaussian 값 계산
                    d2 = (dx / W)**2 + (dy / H)**2
                    weight = np.exp(-0.5 * d2 / (sigma**2))

                    # 기존 캔버스와 alpha blending
                    alpha = weight
                    canvas[y, x] = canvas[y, x] * (1 - alpha) + color * alpha
                    alpha_canvas[y, x] = alpha_canvas[y, x] + alpha * (1 - alpha_canvas[y, x])

    return canvas

# 테스트 예제
colors = np.array([g['color'] for g in gaussians])
points_2d, depths = project_points(np.array([g['position'] for g in gaussians]), view_matrix, proj_matrix)

result = splat_gaussians(points_2d, colors, depths)

plt.imshow(np.clip(result, 0, 1))
# plt.axis('off')
plt.title('Splatting Gaussians')
plt.savefig('splatting_result.png')

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