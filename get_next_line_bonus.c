/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaguirr <alaguirr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:59:32 by alaguirr          #+#    #+#             */
/*   Updated: 2024/02/12 19:09:16 by alaguirr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_buffer	*find_or_add_fd(t_fd_buffer **head, int fd)
{
	t_fd_buffer *temp = *head;
	t_fd_buffer *prev = NULL;

	while (temp)
	{
		if (temp->fd == fd)
			return temp;
		prev = temp;
		temp = temp->next;
	}

	t_fd_buffer *new_node = (t_fd_buffer *)malloc(sizeof(t_fd_buffer));
	if (!new_node)
		return NULL;
	new_node->fd = fd;
	new_node->buffer = NULL;

	if (!prev)
		*head = new_node;
	else
		prev->next = new_node;

	return (new_node);
}

char *extract_line_from_buffer(char **buffer)
{
	char *line_end;
	char *line;
	char *new_buffer;

	if (!(line_end = ft_strchr(*buffer, '\n')))
		line_end = ft_strchr(*buffer, '\0');

	line = ft_substr(*buffer, 0, line_end - *buffer + (*line_end == '\n' ? 1 : 0));
	if (*(line_end + (*line_end == '\n' ? 1 : 0)) != '\0')
	{
		new_buffer = ft_strdup(line_end + (*line_end == '\n' ? 1 : 0));
		free(*buffer);
		*buffer = new_buffer;
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
	}

	return line;
}

char *read_and_update_buffer(t_fd_buffer *current_fd)
{
	char    *temp_buf;
	ssize_t bytes_read;
	char    *temp;
	char    *line;

	temp_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buf)
		return (NULL);
	
	while ((bytes_read = read(current_fd->fd, temp_buf, BUFFER_SIZE)) > 0)
	{
		temp_buf[bytes_read] = '\0';
		if (!current_fd->buffer)
			current_fd->buffer = ft_strdup(temp_buf);
		else
		{
			temp = ft_strjoin(current_fd->buffer, temp_buf);
			free(current_fd->buffer);
			current_fd->buffer = temp;
		}
		if (ft_strchr(current_fd->buffer, '\n'))
			break;
	}
	free(temp_buf);
	
	if (bytes_read < 0)
		return (NULL); // Error de lectura

	if (bytes_read == 0 && (!current_fd->buffer || *current_fd->buffer == '\0'))
	{
		// EOF y buffer vacío
		return (NULL);
	}

	line = extract_line_from_buffer(&(current_fd->buffer));
	return line;
}

char	*get_next_line(int fd)
{
	static t_fd_buffer	*head = NULL;
	t_fd_buffer			*current_fd;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd = find_or_add_fd(&head, fd);
	if (!current_fd)
		return (NULL);
	return (read_and_update_buffer(current_fd));
}