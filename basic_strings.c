#include "simple_shell.h"

/**
 * _strlen - get the length of the string
 * @str: input string
 * Return: length
 */
int _strlen(const char *str)
{
	int count = 0;

	if (!str)
		return (count);

	while (str[count])
		count++;

	return (count);
}

/**
 * _strconcat - Concatenate 2 string into one
 * @s1: first string to concatenate
 * @s2: second string to concatenate
 * @s3: third string to concatenate
 * Return: string concatenated
 */
char *_strconcat(char *s1, char *s2, char *s3)
{
	char *pstr = NULL;
	unsigned int len, i = 0, current = 0;
	unsigned int x = 0, y = 0, z = 0;

	s1 = s1 ? s1 : EMPTY_STR;
	s2 = s2 ? s2 : EMPTY_STR;
	s3 = s3 ? s3 : EMPTY_STR;

	x = _strlen(s1), y = _strlen(s2), z = _strlen(s3);

	len = x + y + z;
	if (len == 0)
		return (NULL);

	pstr = malloc(sizeof(char) * (len + 1));

	if (pstr == NULL)
		return (NULL);

	for (current = 0; current < x; current++)
		pstr[current] = s1[current];
	for (i = 0; i < y; current++, i++)
		pstr[current] = s2[i];
	for (i = 0; i < z; current++, i++)
		pstr[current] = s3[i];

	pstr[current] = '\0';
	return (pstr);
}

/**
 * _strdup - duplicate a string
 * @str: input string
 * Return: string duplicated
 */
char *_strdup(char *str)
{
	char *dup, *j;
	int len = 0;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);

	dup = malloc(len + 1);
	j = dup;

	if (j == NULL)
		return (NULL);

	while (*str)
	{
		*j++ = *str++;
		*j = '\0';
	}

	return (dup);
}

/**
 * _strcmp - compares two strings
 * @s1: input parameter
 * @s2: input parameter
 *
 * Return: 0 if equal or b if is different
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0, j = 0;

	for (; s1[i] != '\0' && j == 0; i++)
		j = s1[i] - s2[i];
	return (j);
}
