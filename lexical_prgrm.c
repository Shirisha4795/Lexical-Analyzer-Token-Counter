#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char word[])
{
    char keywords[][10] = {
        "int", "float", "char", "double", "if",
        "else", "for", "while", "do", "return",
        "void", "main", "break", "continue"
    };

    int i;
    for (i = 0; i < 14; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    FILE *fp;
    char ch, word[50];
    int i;
    int keywords = 0, identifiers = 0;
    int numbers = 0, operators = 0, special = 0;

    fp = fopen("input.c", "r");

    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalpha(ch) || ch == '_')
        {
            i = 0;

            while (isalnum(ch) || ch == '_')
            {
                word[i++] = ch;
                ch = fgetc(fp);
            }

            word[i] = '\0';

            if (isKeyword(word))
            {
                printf("Keyword    : %s\n", word);
                keywords++;
            }
            else
            {
                printf("Identifier : %s\n", word);
                identifiers++;
            }

            ungetc(ch, fp);
        }

        else if (isdigit(ch))
        {
            i = 0;

            while (isdigit(ch))
            {
                word[i++] = ch;
                ch = fgetc(fp);
            }

            word[i] = '\0';

            printf("Number     : %s\n", word);
            numbers++;

            ungetc(ch, fp);
        }

        else if (ch == '+' || ch == '-' || ch == '*' ||
                 ch == '/' || ch == '=' || ch == '<' ||
                 ch == '>' || ch == '%')
        {
            printf("Operator   : %c\n", ch);
            operators++;
        }

        else if (ch == ';' || ch == ',' || ch == '(' ||
                 ch == ')' || ch == '{' || ch == '}' ||
                 ch == '[' || ch == ']')
        {
            printf("Special    : %c\n", ch);
            special++;
        }
    }

    fclose(fp);

    printf("\n------ Token Count ------\n");
    printf("Keywords    : %d\n", keywords);
    printf("Identifiers : %d\n", identifiers);
    printf("Numbers     : %d\n", numbers);
    printf("Operators   : %d\n", operators);
    printf("Special     : %d\n", special);

    return 0;
}
