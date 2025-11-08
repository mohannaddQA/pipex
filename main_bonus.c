/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 22:38:09 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/08 14:42:28 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	process_cmd(char *bin_path, char **cmd_args, t_pipex *p_info,
		int cmd_idx)
{
	int	input_status;
	int	output_status;
	int	redirect_status;

	input_status = 0;
	output_status = 0;
	redirect_status = 0;
	if (cmd_idx == p_info->first_cmd_idx)
		input_status = setup_input_file(p_info);
	if (cmd_idx == p_info->first_cmd_idx + p_info->processes_count - 1)
		output_status = setup_output_file(p_info);
	else
		redirect_status = redirect_output(p_info);
	if (input_status == -1 || output_status == -1 || redirect_status == -1)
	{
		free(bin_path);
		ft_free_arr(cmd_args);
		throw_err(NULL, 1, *p_info);
	}
	execve(bin_path, cmd_args, p_info->envp);
	free(bin_path);
	ft_free_arr(cmd_args);
	throw_err(NULL, 0, *p_info);
}

void	init_process(char **argv, char **envp, t_pipex *p_info, int cmd_idx)
{
	char	*full_bin_path;
	char	**cmd_args;

	cmd_args = ft_split_enhanced(argv[cmd_idx]);
	if (!cmd_args)
		throw_err(NULL, 0, *p_info);
	full_bin_path = find_full_path(cmd_args[0], envp);
	if (!full_bin_path)
	{
		if (cmd_idx == p_info->first_cmd_idx + p_info->processes_count - 1
			&& setup_output_file(p_info) == -1)
		{
			throw_err(NULL, 0, *p_info);
		}
		ft_free_arr(cmd_args);
		throw_err("command not found", 127, *p_info);
	}
	process_cmd(full_bin_path, cmd_args, p_info, cmd_idx);
}

void	close_unneded_heredoc(int i, t_pipex *p_info)
{
	if (i != 0 && p_info->here_doc_enabled)
	{
		if (p_info->file_fds[0] != -1)
		{
			close(p_info->file_fds[0]);
			p_info->file_fds[0] = -1;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p_info;
	int		status;
	int		i;

	i = 0;
	status = 0;
	parse_input(argc, argv, &p_info, envp);
	while (i < p_info.processes_count)
	{
		close_unneded_heredoc(i, &p_info);
		if (pipe(p_info.pipe_fds) == -1)
			throw_err(NULL, 0, p_info);
		p_info.pd = fork();
		if (p_info.pd == -1)
			throw_err(NULL, 0, p_info);
		if (p_info.pd == 0)
			init_process(argv, envp, &p_info, i + p_info.first_cmd_idx);
		if (i++ == p_info.processes_count - 1)
			p_info.last_pid = p_info.pd;
		redirect_input(&p_info);
	}
	waitpid(p_info.last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (WEXITSTATUS(status));
}
