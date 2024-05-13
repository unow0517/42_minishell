/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:12:05 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 19:06:53 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(char *line_const, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		chars_read;
	char	*temp;

	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
			return (NULL);
		buffer[chars_read] = '\0';
		temp = line_const;
		line_const = ft_strjoin(temp, buffer);
		if (!line_const)
			return (NULL);
		free(temp);
	}
	return (line_const);
}

char	*return_line(char	*line_const)
{
	char	*output_line;
	int		i;

	i = 0;
	if (line_const && line_const[i] == '\0')
		return (NULL);
	while (line_const && line_const[i] != '\0' && line_const[i] != '\n')
		i++;
	if (line_const[i] == '\n')
		i++;
	output_line = ft_calloc(i + 1, sizeof(char));
	if (!output_line)
		return (NULL);
	i = 0;
	while (line_const && line_const[i] != '\0' && line_const[i] != '\n')
	{
		output_line[i] = line_const[i];
		i++;
	}
	if (line_const[i] == '\n')
		output_line[i] = '\n';
	return (output_line);
}

char	*remaining_line(char *line_const)
{
	int		i;
	char	*remaining_chars;
	char	*new_startpoint;

	i = 0;
	if (!line_const)
		return (NULL);
	remaining_chars = 0;
	new_startpoint = ft_strchr(line_const, '\n');
	if (new_startpoint)
	{
		while (line_const && line_const[i] != '\n')
			i++;
		if (line_const[i + 1] != 0)
			remaining_chars = ft_strdup(&line_const[i + 1]);
	}
	return (free(line_const), line_const = NULL, remaining_chars);
}

char	*get_next_line(int fd)
{
	static char	*line_const = NULL;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(line_const), line_const = NULL, NULL);
	if (line_const == NULL)
	{
		line_const = ft_calloc(1, sizeof(char));
		if (!line_const)
			return (NULL);
	}
	line_const = read_line(line_const, fd);
	if (!line_const)
		return (NULL);
	current_line = return_line(line_const);
	if (!current_line)
		return (free(line_const), line_const = NULL, NULL);
	line_const = remaining_line(line_const);
	return (current_line);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	size_t	i;
	size_t	len_s1cpy;

	if (!s1)
		return (NULL);
	len_s1cpy = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(len_s1cpy + 1);
	if (!ptr)
		return (NULL);
	if (ptr)
	{
		while (len_s1cpy > i)
		{
			ptr[i] = s1[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
