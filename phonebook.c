#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "header.h"
#include "menu.h"
#include "phoneAdd.h"
#include "phoneList.h"
#include "phoneSearch.h"   


int main()
{
    int choice = 0;
    char searhName[15];
    int searchResult = 0;
    menu();

    do {
        printf("Please enter your choice: ");
        scanf_s("%d", &choice);
        switch (choice) {
            case 1:
                if (phoneAdd() == 0) {
                    printf("\nAdded successfully.\n");
                }
                else {
                    printf("\nAn error occurred.\n");
                }
                break;

            case 2:
                if (phoneList() == 0) {
                    printf("\nListed successfully.\n");
                }
                else {
                    printf("\nAn error occurred.\n");
                }
                break;

            case 3:printf("Enter the name to search: ");
                scanf_s("%s", &searhName, (unsigned int)sizeof(searhName));
                searchResult = phoneSearch(searhName);
                if (searchResult == 0) {
                    printf("\nNo matching record found.\n");
                }
                else {
                    printf("\nTotal %d record(s) found.\n", searchResult);
                }
                break;

            case 4: printf("Exited successfully");
                return 1;
                break;
            default: printf("Please enter a number between 1 and 4.");
        }
    } while (choice != 4);


    return 0;
}
