/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:31:15 by hshehab           #+#    #+#             */
/*   Updated: 2024/09/11 18:59:29 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_treenode	*create_treenode(t_type type)
{
	t_treenode	*new;

	new = (t_treenode *)malloc(sizeof(t_treenode));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->value = NULL;
	new->file_type = UNSET;
	new->type = type;
	new->pipefd[0] = -1;
	new->pipefd[1] = -1;
	return (new);
}

void	split_token_list(t_node *head, t_node **left, t_node **right,
		t_node *min)
{
	t_node	*ptr;

	*left = head;
	*right = min->next;
	ptr = *left;
	if (ptr == min)
	{
		*left = NULL;
		return ;
	}
	while (ptr->next != min)
	{
		ptr = ptr->next;
	}
	ptr->next = NULL;
}

int	thereispipe(t_node *head)
{
	while (head)
	{
		if (head->type == PIPE)
			return (1);
		head = head->next;
	}
	return (0);
}

int	thereisred(t_node *head)
{
	while (head)
	{
		if (head->type == REDIRECTION_APPEND
			|| head->type == REDIRECTION_HEREDOC || head->type == REDIRECTION_IN
			|| head->type == REDIRECTION_OUT)
			return (1);
		head = head->next;
	}
	return (0);
}

void	process_type_less_equal_2(t_node **ptr, t_node **newlist)
{
	while (*ptr)
	{
		if ((*ptr)->type <= 1)
		{
			*newlist = pushtoback(*newlist, (*ptr)->string, (*ptr)->type);
			*ptr = (*ptr)->next;
		}
		else if ((*ptr)->type > 1 && (*ptr)->next)
		{
			*ptr = (*ptr)->next->next;
		}
		else
		{
			break ;
		}
	}
}
