#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <conio.h> // for getch()

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

// coloured texts
const char *PINK = "\033[1;35m";
const char *COLOR_END = "\033[0m";

// TODO: all usernames should be unique

typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS]; // array of size 10 and type User
int user_count = 0;

void register_user();
int login_user(); // returns user index
void fix_fgets_input(char *);
void input_credentials(char *, char *);
void get_password(char *password, int maxLength);

int main()
{
    int option;
    while (1)
    {
        printf("\n%sWelcome to User Management%s", PINK, COLOR_END);
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit");
        printf("\nSelect an option: ");
        scanf("%d", &option);
        getchar(); // consume extra enter(new line)

        int user_index;
        switch (option)
        {
        case 1:
            register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("Login successful! Welcome, %s!", users[user_index].username);
            }
            else
            {
                printf("Login Failed! Incorrect username or password\n");
            }
            break;
        case 3:
            printf("\nExiting program.");
            return 0;
            break;

        default:
            printf("\nInvalid option. Please try again.");
            break;
        }
    }

    return 0;
}

void register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("\nMaximum %d users are supported! No more registrations allowed!!!\n", MAX_USERS);
        return;
    }
    int new_index = user_count;
    printf("\nRegister a new user");
    input_credentials(users[new_index].username, users[new_index].password);

    user_count++;

    printf("\nRegistration successful!\n");
}

int login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    input_credentials(username, password);

    int i;
    for (i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i;
        }
    }

    return -1;
}

void input_credentials(char *username, char *password)
{
    printf("\nEnter username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    printf("Enter password (masking enabled): ");
    get_password(password, CREDENTIAL_LENGTH); // Use masked input
}

void get_password(char *password, int maxLength)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch(); // Read a character without echoing

        if (ch == 13) // ENTER key (ASCII 13)
        {
            break;
        }
        else if (ch == 8) // BACKSPACE key (ASCII 8)
        {
            if (i > 0)
            {
                printf("\b \b"); // Remove last *
                i--;
            }
        }
        else if (i < maxLength - 1) // Limit password length
        {
            password[i++] = ch;
            printf("*"); // Print * instead of actual character
        }
    }

    password[i] = '\0'; // Null-terminate the string
    printf("\n");
}

void fix_fgets_input(char *string)
{
    int index = strcspn(string, "\n");
    string[index] = '\0';
}