#include "shell.h"

/**
 * _strcpy - copies a string from src to dest
 * @dest: new copy of string
 * @src: the source of the copy
 *
 * Return: pointer to copy
 */
char *_strcpy(char *dest, const char *src)
{
    int i = 0;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return (dest);
}

/**
 * _strncpy - copies string from source to destination
 * @dest: destination string
 * @src: source string to be copied
 * @n: bytes to be copied from source string
 *
 * Return: destination string concatenated
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];

    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }

    return (dest);
}

/**
 * _strcat - concatenates from src string to dest string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination
 */
char *_strcat(char *dest, const char *src)
{
    size_t dest_len = _strlen(dest);
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];

    dest[dest_len + i] = '\0';

    return (dest);
}
