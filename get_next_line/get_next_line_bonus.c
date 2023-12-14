/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:06:06 by ashirzad          #+#    #+#             */
/*   Updated: 2023/11/23 18:21:55 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_static_buffer(char **list)
{
	if ((*list) != NULL)
	{
		free(*list);
		*list = NULL;
	}
}

static char	*polish_list(char **list)
{
	char	*buffer;
	int		i;

	i = 0;
	if (list == NULL)
		return (NULL);
	while ((*list)[i] && (*list)[i] != '\n')
		i++;
	if ((*list)[i] == '\0' || (*list)[i + 1] == '\0')
		return (NULL);
	i += 1;
	buffer = ft_strdup((*list) + i);
	if (buffer == NULL)
	{
		free_static_buffer(list);
		return (NULL);
	}
	return (buffer);
}

static char	*polish_line(char **list)
{
	char	*temp;
	char	*str;
	int		i;

	i = 0;
	if (!(*list) || !(*list)[0])
		return (NULL);
	while ((*list)[i] && (*list)[i] != '\n')
		i++;
	str = (char *)malloc((i + 1) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while ((*list)[++i] && ((*list)[i] != '\n' && (*list)[i + 1] != '\0'))
		str[i] = (*list)[i];
	if ((*list)[i] == '\n' || (*list)[i + 1] == '\0')
	{
		str[i] = (*list)[i];
		str[i + 1] = '\0';
		temp = polish_list(list);
		free_static_buffer(list);
		*list = temp;
		return (str);
	}
	return (NULL);
}

static void	create_line(char **list, int fd)
{
	char		*buffer;
	int			chars_read;
	char		*temp;

	chars_read = 1;
	while (*list == NULL || !ft_strchr(*list, '\n'))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[chars_read] = '\0';
		temp = *list;
		*list = ft_strjoin(*list, buffer);
		free(temp);
		free(buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*lists[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free_static_buffer(&lists[fd]);
		return (NULL);
	}
	create_line(&lists[fd], fd);
	if (lists[fd] == NULL)
		return (NULL);
	line = polish_line(&lists[fd]);
	return (line);
}
