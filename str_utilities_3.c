/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utilities_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 22:52:07 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/07 15:21:11 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char *s, char c);
static char	**fill_arr(char *s, char del, char **arr);
static char	*fill_word(char *s, char del, int *pos);

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**arr;

	if (!s)
		return (NULL);
	len = count_words((char *)s, c);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = NULL;
	arr = fill_arr((char *)s, c, arr);
	return (arr);
}

static int	count_words(char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	**fill_arr(char *s, char del, char **arr)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] == del)
		{
			i++;
			continue ;
		}
		arr[word_count++] = fill_word(&s[i], del, &i);
		if (!arr[word_count - 1])
			return (ft_free(arr, word_count - 1));
	}
	return (arr);
}

static char	*fill_word(char *s, char del, int *pos)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = 0;
	while (s[len] && s[len] != del)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (len--)
	{
		word[i++] = *s++;
		*pos += 1;
	}
	word[i] = '\0';
	return (word);
}

void	*ft_free(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
