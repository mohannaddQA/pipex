/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_io_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:14:34 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/07 15:31:51 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_output(t_pipex p_info)
{
	close(p_info.pipe_fds[READ]);
	if (dup2(p_info.pipe_fds[WRITE], STDOUT_FILENO) == -1)
		return (-1);
	close(p_info.pipe_fds[WRITE]);
	return (0);
}

int	redirect_input(t_pipex p_info)
{
	close(p_info.pipe_fds[WRITE]);
	if (dup2(p_info.pipe_fds[READ], STDIN_FILENO) == -1)
		return (-1);
	close(p_info.pipe_fds[READ]);
	return (0);
}

int	setup_input_file(t_pipex p_info)
{
	p_info.file_fds[0] = open(p_info.in_file, O_RDONLY);
	if (p_info.file_fds[0] == -1)
		return (-1);
	if (dup2(p_info.file_fds[0], STDIN_FILENO) == -1)
		return (-1);
	close(p_info.file_fds[0]);
	p_info.file_fds[0] = -1;
	return (0);
}

int	setup_output_file(t_pipex p_info)
{
	close(p_info.pipe_fds[READ]);
	close(p_info.pipe_fds[WRITE]);
	p_info.file_fds[1] = open(p_info.out_file, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (p_info.file_fds[1] == -1)
		return (-1);
	if (dup2(p_info.file_fds[1], STDOUT_FILENO) == -1)
		return (-1);
	close(p_info.file_fds[1]);
	p_info.file_fds[1] = -1;
	return (0);
}
