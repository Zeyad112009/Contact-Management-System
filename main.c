#include <stdio.h>
#include <stdlib.h>

struct contact {
    char name[50];
    char phone[15];
    char email[50];
};

int main(void)
{
    int choice;
    while (1) {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add New Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Delete Contact\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Here you can implement the logic to add a new contact
                struct contact new_contact;
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                //Name input
                printf("\nEnter name: ");
                fgets(new_contact.name, sizeof(new_contact.name), stdin);
                //Phone input
                printf("Enter phone: ");
                fgets(new_contact.phone, sizeof(new_contact.phone), stdin);
                //Email input
                printf("Enter email: ");
                fgets(new_contact.email, sizeof(new_contact.email), stdin);


                FILE *file = fopen("contacts.txt", "a");
                if (file == NULL) {
                    printf("[Error] Could not open file for writing.\n");
                    break;
                }
                fprintf(file, "Name: %sPhone: %sEmail: %s\n", new_contact.name, new_contact.phone, new_contact.email);
                fclose(file);

                printf("\n[Success] Contact saved permanently to contacts.txt!\n");
                break;
            case 2:
                printf("\n[System] Display contacts functionality coming soon...\n");
                break;
            case 3:
                printf("\n[System] Delete contact functionality coming soon...\n");
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