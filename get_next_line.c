#include "get_next_line.h"

char	*ft_read_line(int fd, char *buffer, int *err_code)
{
	char	*temp_buf;
	char	*temp_ptr;
	int		bytes_read;

	bytes_read = 1;
	temp_buf = malloc(BUFFER_SIZE + 1);
	if (temp_buf == NULL)
	{
		*err_code = 1;
		return (NULL);
	}
	while (bytes_read && !ft_strchr_l(buffer, '\n'))
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			*err_code = 1;
			ft_deallocate((void *)&temp_buf);
			return (ft_deallocate((void *)&buffer), NULL);
		}
		temp_buf[bytes_read] = '\0';
		temp_ptr = buffer;
		buffer = ft_strjoin_l(buffer, temp_buf);
		if (buffer == NULL)
		{
			*err_code = 1;
			ft_deallocate((void *)&buffer);
			ft_deallocate((void *)&temp_ptr);
			return (ft_deallocate((void *)&temp_buf), NULL);
		}
		// ft_deallocate((void *)&temp_buf);
	}
	return (ft_deallocate((void *)&temp_buf), buffer);
}

char	*ft_build_line(char *buffer, int *err_code)
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
	{
		*err_code = 1;
		return (/* ft_deallocate((void *)&buffer), */ (NULL)); // !
	}
	count = -1;
	while (++count < split_index)
		line[count] = buffer[count];
	line[count] = '\0';
	return (line);
}

char	*ft_split_remainder(char *buffer, int *err_code)
{
	char	*remainder;
	char	*nl_pos;
	char	*temp_ptr;

	if (buffer == NULL)
		return (NULL);
	nl_pos = ft_strchr_l(buffer, '\n');
	if (!nl_pos)
		return (ft_deallocate((void *)&buffer), NULL);
	temp_ptr = buffer;
	remainder = ft_strdup(nl_pos + 1);
	if (remainder == NULL)
	{
		*err_code = 1;
		return (ft_deallocate((void *)&temp_ptr), (NULL));
	}
	return (ft_deallocate((void *)&buffer), remainder);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	int			err_code;

	err_code = 0;
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd < 0 || fd >= MAX_FD)
		return (NULL);
	buffer[fd] = ft_read_line(fd, buffer[fd], &err_code);
	if (err_code == 1)
	{
		ft_deallocate((void *)&buffer[fd]);
		return (NULL);
	}
	if (buffer[fd] == NULL)
		return (NULL);
	line = ft_build_line(buffer[fd], &err_code);
	if (err_code == 1)
	{	
		// printf("%d err_code\n", err_code);
		return (ft_deallocate((void *)&buffer[fd]), (NULL));
	}
	buffer[fd] = ft_split_remainder(buffer[fd], &err_code);
	if (err_code == 1)
	{
		ft_deallocate((void *)&line);
		return (ft_deallocate((void *)&buffer[fd]), (NULL));
	}
	return (line);
}

// #include <fcntl.h> // open/write
// # include <sys/stat.h> // USR permissions
// #include <stdio.h> // printf

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("standard_test.txt", O_RDONLY);

// 	line = get_next_line(fd);
// 	printf("NEXT LINE:%s\n", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("NEXT LINE:%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("NEXT LINE:%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("NEXT LINE:%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("NEXT LINE:%s\n", line);
// 	free(line);

// 	close(fd);}