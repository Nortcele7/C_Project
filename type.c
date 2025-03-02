#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#define GREEN 10
#define RED 12
#define WHITE 15
#define MAX_LINES 100
#define MAX_LENGTH 256

void gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);
}

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to fetch a random lesson from file
void getRandomLesson(char *filename, char *text)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    char lines[MAX_LINES][MAX_LENGTH]; // Array to store lines
    int count = 0;

    // Read lines into array
    while (fgets(lines[count], MAX_LENGTH, file))
    {
        lines[count][strcspn(lines[count], "\n")] = '\0'; // Remove newline
        count++;
        if (count >= MAX_LINES)
            break;
    }

    fclose(file);

    if (count == 0)
    {
        printf("No lessons found in file!\n");
        exit(1);
    }

    // Generate a random index
    srand(time(NULL));
    int randomIndex = rand() % count;

    // Store the selected line in text[]
    strcpy(text, lines[randomIndex]);
}

int main()
{
    system("cls"); // Clear screen

    char text[MAX_LENGTH];

    // Get a random lesson
    getRandomLesson("typing_test_sentences.txt", text);
    int len = strlen(text);

    printf("%s", text); // Display the text
    gotoxy(0, 0);       // Move cursor to the start of text

    int i = 0, mistakes = 0, totalKeystrokes = 0;
    time_t startTime = time(NULL); // Start time

    while (i < len)
    {
        char ch = getch(); // Get user input

        // Handle Backspace
        if (ch == 8)
        { // ASCII code for Backspace
            if (i > 0)
            { // Only allow backspace if not at the start
                i--;
                gotoxy(i, 0);          // Move cursor back
                setColor(WHITE);       // Reset to normal color
                printf("%c", text[i]); // Print original character to restore
                gotoxy(i, 0);          // Move cursor back again for correction
            }
            continue;
        }

        totalKeystrokes++; // Increase total keystroke count

        // Handle Spacebar properly
        if (ch == ' ')
        {
            if (text[i] != ' ')
            {
                mistakes++; // Count incorrect spacebar press
                continue;
            }
        }

        // Check if correct character is typed
        if (ch == text[i])
        {
            setColor(GREEN); // Correct → Green
        }
        else
        {
            setColor(RED); // Incorrect → Red
            mistakes++;    // Count incorrect character press
        }

        printf("%c", ch); // Print typed character
        setColor(WHITE);  // Reset color to default
        i++;              // Move to the next character
    }

    // End time and calculations
    time_t endTime = time(NULL);
    double elapsedTime = difftime(endTime, startTime); // Time in seconds

    double wordsTyped = len / 5.0;                                                      // Average word length is 5
    double WPM = (wordsTyped / elapsedTime) * 60.0;                                     // Words per minute
    double accuracy = ((double)(totalKeystrokes - mistakes) / totalKeystrokes) * 100.0; // Accuracy percentage

    printf("\nTyping Complete!\n");
    printf("Total Time: %.2f seconds\n", elapsedTime);
    printf("Words Per Minute (WPM): %.2f\n", WPM);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Total Mistakes: %d\n", mistakes);

    return 0;
}