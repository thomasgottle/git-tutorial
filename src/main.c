#include <stdio.h>

#include "espl_lib.h"

int main()
{
    unsigned int number;
    int choice;

    printf("Enter an integer: ");
    scanf("%d", &number);

    char* text = num_to_words(number);

    printf("The functions output is: %s \n", text);


    do{
        printf("Enter '1' to run another number or '0' to exit: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Running the program again ... \n");
            printf("Enter an integer: ");
            scanf("%d", &number);

            char* text = num_to_words(number);

            printf("The functions output is: %s \n", text);
        }
        else if (choice == 0)
        {
            printf("Exiting the program. \n");
        }
        else
        {
            printf("Invalid choice. Please try again. \n");
        }
    } while (choice != 0);
    
    return 0;
}