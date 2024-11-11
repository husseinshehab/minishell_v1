/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:03:37 by hshehab           #+#    #+#             */
/*   Updated: 2024/10/24 13:01:08 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_question_mark(t_minishell *mini)
{
	t_env	*ptr;
	char	*joined;
	char	*num;

	ptr = mini->env;
	while (ptr)
	{
		if (!strncmp("?=", ptr->string, 2))
		{
			free(ptr->string);
			num = ft_itoa(mini->exit_code);
			joined = ft_strjoin("?=", num);
			free(num);
			ptr->string = ft_strdup(joined);
			free(joined);
		}
		ptr = ptr->next;
	}
}

int	is_all_digits(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		return (0);
	}
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

void	ft_etoi_helper(long long number, long long number2, int *flag1,
		int flag)
{
	if (number <= number2 && number >= -number2 - 1)
		*flag1 = (number * flag) % 256;
	else
		(*flag1) = 2;
}

void	ft_etoi(const char *nptr, int *flag1)
{
	int			i;
	int			flag;
	long long	number2;
	long long	number;

	i = 0;
	flag = 1;
	number = 0;
	number2 = 9223372036854775807;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			flag = -1;
		i++;
	}
	while ((nptr[i] >= 48 && nptr[i] <= 57))
	{
		number = number * 10 + (nptr[i] - 48);
		i++;
	}
	ft_etoi_helper(number, number2, flag1, flag);
}

void	ft_exit(t_minishell *mini)
{
	if (mini->tree->value[1] == NULL)
	{
		ft_printf("exit\n");
		exit(mini->exit_code);
	}
	else if (mini->tree->value[1] && mini->tree->value[2])
	{
		exit(1);
		return ;
	}
	else if (mini->tree->value[1] && is_all_digits(mini->tree->value[1]))
	{
		ft_etoi(mini->tree->value[1], &(mini->exit_code));
		exit(mini->exit_code);
	}
	mini->exit_code = 2;
	exit(2);
}
