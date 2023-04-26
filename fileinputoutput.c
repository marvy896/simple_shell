#include "shell.h"
/**
 * read_textfile - reads a text file and prints it to the POSIX stdout
 * @filename: the file
 * @letters: number of letters to print
 *
 * Return: actual number of letters it could read and print
 */
ssize_t read_textfile(char *filename, size_t letters)
{
	int fd;
	ssize_t bytes_read;
	char *buffer;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		_perror("read_textfile");
		return (-1);
	}
	buffer = malloc(sizeof(char) * (letters + 1));
	if (buffer == NULL)
	{
		_perror("read_textfile");
		return (-1);
	}
	bytes_read = read(fd, buffer, letters);
	if (bytes_read == -1)
	{
		_perror("read_textfile");
		free(buffer);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	bytes_read = write(STDOUT_FILENO, buffer, bytes_read);
	if (bytes_read == -1)
	{
		_perror("read_textfile");
		free(buffer);
		return (-1);
	}
	free(buffer);
	if (close(fd) == -1)
	{
		_perror("read_textfile");
		return (-1);
	}
	return (bytes_read);
}
/**
 * trunc_text_to_file - appends text to the end of a file
 * @filename: name of file to have text appended to
 * @text_content: text to be appended to the file
 *
 * Return: 1 on success, -1 on failure
 */
int trunc_text_to_file(char *filename, char *text_content)
{
	int fd;
	size_t len;
	ssize_t bytes_written;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		_perror("trunc_text_to_file");
		return (-1);
	}
	if (text_content == NULL)
	{
		if (close(fd) == -1)
		{
			_perror("trunc_text_to_file");
			return (-1);
		}
		return (1);
	}
	len = _strlen(text_content);
	bytes_written = write(fd, text_content, len);
	if (bytes_written == -1)
	{
		_perror("trunc_text_to_file");
		close(fd);
		return (-1);
	}
	if (close(fd) == -1)
	{
		_perror("trunc_text_to_file");
		return (-1);
	}
	return (1);
}

/**
 * append_text_to_file - appends text to the end of a file
 * @filename: name of file to have text appended to
 * @text_content: text to be appended to the file
 *
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(char *filename, char *text_content)
{
	int fd;
	size_t len;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
		return (-1);

	if (text_content == NULL)
		return (close(fd) == -1 ? -1 : 1);

	len = _strlen(text_content);

	if (write(fd, text_content, len) == -1)
	{
		close(fd);
		return (-1);
	}

	return (close(fd) == -1 ? -1 : 1);
}
