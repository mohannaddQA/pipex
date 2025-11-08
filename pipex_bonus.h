/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:14:46 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/08 13:58:34 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line_bonus.h"
# include "pipex_shared_utils.h"

typedef struct s_pipex
{
	int		here_doc_enabled;
	int		processes_count;
	int		pipe_fds[2];
	int		file_fds[2];
	int		heredoc_fd;
	int		first_cmd_idx;
	int		last_cmd_idx;
	char	*in_file;
	char	*out_file;
	char	*limiter;
	char	**envp;
	pid_t	pd;
	pid_t	last_pid;
}			t_pipex;

/*Here_doc setup*/
int			setup_heredoc_input_file(t_pipex p_info);
/*Get Next Line*/
char		*get_next_line(int fd);
/*---Setup I/O---*/
int			setup_output_file(t_pipex *p_info);
int			setup_input_file(t_pipex *p_info);
int			redirect_output(t_pipex *p_info);
int			redirect_input(t_pipex *p_info);
void		parse_input(int argc, char **argv, t_pipex *p_info, char **envp);
/*---Error handlers---*/
void		*throw_err(char *custom_err, int custom_errno, t_pipex p_info);
void		ft_close_fds(t_pipex p_info, int close_read, int close_write);
#endif