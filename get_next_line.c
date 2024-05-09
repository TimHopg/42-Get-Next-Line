#include "get_next_line.h"

void	ft_deallocate(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}

char	*ft_read_line(int fd, char *buffer)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (bytes_read != 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (NULL);
	}
	free(tmp);
	return (buffer);
}

char	*ft_build_line(char *buffer)
{
	char	*line;
	int		i;
	// int		j;
	size_t	split_index;
	char	*nl_ptr;

	i = 0;
	// j = 0;
	if (buffer[0] == '\0')
		return (NULL);



	nl_ptr = ft_strchr(buffer, '\n');
	if (nl_ptr)
		split_index = (nl_ptr - buffer + 1);
	else
		split_index = ft_strlen(buffer);
	
	

	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i])
		i++;
	


	line = malloc(split_index + 1);
	if (!line)
		return (NULL);
	
	
	i = 0;
	while (split_index-- >= 0)
	{
		line[i] = buffer[i];
		i++;
	}

	
	// while (buffer[i] && buffer[i] != '\n')
	// 	line[j++] = buffer[i++];
	// if (buffer[i] == '\n')
	// {
	// 	line[j] = '\n';
	// 	j++;
	// }
	// line[j] = '\0';
	return (line);
}

char	*ft_split_remainder(char *buffer)
{
	char	*remainder;
	char 	*nl_pos;

	if (buffer == NULL)
		return (NULL);
	nl_pos = ft_strchr(buffer, '\n');
	if (!nl_pos)
		return (ft_deallocate((void *)&buffer), NULL);
	remainder = ft_strdup(nl_pos + 1);
	if (remainder == NULL)
		return (NULL);
	return (ft_deallocate((void *)&buffer), remainder);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd < 0 || fd >= MAX_FD)
		return (NULL);
	buffer[fd] = ft_read_line(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = ft_build_line(buffer[fd]);
	buffer[fd] = ft_split_remainder(buffer[fd]);
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