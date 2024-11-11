/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:03:37 by hshehab           #+#    #+#             */
/*   Updated: 2024/10/24 12:52:00 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_minishell *mini)
{
	t_env	*ptr;

	ptr = mini->env;
	while (ptr)
	{
		if (ft_strchr(ptr->string, '='))
		{
			if (!ft_strncmp(ptr->string, "?=", 2) || !ft_strncmp(ptr->string,
					"status=", 7))
			{
				ptr = ptr->next;
				continue ;
			}
			ft_printf("%s\n", ptr->string);
		}
		ptr = ptr->next;
	}
	return (0);
}
