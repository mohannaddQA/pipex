/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare  <mabuqare@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:19:30 by mabuqare          #+#    #+#             */
/*   Updated: 2025/11/02 20:53:02 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		check_new_line(char *buffer);
int		ft_strlen_gnl(const char *str);
void	*ft_strjoin_gnl(char *s1, char *s2);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
void	*free_buffers(char **buffer_1, char **buffer_2, char **buffer_3);

# if !defined(BUFFER_SIZE)
#  define BUFFER_SIZE 10
# endif
#endif
