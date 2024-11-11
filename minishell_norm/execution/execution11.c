/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:01:44 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 11:20:15 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	perform_execution(t_minishell *mini, t_treenode *root, t_env *env)
// {
// 	int		flag_fd;
// 	char	*lastin;
// 	int		fd_read;
// 	int		fd_write;
// 	int		flag;
// 	char	*lastout;
// 	char	**joined;
// 	int		code;
// 	int		open_flags;
// 	char	*command_path;

// 	flag_fd = -1;
// 	lastin = last_input(root, &flag_fd);
// 	fd_read = -1;
// 	fd_write = -1;
// 	lastout = last_output(root, &flag);
// 	code = 0;
// 	if (root->type != WORD && root->type != PIPE)
// 	{
// 		code = check_tree(root);
// 		if (code == 2)
// 			exit(0);
// 		if (code)
// 			exit(code);
// 	}
// 	if (flag_fd != -1)
// 	{
// 		if (dup2(flag_fd, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 lastin");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(flag_fd);
// 	}
// 	else if (lastin)
// 	{
// 		fd_read = open(lastin, O_RDONLY);
// 		if (fd_read < 0)
// 		{
// 			perror("open lastin");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(fd_read, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 lastin");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(fd_read);
// 	}
// 	if (lastout)
// 	{
// 		open_flags = O_WRONLY | O_CREAT;
// 		if (!flag)
// 			open_flags |= O_APPEND;
// 		else
// 			open_flags |= O_TRUNC;
// 		fd_write = open(lastout, open_flags, 0644);
// 		if (fd_write < 0)
// 		{
// 			perror("open lastout");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(fd_write, STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 lastout");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(fd_write);
// 	}
// 	if (root && ((root->type == WORD && !is_builtin(root->value[0]))
// 			|| (root->type != WORD && root->left
// 				&& !is_builtin(root->left->value[0]))))
// 	{
// 		joined = joinlist1(env); // hpnon
// 		if (root->type != WORD)
// 			command_path = get_command_path(root->left->value[0], mini->env);
// 		else
// 			command_path = get_command_path(root->value[0], mini->env);
// 		if (command_path) // hon
// 		{
// 			if (root->type == WORD)
// 			{
// 				execve(command_path, root->value, joined);
// 				free_char_matrix(joined);
// 				perror("execve");
// 				exit(127);
// 			}
// 			execve(command_path, root->left->value, joined);
// 			free(command_path);
// 		}
// 		perror("execve");
// 		free_char_matrix(joined);
// 		exit(127);
// 	}
// 	else if (root && root->type == WORD && is_builtin(root->value[0]))
// 	{
// 		code = execute_builtin(root->value, mini);
// 		exit(code);
// 	}
// 	else if (root && root->type != WORD && root->left
// 		&& is_builtin(root->left->value[0]))
// 	{
// 		if (code != 0)
// 		{
// 			execute_builtin(root->left->value, mini);
// 			exit(code);
// 		}
// 		else
// 			code = execute_builtin(root->left->value, mini);
// 		exit(code);
// 	}
// 	else if (root && root->type != WORD && root->left == NULL && (lastin
// 			|| lastout))
// 		exit(code);
// 	else
// 	{
// 		perror("execve");
// 		exit(127);
// 	}
// }
// IMPORTANT EKHER SATER BI ALEB ELSE IF HUWE 
//CLOSE(FD_READ SHELTO LA SHUF EZA BYEZBAT KERMEL NORMINETTE
void	handle_input_redirection(int flag_fd, char *lastin)
{
	int	fd_read;

	if (flag_fd != -1)
	{
		if (dup2(flag_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 lastin");
			exit(EXIT_FAILURE);
		}
		close(flag_fd);
	}
	else if (lastin)
	{
		fd_read = open(lastin, O_RDONLY);
		if (fd_read < 0)
		{
			perror("open lastin");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_read, STDIN_FILENO) == -1)
		{
			perror("dup2 lastin");
			exit(EXIT_FAILURE);
		}
	}
}

void	handle_output_redirection(char *lastout, int flag)
{
	int	open_flags;
	int	fd_write;

	if (lastout)
	{
		open_flags = O_WRONLY | O_CREAT;
		if (!flag)
			open_flags |= O_APPEND;
		else
			open_flags |= O_TRUNC;
		fd_write = open(lastout, open_flags, 0644);
		if (fd_write < 0)
		{
			perror("open lastout");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_write, STDOUT_FILENO) == -1)
		{
			perror("dup2 lastout");
			exit(EXIT_FAILURE);
		}
		close(fd_write);
	}
}

void	execute_external_command(t_treenode *root, t_minishell *mini,
		t_env *env)
{
	char	**joined;
	char	*command_path;

	joined = joinlist1(env);
	if (root->type != WORD)
		command_path = get_command_path(root->left->value[0], mini->env);
	else
		command_path = get_command_path(root->value[0], mini->env);
	if (command_path)
	{
		if (root->type == WORD)
		{
			execve(command_path, root->value, joined);
			free_char_matrix(joined);
			perror("execve");
			exit(127);
		}
		execve(command_path, root->left->value, joined);
		free(command_path);
	}
	perror("execve");
	free_char_matrix(joined);
	exit(127);
}

void	execute_builtin_command(t_treenode *root, t_minishell *mini)
{
	int	code;

	code = execute_builtin(root->value, mini);
	exit(code);
}

int	handle_tree_checks(t_treenode *root)
{
	int	code;

	code = check_tree(root);
	if (code == 2)
		exit(0);
	if (code)
		exit(code);
	return (code);
}
