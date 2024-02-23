#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
    char write_msg[BUFFER_SIZE] = "Hello, pipe!";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // 创建管道
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // 创建子进程
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) {  // 父进程
        close(fd[READ_END]);  // 关闭读取端

        // 写入数据到管道
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        close(fd[WRITE_END]);  // 关闭写入端
        printf("Parent process wrote to the pipe: %s\n", write_msg);
    } else {  // 子进程
        close(fd[WRITE_END]);  // 关闭写入端

        // 从管道中读取数据
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Child process read from the pipe: %s\n", read_msg);
        close(fd[READ_END]);  // 关闭读取端
    }

    return 0;
}
