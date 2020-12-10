#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>


int main(int argc, char *argv[]){
    struct timeval current_time;
    int fd[2];
    char convert;
    char buf[15];
    long int time_before;
    pipe(fd);
    int pid = fork();

    if(pid == 0){//proceso hijo
        gettimeofday(&current_time, NULL);
        close(fd[0]);
        time_before = current_time.tv_sec;
        //printf("tiempo hijo %ld\n ",time_before);
        write(fd[1], &time_before, sizeof(time_before));
        close(fd[1]);
        execlp("/bin/ls",argv[1],NULL);
       
    return 0;
    }else{
        wait(NULL);
        gettimeofday(&current_time, NULL);
        close(fd[1]);
        long int a = current_time.tv_sec;//capturo el tiempo
        read(fd[0],&time_before,sizeof(time_before));
        //printf("tiempo padre %ld\n ", a);
        //printf("tiempo hijo %ld\n ", time_before);
        printf("elapsed time %ld\n ", a-time_before);
    }
    
    return 0;
}