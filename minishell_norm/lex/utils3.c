/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:37:21 by ldarsa            #+#    #+#             */
/*   Updated: 2024/09/16 16:08:19 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_string;

	temp_string = a->string;
	a->string = b->string;
	b->string = temp_string;
}

void	bubble_sort_list(t_env *head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->string, ptr1->next->string) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	printlinkedlist_export(head);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
