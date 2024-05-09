#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_l(char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr_l(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_deallocate(void **ptr);

#endif
