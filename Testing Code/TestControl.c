#include <stdio.h>
#include <stdlib.h>

int main(){
    int returnCode = system("echo Hello, World!");

    if (returnCode == 0) {
        printf("Success");
    }
    else{
        printf("Failure");
    }

    //system("gcc -o a.out "+filename) can compile an code
    //Need to perform systme("./a.out") to execute it.
    //Make a script to go into directories and do make commands before executing maybe?
    //how to implement performance tracking in-between?
    return 0;

}