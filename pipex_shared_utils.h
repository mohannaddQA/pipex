/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_shared_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:52:02 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/03 22:03:58 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_SHARED_UTILS_H
# define PIPEX_SHARED_UTILS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ 0
# define WRITE 1

char	*find_full_path(char *path, char **envp);
/*---String methods---*/
size_t	ft_strlen(const char *str);
int		ft_streq(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_strlcat(char *dst, char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	**ft_split_enhanced(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
/*---Memory related*/
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_free(char **arr, int count);
void	*ft_free_arr(char **arr);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
/*---Printing---*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif