/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:26:53 by hshehab           #+#    #+#             */
/*   Updated: 2024/10/24 13:03:32 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	no_new_line(char **s, int *j)
{
	int	i;
	int	k;

	k = *j;
	while (s[k] && s[k][0] == '-')
	{
		i = 1;
		while (s[k][i] == 'n')
			i++;
		if (s[k][i] == '\0')
			k++;
		else
			break ;
	}
	if (k != *j)
	{
		*j = k;
		return (1);
	}
	*j = k;
	return (0);
}

void	print_echo_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && (str[i + 1] == '\\' || str[i
					+ 1] == '\'' || str[i + 1] == '\"'))
		{
			ft_printf("%c", str[i + 1]);
			i++;
		}
		else if (str[i] != '\0')
		{
			ft_printf("%c", str[i]);
		}
		i++;
	}
}

int	ft_echo(char **command)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (command[1] && no_new_line(command, &i))
		newline = 0;
	while (command[i])
	{
		print_echo_arg(command[i]);
		i++;
		if (command[i])
			ft_printf(" ");
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
