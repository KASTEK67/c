int phoneList() {
    Record currentRecord;
    FILE* fptr = NULL;

    errno_t err = fopen_s(&fptr, "data.txt", "r");

    if (err != 0) {
        return -1;
    }

    printf("Name\t\t\tLastname\t\tNumber\n\n");

    while (!feof(fptr)) {
        fscanf_s(fptr, "%s %s %s", currentRecord.name, (unsigned int)sizeof(currentRecord.name), currentRecord.Lastname, (unsigned int)sizeof(currentRecord.Lastname), currentRecord.number, (unsigned int)sizeof(currentRecord.number));
        printf("%-24s", currentRecord.name);
        printf("%-24s", currentRecord.Lastname);
        printf("%-24s\n", currentRecord.number);
    }
    fclose(fptr);
    return 0;
}
