#include "shell.h"

/**
 * _strncat - concatenates n bytes from src string to dest string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to concatenate
 *
 * Return: pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    size_t i, j;

    i = 0;
    while (dest[i] != '\0')
        i++;

    for (j = 0; j < n && src[j] != '\0'; j++)
        dest[i + j] = src[j];

    dest[i + j] = '\0';

    return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: difference between two ascii values
 */
int _strcmp(const char *s1, const char *s2)
{
    size_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;

    return (s1[i] - s2[i]);
}

/**
 * _strlen - finds and returns length of a string
 * @str: string to find length of
 *
 * Return: length of string
 */
size_t _strlen(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
        len++;

    return (len);
}

/**
 * _strdup - duplicates a string to a new memory location
 * @str: string to duplicate
 *
 * Return: pointer to new duplicated string
 */
char *_strdup(const char *str)
{
    size_t len = _strlen(str);
    char *newstr = safe_malloc((len + 1) * sizeof(char));

    for (size_t i = 0; i <= len; i++)
        newstr[i] = str[i];

    return (newstr);
}

/**
 * _strncmp - compares two strings up to n bytes
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 *
 * Return: difference between first non-matching characters or 0 if equal
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;

    while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;

    if (i == n)
        return (0);

    return (s1[i] - s2[i]);
}
