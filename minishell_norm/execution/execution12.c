/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:19:47 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 11:21:57 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_command_execution(t_treenode *root, t_minishell *mini,
		t_env *env, int code)
{
	if (root->type == WORD && !is_builtin(root->value[0]))
		execute_external_command(root, mini, env);
	else if (root->type != WORD && root->left
		&& !is_builtin(root->left->value[0]))
	{
		execute_external_command(root, mini, env);
	}
	else if (root->type == WORD && is_builtin(root->value[0]))
		execute_builtin_command(root, mini);
	else if (root->type != WORD && root->left
		&& is_builtin(root->left->value[0]))
	{
		if (code != 0)
			execute_builtin_command(root, mini);
		else
			code = execute_builtin(root->left->value, mini);
		exit(code);
	}
	else
		exit(code);
}

void	perform_execution(t_minishell *mini, t_treenode *root, t_env *env)
{
	int		flag_fd;
	int		flag;
	char	*lastin;
	char	*lastout;
	int		code;

	flag_fd = -1;
	flag = 0;
	lastin = last_input(root, &flag_fd);
	lastout = last_output(root, &flag);
	code = 0;
	if (root->type != WORD && root->type != PIPE)
	{
		code = handle_tree_checks(root);
	}
	handle_input_redirection(flag_fd, lastin);
	handle_output_redirection(lastout, flag);
	handle_command_execution(root, mini, env, code);
}

void	execute(t_minishell *mini, t_treenode *root, t_env *env)
{
	if (!root)
		return ;
	execute_tree(mini, root, env);
}
