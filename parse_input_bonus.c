/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:53:21 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/06 09:28:49 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	parse_heredoc(int argc, char **argv, t_pipex *p_info)
{
	p_info->here_doc_enabled = 1;
	p_info->processes_count = argc - 4;
	p_info->first_cmd_idx = 3;
	p_info->in_file = NULL;
	p_info->out_file = argv[argc - 1];
	p_info->limiter = argv[2];
	p_info->file_fds[0] = setup_heredoc_input_file(*p_info);
	return (p_info->file_fds[0]);
}

void	init_pipex_info(int argc, char **argv, t_pipex *p_info)
{
	if (ft_streq(argv[1], "here_doc") && argc > 5)
	{
		if (parse_heredoc(argc, argv, p_info) < 0)
			throw_err(NULL, 0, *p_info);
	}
	else
	{
		p_info->here_doc_enabled = 0;
		p_info->processes_count = argc - 3;
		p_info->first_cmd_idx = 2;
		p_info->in_file = argv[1];
		p_info->out_file = argv[argc - 1];
		p_info->limiter = NULL;
	}
	p_info->last_cmd_idx = argc - 2;
}

void	parse_input(int argc, char **argv, t_pipex *p_info)
{
	p_info->pipe_fds[READ] = -1;
	p_info->pipe_fds[WRITE] = -1;
	p_info->file_fds[STDOUT_FILENO] = -1;
	p_info->file_fds[STDIN_FILENO] = -1;
	p_info->pd = -1;
	p_info->last_pid = -1;
	if (argc > 4)
		init_pipex_info(argc, argv, p_info);
	if (argc - 1 <= 4 && argv[1] && ft_streq(argv[1], "here_doc"))
		throw_err("there must be at least 5 arguments", 1, *p_info);
	else if ((argc - 1 <= 3))
		throw_err("there must be at least 4 arguments", 1, *p_info);
}
