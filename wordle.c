/* wordle.c */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 3
#define BufferSize 8
#define MaxWordCount 302
#define ClrGreen "\033[1;42m"
#define ClrYellow "\033[1;43m"
#define ClrRed "\033[1;41m"
#define ClrTrm "\033[0m"
#define ClrHeader "\033[1;32m"

typedef char Result;
typedef Result *Results;

static char selected_word[5];
static char words[MaxWordCount][5];
static int tries;
static int tried;

int main(int, char **);
void setword(int);
int readfile(char *);
bool isin(char);
void prompt_guess_progress(bool *);
void print_results(Result *, char *);
bool words_matched(bool *);
void mainloop();
Result check_char(int, char);
Result *check_word(char *);

void setword(int max)
{
    int id, x;

    x = getpid();
    srand(x);

    id = rand() % max;

    selected_word[0] = words[id][0];
    selected_word[1] = words[id][1];
    selected_word[2] = words[id][2];
    selected_word[3] = words[id][3];
    selected_word[4] = words[id][4];
}

int readfile(char *filename)
{
    char buff[BufferSize];
    FILE *fp;
    int i, word_size;

    fp = fopen(filename, "r");

    if (!fp)
    {
        perror("fopen");
        return -1;
    }

    memset(buff, 0, 8);

    i = 0;

    while (fgets(buff, BufferSize - 1, fp))
    {

        if (i > MaxWordCount)
            break;

        word_size = strlen(buff);

        if (--word_size == 5)
        {
            buff[word_size] = 0;
        }
        else
        {
            continue;
        }

        words[i][0] = buff[0];
        words[i][1] = buff[1];
        words[i][2] = buff[2];
        words[i][3] = buff[3];
        words[i][4] = buff[4];

        i++;
    }

    fclose(fp);

    return i;
}

bool isin(char ch)
{

    int i;

    for (i = 0; i < 5; i++)
    {
        if (selected_word[i] == ch)
            return true;
    }

    return false;
}

Result check_char(int current_idx, char guess_c)
{
    Result res;

    if (selected_word[current_idx] == guess_c)
    {
        res = ResultGreen;
    }
    else if (isin(guess_c))
    {
        res = ResultYellow;
    }
    else
    {
        res = ResultRed;
    }

    return res;
}

Result *check_word(char *guess_word)
{
    int i;
    static Result results[5];

    for (i = 0; i < 5; i++)
    {
        results[i] = check_char(i, guess_word[i]);
    }

    return results;
}

void prompt_guess_progress(bool correct_indexes[5])
{
    int a;
    printf(" [ ");
    for (a = 0; a < 5; a++)
    {
        if (correct_indexes[a])
        {
            printf(" %c ", selected_word[a]);
        }
        else
        {
            printf(" _ ");
        }
    }
    printf("]\n");
    return;
}

void print_results(Result *res, char *guessed_word)
{
    int a;
    char *Clr;
    for (a = 0; a < 5; a++)
    {
        switch (res[a])
        {
        case ResultGreen:
            Clr = ClrGreen;
            break;
        case ResultYellow:
            Clr = ClrYellow;
            break;
        case ResultRed:
            Clr = ClrRed;
            break;
        default:
            printf("Unkown : %d", res[a]);
            break;
        }
        printf("%s%c%s", Clr, guessed_word[a], ClrTrm);
    }

    printf(" \n");
    return;
}

bool words_matched(bool *arr)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        if (!arr[i])
        {
            return false;
            break;
        }
    }
    return true;
}

void mainloop()
{
    char guess_word[5];
    Result *res;
    bool correct_indexes[5];
    int i;

    while (1)
    {
        printf("\n\n >_ ");
        scanf("%s", guess_word);

        res = check_word(guess_word);

        for (i = 0; i < 5; i++)
        {
            switch (res[i])
            {
            case ResultGreen:
                correct_indexes[i] = 1;
                break;
            case ResultYellow:
                correct_indexes[i] = 0;
                break;
            case ResultRed:
                correct_indexes[i] = 0;
                break;
            }
        }

        printf("\nResult : ");
        print_results(res, guess_word);

        if (words_matched(correct_indexes))
        {
            printf("\nCongratulations! Guess matched.\n");
            break;
        }
        else
        {
            printf("\nProgress : ");
            prompt_guess_progress(correct_indexes);

            if (++tried == tries)
            {
                printf("\nSorry! You couldn't guess the word >>> [ %s ]\n", selected_word);
                tried = 0;
                tries = 30;
                break;
            }

            printf("\nTried %d / %d", tried, tries);
        }
    }
    return;
}

int main(int argc, char *argv[])
{

    int count;

    count = readfile("words.txt");

    setword(count);

    tries = 10;
    tried = 0;

    printf(ClrHeader);
    printf("\n\n\t  ______ _     _ _______ _______ _______      _______ _     _ _______      _  _  _  _____   ______ ______ ");
    printf("\n\t |  ____ |     | |______ |______ |______         |    |_____| |______      |  |  | |     | |_____/ |     \\");
    printf("\n\t |_____| |_____| |______ ______| ______|         |    |     | |______      |__|__| |_____| |    \\_ |_____/");
    printf(ClrTrm);

    printf("\n\n\n\n - Guess the 5 letter word [ _ _ _ _ _ ]");
    printf("\n - Hint :\n\n");
    printf("\t Red -> Character doesn't contain in the correct word\n");
    printf("\t Yellow -> Character contains in the correct word\n");
    printf("\t Green -> Character matches with the correct word\n\n");
    printf(" - You have %d tries to figure it out. Go!", tries);

    mainloop();

    printf("\n\t\033[1;35m-- PLAY AGAIN --\033[0m\n\n");

    return 0;
}