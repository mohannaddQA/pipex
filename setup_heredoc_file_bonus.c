/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc_file_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:07:17 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/02 20:43:28 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_limiter_line(char *line, char *limiter)
{
	size_t	lim_len;
	size_t	line_len;

	lim_len = ft_strlen(limiter);
	line_len = ft_strlen(line);
	if (line_len != lim_len + 1 && line_len != lim_len)
		return (0);
	if (ft_strncmp(line, limiter, lim_len) != 0)
		return (0);
	if (line_len == lim_len + 1 && line[lim_len] != '\n')
		return (0);
	return (1);
}

int	write_heredoc_to_file(t_pipex p_info, int fd)
{
	int		found_limiter;
	char	*line;

	write(1, "pipex heredoc> ", 16);
	line = get_next_line(0);
	while (line)
	{
		found_limiter = is_limiter_line(line, p_info.limiter);
		if (!found_limiter)
			write(fd, line, ft_strlen(line));
		else if (found_limiter)
		{
			free(line);
			return (found_limiter);
		}
		free(line);
		write(1, "pipex heredoc> ", 16);
		line = get_next_line(0);
	}
	return (0);
}

int	setup_heredoc_input_file(t_pipex p_info)
{
	int	fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	write_heredoc_to_file(p_info, fd);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		unlink(".heredoc_tmp");
		return (-1);
	}
	unlink(".heredoc_tmp");
	return (fd);
}
