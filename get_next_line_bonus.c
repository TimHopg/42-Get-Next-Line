/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:40:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/05/09 21:32:51 by thopgood         ###   ########.fr       */
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
