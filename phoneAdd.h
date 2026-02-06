int phoneAdd() {
    Record newRecord;
    FILE* fptr = NULL;

    errno_t err = fopen_s(&fptr, "data.txt", "a");

    if (err != 0) {
        return -1;
    }

    printf("\n\nEnter first name:");
    scanf_s("%s", newRecord.name, (unsigned int)sizeof(newRecord.name));

    printf("Enter last name:");
    scanf_s("%s", newRecord.Lastname, (unsigned int)sizeof(newRecord.Lastname));

    printf("Enter phone number:");
    scanf_s("%s", newRecord.number, (unsigned int)sizeof(newRecord.number));

    
    if (fptr != NULL) {
        fprintf(fptr, "\n%s %s %s", newRecord.name, newRecord.Lastname, newRecord.number);
        fclose(fptr);
    }

    return 0;
}