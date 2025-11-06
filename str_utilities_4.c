/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utilities_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:42:21 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/01 20:50:46 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	char	*joined_str_cpy;

	if (!s1 || !s2)
		return (NULL);
	joined_str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!joined_str)
		return (NULL);
	joined_str_cpy = joined_str;
	while (*s1)
		*joined_str++ = *s1++;
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	return (joined_str_cpy);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	char	*s_copy;

	s_copy = s;
	while (n--)
		*s_copy++ = c;
	return (s);
}

static void	fill_ascii_array(int *arr, char const *set)
{
	ft_memset(arr, '\0', 128 * sizeof(int));
	while (*set)
	{
		if (!arr[(int)*set])
			arr[(int)*set] = 1;
		set++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		ascii[128];
	int		len;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	fill_ascii_array(ascii, set);
	while (ascii[(int)*s1])
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	while (ascii[(int)s1[len - 1]])
		len--;
	trimmed_str = malloc(sizeof(char) * (len + 1));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1, len + 1);
	return (trimmed_str);
}
