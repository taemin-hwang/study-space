#ifndef MESSAGE_FORMAT_H_
#define MESSAGE_FORMAT_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

struct Skeleton3d
{
    int msgtype = 1;
    int length = 132;
    float body[11][3];
};

struct Skeleton2d
{
    int msgtype = 2;
    int length = 92;
    int camid;
    float body[11][2];
};

struct DriverStatus
{
    int msgtype = 3;
    int length = 4;
    int status;
};

struct UiControl
{
    int msgtype = 4;
    int length = 4;
    int control;
};

#endif
