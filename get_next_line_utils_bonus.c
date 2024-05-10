/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:40:13 by thopgood          #+#    #+#             */
/*   Updated: 2024/05/09 21:55:34 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_dealloc(char **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return (NULL);
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

/*
 * Returns a pointer to the first occurrence of c in string s incl. '\0'.
 * Returns NULL if c is not found.
 * *l = also returns null if !s
 */

char	*ft_strchr_l(const char *s, int c)
{
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	i = -1;
	str_len = ft_strlen(s);
	while (++i < str_len + 1)
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	return (NULL);
}

/*
 * String duplication. Allocates memory using malloc for new string and copies
	contents of original string incl. null termination.
*/

char	*ft_strdup(const char *s)
{
	char	*dup_s;
	size_t	i;

	dup_s = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dup_s == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		dup_s[i] = s[i];
	dup_s[i] = '\0';
	return (dup_s);
}

/*
 * Allocates with malloc and returns new string, s1 + s2.
 * Returns ptr to new string or NULL if fails.
 * *** if !s1, returns dup of s2
 */

char	*ft_strjoin_l(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	ft_dealloc((char **)&s1);
	return (res);
}
