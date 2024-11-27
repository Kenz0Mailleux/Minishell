/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:58:02 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/27 14:39:26 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000000
#endif

char 	*get_next_line(int fd);
char 	*ft_set_line(char *line_buffer);
char 	*ft_fill_line_buffer(int fd, char *stash, char *buffer);
char	*ft_strchr_index(char *str);
int		ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *src);
char	*ft_substr_gnl(char *s, int start, int len);

#endif
