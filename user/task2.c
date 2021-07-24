// #include "kernel/types.h"

// #include "user/user.h"

// #include "kernel/fcntl.h"



// int main(int argc, char** argv){

//     fprintf(2, "Hello world!\n");

//     //mask=(1<< SYS_fork)|( 1<< SYS_kill)| ( 1<< SYS_sbrk) | ( 1<< SYS_write);

//     int mask=(1<< 1);

//     sleep(1); //doesn't print this sleep

//     trace(mask, getpid());

//     int cpid=fork();//prints fork once

//     if (cpid==0){

//         fork();// prints fork for the second time - the first son forks

//         mask= (1<< 13); //to turn on only the sleep bit

//         //mask= (1<< 1)|(1<< 13); you can uncomment this inorder to check you print for both fork and sleep syscalls

//         trace(mask, getpid()); //the first son and the grandchilde changes mask to print sleep

//         sleep(1);

//         fork();//should print nothing

//         exit(0);//shold print nothing

//     }

//     else {

//         sleep(10);// the father doesnt pring it - has original mask

//     }

//     exit(0);

// }



// /* example for right printing:
// 3: syscall fork NULL -> 4
// 4: syscall fork NULL -> 5
// 4: syscall sleep -> 0
// 5: syscall sleep -> 0
//  */


#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

#include "kernel/fcntl.h"
#include "kernel/syscall.h"
//#include "kernel/perf.h"

struct perf
{
    int ctime;
    int ttime;
    int stime;
    int retime;
    int rutime;
    int average_bursttime;
};


int main (int argc, char**argv){

    struct perf pe;
    int status;
    int id;
    int sum;
    int i;
//    printf("trace.c. status addr = %d, performance addr = %d\n", &status, &pe);

    int mask= (1<< SYS_fork) | (1<<SYS_wait) | (1<<SYS_set_priority);
    trace(mask,getpid());
    set_priority(1);

    // trace(mask,2);
    if(fork()==0){
        // sleep(3);
        set_priority(2);

        if(fork()==0){
            set_priority(3);
            // sleep(3);
            sum = 0;
            for (i=0; i<1000000000; i++)
                sum += i;

            sleep(1);

            for (i=0; i<1000000000; i++)
                sum += i;
        }
        else {
            // wait(0);
            // sleep(3);

            sum = 0;
            for (i=0; i<1000000000; i++)
                sum += i;
            sleep(1);
            for (i=0; i<1000000000; i++)
                sum += i;

            id = wait_stat(&status,&pe);
            printf("pid %d\n", id);
            printf("ctime: %d\n", pe.ctime);
            printf("ttime: %d\n", pe.ttime);
            printf("stime: %d\n", pe.stime);
            printf("retime: %d\n", pe.retime);
            printf("rutime: %d\n", pe.rutime);
            printf("%lf\n", pe.average_bursttime); //@TODO
        }
    }
    else {
        // wait(0);
        // sleep(3);

        sum = 0;
        for (i=0; i<1000000000; i++)
            sum += i;

        sleep(1);

        for (i=0; i<1000000000; i++)
            sum += i;

        id = wait_stat(&status,&pe);
        printf("pid %d\n", id);
        printf("ctime: %d\n", pe.ctime);
        printf("ttime: %d\n", pe.ttime);
        printf("stime: %d\n", pe.stime);
        printf("retime: %d\n", pe.retime);
        printf("rutime: %d\n", pe.rutime);
        printf("bursttime: %d\n", pe.average_bursttime); //@TODO
    }
    exit(0);
}