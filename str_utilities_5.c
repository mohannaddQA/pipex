/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utilities_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:19:07 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/08 14:36:30 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	max_args_num(char *s)
{
	int		count;
	int		i;
	int		in_arg;
	char	quote;

	count = 0;
	i = -1;
	in_arg = 0;
	while (s[++i])
	{
		if (ft_is_space(s[i]))
			in_arg = 0;
		else if (!in_arg && ++count)
			in_arg = 1;
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
		}
	}
	return (count + 1);
}

char	*handle_quoted_part(char *s, int *pos, char q)
{
	int		len;
	char	*quoted_arg;
	int		i;

	s++;
	len = 0;
	while (s[len] && s[len] != q)
		len++;
	quoted_arg = ft_calloc(len + 1, sizeof(char));
	if (!quoted_arg)
		return (NULL);
	i = 0;
	while (i < len)
	{
		quoted_arg[i] = s[i];
		i++;
	}
	quoted_arg[i] = '\0';
	*pos += len + 2;
	return (quoted_arg);
}

char	*handle_unquoted_part(char *s, int *pos)
{
	int		len;
	char	*unquoted_arg;
	int		i;

	i = 0;
	len = 0;
	while (s[len] && !ft_is_space(s[len]) && s[len] != '\'' && s[len] != '\"')
		len++;
	unquoted_arg = ft_calloc(len + 1, sizeof(char));
	if (!unquoted_arg)
		return (NULL);
	while (i < len)
	{
		unquoted_arg[i] = s[i];
		i++;
	}
	unquoted_arg[i] = '\0';
	*pos += len;
	return (unquoted_arg);
}

char	**ft_split_enhanced(char *s)
{
	char	**arr;
	int		i;
	int		count;

	count = 0;
	i = 0;
	arr = ft_calloc(max_args_num(s), sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		{
			i++;
			continue ;
		}
		else if (s[i] == '\"' || s[i] == '\'')
			arr[count] = handle_quoted_part(&s[i], &i, s[i]);
		else
			arr[count] = handle_unquoted_part(&s[i], &i);
		if (!arr[count++])
			return (ft_free(arr, count - 1));
	}
	arr[count] = NULL;
	return (arr);
}
