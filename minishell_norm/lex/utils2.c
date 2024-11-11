/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:33:30 by ldarsa            #+#    #+#             */
/*   Updated: 2024/09/21 11:35:40 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*createnode(char *str, t_type type)
{
	t_node	*newnode;

	newnode = malloc(sizeof(t_node));
	if (newnode == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	newnode->string = ft_strdup(str);
	if (newnode->string == NULL)
	{
		perror("Failed to allocate memory for data");
		exit(EXIT_FAILURE);
	}
	newnode->type = type;
	newnode->next = NULL;
	newnode->previous = NULL;
	return (newnode);
}

t_node	*pushtoback(t_node *head, char *str, t_type type)
{
	t_node	*ptr;
	t_node	*newnode;

	if (head == NULL)
	{
		return (createnode(str, type));
	}
	else
	{
		ptr = head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		newnode = createnode(str, type);
		newnode->previous = ptr;
		ptr->next = newnode;
		return (head);
	}
}

void	init_env(t_minishell *mini, char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
	{
		return ;
	}
	else
	{
		while (env[i] != NULL)
		{
			mini->env = pushtoback_env(mini->env, env[i]);
			i++;
		}
	}
	pushtoback_env(mini->env, "?=0");
	pushtoback_env(mini->env, "status=0");
}

void	free_mini(t_minishell *mini)
{
	freelinkedlist_ev(mini->env);
	free_tree(mini->tree);
	free(mini);
}

void	resetfd(t_minishell *mini)
{
	dup2(mini->infd, STDIN);
	dup2(mini->outfd, STDOUT);
}
