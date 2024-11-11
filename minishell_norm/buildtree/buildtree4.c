/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtree4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:26:28 by hshehab           #+#    #+#             */
/*   Updated: 2024/10/24 12:47:36 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*find_min_redirection(t_node *head)
{
	t_node	*ptr;

	ptr = head;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			return (ptr);
		}
		ptr = ptr->next;
	}
	ptr = head;
	while (ptr)
	{
		if (ptr->type == REDIRECTION_APPEND || ptr->type == REDIRECTION_HEREDOC
			|| ptr->type == REDIRECTION_IN || ptr->type == REDIRECTION_OUT)
		{
			return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

t_treenode	*create_tree_node_if_no_special(t_node *head)
{
	char		**joined;
	t_treenode	*root;

	joined = joinlist(head);
	if (joined == NULL)
	{
		return (NULL);
	}
	root = create_treenode(0);
	if (root == NULL)
	{
		free_char_matrix(joined);
		return (NULL);
	}
	root->value = copymatrix1(joined);
	free_char_matrix(joined);
	freelinkedlist_tok(head);
	return (root);
}

t_treenode	*buildtree(t_node *head)
{
	t_node		*min;
	t_node		*left;
	t_node		*right;
	t_treenode	*root;

	left = NULL;
	right = NULL;
	if (head == NULL)
		return (NULL);
	min = find_min_redirection(head);
	if (min == NULL)
		return (create_tree_node_if_no_special(head));
	root = create_treenode(min->type);
	if (root == NULL)
		return (NULL);
	split_token_list(head, &left, &right, min);
	rearrange(&left);
	root->left = buildtree(left);
	rearrange(&right);
	root->right = buildtree(right);
	if (min)
		return (free(min->string), free(min), root);
	return (root);
}
