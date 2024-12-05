/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:01:06 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/05 07:54:50 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_printf("%s\n", cwd), 0);
	else
		return (perror("pwd"), 1);
}

char	*get_pwd(void)
{
	char	cwd[1024];
	char	*pwd;

	pwd = getcwd(cwd, sizeof(cwd));
	if (pwd != NULL)
		return (pwd);
	return (NULL);
}
