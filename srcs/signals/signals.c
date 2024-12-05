/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:45:32 by nicolive          #+#    #+#             */
/*   Updated: 2024/12/05 05:13:15 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	prompt(int sig)
{
	g_exit_value = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	reset_ctrl_c(int sig)
{
	g_exit_value = 130;
	(void)sig;
}

void	reset_ctrl_slash(int sig)
{
	g_exit_value = 131;
	write(2, "Quit: 3\n", 8);
	(void)sig;
}

void	check_for_signals(int process)
{
	struct termios	term;

	if (process == 0)
	{
		signal(SIGINT, prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (process == 1)
	{
		signal(SIGINT, reset_ctrl_c);
		signal(SIGQUIT, reset_ctrl_slash);
	}
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
