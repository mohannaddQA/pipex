/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:43:28 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/02 20:44:09 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*create_new_main(char *main_buff, char **remaining_buff, int len)
{
	char	*new_main;

	new_main = ft_calloc_gnl(len + 1, 1);
	if (!new_main)
		return (free_buffers(&main_buff, remaining_buff, NULL));
	len = 0;
	while ((main_buff)[len] != '\n')
	{
		new_main[len] = (main_buff)[len];
		len++;
	}
	new_main[len++] = '\n';
	new_main[len] = '\0';
	free_buffers(&main_buff, NULL, NULL);
	return (new_main);
}

void	*split_by_new_line(char *main_buffer, char **remaining_buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (main_buffer[i] && main_buffer[i] != '\n')
		i++;
	if (main_buffer[i] == '\n' && main_buffer[i + 1])
	{
		i++;
		*remaining_buff = ft_calloc_gnl(ft_strlen_gnl(&(main_buffer)[i]) + 1,
				1);
		if (*remaining_buff == NULL)
			return (free_buffers(&main_buffer, NULL, NULL));
		while (main_buffer[i + j])
		{
			(*remaining_buff)[j] = main_buffer[i + j];
			j++;
		}
		main_buffer = create_new_main(main_buffer, remaining_buff, i);
		if (!main_buffer)
			return (NULL);
		(*remaining_buff)[j] = '\0';
	}
	return (main_buffer);
}

char	*read_by_line(int fd, char *main_buff, char **remaining_buff)
{
	char	*temp_buff;
	int		read_state;

	temp_buff = (char *)ft_calloc_gnl(BUFFER_SIZE + 1, 1);
	if (!temp_buff)
		return (free_buffers(&main_buff, NULL, NULL));
	read_state = read(fd, temp_buff, BUFFER_SIZE);
	if (read_state > 0)
	{
		main_buff = ft_strjoin_gnl(main_buff, temp_buff);
		if (!main_buff)
			return (NULL);
		if (check_new_line(main_buff))
		{
			main_buff = split_by_new_line(main_buff, remaining_buff);
			return (main_buff);
		}
		return (read_by_line(fd, main_buff, remaining_buff));
	}
	else if (read_state == 0 && *main_buff && check_new_line(main_buff))
		main_buff = split_by_new_line(main_buff, remaining_buff);
	else if (read_state < 0 || !*main_buff)
		return (free_buffers(&main_buff, &temp_buff, NULL));
	free_buffers(&temp_buff, NULL, NULL);
	return (main_buff);
}

void	*prepare_main_buffer(char **main_buff, char **remaining_buff)
{
	*main_buff = ft_calloc_gnl(1, 1);
	if (!*main_buff)
		return (free_buffers(remaining_buff, NULL, NULL));
	if (*remaining_buff)
		*main_buff = ft_strjoin_gnl(*main_buff, *remaining_buff);
	*remaining_buff = NULL;
	return (*main_buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*main_buff;
	static char	*remaining_buff;

	main_buff = prepare_main_buffer(&main_buff, &remaining_buff);
	if (!main_buff)
		return (NULL);
	line = read_by_line(fd, main_buff, &remaining_buff);
	return (line);
}
