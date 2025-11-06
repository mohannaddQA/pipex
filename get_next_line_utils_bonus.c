/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:21:48 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/02 20:44:17 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*free_buffers(char **buffer_1, char **buffer_2, char **buffer_3)
{
	if (buffer_1 && *buffer_1)
	{
		free(*buffer_1);
		*buffer_1 = NULL;
	}
	if (buffer_2 && *buffer_2)
	{
		free(*buffer_2);
		*buffer_2 = NULL;
	}
	if (buffer_3 && *buffer_3)
	{
		free(*buffer_3);
		*buffer_3 = NULL;
	}
	return (NULL);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void	*mem;
	char	*mem_copy;
	size_t	total_bytes;

	total_bytes = size * nmemb;
	mem = (void *)malloc(total_bytes);
	if (!mem)
		return (NULL);
	mem_copy = mem;
	while (total_bytes--)
		*mem_copy++ = 0;
	return (mem);
}

int	ft_strlen_gnl(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	check_new_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i++] == '\n')
			return (1);
	}
	return (0);
}

void	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*joined_str;

	i = 0;
	j = 0;
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	joined_str = (char *)ft_calloc_gnl((len + 1), 1);
	if (!joined_str)
		return (free_buffers(&s1, &s2, NULL));
	while ((s1)[i])
	{
		joined_str[i] = (s1)[i];
		i++;
	}
	while (s2[j])
	{
		joined_str[i + j] = s2[j];
		j++;
	}
	free_buffers(&s1, &s2, NULL);
	joined_str[i + j] = '\0';
	return (joined_str);
}
