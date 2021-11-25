char *strchr(char *str, char c);
char *strcpy(char *destination, const char *source);
void strins(char *s, char *sub_s);
unsigned int strlen(const char *str);
char *strstr1(const char *str, const char *substring);
int compare(const char *X, const char *Y);
char *strstr(char *X, char *Y);

char *strchr(char *str, char c)
{
    char *p = str;
    for (; *p && *p != c; p++);
    return *p ? p : 0;
}

char *strcpy(char *destination, const char *source)
{
    while ((*destination++ = *source++) != '\0');
    return destination;
}

void strins(char *s, char *sub_s)
{
    char *temp = (char *)malloc(strlen(s) + 1);
    strcpy(temp, s);
    strcpy(s, sub_s);
    strcpy(s + strlen(sub_s), temp);
    free(temp);
}

unsigned int strlen(const char *str)
{
    unsigned int len = 0;
    for (; *str != '\0'; len++, str++);
    return len;
}

char *strstr1(const char *str, const char *substring)
{
    const char *a;
    const char *b;

    b = substring;

    if (*b == 0)
    {
        return (char *)str;
    }

    for (; *str != 0; str += 1)
    {
        if (*str != *b)
        {
            continue;
        }

        a = str;
        while (1)
        {
            if (*b == 0)
            {
                return (char *)str;
            }
            if (*a++ != *b++)
            {
                break;
            }
        }
        b = substring;
    }

    return NULL;
}

// returns true if `X` and `Y` are the same
int compare(const char *X, const char *Y)
{
    while (*X && *Y)
    {
        if (*X != *Y)
        {
            return 0;
        }

        X++;
        Y++;
    }

    return (*Y == '\0');
}

// Function to implement `strstr()` function
char *strstr(char *X, char *Y)
{
    while (*X != '\0')
    {
        if ((*X == *Y) && compare(X, Y))
        {
            return X;
        }
        X++;
    }

    return NULL;
}