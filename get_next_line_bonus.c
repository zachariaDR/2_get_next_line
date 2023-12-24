/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadriouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:57:27 by zadriouc          #+#    #+#             */
/*   Updated: 2023/12/22 23:19:37 by zadriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*str_init(int fd)
{
	char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*read_line(int fd, ssize_t *bytes_read, char *buffer, char *part)
{
	ssize_t	rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	rd = read(fd, part, BUFFER_SIZE);
	if (rd < 0)
	{
		free(part);
		free(buffer);
		return (0);
	}
	part[rd] = '\0';
	*bytes_read = rd;
	buffer = ft_strjoin(buffer, part);
	return (buffer);
}

char	*make_clean(char *buffer)
{
	int	i;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (ft_substr(buffer, 0, i));
}

char	*start_newline(char *buffer)
{
	char	*rest;
	int		len;
	int		i;

	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (*(buffer + i) && *(buffer + i) != '\n')
		i++;
	if (*(buffer + i) && *(buffer + i) == '\n')
		i++;
	len = ft_strlen(buffer + i) + 1;
	if (len == 1)
	{
		free(buffer);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * len);
	ft_strlcpy(rest, buffer + i, len);
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*part;
	char		*clean_line;
	static char	*buffer[12288];
	ssize_t		bytes_read;

	part = str_init(fd);
	if (!part)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(part, '\n'))
	{
		buffer[fd] = read_line(fd, &bytes_read, buffer[fd], part);
		if (!buffer[fd])
			return (NULL);
	}
	clean_line = make_clean(buffer[fd]);
	buffer[fd] = start_newline(buffer[fd]);
	free(part);
	return (clean_line);
}
