/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Team xx (please insert your team number instead of xx)*
 * Team member 1 Adam Jennissen | 50%                    *
 * Team member 2 Carter Bebee | 50%                      *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>

#define WORDLENGTH 20
#define MAXWORDS 2000
#define DEBUGM 0 // Set this to 0 to disable debug output

#define AVATAR '*'
#define EMPTY_SPACE ' '

//////////////////////
// Struct Definition//
////////////////////

/////////////////////////////////////
// User Defined Functions Prototype//
// List prototypes here and define//
// tehm below the main function////
/////////////////////////////////

/*	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y */
void draw_character(int y, int x, char use);

// Reads words from the file into WL and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int read_words(char *WL[MAXWORDS], char *file_name);

// writes words from user into the file
void write_words(char *file_name);

// modifies str to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char *str);

int main(int argc, char *argv[])
{
    // compile with gcc final.c -o final -lncurses ****************************************
    // run with ./final wordlist.txt ******************************************************
    char *wordlist[MAXWORDS];
    int wordcount, minWordLen;
    char playState;
    int i;

    if (argc < 2)
    {
        printf("Please provide an argument\n");
        return 1;
    }

    wordcount = read_words(wordlist, argv[1]);

    if (DEBUGM)
    {
        printf("Read %d words from %s \n", wordcount, argv[1]);
        for (i = 0; i < wordcount; i++)
        {
            printf("%s,", wordlist[i]);
        }
        printf("\n");
    }

    printf("Hello, this is a typing game. You will need to type the words as they appear.\n");
    printf("Would you like to play or add a word?\n");
    printf("You currently have %d words that can be used. (p/w)\n", wordcount);
    scanf(" %c", &playState);

    if (playState == 'w') // code for adding words to the list
    {
        write_words(argv[1]);
        wordcount = read_words(wordlist, argv[1]);
        printf("Would you like to play the game or quit the program? (p/q)\n");
        scanf(" %c", &playState);
    }

    if (playState == 'p') // code for pllaying the game
    {
        printf("What would you like your minimum word length to be?\n");
        scanf(" %d", &minWordLen);
        /* 	Setup screen for Ncurses
        The initscr functionis used to setup the Ncurses environment
        The refreash function needs to be called to refresh the outputs
        to the screen */
        initscr();
        refresh();

        // close the window and end the program
        endwin();
    }
    return 0;
}

///////////////////////////////////////
// User Defined Functions' Definition//
/////////////////////////////////////

/* 	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y
    THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
    DO NOT NEED TO CHANGE THIS FUNCTION. */
void draw_character(int y, int x, char use)
{
    mvaddch(y, x, use);
    refresh();
}

// DO NOT MODIFY THIS FUNCTION!
void trimws(char *str)
{
    int length = strlen(str);
    int x;
    if (length == 0)
        return;
    x = length - 1;
    while (isspace(str[x]) && (x >= 0))
    {
        str[x] = '\0';
        x -= 1;
    }
}

// DO NOT MODIFY THIS FUNCTION!
int read_words(char *WL[MAXWORDS], char *file_name)
{
    int numread = 0;
    char line[WORDLENGTH];
    char *p;
    FILE *fp = fopen(file_name, "r");
    while (!feof(fp))
    {
        p = fgets(line, WORDLENGTH, fp);
        if (p != NULL)
        {
            trimws(line);
            WL[numread] = (char *)malloc(strlen(line) + 1);
            strcpy(WL[numread], line);
            numread++;
        }
    }
    fclose(fp);
    return numread;
}

// DO NOT MODIFY THIS FUNCTION!
void write_words(char *file_name)
{
    char newWord[WORDLENGTH];
    char addWord;
    FILE *fp = fopen(file_name, "a");
    if (fp == NULL)
    {
        printf("Error!");
        exit(1);
    }
    do
    {
        printf("What word would you like to add?\n");
        scanf(" %s", newWord);
        fprintf(fp, "\n%s", newWord);
        printf("Would you like to add any more words? (y/n)\n");
        scanf(" %c", &addWord);
        fflush(stdin);
    } while (addWord == 'y');
    fclose(fp);
}