/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:38:12 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/27 14:24:17 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		from_char(int c);
int		from_str(char *str);
int		from_ptr(unsigned long long nbr);
int		from_int(int nbr);
int		from_uint(unsigned int nbr);
int		from_x_x(unsigned int nbr, char format);
char	*to_hexa(unsigned long long nbr, char *base);
int		hex_len(unsigned long long nbr);

// utils
int		ft_putstr(char *str);
int		ft_putchar(char str);
void	reverse_string(char *str);

#endif