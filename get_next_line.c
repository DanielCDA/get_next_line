/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:14:33 by danagost          #+#    #+#             */
/*   Updated: 2026/09/03 23:38:37 by danagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_read_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while ((!stash || !gnl_strchr(stash, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

static char	*gnl_extract_line(char *stash)
{
	char	*newline;
	char	*line;

	newline = gnl_strchr(stash, '\n');
	if (newline)
		line = gnl_substr(stash, 0, (newline - stash) + 1);
	else
		line = gnl_substr(stash, 0, gnl_strlen(stash));
	return (line);
}

static char	*gnl_update_stash(char *stash)
{
	char	*newline;
	char	*rest;

	newline = gnl_strchr(stash, '\n');
	if (!newline)
	{
		free(stash);
		return (NULL);
	}
	rest = gnl_substr(stash, (newline - stash) + 1,
			gnl_strlen(stash) - (newline - stash) - 1);
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = gnl_read_stash(fd, stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = gnl_extract_line(stash);
	stash = gnl_update_stash(stash);
	return (line);
}
