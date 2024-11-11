/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:07:19 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 08:37:14 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_next_heredoc(t_treenode **heredoc_ptr)
{
	if (!heredoc_ptr || !(*heredoc_ptr))
		return (0);
	while (*heredoc_ptr)
	{
		if ((*heredoc_ptr)->type == REDIRECTION_HEREDOC)
		{
			(*heredoc_ptr)->type = REDIRECTION_IN;
			return (1);
		}
		(*heredoc_ptr) = (*heredoc_ptr)->right;
	}
	return (0);
}

void	execute_heredoc_write(char *expanded_input,
			t_treenode *root)
{
	write(root->pipefd[1], expanded_input, strlen(expanded_input));
	write(root->pipefd[1], "\n", 1);
}

void	execute_heredoc(t_treenode *root, t_env *env, char *delimeter)
{
	char	*input;
	char	*expanded_input;

	pipe(root->pipefd);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (strcmp(input, delimeter) == 0)
		{
			free(input);
			break ;
		}
		expanded_input = expand(input, env);
		execute_heredoc_write(expanded_input, root);
		free(input);
		free(expanded_input);
	}
	close(root->pipefd[1]);
}

t_treenode	*get_heredoc(t_treenode *root)
{
	t_treenode	*left_result;

	if (root == NULL)
		return (NULL);
	if (root->type == REDIRECTION_HEREDOC)
		return (root);
	left_result = get_heredoc(root->left);
	if (left_result != NULL)
		return (left_result);
	return (get_heredoc(root->right));
}

void	quit_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(0);
}
