/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:16:53 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/17 12:16:59 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(0);
	}
	free(line);
}

/************* MAIN TESTS ***************/
/* int	main(void)
{
	int		fd;
	char	*line;
	int		lines_read;

	fd = 42;
	printf("NON-READABLE FD VALUE\n");
	printf("fd = %d: Should return (null)\n", fd);
	printf("RETURNS: %s\n\n", get_next_line(fd));

	fd = open("txt/standard_test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	write(fd, "AAAAAAAAAA\n", 11);
	write(fd, "BBBBBBBBBB\n", 11);
	write(fd, "CCCCCCCCCC\n", 11);
	write(fd, "DDDDDDDDDD", 10);
	close(fd);

	printf("STANDARD TEST\n");
	lines_read = 1;
	fd = open("txt/standard_test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("[Line %d]%s⤶", lines_read++, line);
		free(line);
	}
	close(fd);
	printf("\n\n");

	printf("READ FAIL 1ST ITERATION\n");
	lines_read = 1;
	fd = -1;
	line = get_next_line(fd);
	printf("[Line %d]%s⤶", lines_read++, line);
	free(line);
	printf("\n\n");

	printf("READ FAIL 3RD ITERATION\n");
	lines_read = 1;
	fd = open("txt/standard_test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("[Line %d]%s⤶", lines_read++, line);
	free(line);
	line = get_next_line(fd);
	printf("[Line %d]%s⤶", lines_read++, line);
	free(line);
	line = get_next_line(-1);
	printf("[Line %d]%s⤶", lines_read++, line);
	free(line);
	close(fd);
	printf("\n\n");

	printf("SINGLE LONG LINE\n");
	fd = open("txt/single_longline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	int l = 0;
	while (l++ < 2500)
		write(fd, "A", 1);
	close(fd);

	fd = open("txt/single_longline.txt", O_RDONLY);
	lines_read = 1;
	while ((line = get_next_line(fd)))
	{
		printf("[Line %d]%s⤶", lines_read++, line);
		free(line);
	}
	close(fd);
	printf("\n\n");

	printf("MULTIPLE LONG LINE\n");
	fd = open("txt/multi_longline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	l = 0;
	while (l++ < 2500)
		write(fd, "A", 1);
	write(fd, "\n", 1);
	l = 0;
	while (l++ < 2500)
		write(fd, "B", 1);
	write(fd, "\n", 1);
	l = 0;
	while (l++ < 2500)
		write(fd, "C", 1);
	close(fd);

	fd = open("txt/multi_longline.txt", O_RDONLY);
	lines_read = 1;
	while ((line = get_next_line(fd)))
	{
		printf("[Line %d]%s⤶", lines_read++, line);
		free(line);
	}
	close(fd);
	printf("\n\n");

	printf("SINGLE SHORT LINE\n");
	fd = open("txt/single_shortline.txt", O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR);
	write(fd, "Z", 1);
	close(fd);

	fd = open("txt/single_shortline.txt", O_RDONLY);
	lines_read = 1;
	while ((line = get_next_line(fd)))
	{
		printf("[Line %d]%s⤶", lines_read++, line);
		free(line);
	}
	close(fd);
	printf("\n\n");

	printf("MULTI SHORT LINE\n");
	fd = open("txt/multi_shortline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	write(fd, "W\n", 2);
	write(fd, "X\n", 2);
	write(fd, "Y\n", 2);
	write(fd, "Z", 1);
	close(fd);

	fd = open("txt/multi_shortline.txt", O_RDONLY);
	lines_read = 1;
	while ((line = get_next_line(fd)))
	{
		printf("[Line %d]%s⤶", lines_read++, line);
		free(line);
	}
	close(fd);
	printf("\n\n");

	printf("SINGLE EMTPY LINE\n");
	printf("Should return (null)\n");
	fd = open("txt/single_emptyline.txt", O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR);
	write(fd, "", 0);
	close(fd);

	fd = open("txt/single_emptyline.txt", O_RDONLY);
	lines_read = 1;
	line = get_next_line(fd);
	printf("[Line %d]%s⤶", lines_read++, line);
	free(line);
	close(fd);
	printf("\n\n");

	printf("MULTI EMPTY LINE\n");
	fd = open("txt/multi_emptyline.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	write(fd, "\n", 1);
	write(fd, "\n", 1);
	write(fd, "\n", 1);
	write(fd, "", 0);
	close(fd);

	fd = open("txt/multi_emptyline.txt", O_RDONLY);
	lines_read = 1;
	while ((line = get_next_line(fd)))
	{
		printf("[Line %d]%s⤶", lines_read++, line);
		free(line);
	}
	close(fd);
	printf("\n\n");

	return (0);
} */
