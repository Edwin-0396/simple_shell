#include "simple_shell.h"
/**
 * strlen - String len
 */
int *_strlen(char *str)
{
	return (0);
}

/**
 * str_concat - Concatenate 2 string into one
 */
char *str_concat(char *s1, char *s2)
{
	char *pstr = NULL;
	unsigned int len;
	unsigned int x = 0,
							 y = 0,
							 z = 0,
							 zz = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[x] != '\0')
		x++;

	while (s2[y] != '\0')
		y++;

	len = x + y + 1;
	pstr = malloc(len * sizeof(char));

	if (pstr == NULL)
		return (NULL);

	for (z = 0; z < x; z++)
		pstr[z] = s1[z];

	for (zz = 0; zz < y; z++, zz++)
		pstr[z] = s2[zz];

	pstr[len] = s2[zz];
	return (pstr);
}

char *_strdup(char *str)
{
	char *c, *j;
	int e = 0;

	if (str == NULL)
		return (NULL);

	while (str[e])
		e++;

	c = malloc(e + 1);
	j = c;

	if (j == NULL)
		return (NULL);

	while (*str)
	{
		*j++ = *str++;
		*j = '\0';
	}

	return (c);
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