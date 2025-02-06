#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
// #include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        printf("\033[0m");
        //printf("%-10d%-20s%-20s%-20s\n\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
   //loadContactsFromFile(addressBook);

    FILE *fptr = fopen("contacts.txt", "r");
    if (fptr == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char temp[100];
    int i = 0;
    char ch;

    while ((ch = getc(fptr)) != EOF) {

        if (ch == '\n') {
            temp[i] = 0;

            char *tempName = strtok(temp, ",");
            char *tempNumber = strtok(NULL, ",");
            char *tempMail = strtok(NULL, ",");

            strcpy(addressBook->contacts[addressBook->contactCount].name, tempName);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, tempNumber);
            strcpy(addressBook->contacts[addressBook->contactCount].email, tempMail);
            
            addressBook->contactCount++;

            i = 0;
        } else {
            temp[i++] = ch;
        }
    }

    fclose(fptr);
}

/* Function to Save contacts */
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.txt", "w+");

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("Contacts saved successfully\n");
    fclose(fptr);
}

/* Function to Create new contacts */
void createContact(AddressBook *addressBook)
{
    //name
    char temp_name[20];
    printf("Enter the name : ");
    scanf("%[^\n]",temp_name);

    //Phone Number
    char temp_mobile[20];
    printf("Enter the phone : ");
    getchar();
    scanf("%[^\n]",temp_mobile);

    //Email
    char temp_email[20];
    printf("Enter the email : ");
    getchar();
    scanf("%[^\n]",temp_email);

    int Nameflag = 0;
    int Phoneflag = 0;
    int Emailflag = 0;

    //Name validation
    for(int i = 0; temp_name[i]; i++){
        if(!((temp_name[i] >= 'a' && temp_name[i] <= 'z') || (temp_name[i] >= 'A' && temp_name[i] <= 'Z') || temp_name[i] == ' ')){
            Nameflag = 1;
            printf("Invalid name\n");
            break;
        }
    }
    //Checking if the name is already present or not in existing contacts
    for(int i = 0; i < addressBook->contactCount; i++){
        if(!(strcasecmp(temp_name, addressBook->contacts[i].name))){
            Nameflag = 1;
            printf("Name is already exists\n");
            break;
        }
    }
    //mobile number validatation
    for(int i = 0; temp_mobile[i]; i++){
        if(!((temp_mobile[i] >= '0' && temp_mobile[i] <= '9') && strlen(temp_mobile) != 10)){
            Phoneflag = 1;
            printf("Invalid number\n");
            break;
        }
    }
    //Checking if the phone number is already present or not in existing contacts
    for(int i = 0; i < addressBook->contactCount; i++){
        if(!(strcmp(temp_mobile, addressBook->contacts[i].phone))){
            Phoneflag = 1;
            printf("Phone number already exists\n");
            break;
        }
    }
    //email validation
    for(int i = 0; temp_email[i]; i++){
        if(!(strstr(temp_email, ".com") && (strchr(temp_email, '@')))){
            Emailflag = 1;
            printf("Invalid email\n");
            break;
        }
        if(!((temp_email[i] >= '0' && temp_email[i] <= '9') || (temp_email[i] >= 'a' && temp_email[i] <= 'z') || (temp_email[i] >= 'A' && temp_email[i] <= 'Z') || (temp_email[i] == '@') || (temp_email[i] == '.'))){
            Emailflag = 1;
            printf("Invalid email\n");
            break;
        }
    }
    //Check if the email is already present or not in existing contacts
    for(int i = 0; i < addressBook->contactCount; i++){
        if(!(strcasecmp(temp_email, addressBook->contacts[i].email))){
            Emailflag = 1;
            printf("Email ID already exists\n");
            break;
        }
    }
    //If all the name, number and email are valid and not present in existing contacts, Then save the contact
    if((Nameflag == 0) && (Phoneflag == 0) && (Emailflag == 0)){
        strcpy(addressBook->contacts[addressBook->contactCount].name, temp_name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, temp_mobile);
        strcpy(addressBook->contacts[addressBook->contactCount].email, temp_email);
        printf("New Contact is created successfully\n");
        addressBook->contactCount++;
    }

}

/* Function to Search contact in contacts */
void searchContact(AddressBook *addressBook) 
{
    int option;

    char temp_name[50];
    char temp_number[20];
    char temp_mail[20];

    int Nameflag;
    int Numflag;
    int Mailflag;

    int SearchIndex = 0;

    printf("1.Search by Name: \n2.Search by Number: \n3.Search by Email: \nEnter your choice: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        printf("Enter the name: ");
        getchar();
        scanf("%[^\n]", temp_name);
        Nameflag = 0;
        //Searching the name in existing contacts
        printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
        for (int i = 0; i < addressBook->contactCount; i++) {
            if ((strcasestr(addressBook->contacts[i].name, temp_name))) {
                printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++SearchIndex, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\033[0m");
                Nameflag = 1;
                //break;
            }
        }
        if (Nameflag == 0) {
            printf("Name not found\n");
        }
        break;
    case 2:
        printf("Enter the Number: ");
        getchar();
        scanf("%[^\n]", temp_number);
        Numflag = 0;
        //Searching the number in existing contacts
        printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
        for (int i = 0; i < addressBook->contactCount; i++) {
            if ((strstr(addressBook->contacts[i].phone, temp_number))) {
                printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++SearchIndex, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\033[0m");
                Numflag = 1;
                //break;
            }
        }
        if (Numflag == 0) {
            printf("Number not found\n");
        }
        break;
    case 3:
        printf("Enter the Email: ");
        getchar();
        scanf("%[^\n]", temp_mail);
        Mailflag = 0;
        //Searching the mail in existing contacts
        printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
        for (int i = 0; i < addressBook->contactCount; i++) {
            if ((strcasestr(addressBook->contacts[i].email, temp_mail))) {
                printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++SearchIndex, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\033[0m");
                Mailflag = 1;
                //break;
            }
        }
        if (Mailflag == 0) {
            printf("Mail not found\n");
        }
        break;
    default:
        printf("Invalid option\n");
        break;
    }
}

/* Function to edit contacts */
void editContact(AddressBook *addressBook)
{
	printf("Select the options\n");
    printf("1.Edit by name \n2.Edit by email \n");
    printf("Enter the choice: ");

    int editby;
    int nameOption;
    int mailOption;

    char editby_name[50];
    char editby_mail[50];

    int indexMap[100];
    int index = 0;
    int userIndex;
    int actualIndex;

    char new_name[50];
    char new_number[20];
    char new_mail[50];

    int newNameflag;
    int newNumflag;
    int newMailflag;

    scanf("%d", &editby);
    getchar();

    switch (editby)
    {
    case 1:
        printf("Enter the name: ");
        scanf("%[^\n]", editby_name);
        //Searching for the contact in existing contacts by name
        printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
        for(int i = 0; i < addressBook->contactCount; i++){
            
            if(strcasestr(addressBook->contacts[i].name, editby_name)){
                //Storing the Actual indexes in an array
                indexMap[index] = i;
                printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\033[0m");
            }
        //If contacts are matches
        }if (index != 0) {

            //Selecting the Sno which user want to edit
            printf("Enter the SNo to Edit: (1-%d)", index);
            scanf("%d", &userIndex);

            if (index > 0 && userIndex <= index) {
                //getting the actual index value
                actualIndex = indexMap[userIndex-1];

                printf("1.Edit the Name: \n2.Edit the Number: \n3.Edit the Mail: \nEnter the choice: ");
                scanf("%d", &nameOption);
                getchar();
            
                switch (nameOption)
                 {
                    case 1:

                    do {

                        printf("Enter the new Name: ");
                        scanf(" %[^\n]", new_name);
                        newNameflag = 0;
                        //Validating the entered name
                        for(int i = 0; new_name[i]; i++){
                            if(!((new_name[i] >= 'a' && new_name[i] <= 'z') || (new_name[i] >= 'A' && new_name[i] <= 'Z') || new_name[i] == ' ')){
                                newNameflag = 1;
                                printf("Invalid name\n");
                                break;
                            }
                        }
                        //Checking if the name is already present or not in existing contacts, if present print below statement
                        for(int i = 0; i < addressBook->contactCount; i++){
                            if(!(strcasecmp(new_name, addressBook->contacts[i].name))){
                                newNameflag = 1;
                                printf("Name is already exists\n");
                                break;
                            }
                        }
                        //If entered name is not present, Then edit/replace the existing name with entered name at actual location
                        if (newNameflag == 0) {
                            strcpy(addressBook->contacts[actualIndex].name, new_name);
                            printf("Name is edited successfully\n");
                        }
                    } while (newNameflag);
                    break;
                case 2:
                    do {
                        printf("Enter the new Number: ");
                        scanf(" %[^\n]", new_number);
                        newNumflag = 0;
                        //mobile number validation
                        for(int i = 0; new_number[i]; i++){
                            if(!((new_number[i] >= '0' && new_number[i] <= '9') && strlen(new_number) == 10)){
                                newNumflag = 1;
                                printf("Invalid number\n");
                                break;
                            }
                        }
                        //Checking if the number is already present or not in existing contacts, If present then print the below statement
                        for(int i = 0; i < addressBook->contactCount; i++){
                            if(!(strcmp(new_number, addressBook->contacts[i].phone))){
                                newNumflag = 1;
                                printf("Number is already exists\n");
                                break;
                            }
                        }
                        //If the number is not present in existing contacts, Then edit/replace existing number with entered number at actual index
                        if (newNumflag == 0) {
                            strcpy(addressBook->contacts[actualIndex].phone, new_number);
                            printf("Number is edited successfully\n");
                        }
                    }while(newNumflag);
                    break;
                case 3:
                    do {
                        printf("Enter the new Mail: ");
                        scanf(" %[^\n]", new_mail);
                        newMailflag = 0;
                        //email validation
                        for(int i = 0; new_mail[i]; i++){
                            if(!(strstr(new_mail, ".com") && (strchr(new_mail, '@')))){
                                newMailflag = 1;
                                printf("Invalid email\n");
                                break;
                            }
                            if(!((new_mail[i] >= '0' && new_mail[i] <= '9') || (new_mail[i] >= 'a' && new_mail[i] <= 'z') || (new_mail[i] >= 'A' && new_mail[i] <= 'Z') || (new_mail[i] == '@') || (new_mail[i] == '.'))){
                                newMailflag = 1;
                                printf("Invalid email\n");
                                break;
                            }
                        }
                        //Checking if the email is already present or not in existing contacts, If yes then print the below statement 
                        for(int i = 0; i < addressBook->contactCount; i++){
                            if(!(strcasecmp(new_mail, addressBook->contacts[i].email))){
                                newMailflag = 1;
                                printf("Mail is already exists\n");
                                break;
                            }
                        }
                        //If the email is not present, Then eidt/replace the existing email with entered emial at actual index
                        if (newMailflag == 0) {
                            strcpy(addressBook->contacts[actualIndex].email, new_mail);
                            printf("Email is edited successfully\n");
                        }
                    }while(newMailflag);
                    break;
                default:
                    printf("Invalid option");
                    break;
                }
            }
        }else {
            printf("Invalid option\n");
        }
        break;
    case 2:
        printf("Enter the mail: ");
        scanf("%[^\n]", editby_mail);

        //Searching for the contact in existing contacts by email
        printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
        for(int i = 0; i < addressBook->contactCount; i++){
            if(strcasestr(addressBook->contacts[i].email, editby_mail)){
                //Storing the matched contacts indexes
                indexMap[index] = i;
                printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\033[0m");
            }
        //if contacts matches
        }if (index != 0) {
            //Strring the Sno which user want to edit
            printf("Enter the SNo to Edit: ");
            scanf("%d", &userIndex);

            if (userIndex > 0 && userIndex <= index) {
                //Getting actual index
                actualIndex = indexMap[userIndex-1];
                printf("1.Edit the Name: \n2.Edit the Number: \n3.Edit the Mail: ");
                scanf("%d", &mailOption);
                getchar();
                
                switch (mailOption)
                {
                case 1:

                    do {

                        printf("Enter the new Name: ");
                        scanf(" %[^\n]", new_name);
                        newNameflag = 0;
                        //Validating the name
                        for(int i = 0; new_name[i]; i++){
                            if(!((new_name[i] >= 'a' && new_name[i] <= 'z') || (new_name[i] >= 'A' && new_name[i] <= 'Z') || new_name[i] == ' ')){
                                newNameflag = 1;
                                printf("Invalid name\n");
                                break;
                            }
                        }
                        //Checking if the name is already present or not in existing contacts, If yes then print the below statement
                        for(int i = 0; i < addressBook->contactCount; i++){
                            if(!(strcasecmp(new_name, addressBook->contacts[i].name))){
                                newNameflag = 1;
                                printf("Name is already exists\n");
                                break;
                            }
                        }
                        //If name is not present in existing contacts, Then edit/replace existing name with entered name at actual index
                        if (newNameflag == 0) {
                            strcpy(addressBook->contacts[actualIndex].name, new_name);
                            printf("Name is edited successfully\n");
                        }
                    } while (newNameflag);
                    break;
                case 2:
                    do {
                        printf("Enter the new Number: ");
                        scanf(" %[^\n]", new_number);
                        newNumflag = 0;
                        //mobile number validating
                        for(int i = 0; new_number[i]; i++){
                            if(!((new_number[i] >= '0' && new_number[i] <= '9') && strlen(new_number) == 10)){
                                newNumflag = 1;
                                printf("Invalid number\n");
                                break;
                            }
                        }
                        //Checking if the name is already present or not in existing contacts, If yes then print the below statement
                        for(int i = 0; i < addressBook->contactCount; i++){
                            if(!(strcmp(new_number, addressBook->contacts[i].phone))){
                                newNumflag = 1;
                                printf("Number is already exists\n");
                                break;
                            }
                        }
                        //If the number is not present in existing contacts, Then edit/replace the existing number with entered number at actual index
                        if (newNumflag == 0) {
                            strcpy(addressBook->contacts[actualIndex].phone, new_number);
                            printf("Number is edited successfully\n");
                        }
                    }while(newNumflag);
                    break;
                case 3:
                    do {
                        
                        printf("Enter the new Mail: ");
                        scanf(" %[^\n]", new_mail);
                        newMailflag = 0;
                        //email validation
                        for(int i = 0; new_mail[i]; i++){
                            if(!(strstr(new_mail, ".com") && (strchr(new_mail, '@')))){
                                newMailflag = 1;
                                printf("Invalid email\n");
                                break;
                            }
                            if(!((new_mail[i] >= '0' && new_mail[i] <= '9') || (new_mail[i] >= 'a' && new_mail[i] <= 'z') || (new_mail[i] >= 'A' && new_mail[i] <= 'Z') || (new_mail[i] == '@') || (new_mail[i] == '.'))){
                                newMailflag = 1;
                                printf("Invalid email\n");
                                break;
                            }
                        }
                        //Checking if the email is already present or not in existing contacts, If yes then print the below statement
                        for(int i = 0; i < addressBook->contactCount; i++){
                            if(!(strcasecmp(new_mail, addressBook->contacts[i].email))){
                                newMailflag = 1;
                                printf("Mail is already exists\n");
                                break;
                            }
                        }
                        //If the contact is not present, then edit/replace the existed email with entered email at actual index
                        if (newMailflag == 0) {
                            strcpy(addressBook->contacts[actualIndex].email, new_mail);
                            printf("Email is edited successfully\n");
                        }
                    //If user enters an invalid name, number or email we have to give another opportunity to enter again, for this we 
                    //are using the while loop
                    }while(newMailflag);
                    break;
                default:
                    printf("Invalid option\n");
                    break;
                }

            }
            break;
            default:
                printf("Invalid option\n");
                break;
        }else {
            printf("Invalid option\n");
        }
        break;
    }
    
}

/* Function to edit contacts */
void deleteContact(AddressBook *addressBook)
{
    // searchContact(addressBook);

    char deleteName[50];
    char deleteNum[20];
    char deleteMail[50];

    int indexMap[100];

    int ContactLocation = -1;
    int index = 0;
    int userIndex = 1;
    int actualIndex = 0;

    int Nameflag;
    int Numflag;
    int Mailflag;

    int option;
    printf("1.Delete by name: \n2.Delete by Number: \n3.Delete by email: \nEnter your choice: ");
    scanf("%d", &option);
    getchar();

    switch (option) {
        case 1:
            printf("Enter the name: ");
            scanf("%[^\n]", deleteName);
            getchar();
            Nameflag = 0;
            //Searching the name in existing contacts
            printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
            for (int i = 0; i < addressBook->contactCount; i++) {
                if ((strcasestr(addressBook->contacts[i].name, deleteName))) {
                    //Storing the matched contacts index values
                    indexMap[index] = i;
                    printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    printf("\033[0m");
                    Nameflag = 1;
                    //break;
                }
            }
            if (Nameflag == 0) {
                printf("Name not found\n");
                return;
            }else {
                //Getting the Sno which user want to delete
                printf("Enter the SNo to delete (1-%d): ", index);
                scanf("%d", &userIndex);

                if (userIndex > 0 && userIndex <= index) {
                    //Getting the actual index, Which we want to delete
                    actualIndex = indexMap[userIndex-1];
                    for (int i = actualIndex; i < addressBook->contactCount; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i+1];
                    }
                    printf("Contact deleted successfully\n");
                }else {
                    printf("Invalid selection\n");
                }
            }
            break;
        case 2:
            printf("Enter the mobile number: ");
            scanf("%[^\n]", deleteNum);
            getchar();
            Nameflag = 0;
            //Searching the name in existing contacts
            printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
            for (int i = 0; i < addressBook->contactCount; i++) {
                if ((strcasestr(addressBook->contacts[i].phone, deleteNum))) {
                    //Storing the matched contacts indexes
                    indexMap[index] = i;
                    printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    printf("\033[0m");
                    Nameflag = 1;
                    //break;
                }
            }
            if (Nameflag == 0) {
                printf("Number not found\n");
                return;
            }else {
                //Getting the Sno which user want to delete
                printf("Enter the SNo to delete (1-%d): ", index);
                scanf("%d", &userIndex);

                if (userIndex > 0 && userIndex <= index) {
                    //Getting the actual index
                    actualIndex = indexMap[userIndex-1];
                    for (int i = actualIndex; i < addressBook->contactCount; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i+1];
                    }
                    printf("Contact deleted successfully\n");
                }else {
                    printf("Invalid selection\n");
                    return;
                }
            }
            break;
        case 3:
            printf("Enter the email: ");
            scanf("%[^\n]", deleteMail);
            getchar();
            Nameflag = 0;
            //Searching the name in existing contacts
            printf("%-10s%-20s%-20s%-20s\n\n", "SNo.", "Name", "Number", "Email");
            for (int i = 0; i < addressBook->contactCount; i++) {
                if ((strcasestr(addressBook->contacts[i].email, deleteMail))) {
                    //Storing the matched contacts locations
                    indexMap[index] = i;
                    printf("\033[0;36m%-10d\033[0;32m%-20s\033[0;31m%-20s\033[0;33m%-20s\n\n", ++index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    printf("\033[0m");
                    Nameflag = 1;
                    //break;
                }
            }
            if (Nameflag == 0) {
                printf("Mail not found\n");
                return;
            }else {
                //Getting the Sno which user want to delete
                printf("Enter the SNo to delete (1-%d): ", index);
                scanf("%d", &userIndex);

                if (userIndex > 0 && userIndex <= index) {
                    //Getting the actual index
                    actualIndex = indexMap[userIndex-1];
                    for (int i = actualIndex; i < addressBook->contactCount; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i+1];
                    }
                    printf("Contact deleted successfully\n");
                }else {
                    printf("Invalid selection\n");
                }
            }
            break;
        default :
            printf("Invalid option: ");
    }

    

}