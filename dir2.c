#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    char dirname[100];
    struct dirent *de;
    DIR *dir;
    
    printf("Enter the directory name: ");
    scanf("%[^\n]%*c", dirname);

    dir = opendir(dirname);
    if (dir == NULL) {
        perror("Not openning\n");
        return 1;
    }

    printf("Contents of directory '%s':\n", dirname);


    while ((de = readdir(dir)) != NULL){
        printf("%s\n", de->d_name);
    }
    closedir(dir);

    return 0;
}
