/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:01:06 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/09 17:09:19 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"

int ft_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (printf("%s\n", cwd), 0);
	else
		return (perror("pwd"), 1);
}
