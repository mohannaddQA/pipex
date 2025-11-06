/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:56:39 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/06 09:28:10 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_path_access(char **bin_paths, char *path)
{
	char	*full_path;
	int		i;

	i = 0;
	while (bin_paths[i])
	{
		full_path = ft_strjoin(bin_paths[i++], path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

char	*search_env_bin_paths(char **envp, char *path)
{
	int		i;
	char	**env_bin_paths;
	char	*path_str;
	char	*full_path;

	i = -1;
	path_str = NULL;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path_str = envp[i];
			break ;
		}
	}
	if (!path_str)
		return (NULL);
	env_bin_paths = ft_split(&path_str[5], ':');
	full_path = check_path_access(env_bin_paths, path);
	ft_free_arr(env_bin_paths);
	return (full_path);
}

char	*search_hardcoded_bin_paths(char *path)
{
	char	*bin_paths[7];
	char	*full_path;

	bin_paths[6] = NULL;
	bin_paths[5] = "/usr/local/sbin";
	bin_paths[4] = "/usr/local/bin";
	bin_paths[3] = "/usr/sbin";
	bin_paths[2] = "/usr/bin";
	bin_paths[1] = "/sbin";
	bin_paths[0] = "/bin";
	full_path = check_path_access(bin_paths, path);
	return (full_path);
}

char	*search_bin_paths(char *path, char **envp)
{
	char	*full_path;

	full_path = NULL;
	if (envp)
		full_path = search_env_bin_paths(envp, path);
	else
		full_path = search_hardcoded_bin_paths(path);
	return (full_path);
}

char	*find_full_path(char *cmd, char **envp)
{
	char	*prepared_path;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	prepared_path = ft_strjoin("/", cmd);
	if (!prepared_path)
		return (NULL);
	full_path = search_bin_paths(prepared_path, envp);
	free(prepared_path);
	return (full_path);
}
