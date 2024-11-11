/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:31:33 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 13:05:59 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	*init_minishell(void)
{
	t_minishell	*mini;

	mini = malloc(sizeof(t_minishell));
	mini->env = NULL;
	mini->head = NULL;
	mini->tree = NULL;
	mini->exit_code = 0;
	return (mini);
}

void	printlinkedlist_tok(t_node *head)
{
	int	i;

	i = 1;
	if (head == NULL)
	{
		printf("the node is empty");
		return ;
	}
	else
	{
		while (head)
		{
			printf("token node %d: type(%d) string[%s]\n", i, head->type,
				head->string);
			head = head->next;
			i++;
		}
	}
}

void	printlinkedlist_env(t_env *head)
{
	if (head == NULL)
	{
		printf("the env node is empty");
		return ;
	}
	else
	{
		while (head)
		{
			if (ft_strncmp(head->string, "?=", 2) || ft_strncmp(head->string,
					"status=", 7))
			{
				head = head->next;
				continue ;
			}
			printf("%s\n", head->string);
			head = head->next;
		}
	}
}

void	print_export_string(const char *s)
{
	int	i;
	int	found_equal;

	if (s == NULL)
	{
		return ;
	}
	i = 0;
	found_equal = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=' && !found_equal)
		{
			printf("%c\"", s[i]);
			found_equal = 1;
		}
		else
			printf("%c", s[i]);
		i++;
	}
	if (found_equal)
		printf("\"\n");
	else
		printf("\n");
}

void	printlinkedlist_export(t_env *head)
{
	int	i;

	i = 1;
	if (head == NULL)
	{
		printf("the env node is empty");
		return ;
	}
	else
	{
		while (head)
		{
			if (!ft_strncmp(head->string, "?=", 2) || !ft_strncmp(head->string,
					"status=", 7))
			{
				head = head->next;
				continue ;
			}
			printf("declare -x ");
			print_export_string(head->string);
			head = head->next;
			i++;
		}
	}
}
