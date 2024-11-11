/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:32:10 by ldarsa            #+#    #+#             */
/*   Updated: 2024/08/30 22:32:38 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freelinkedlist_ev(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	while (head)
	{
		head = head->next;
		if (ptr->next != NULL)
		{
			ptr->next = NULL;
		}
		free(ptr->string);
		free(ptr);
		ptr = head;
	}
}

t_env	*createnode_env(char *str)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
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
	newnode->next = NULL;
	newnode->flag = 1;
	return (newnode);
}

void	freelinkedlist_tok(t_node *head)
{
	t_node	*ptr;

	ptr = head;
	while (head)
	{
		head = head->next;
		if (ptr->previous != NULL)
		{
			ptr->previous = NULL;
		}
		if (ptr->next != NULL)
		{
			ptr->next = NULL;
		}
		free(ptr->string);
		if (ptr != NULL)
			free(ptr);
		ptr = head;
	}
}

t_env	*pushtoback_env(t_env *head, char *str)
{
	t_env	*ptr;
	t_env	*newnode;

	if (head == NULL)
	{
		head = createnode_env(str);
		return (head);
	}
	else
	{
		ptr = head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		newnode = createnode_env(str);
		ptr->next = newnode;
		return (head);
	}
}

t_env	*duplicate_env_list(t_minishell *mini)
{
	t_env	*ptr;
	t_env	*newhead;

	newhead = NULL;
	ptr = mini->env;
	while (ptr)
	{
		newhead = pushtoback_env(newhead, ptr->string);
		ptr = ptr->next;
	}
	return (newhead);
}
