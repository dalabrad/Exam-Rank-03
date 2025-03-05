/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:24:56 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/05 19:04:36 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

void	ft_bzero(void *dest, size_t bytes)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)dest;
	if (bytes == 0)
		return ;
	while (bytes > 0)
	{
		*ptr = 0;
		ptr++;
		bytes--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtrn_ptr;

	rtrn_ptr = malloc(count * size);
	if (!rtrn_ptr)
		return (NULL);
	ft_bzero(rtrn_ptr, count * size);
	return (rtrn_ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

char	*ft_strchr(const char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((char)*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlcpy(char	*dest, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while ((size - 1) > 0 && *src)
	{
		*dest = *src;
		dest++;
		src++;
		size--;
	}
	*dest = '\0';
	return (src_len);
}

char	*append_buffer(char *line, char *buffer)
{
	char	*new_line;
	size_t	len;
	size_t	i;

	len = ft_strlen(line) + ft_strlen(buffer);
	new_line = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, line, ft_strlen(line) + 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new_line[ft_strlen(line) + i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		new_line[ft_strlen(line) + i] = '\n';
		i++;
	}
	new_line[ft_strlen(line) + i] = '\0';
	free(line);
	line = NULL;
	return (new_line);
}

void	remaining_buffer(char *buffer)
{
	char	*nl_ptr;
	size_t	len;

	nl_ptr = ft_strchr(buffer, '\n');
	if (!nl_ptr)
		ft_bzero(buffer, BUFFER_SIZE + 1);
	else
	{
		len = ft_strlen(nl_ptr + 1);
		ft_strlcpy(buffer, nl_ptr + 1, len + 1);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1048576)
		return (NULL);
	line = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (ft_bzero(buffer, BUFFER_SIZE + 1), NULL);
	if (buffer[0])
		line = append_buffer(line, buffer);
	if (!line)
		return (ft_bzero(buffer, BUFFER_SIZE + 1), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(line, '\n') && line)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line), ft_bzero(buffer, BUFFER_SIZE + 1), NULL);
		buffer[bytes_read] = '\0';
		line = append_buffer(line, buffer);
	}
	if (*line == '\0')
		return (free(line), ft_bzero(buffer, BUFFER_SIZE + 1), NULL);
	return (remaining_buffer(buffer), line);
}

/* int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	printf("Maximum amount of fd is %ld\n", sysconf(_SC_OPEN_MAX));
	if (argc > 2)
	{
		printf("Error : use ./a.out <filename>." \
			"If no filename provided, read from STDIN_FILENO\n");
		return (EXIT_FAILURE);
	}
	else if (argc == 1)
		fd = STDIN_FILENO;
	else
		fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	i = 1;
	printf("------------------------PRINTING FILE--------------------------\n");
	while (i > 0)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("Line[%d] : %s", i, line);
		i++;
		free(line);
		line = NULL;
	}
	printf("\n------------------------END OF FILE--------------------------\n");
	return (EXIT_SUCCESS);
}
 */