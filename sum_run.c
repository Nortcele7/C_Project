#include <stdio.h>
#include <stdlib.h>

void main() {
    int a;
    char filename[50];

    printf("Enter any number: ");
    scanf("%d", &a);

    if (a == 1) {
        // Ask the user for the file name to store the output
        printf("Enter the name of the file to store the output: ");
        scanf("%s", filename);

        // Prepare the command to run sum.exe and redirect output to the file
        char command[256];
        snprintf(command, sizeof(command), "C:/Users/User/Desktop/C/sum.exe > %s", filename);

        // Run sum.exe normally (this will let it take user input as it would normally)
        int system_status = system(command);

        if (system_status == 0) {
            printf("Output from sum.exe has been saved to %s\n", filename);
        } else {
            printf("Error executing sum.exe.\n");
        }
    } else {
        printf("Ok\n");
    }
}
