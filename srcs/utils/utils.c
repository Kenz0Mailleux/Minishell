/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:47:54 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/30 14:51:15 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while(str1[i] && str2[i] && str1[i] == str2[i])
			i++;
		if (str1[i] == 0)
			return (1);
	}
	return (0);
}
