/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:49:10 by ashirzad          #+#    #+#             */
/*   Updated: 2023/11/28 23:02:15 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = (char *)malloc(ft_strlen(s1)+1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (s1[count] != '\0')
	{
		ptr[count] = s1[count];
		count++;
	}
	ptr[count] = '\0';
	return (ptr);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	char	*ptr;

	ptr = dest;
	while (n > 0 && *src)
	{
		*dest++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (s1 != NULL)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	ptr = (char *)malloc(len1 + len2 + 1);
	if (ptr == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strncpy(ptr, s1, len1);
	if (s2 != NULL)
		ft_strncpy(ptr + len1, s2, len2);
	ptr[len1 + len2] = '\0';
	return (ptr);
}
