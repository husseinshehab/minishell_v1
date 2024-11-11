/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:58:49 by hshehab           #+#    #+#             */
/*   Updated: 2024/11/05 11:39:22 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		g_signal_num = 0;

char	*colorize(const char *text, const char *color)
{
	size_t	text_len;
	size_t	color_len;
	size_t	reset_len;
	char	*colored_text;

	text_len = strlen(text);
	color_len = strlen(color);
	reset_len = strlen(COLOR_RESET);
	colored_text = malloc(color_len + text_len + reset_len + 1);
	if (!colored_text)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(colored_text, color);
	strcpy(colored_text + color_len, text);
	strcpy(colored_text + color_len + text_len, COLOR_RESET);
	return (colored_text);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") || !ft_strcmp(str,
			"env") || !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit") || !ft_strcmp(str, "pwd"))
	{
		return (1);
	}
	return (0);
}

int	execute_builtin(char **str, t_minishell *mini)
{
	if (!ft_strcmp(str[0], "echo"))
		return (ft_echo(str));
	else if (!ft_strcmp(str[0], "cd"))
		return (ft_cd(str, mini));
	else if (!ft_strcmp(str[0], "export"))
		return (ft_export(str, mini));
	else if (!ft_strcmp(str[0], "env"))
		return (ft_env(mini));
	else if (!ft_strcmp(str[0], "unset"))
		return (ft_unset(mini));
	else if (!ft_strcmp(str[0], "pwd"))
	{
		return (ft_pwd(mini->env));
	}
	else if (!ft_strcmp(str[0], "exit"))
	{
		return (ft_exit(mini), 42);
	}
	return (0);
}

int	check_input(t_node *head)
{
	t_node	*ptr;

	ptr = head;
	if (ptr->type == PIPE)
	{
		return (0);
	}
	while (ptr)
	{
		if (ptr->type != WORD && ptr->next && ptr->next->type != WORD)
		{
			if ((ptr->type == PIPE) && ptr->next
				&& (ptr->next->type == REDIRECTION_IN
					|| ptr->next->type == REDIRECTION_OUT
					|| ptr->next->type == REDIRECTION_HEREDOC))
			{
				ptr = ptr->next;
				continue ;
			}
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}
