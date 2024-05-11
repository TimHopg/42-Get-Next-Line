/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:39:06 by thopgood          #+#    #+#             */
/*   Updated: 2024/05/11 11:04:52 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Copies at most dstsize - 1 bytes from src to dest truncating src
 *		if necessary.
 * The destination string is always null terminated.
 * Returns total length of string that was attempted to create (len of src).
 * Check for buffer overflow as follows:
 *	if (strlcpy(dst, src, dstsize) >= dstsize)
 *		return (−1);
*/

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	const char	*src_ptr;

	src_ptr = src;
	if (dstsize > 0)
	{
		while (*src_ptr && dstsize-- > 1)
			*dest++ = *src_ptr++;
		*dest = '\0';
	}
	return (ft_strlen(src));
}

/*
 * Copies contents of rem to buffer.
 * temp_buf of BUFFER_SIZE + 1 reads that many bytes from file
 * temp_buf is then copied to buffer.
 * Repeats until '\n' is encountered or EOF.
 * Returns -1 if error encountered.
 */

int	ft_read_line(int fd, char **buffer, char *rem)
{
	char	*temp_buf;
	char	*temp_ptr;
	int		bytes_read;

	bytes_read = 1;
	*buffer = ft_strdup(rem);
	if (*buffer == NULL)
		return (-1);
	temp_buf = malloc(BUFFER_SIZE + 1);
	if (temp_buf == NULL)
		return (ft_dealloc(buffer), -1);
	while (bytes_read && !ft_strchr_l(*buffer, '\n'))
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_dealloc(buffer), ft_dealloc(&temp_buf), -1);
		temp_buf[bytes_read] = '\0';
		temp_ptr = *buffer;
		*buffer = ft_strjoin_l(*buffer, temp_buf);
		if (*buffer == NULL)
			return (ft_dealloc(&temp_buf), ft_dealloc(&temp_ptr), -1);
	}
	return (ft_dealloc(&temp_buf), 0);
}

/*
 * Receives buffer string which either contains '\n' or is EOF line
 * Locates '\n' if it exists and assigns its index to 'split_index'.
 * If no '\n' split_index is set to length of buffer.
 * Appropriate chars are then copied to line and returned.
 */

char	*ft_build_line(char *buffer)
{
	char	*line;
	size_t	split_index;
	char	*nl_ptr;

	if (buffer[0] == '\0')
		return (NULL);
	nl_ptr = ft_strchr_l(buffer, '\n');
	if (nl_ptr)
		split_index = (nl_ptr - buffer + 1);
	else
		split_index = ft_strlen(buffer);
	line = malloc(split_index + 1);
	if (line == NULL)
		return ((NULL));
	ft_strlcpy(line, buffer, split_index + 1);
	return (line);
}

/*
 * Locates '\n' if it exists and copies following chars to remainder,
 * Returns -1 if error encountered.
 */

int	ft_split_remainder(char **buffer)
{
	char	*remainder;
	char	*nl_pos;
	char	*temp_ptr;

	if (*buffer == NULL)
		return (0);
	nl_pos = ft_strchr_l(*buffer, '\n');
	if (!nl_pos)
		return (ft_dealloc(buffer), 0);
	temp_ptr = *buffer;
	remainder = ft_strdup(nl_pos + 1);
	if (remainder == NULL)
		return (ft_dealloc(&temp_ptr), -1);
	ft_dealloc(buffer);
	*buffer = remainder;
	return (0);
}

/*
 * Reads from buffer
 * Builds line for return
 * Splits remaining string if necessary
 * Copies to static remainder or sets rem to 0
 */

char	*get_next_line(int fd)
{
	static char	remainder[BUFFER_SIZE + 1];
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (ft_read_line(fd, &buffer, remainder) == -1)
	{
		remainder[0] = '\0';
		return (NULL);
	}
	line = ft_build_line(buffer);
	if (line == NULL)
		return (ft_dealloc(&buffer));
	if (ft_split_remainder(&buffer) == -1)
		return (ft_dealloc(&line));
	if (buffer)
		ft_strlcpy(remainder, buffer, ft_strlen(buffer) + 1);
	else
		remainder[0] = '\0';
	return (ft_dealloc(&buffer), line);
}

// /************* STANDARD INPUT ***************/
// int main(void)
// {
//     char *line;
//     int fd = 0; // std input

// 	//ctrl+d == end of file
//     printf("Enter text (press Ctrl+D to exit):\n");

//     /* Read lines until EOF (ctrl+d is pressed) */
//     while ((line = get_next_line(fd)))
//     {
// 			printf("Next line: %s", line);
// 			free(line);
//     }

//     printf("End of input reached. Exiting...\n");
//     return (0);
// }

// /************ EVALUATOR'S INPUT ************/
// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("empty.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	close(fd);

// 	fd = open("empty.txt", O_RDONLY);

// 	for (int i = 0; (line = get_next_line(fd)) != NULL; i++)
// 	{
// 		printf("Line %d: %s", i, line);
// 		free(line);
// 	}

// 	close(fd);
// 	return (0);
// }

// /************* MAIN TESTS ***************/
// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		lines_read;

// 	fd = 42;
// 	printf("NON-READABLE FD VALUE\n");
// 	printf("fd = %d: Should return (null)\n", fd);
// 	printf("RETURNS: %s\n\n", get_next_line(fd));

// 	fd = open("standard_test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd, "AAAAAAAAAA\n", 11);
// 	write(fd, "BBBBBBBBBB\n", 11);
// 	write(fd, "CCCCCCCCCC\n", 11);
// 	write(fd, "DDDDDDDDDD", 10);
// 	close(fd);

// 	printf("STANDARD TEST\n");
// 	lines_read = 1;
// 	fd = open("standard_test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("[Line %d]%s⤶", lines_read++, line);
// 		free(line);
// 	}
//     close(fd);
// 	printf("\n\n");

// 	printf("READ FAIL 1ST ITERATION\n");
// 	lines_read = 1;
// 	fd = -1;
// 	line = get_next_line(fd);
// 	printf("[Line %d]%s⤶", lines_read++, line);
// 	free(line);
// 	printf("\n\n");

// 	printf("READ FAIL 3RD ITERATION\n");
// 	lines_read = 1;
// 	fd = open("standard_test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("[Line %d]%s⤶", lines_read++, line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("[Line %d]%s⤶", lines_read++, line);
// 	free(line);
// 	line = get_next_line(-1);
// 	printf("[Line %d]%s⤶", lines_read++, line);
// 	free(line);
// 	close(fd);
// 	printf("\n\n");

// 	printf("SINGLE LONG LINE\n");
// 	fd = open("single_longline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	int l = 0;
// 	while (l++ < 2500)
// 		write(fd, "A", 1);
// 	close(fd);

// 	fd = open("single_longline.txt", O_RDONLY);
// 	lines_read = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("[Line %d]%s⤶", lines_read++, line);
// 		free(line);
// 	}
//     close(fd);
// 	printf("\n\n");

// 	printf("MULTIPLE LONG LINE\n");
// 	fd = open("multi_longline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	l = 0;
// 	while (l++ < 2500)
// 		write(fd, "A", 1);
// 	write(fd, "\n", 1);
// 	l = 0;
// 	while (l++ < 2500)
// 		write(fd, "B", 1);
// 	write(fd, "\n", 1);
// 	l = 0;
// 	while (l++ < 2500)
// 		write(fd, "C", 1);
// 	close(fd);

// 	fd = open("multi_longline.txt", O_RDONLY);
// 	lines_read = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("[Line %d]%s⤶", lines_read++, line);
// 		free(line);
// 	}
//     close(fd);
// 	printf("\n\n");

// 	printf("SINGLE SHORT LINE\n");
// 	fd = open("single_shortline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd, "Z", 1);
// 	close(fd);

// 	fd = open("single_shortline.txt", O_RDONLY);
// 	lines_read = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("[Line %d]%s⤶", lines_read++, line);
// 		free(line);
// 	}
//     close(fd);
// 	printf("\n\n");

// 	printf("MULTI SHORT LINE\n");
// 	fd = open("multi_shortline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd, "W\n", 2);
// 	write(fd, "X\n", 2);
// 	write(fd, "Y\n", 2);
// 	write(fd, "Z", 1);
// 	close(fd);

// 	fd = open("multi_shortline.txt", O_RDONLY);
// 	lines_read = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("[Line %d]%s⤶", lines_read++, line);
// 		free(line);
// 	}
//     close(fd);
// 	printf("\n\n");

// 	printf("SINGLE EMTPY LINE\n");
// 	printf("Should return (null)\n");
// 	fd = open("single_emptyline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd, "", 0);
// 	close(fd);

// 	fd = open("single_emptyline.txt", O_RDONLY);
// 	lines_read = 1;
// 	line = get_next_line(fd);
// 	printf("[Line %d]%s⤶", lines_read++, line);
// 	free(line);
//     close(fd);
// 	printf("\n\n");

// 	printf("MULTI EMPTY LINE\n");
// 	fd = open("multi_emptyline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd, "\n", 1);
// 	write(fd, "\n", 1);
// 	write(fd, "\n", 1);
// 	write(fd, "", 0);
// 	close(fd);

// 	fd = open("multi_emptyline.txt", O_RDONLY);
// 	lines_read = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("[Line %d]%s⤶", lines_read++, line);
// 		free(line);
// 	}
//     close(fd);
// 	printf("\n\n");

// 	return (0);
// }
