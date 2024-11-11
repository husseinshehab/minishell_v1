/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:47:16 by hshehab           #+#    #+#             */
/*   Updated: 2024/11/05 08:35:47 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir_type(t_type type)
{
	return (type == REDIRECTION_APPEND || type == REDIRECTION_HEREDOC
		|| type == REDIRECTION_IN || type == REDIRECTION_OUT);
}

int	type_exists(t_treenode *root, t_type type)
{
	if (!root)
		return (0);
	if (root->type == type)
		return (1);
	return (type_exists(root->left, type) || type_exists(root->right, type));
}

char	*last_input(t_treenode *root, int *flag)
{
	t_treenode	*ptr;

	ptr = NULL;
	if (!type_exists(root, REDIRECTION_IN))
		return (NULL);
	while (root)
	{
		if (root->type == REDIRECTION_IN)
			ptr = root;
		root = root->right;
	}
	if (ptr->pipefd[0] >= 0)
	{
		*flag = ptr->pipefd[0];
		return (NULL);
	}
	if (ptr->right->left)
		return (ptr->right->left->value[0]);
	return (ptr->right->value[0]);
}

char	*last_output(t_treenode *root, int *flag)
{
	t_treenode	*ptr;

	*flag = 1;
	ptr = NULL;
	if (!type_exists(root, REDIRECTION_OUT) && !type_exists(root,
			REDIRECTION_APPEND))
	{
		return (NULL);
	}
	while (root)
	{
		if (root->type == REDIRECTION_OUT || root->type == REDIRECTION_APPEND)
			ptr = root;
		root = root->right;
	}
	if (ptr->type == REDIRECTION_APPEND)
		*flag = 0;
	if (ptr->right->left)
		return (ptr->right->left->value[0]);
	return (ptr->right->value[0]);
}
