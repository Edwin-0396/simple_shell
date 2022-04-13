#include "simple_shell.h"
/**
 * strlen - String len
 */
int *_strlen(char *str)
{
	return (0);
}

/**
 * strconcat - Concatenate 2 string into one
 */
char *_strconcat(char *str1, char *str2)
{
	return (NULL);
}

int _splitstring(char *str)
{
	int i, searchflag = 1, wordcount = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && searchflag == 1)
		{
			wordcount += 1;
			searchflag = 0;
		}
		if (str[i + 1] == ' ')
			searchflag = 1;
	}
	return (wordcount);
}