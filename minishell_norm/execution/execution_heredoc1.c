/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:47:41 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 10:12:06 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	execute_here_doc_main(t_minishell *mini, t_treenode *root, t_env *env)
// {
// 	char		*delimeter;
// 	t_treenode	*heredocnode;
// 	int			pid;
// 	int			status;

// 	(void)mini;
// 	delimeter = NULL;
// 	heredocnode = NULL;
// 	heredocnode = get_heredoc(root);
// 	if (heredocnode != NULL)
// 	{
// 		if (heredocnode->right->left)
// 		{
// 			delimeter = ft_strdup(heredocnode->right->left->value[0]);
// 			heredocnode->type = REDIRECTION_IN;
// 			pid = fork();
// 			if (!pid)
// 				execute_heredoc(heredocnode, env, delimeter);
// 			else if (pid > 0)
// 			{
// 				signal(SIGINT, SIG_IGN);
// 				waitpid(pid, &status, 0);
// 				exit(0);
// 			}
// 		}
// 		else
// 		{
// 			delimeter = ft_strdup(heredocnode->right->value[0]);
// 			heredocnode->type = REDIRECTION_IN;
// 			pid = fork();
// 			if (!pid)
// 				execute_heredoc(heredocnode, env, delimeter);
// 			else if (pid > 0)
// 			{
// 				waitpid(pid, &status, 0);
// 				exit(0);
// 			}
// 		}
// 		free(delimeter);
// 	}
// }

void	handle_parent_process(int pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	exit(0);
}

void	handle_child_process(t_treenode *heredocnode, t_env *env,
		char *delimeter)
{
	execute_heredoc(heredocnode, env, delimeter);
}

char	*get_delimiter(t_treenode *heredocnode)
{
	char	*delimeter;

	if (heredocnode->right->left)
		delimeter = ft_strdup(heredocnode->right->left->value[0]);
	else
		delimeter = ft_strdup(heredocnode->right->value[0]);
	return (delimeter);
}

void	execute_here_doc_main(t_minishell *mini, t_treenode *root, t_env *env)
{
	t_treenode	*heredocnode;
	char		*delimeter;
	int			pid;
	int			status;

	(void)mini;
	heredocnode = get_heredoc(root);
	if (heredocnode != NULL)
	{
		delimeter = get_delimiter(heredocnode);
		heredocnode->type = REDIRECTION_IN;
		pid = fork();
		if (!pid)
			handle_child_process(heredocnode, env, delimeter);
		else if (pid > 0)
			handle_parent_process(pid, &status);
		free(delimeter);
	}
}
