/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:48:25 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/09 17:43:26 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_fds(t_pipex p_info, int close_read, int close_write)
{
	if (close_read && p_info.pipe_fds[READ] > 2)
	{
		close(p_info.pipe_fds[READ]);
	}
	if (close_write && p_info.pipe_fds[WRITE] > 2)
	{
		close(p_info.pipe_fds[WRITE]);
	}
	if (p_info.file_fds[READ] > 2)
	{
		close(p_info.file_fds[READ]);
	}
	if (p_info.file_fds[WRITE] > 2)
	{
		close(p_info.file_fds[WRITE]);
	}
}

void	display_err(char *err_msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putchar_fd('\n', 2);
}

void	*throw_err(char *custom_err, int custom_errno, t_pipex p_info)
{
	int	exit_code;

	if (custom_errno == 0)
		exit_code = errno;
	else
	{
		errno = custom_errno;
		exit_code = custom_errno;
	}
	if (custom_err)
		display_err(custom_err);
	else
		perror("pipex");
	ft_close_fds(p_info, 1, 1);
	exit(exit_code);
}
