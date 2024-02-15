/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaguirr <alaguirr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:31:08 by alaguirr          #+#    #+#             */
/*   Updated: 2024/02/15 09:31:38 by alaguirr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char **buffer, const char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!*buffer)
		*buffer = ft_strdup("");
	len = ft_strlen(*buffer) + ft_strlen(s2) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	i = -1;
	while ((*buffer)[++i])
		str[i] = (*buffer)[i];
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	free(*buffer);
	*buffer = str;
	return (*buffer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	update_buffer(char **buffer, size_t line_length)
{
	char	*new_buffer;

	new_buffer = ft_strdup(*buffer + line_length);
	free(*buffer);
	*buffer = new_buffer;
	if (!*buffer || **buffer == '\0')
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
