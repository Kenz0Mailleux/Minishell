/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:58:02 by nicolive          #+#    #+#             */
/*   Updated: 2024/09/30 17:39:01 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>  
# include <limits.h> 
# include <stddef.h> 
# include <stdlib.h> 
# include <unistd.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);
char	*ft_set_line(char *line_buffer);
char	*ft_fill_line_buffer(int fd, char *stash, char *buffer);

char	*ft_strchr_index(char *str);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);

int		ft_strlen(const char *str);

#endif
