#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define N 256
#define M 50

int main(int argc,char **argv)
{
    setlocale(LC_ALL, "Rus");
    FILE *f;

    char str[N];
    char copy[N];
    char word[M][M];
    char *tmp_words;
    char last[M];
    int word_counter = 0;
    unsigned int min = 9999;

    char *input;
    char *output;

    if (argc != 3)
    {
        printf("Error: found %d arguments. Needs exactly 2", argc-1);
        exit(1);
    }
    input = argv[1];
    output = argv[2];

    f = fopen(input, "r");
    fgets(str, N, f);
    fclose(f);

    f = fopen(output, "w");
    str[strlen(str)] = '\0';
    fprintf(f, "Строка из файлка:\n%s", str);

    int j = 0;
    for(unsigned int i = 0; i < strlen(str); i++)
    {
        if(str[i] != ' ')
        {
            str[j] = str[i];
            j++;
        }
        if( (i>0) && (str[i] == ' ') && (str[i-1] != ' ') )
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';

    if (str[strlen(str) - 1] == '.')
    {
        if (str[strlen(str) - 2] == ' ')
            str[strlen(str) - 2] = '\0';
        else
            str[strlen(str) - 1] = '\0';
    }
    else if (str[strlen(str) - 2] == '.')
    {
        if (str[strlen(str) - 3] == ' ')
            str[strlen(str) - 3] = '\0';
        else
            str[strlen(str) - 2] = '\0';
    }
    else if (str[strlen(str) - 1] == ' ')
        str[strlen(str) - 1] = '\0';

    int len = strlen(str);

    int k;
    for (k = len - 1; k >= 0; k--)
    {
        if (str[k] == ' ')
            break;
    }
    k++;
    for (int i = k;i < len; i++)
    {
        last[i-k] = str[i];
    }
    last[len-k] = '\0';


    strcpy(copy, str);
    strcpy(str, "");

    tmp_words = strtok(copy, " ");
    while (tmp_words != NULL)
    {
        if( strcmp(tmp_words, last) )
        {
            strcat(str, tmp_words);
            strcat(str, " ");
        }
        tmp_words = strtok(NULL, " ");
    }
    str[strlen(str) - 1] = '\0';
    len = strlen(str);
    fprintf(f, "\n\nСтрока без лишних пробелов и слов, равных последнему:\n%s", str);

    j = 0;
    for (int i = 0;i < len; i++)
    {
        if (str[i] != ' ')
        {
            word[word_counter][j] = str[i];
            j++;
        }
        else
        {
            word[word_counter][j] = '\0';
            j = 0;
            word_counter++;
        }
    }
    word[word_counter][j] = '\0';
    word_counter++;

    for (int i = 0; i < word_counter; i++)
    {
        if( strlen(word[i]) < min )
            min = strlen(word[i]);
    }
    fprintf(f, "\n\nСлова с минимальной длиной:\n");

    for (int i = 0; i < word_counter; i++)
    {
        if ( strlen(word[i]) == min )
            fprintf(f, "%s ", word[i]);
    }
    fclose(f);
    return 0;
}
