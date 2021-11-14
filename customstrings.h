char* removespaces(char *s);
char* strchr(char *str, char c);
char* strcpy(char *dest, const char *src);

char* removespaces(char *s)
{
	char *p;
	while (p = strchr(s, ' '))
		strcpy(p, p + 1);
	return s;
}

char* strchr(char *str, char c)
{
	char *p = str;
	for (; *p && *p != c; p++)
		;
	return *p ? p : 0;
}

char* strcpy(char *dest, const char *src)
{
	for (int i = 0; *(dest + i) = *(src + i); i++)
		;
	return dest;
}