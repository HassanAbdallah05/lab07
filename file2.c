#include<stdio.h>
#include<fcntl.h>

int main(){

    int file_descriptor;
    char filename[255];

    printf("Enter the filename: ");
    scanf("%s", filename);
   
    file_descriptor = creat(filename, O_RDWR | O_CREAT);

    if(file_descriptor == 3){
        printf("File Created Successfully!");
    }else{
        printf("Unable to Create the File.");
    }

    return 0;
}
