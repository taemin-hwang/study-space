#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

struct Skeleton3d
{
    long msgtype;

    int length = 132;
    float body[11][3];
};

struct Skeleton2d
{
    long msgtype;

    int length = 92;
    int camid;
    float body[11][2];
};

struct DriverStatus
{
    long msgtype;

    int length = 4;
    int status;
};

struct UiControl
{
    long msgtype;

    int length = 4;
    int control;
};
