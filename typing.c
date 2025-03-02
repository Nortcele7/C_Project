#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#define GREEN 10
#define RED 12
#define WHITE 15

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

int main()
{
    system("cls"); // Clear screen

    // char text[] = "Pulchowk Campus offers undergraduate and graduate programs.";
    char text[] = "Attachment apartments in delightful by motionless it no. ";
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
