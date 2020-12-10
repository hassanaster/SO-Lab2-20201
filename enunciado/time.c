#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>

//the only way to comunicate between process is throug pipeline
int main(int argc, char *argv[]){
    //type from the date
    struct timeval current_time;
    //pipeline
    int fd[2];
    pipe(fd);
    //char convert;
    //char buf[15];
    //save time in seconds
    long int time_before;
    //?
    int pid = fork();

    if(pid == 0){//proceso hijo
        //I got the time 
        gettimeofday(&current_time, NULL);
        //pipeline father write (close read)
        close(fd[0]);
        //convert time in micro seconds
        time_before = current_time.tv_usec;
        //printf("tiempo hijo %ld\n ",time_before);
        write(fd[1], &time_before, sizeof(time_before));
        close(fd[1]);
        //executation command ls 
        execlp("/bin/ls",argv[1],NULL);
        return 0;
    }else{
        //Father process has to wait child proccess execution
        wait(NULL);
        gettimeofday(&current_time, NULL);
        //pipeline father read (close write)
        close(fd[1]);
        long int a = current_time.tv_usec;//capturo el tiempo
        read(fd[0],&time_before,sizeof(time_before));
        //printf("tiempo padre %ld\n ", a);
        //printf("tiempo hijo %ld\n ", time_before);
        printf("elapsed time %ld\n ", a-time_before);
    }
    return 0;
}
