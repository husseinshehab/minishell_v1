/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:52:55 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 13:04:52 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_pwd(t_env *myenv)
{
	char	*p;

	while (myenv->string)
	{
		if (!ft_strncmp("PWD=", myenv->string, 4))
		{
			p = myenv->string + 4;
			ft_printf("%s\n", p);
			break ;
		}
		myenv = myenv->next;
	}
}

int	ft_pwd(t_env *env)
{
	char	*dir;
	char	buf[4096];

	dir = getcwd(buf, sizeof(buf));
	if (!dir || dir[0] == '\0')
	{
		get_pwd(env);
	}
	else
		ft_printf("%s\n", dir);
	return (0);
}
