/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:29:44 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 10:08:54 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
	{
		perror("Error opening file ");
	}
	return (fd);
}

int	handle_redirection_out(t_treenode *root)
{
	int	fd;

	if (root->right->type == WORD)
		fd = open_file(root->right->value[0], O_CREAT | O_WRONLY | O_TRUNC,
				0666);
	else
		fd = open_file(root->right->left->value[0],
				O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return (fd);
}

int	handle_redirection_in(t_treenode *root)
{
	int	fd;

	if (root->pipefd[0] >= 0)
		return (0);
	if (root->right->type == WORD)
		fd = open_file(root->right->value[0], O_RDONLY, 0);
	else
		fd = open_file(root->right->left->value[0], O_RDONLY, 0);
	return (fd);
}

int	handle_redirection_append(t_treenode *root)
{
	int	fd;

	if (root->right->type == WORD)
		fd = open_file(root->right->value[0], O_WRONLY | O_CREAT | O_APPEND,
				0666);
	else
		fd = open_file(root->right->left->value[0],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	return (fd);
}

int	check_tree(t_treenode *root)
{
	int	fd;

	if (!root->left)
		return (2);
	while (root)
	{
		if (root->type == REDIRECTION_OUT)
			fd = handle_redirection_out(root);
		else if (root->type == REDIRECTION_IN)
			fd = handle_redirection_in(root);
		else if (root->type == REDIRECTION_APPEND)
			fd = handle_redirection_append(root);
		else
			break ;
		if (fd < 0)
			return (1);
		close(fd);
		root = root->right;
	}
	return (0);
}
