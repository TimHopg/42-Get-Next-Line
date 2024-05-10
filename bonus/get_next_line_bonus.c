/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:40:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/05/09 21:55:43 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
* temp_buf of BUFFER_SIZE + 1 is created and that number of chars are written
* to it.
* temp_buf is then copied to buffer.
* Repeats until '\n' is encountered or EOF. Buffer is returned.
*/

char	*ft_read_line(int fd, char *buffer)
{
	char	*temp_buf;
	char	*temp_ptr;
	int		bytes_read;

	bytes_read = 1;
	temp_buf = malloc(BUFFER_SIZE + 1);
	if (temp_buf == NULL)
		return (ft_dealloc(&buffer));
	while (bytes_read && !ft_strchr_l(buffer, '\n'))
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_dealloc(&buffer), ft_dealloc(&temp_buf));
		temp_buf[bytes_read] = '\0';
		temp_ptr = buffer;
		buffer = ft_strjoin_l(buffer, temp_buf);
		if (buffer == NULL)
			return (ft_dealloc(&temp_buf), ft_dealloc(&temp_ptr));
	}
	return (ft_dealloc(&temp_buf), buffer);
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
	size_t	count;
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
	count = -1;
	while (++count < split_index)
		line[count] = buffer[count];
	line[count] = '\0';
	return (line);
}

/*
* Locates '\n' if it exists and copies following chars to remainder,
* which is returned. Else returns NULL.
*/

char	*ft_split_remainder(char *buffer, int *err_code)
{
	char	*remainder;
	char	*nl_pos;
	char	*temp_ptr;

	if (buffer == NULL)
		return (NULL);
	nl_pos = ft_strchr_l(buffer, '\n');
	if (!nl_pos)
		return (ft_dealloc(&buffer));
	temp_ptr = buffer;
	remainder = ft_strdup(nl_pos + 1);
	if (remainder == NULL)
	{
		*err_code = 1;
		return (ft_dealloc(&temp_ptr));
	}
	return (ft_dealloc(&buffer), remainder);
}

/*
* Reads from buffer
* Builds line for return
* Splits remaining string if necessary
*/

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	int			err_code;

	err_code = 0;
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd < 0 || fd >= MAX_FD)
		return (NULL);
	buffer[fd] = ft_read_line(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = ft_build_line(buffer[fd]);
	if (line == NULL)
		return (ft_dealloc(&buffer[fd]));
	buffer[fd] = ft_split_remainder(buffer[fd], &err_code);
	if (err_code == 1)
		return (ft_dealloc(&line));
	return (line);
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
