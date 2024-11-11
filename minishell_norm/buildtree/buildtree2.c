/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtree2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:22:55 by hshehab           #+#    #+#             */
/*   Updated: 2024/09/16 15:47:59 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_type_greater_2(t_node **ptr, t_node **newlist)
{
	while (*ptr)
	{
		if ((*ptr)->type > 1)
		{
			*newlist = pushtoback(*newlist, (*ptr)->string, (*ptr)->type);
			*ptr = (*ptr)->next;
			if (*ptr)
			{
				*newlist = pushtoback(*newlist, (*ptr)->string, (*ptr)->type);
				*ptr = (*ptr)->next;
			}
		}
		else
		{
			*ptr = (*ptr)->next;
		}
	}
}

void	clean_and_update_head(t_node **head, t_node *newlist)
{
	freelinkedlist_tok(*head);
	*head = newlist;
}


void	rearrange(t_node **head)
{
	t_node	*newlist;
	t_node	*ptr;

	if (thereispipe(*head))
		return ;
	newlist = NULL;
	ptr = *head;
	process_type_less_equal_2(&ptr, &newlist);
	ptr = *head;
	process_type_greater_2(&ptr, &newlist);
	clean_and_update_head(head, newlist);
}

int	listlength(t_node *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**joinlist(t_node *head)
{
	char	**matrix;
	int		i;
	int		length;

	i = 0;
	length = listlength(head);
	matrix = malloc(sizeof(char *) * (length + 1));
	matrix[length] = NULL;
	while (head)
	{
		matrix[i] = ft_strdup(head->string);
		i++;
		head = head->next;
	}
	return (matrix);
}
