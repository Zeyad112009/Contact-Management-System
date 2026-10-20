#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct contact {
    char name[50];
    char phone[15];
    char email[50];
};
// Function prototypes
void start (int *choice) {

        printf("\n--- Contact Management System ---\n");
        printf("1. Add New Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Delete Contact\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", choice);
}
// Function to clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

// Function to add a new contact
void add_contact() {
    struct contact new_contact;
    clear_input_buffer();

    printf("\nEnter name: ");
    fgets(new_contact.name, sizeof(new_contact.name), stdin);
    new_contact.name[strcspn(new_contact.name, "\n")] = 0; 

    printf("Enter phone: ");
    fgets(new_contact.phone, sizeof(new_contact.phone), stdin);
    new_contact.phone[strcspn(new_contact.phone, "\n")] = 0; 

    printf("Enter email: ");
    fgets(new_contact.email, sizeof(new_contact.email), stdin);
    new_contact.email[strcspn(new_contact.email, "\n")] = 0; 

    FILE *file = fopen("contacts.txt", "a");
    if (file == NULL) {
        printf("[Error] Could not open file for writing.\n");
        return;
    }
    
    fprintf(file, "## %s ## %s ## %s\n", new_contact.name, new_contact.phone, new_contact.email);
    fclose(file);

    printf("\n[Success] Contact saved permanently to contacts.txt!\n");
}
// Function to display all contacts
void display_contact(){
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("[Error] Could not open file for reading.\n");
        return;
    }
    char line[200];
    int count = 1;
    printf("\n--- All Contacts ---\n");
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *name = strtok(line, "##");
        char *phone = strtok(NULL, "##");
        char *email = strtok(NULL, "##");
        if (name != NULL && phone != NULL && email != NULL) {
            printf("%d. Name: %s, Phone: %s, Email: %s\n",count, name, phone, email);
            count++;
        }
    }
    fclose(file);
    printf("================================================\n");
    if (count == 1) {
        printf("[Info] No contacts found.\n");
    }
}
//Delete function
void delete_contact() {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("\n[Info] No contacts found to delete.\n");
        return;
    }
    int delete_choice;
    display_contact();
    printf("\n[System] Choose a contact to delete (enter the number): ");
    scanf("%d", &delete_choice);
    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("[Error] Could not create temporary file.\n");
        fclose(file);
        return;
    }
    char line[200];
    char current_line = 1;
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (current_line != delete_choice) {
            fputs(line, temp_file);
        } else {
            found = 1;
        }
        current_line++;
    }
    fclose(file);
    fclose(temp_file);

    if (found) {
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
        printf("\n[Success] Contact deleted successfully!\n");
    } else {
        remove("temp.txt");
        printf("\n[Error] Invalid contact number. No contact deleted.\n");
    }

    
}
int main(void) {
        int choice;
    while (1) {
        start(&choice);
        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                display_contact();
                break;
            case 3:
                delete_contact();
                break;
            case 4:
                printf("\n[System] Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("\n[Error] Invalid choice! Please try again.\n");
        }
    }
    return 0;
}