int phoneSearch(char* sptr) {
    Record currentRecord;
    FILE* fptr = NULL;
    int i = 0;

    errno_t err = fopen_s(&fptr, "data.txt", "r");

    if (err != 0) {
        return -1;
    }

    while (!feof(fptr)) {
        fscanf_s(fptr, "%s %s %s", currentRecord.name, (unsigned int)sizeof(currentRecord.name), currentRecord.Lastname, (unsigned int)sizeof(currentRecord.Lastname), currentRecord.number, (unsigned int)sizeof(currentRecord.number));
        
        if (strstr(currentRecord.name, sptr) != NULL) {
            printf("%-24s", currentRecord.name);
            printf("%-24s", currentRecord.Lastname);
            printf("%-24s\n", currentRecord.number);
            i++;
        }
        
    }
    fclose(fptr);
    return i;
}
