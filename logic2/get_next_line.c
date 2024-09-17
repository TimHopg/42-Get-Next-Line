#include "get_next_line.h"

// * Logic and implementation by Laher Wenceslau Payot Maciel

int		ft_clean_buffer(char *buffer);
size_t	ft_strlen_l(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);

/*
 * If buffer is clear, reads from file. If read fails, buffer will be zero so
 * 'line' will be returned which is set to NULL.
 * While buffer is not empty, line is created by joining line and buffer.
 * If buffer has newline, line is returned, else buffer reads from file again.
 */

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (!buffer[fd][0])
		read(fd, buffer[fd], BUFFER_SIZE);
	while (buffer[fd][0])
	{
		line = ft_strjoin_gnl(line, buffer[fd]);
		if (ft_clean_buffer(buffer[fd]))
			break ;
		if (read(fd, buffer[fd], BUFFER_SIZE) < 0)
			return (free(line), NULL);
	}
	return (line);
}
