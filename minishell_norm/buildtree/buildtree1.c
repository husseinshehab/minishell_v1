/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtree1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 23:29:29 by ldarsa            #+#    #+#             */
/*   Updated: 2024/08/30 23:29:52 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	listlength1(t_env *head)
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

char	**joinlist1(t_env *head)
{
	char	**matrix;
	int		i;
	int		length;

	i = 0;
	length = listlength1(head);
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
