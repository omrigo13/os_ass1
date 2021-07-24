
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char **argv)
{
    int cpid = fork();
    if (cpid != 0)
    {
        set_priority(1);
        sleep(10);
        for (int i = 1; i < 20; i++)
        {
            printf("%d\n", cpid);
//            sleep(10);
        }

    }
    else
    {
        set_priority(5);
        sleep(10);
        for (int j = 1; j < 20; j++)
        {
            printf("%d\n", cpid);
//            sleep(10);
        }

    }
    exit(0);
}
