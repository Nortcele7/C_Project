#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <conio.h> // for getch()
#include<stdlib.h>

#define MAX_USERS 100
#define CREDENTIAL_LENGTH 30
#define FILE_NAME "users_data.txt"

// coloured texts
const char *PINK = "\033[1;35m";
const char *COLOR_END = "\033[0m";

typedef struct {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users_from_file();
void save_users_to_file();
void register_user();
int login_user();
void fix_fgets_input(char *);
void input_credentials(char *, char *);
void get_password(char *password, int maxLength);

int main() {
    load_users_from_file();
    
    int option;
    while (1) {
        printf("\n%sWelcome to User Management System%s", PINK, COLOR_END);
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Use Guest Mode");
        printf("\n4. Exit");
        printf("\nSelect an option: ");
        scanf("%d", &option);
        getchar(); // consume extra newline

        int user_index;
        switch (option) {
        case 1:
            register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0) {
                printf("Login successful! Welcome, %s!", users[user_index].username);
            } else {
                printf("Login Failed! Incorrect username or password\n");
            }
            break;
        case 3:
        {
            printf("USING GUEST MODE");
            system("type.exe");
            break;
        }
        case 4:
            printf("\nExiting program.");
            return 0;
        default:
            printf("\nInvalid option. Please try again.");
            break;
        }
    }
    return 0;
}

void load_users_from_file() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file) {
        user_count = 0;
        while (fscanf(file, "%s %s", users[user_count].username, users[user_count].password) == 2) {
            user_count++;
            if (user_count >= MAX_USERS) break;
        }
        fclose(file);
    }
}

void save_users_to_file() {
    FILE *file = fopen(FILE_NAME, "w");
    fprintf(file,"Name Password\n");
    if (file) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%s %s\n", users[i].username, users[i].password);
        }
        fclose(file);
    }
}

void register_user() {
    if (user_count == MAX_USERS) {
        printf("\nMaximum %d users are supported! No more registrations allowed!!!\n", MAX_USERS);
        return;
    }
    int new_index = user_count;
    printf("\nRegister a new user");
    input_credentials(users[new_index].username, users[new_index].password);

    user_count++;
    save_users_to_file(); // Save to file after registration

    printf("\nRegistration successful!\n");
}

int login_user() {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    
    input_credentials(username, password);
    
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return i;
        }
    }
    return -1;
}

void input_credentials(char *username, char *password) {
    printf("\nEnter username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    printf("Enter password (masking enabled): ");
    get_password(password, CREDENTIAL_LENGTH);
}

void get_password(char *password, int maxLength) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();
        if (ch == 13) // ENTER key
            break;
        else if (ch == 8) { // BACKSPACE key
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (i < maxLength - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

void fix_fgets_input(char *string) {
    int index = strcspn(string, "\n");
    string[index] = '\0';
}