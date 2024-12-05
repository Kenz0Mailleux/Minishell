/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:00:40 by nicolive          #+#    #+#             */
/*   Updated: 2024/12/05 08:16:26 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*env_i_add(t_data *data, t_env *head, char *pwd)
{
	t_env	*new_env;

	new_env = create_env(data, "PWD", pwd, 1);
	if (!new_env)
		return (free_all(data, EXIT_FAILURE), head);
	append_env(&head, new_env);
	new_env = create_env(data, "SHLVL", "0", 1);
	if (!new_env)
		return (free_all(data, EXIT_FAILURE), head);
	append_env(&head, new_env);
	new_env = create_env(data, "_", ft_strjoin(pwd, "/./minishell"), 1);
	if (!new_env)
		return (free_all(data, EXIT_FAILURE), head);
	append_env(&head, new_env);
	new_env = create_env(data, "OLDPWD", pwd, 0);
	if (!new_env)
		return (free_all(data, EXIT_FAILURE), head);
	append_env(&head, new_env);
	new_env = create_env(data, "PATH", PATH, 2);
	if (!new_env)
		return (free_all(data, EXIT_FAILURE), head);
	append_env(&head, new_env);
	return (head);
}

t_env	*env_i(t_data *data)
{
	t_env	*head;
	char	*pwd;

	head = NULL;
	pwd = get_pwd();
	if (!pwd)
		return (free_all(data, EXIT_FAILURE), head);
	head = env_i_add(data,head,pwd);
	return (head);
}
