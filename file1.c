#include<stdio.h>
#include<fcntl.h>

int main(){

    int file_descriptor;
    char filename[255];

    printf("Enter the filename: ");
    scanf("%s", filename);

    file_descriptor = open(filename, O_RDONLY);
    
    if(file_descriptor == 3){
        printf("%s Opened Successfully!",filename);
    }else{
        printf("Unable to Open %s",filename);
    }

    return 0;
}
