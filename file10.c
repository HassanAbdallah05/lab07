#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: ./program <input_file> <output_file>\n", 45);
        exit(1);
    }

    const char *in_file = argv[1];
    const char *out_file = argv[2];

    int in_fd = open(in_file, O_RDONLY);
    if (in_fd < 0) {
        perror("open input");
        exit(1);
    }

    int out_fd = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (out_fd < 0){
        perror("Error while openning output");
        close(in_fd);
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("eror fork");
        exit(1);
    }

    else if (pid == 0){
        int al_ctr = 0;
        char buf[BUF_SIZE];
        int b;

        int child_fd = open(in_file, O_RDONLY);
        if (child_fd < 0) {
            perror("child open input");
            exit(1);
        }

        while ((b = read(child_fd, buf, BUF_SIZE)) > 0) {
            for (int i = 0; i < b; i++) {
                if (isalpha(buf[i])) {
                    al_ctr++;
                }
            }
        }

        char msg[100];
        int len = sprintf(msg, "Child PID %d counted %d alphabets.\n", getpid(), al_ctr);
        write(out_fd, msg, len);

        close(child_fd);
        close(out_fd);
        exit(0);
    }

    else{
        int d_ctr = 0;
        char buf[BUF_SIZE];
        int b;

        while((b = read(in_fd, buf, BUF_SIZE)) > 0){
            for (int i = 0; i < b; i++){
                if (isdigit(buf[i])){
                    d_ctr++;
                }
            }
        }

        wait(NULL);

        char msg[100];
        int len = sprintf(msg, "Parent PID %d counted %d digits.\n", getpid(), d_ctr);
        write(out_fd, msg, len);

        close(in_fd);
        close(out_fd);
    }

    return 0;
}
