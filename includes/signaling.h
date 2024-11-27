/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:45:54 by nicolive          #+#    #+#             */
/*   Updated: 2024/09/28 16:34:01 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALING_H
# define SIGNALING_H
# include "minishell.h"

# include <unistd.h>
# include "termios.h"
# include "signal.h"

void	check_for_signals(int process);
#endif