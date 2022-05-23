/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:55 by lolemmen          #+#    #+#             */
/*   Updated: 2022/05/18 15:53:33 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_leaks_free(char *buffer, char *str)
{
	char	*mem;

	mem = ft_strjoin(buffer, str);
	free(buffer);
	return (mem);
}

static char	*ft_save_memory(char *buffer)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	save = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
	{
		save[j] = buffer[i];
		i++;
		j++;
	}
	free(buffer);
	return (save);
}

static char	*ft_treat_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	return (line);
}

static char	*ft_read_file(int fd, char *buffer)
{
	char	*str;
	int		readchar;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	readchar = 1;
	while (!ft_strchr(str, '\n') && readchar > 0)
	{
		readchar = read(fd, str, BUFFER_SIZE);
		if (readchar == -1)
		{
			free(str);
			return (NULL);
		}
		str[readchar] = '\0';
		buffer = ft_leaks_free(buffer, str);
	}
	free(str);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1025];
	char		*line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_treat_line(buffer[fd]);
	buffer[fd] = ft_save_memory(buffer[fd]);
	return (line);
}
