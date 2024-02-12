/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaguirr <alaguirr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:25:36 by alaguirr          #+#    #+#             */
/*   Updated: 2024/02/12 21:28:20 by alaguirr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s1) + 1;
	copy = malloc(len);
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s1, len);
	return (copy);
}

char	*extract_line(char **buffer)
{
	char	*line;
	size_t	line_length;

	line_length = 0;
	while ((*buffer)[line_length] && (*buffer)[line_length] != '\n')
		line_length++;
	if ((*buffer)[line_length] == '\n')
		line_length++;
	line = ft_substr(*buffer, 0, line_length);
	if (!line)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	update_buffer(buffer, line_length);
	return (line);
}

static char	*read_and_update_buffer(int fd, char **buffer)
{
	char	*temp_buf;
	int		bytes_read;
	char	*temp;

	temp_buf = malloc(BUFFER_SIZE + 1);
	if (!temp_buf)
		return (NULL);
	bytes_read = read(fd, temp_buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp_buf[bytes_read] = '\0';
		if (!*buffer)
			*buffer = ft_strdup("");
		temp = ft_strjoin(*buffer, temp_buf);
		free(*buffer);
		*buffer = temp;
		if (ft_strchr(temp_buf, '\n'))
			break ;
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
	}
	free(temp_buf);
	if (bytes_read < 0)
		return (NULL);
	return (*buffer);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*source;

	if (!dst && !src)
		return (NULL);
	i = 0;
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_SETSIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	buffer[fd] = read_and_update_buffer(fd, &buffer[fd]);
	if (!buffer[fd] || *buffer[fd] == '\0')
	{
		if (buffer[fd] != NULL)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	line = extract_line(&buffer[fd]);
	return (line);
}
