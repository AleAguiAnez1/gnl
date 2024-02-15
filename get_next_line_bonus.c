/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaguirr <alaguirr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:59:32 by alaguirr          #+#    #+#             */
/*   Updated: 2024/02/15 11:33:44 by alaguirr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	char	temp_buf[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, temp_buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp_buf[bytes_read] = '\0';
		temp = ft_strjoin(buffer, temp_buf);
		if (!temp)
			return (free(temp_buf), NULL);
		*buffer = temp;
		if (ft_strchr(temp_buf, '\n'))
			break ;
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
	}
	if (bytes_read < 0 || !*buffer || **buffer == '\0')
	{
		free(*buffer);
		*buffer = NULL;
	}
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
