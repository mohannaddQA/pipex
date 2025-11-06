/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:44:13 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/02 22:24:12 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t nmemb, size_t size)
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

void	*ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_copy;

	if ((!src && !dest) || !n)
		return (dest);
	dest_copy = dest;
	while (n-- > 0)
		*((char *)dest_copy++) = *((char *)src++);
	return (dest);
}
