#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    char c[1024];

    if (getcwd(c, sizeof(c)) != NULL){
        printf("Current working directory: %s\n", c);
    } else{
        perror("error\n");
        return 1;
    }

    return 0;
}
