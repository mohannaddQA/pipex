/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:53:21 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/06 12:42:37 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex_info(int argc, char **argv, t_pipex *p_info)
{
	p_info->processes_count = argc - 3;
	p_info->first_cmd_idx = 2;
	p_info->in_file = argv[1];
	p_info->out_file = argv[argc - 1];
	p_info->last_cmd_idx = argc - 2;
}

void	parse_input(int argc, char **argv, t_pipex *p_info, char **envp)
{
	p_info->pipe_fds[READ] = -1;
	p_info->pipe_fds[WRITE] = -1;
	p_info->file_fds[STDOUT_FILENO] = -1;
	p_info->file_fds[STDIN_FILENO] = -1;
	p_info->pd = -1;
	p_info->last_pid = -1;
	p_info->envp = envp;
	if (argc - 1 != 4)
		throw_err("there must be exactly 4 arguments", 1, *p_info);
	init_pipex_info(argc, argv, p_info);
}
