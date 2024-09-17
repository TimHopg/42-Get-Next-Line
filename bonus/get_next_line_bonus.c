/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:40:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/05/25 19:57:36 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	remainder[MAX_FD][BUFFER_SIZE + 1];
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (ft_read_line(fd, &buffer, remainder[fd]) == -1)
	{
		remainder[fd][0] = '\0';
		return (NULL);
	}
	line = ft_build_line(buffer);
	if (line == NULL)
		return (ft_dealloc(&buffer));
	if (ft_split_remainder(&buffer) == -1)
		return (ft_dealloc(&line));
	if (buffer)
		ft_strlcpy(remainder[fd], buffer, ft_strlen(buffer) + 1);
	else
		remainder[fd][0] = '\0';
	return (ft_dealloc(&buffer), line);
}

// int	main(void)
// {
// 	int fd1;
// 	int fd2;
// 	int fd3;
// 	char	*line;

// 	fd1 = open("bonus1.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd1, "AAAAAAAAAA\n", 11);
// 	write(fd1, "BBBBBBBBBB\n", 11);
// 	write(fd1, "CCCCCCCCCC\n", 11);
// 	write(fd1, "DDDDDDDDDD", 10);
// 	close(fd1);

// 	fd2 = open("bonus2.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd2, "EEEEEEEEEE\n", 11);
// 	write(fd2, "FFFFFFFFFF\n", 11);
// 	write(fd2, "GGGGGGGGGG\n", 11);
// 	write(fd2, "HHHHHHHHHH", 10);
// 	close(fd2);

// 	fd3 = open("bonus3.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	write(fd3, "IIIIIIIIII\n", 11);
// 	write(fd3, "JJJJJJJJJJ\n", 11);
// 	write(fd3, "KKKKKKKKKK\n", 11);
// 	write(fd3, "LLLLLLLLLL", 10);
// 	close(fd3);

// 	int fd1_lines = 1;
// 	int fd2_lines = 1;
// 	int fd3_lines = 1;

// 	printf("MULTIPLE FD TESTS\n");

// 	fd1 = open("bonus1.txt", O_RDONLY);
// 	fd2 = open("bonus2.txt", O_RDONLY);
// 	fd3 = open("bonus3.txt", O_RDONLY);

// 	line = get_next_line(fd1);
// 	printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// 	free(line);

// line = get_next_line(fd2);
// printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// free(line);

// line = get_next_line(fd3);
// printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// free(line);

// line = get_next_line(fd1);
// printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// free(line);

// line = get_next_line(fd2);
// 	printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// 	free(line);

// 	line = get_next_line(fd3);
// 	printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// 	free(line);

// 	line = get_next_line(fd1);
// 	printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// 	free(line);

// 	line = get_next_line(fd2);
// 	printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// 	free(line);

// 	line = get_next_line(fd3);
// 	printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// 	free(line);

// 	line = get_next_line(fd1);
// 	printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// 	free(line);
// 	printf("\n");

// 	line = get_next_line(fd2);
// 	printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// 	free(line);
// 	printf("\n");

// 	line = get_next_line(fd3);
// 	printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// 	free(line);
// 	printf("\n\n");

// 	close(fd1);
// 	close(fd2);
// 	close(fd3);

// 	fd1_lines = 1;
// 	fd2_lines = 1;
// 	fd3_lines = 1;

// 	printf("MULTIPLE FD WITH ERROR\n");

// 	fd1 = open("bonus1.txt", O_RDONLY);
// 	fd2 = open("bonus2.txt", O_RDONLY);
// 	fd3 = open("bonus3.txt", O_RDONLY);

// 	line = get_next_line(fd1);
// 	printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// 	free(line);
// 	line = get_next_line(fd3);
// 	printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// 	free(line);
// 	line = get_next_line(fd3);
// 	printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// 	free(line);
// 	line = get_next_line(-1);
// 	printf("NON-EXISTING FD\n");
// 	printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// 	printf("\n");
// 	line = get_next_line(fd3);
// 	printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("[Line %d][File 1] %s⤶", fd1_lines++, line);
// 	free(line);
// 	printf("\n");
// 	line = get_next_line(fd2);
// 	printf("[Line %d][File 2] %s⤶", fd2_lines++, line);
// 	free(line);
// 	line = get_next_line(fd3);
// 	printf("[Line %d][File 3] %s⤶", fd3_lines++, line);
// 	free(line);
// 	printf("\n");

// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }

// /*
//  * ulimit -a -H: hard limits of system processes
//  * FOPEN_MAX a macro of maximum number of files (not relevant)
//  * sysconf(_SC_OPEN_MAX) in stdio.h system wide max fd
//  * getrlimit/setrlimit process specific limits
//  * #include <sys/stat.h> // USR permissions
// */
