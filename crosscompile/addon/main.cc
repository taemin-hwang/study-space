#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include <cstdio>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include "transfer/message_format.h"

using namespace std;
using namespace std::chrono_literals;

class TestManager {
 public:
    TestManager() = default;
    virtual ~TestManager() = default;

    void Initialize();
    void Run();

 private:
    int sk_port_ = 50001;
    int mq_key_ = 50002;
    int sm_2d_key_ = 50003;
    int sm_3d_key_ = 50004;
    int sm_ds_key_ = 50005;

    int mq_id_, sm_2d_id_, sm_3d_id_, sm_ds_id_;
};

void TestManager::Initialize() {
    while(1) {
        mq_id_ = msgget((key_t)mq_key_, IPC_CREAT|0666);
        sm_2d_id_ = shmget((key_t)sm_2d_key_, sizeof(struct Skeleton2d), 0);
        sm_3d_id_ = shmget((key_t)sm_3d_key_, sizeof(struct Skeleton3d), 0);
        sm_ds_id_ = shmget((key_t)sm_ds_key_, sizeof(struct DriverStatus), 0);

        if (mq_id_ < 0 || sm_2d_id_ < 0 || sm_3d_id_ < 0 || sm_ds_id_ < 0) {
            perror("msgget error : ");
        } else {
            break;
        }

        std::this_thread::sleep_for(100ms);
    }
}

void TestManager::Run() {
    struct Skeleton2d skeleton_2d;
    struct Skeleton3d skeleton_3d;
    struct DriverStatus driver_status;
    struct UiControl ui_control;

    void* sm_2d_mem = (void*)0;
    void* sm_3d_mem = (void*)0;
    void* sm_ds_mem = (void*)0;

    std::cout << "Try to receive message from mq" << std::endl;

    sm_2d_mem = shmat(sm_2d_id_, (const void*)0, 0);
    sm_3d_mem = shmat(sm_3d_id_, (const void*)0, 0);
    sm_ds_mem = shmat(sm_ds_id_, (const void*)0, 0);

    std::cout << "=====================================" << std::endl;
    while(1) {
        // UI Control from MessageQueue
        if (msgrcv( mq_id_, (void *)&ui_control, sizeof(struct UiControl), 0, 0) == -1)         {
            perror("msgrcv error ");
        } else {
            std::cout << "-------------------------------------" << std::endl;
            std::cout << "[1] Type    : " << ui_control.msgtype << std::endl;
            std::cout << "[2] Length  : " << ui_control.length << std::endl;
            std::cout << "[3] Control : " << ui_control.control << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }

        if (sm_2d_mem == (void *)-1) {
            perror("shmat attach is failed ");
        } else {
            memcpy(&skeleton_2d, sm_2d_mem, sizeof(struct Skeleton2d));
            std::cout << "-------------------------------------" << std::endl;
            std::cout << "[1] Type    : " << skeleton_2d.msgtype << std::endl;
            std::cout << "[2] Length  : " << skeleton_2d.length << std::endl;
            std::cout << "[3] Cam ID  : " << skeleton_2d.camid << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }

        // 2D Skeleton from SharedMemory
        if (sm_3d_mem == (void *)-1) {
            perror("shmat attach is failed ");
        } else {
            memcpy(&skeleton_3d, sm_3d_mem, sizeof(struct Skeleton3d));
            std::cout << "-------------------------------------" << std::endl;
            std::cout << "[1] Type    : " << skeleton_3d.msgtype << std::endl;
            std::cout << "[2] Length  : " << skeleton_3d.length << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }

        // 2D Skeleton from SharedMemory
        if (sm_ds_mem == (void *)-1) {
            perror("shmat attach is failed ");
        } else {
            memcpy(&driver_status, sm_ds_mem, sizeof(struct DriverStatus));
            std::cout << "-------------------------------------" << std::endl;
            std::cout << "[1] Type    : " << driver_status.msgtype << std::endl;
            std::cout << "[2] Length  : " << driver_status.length << std::endl;
            std::cout << "[3] Status  : " << driver_status.status << std::endl;
            std::cout << "-------------------------------------" << std::endl;
        }

        std::this_thread::sleep_for(100ms);
    }
    std::cout << "=====================================" << std::endl;
}

int main() {
    cout << "Hello addon!" << endl;
    auto test_manager = make_unique<TestManager>();
    test_manager->Initialize();
    test_manager->Run();
}
