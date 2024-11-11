/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:06:08 by ldarsa            #+#    #+#             */
/*   Updated: 2024/09/21 14:11:13 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	close_pipe_and_wait(int pipefd[2], pid_t left_pid, pid_t right_pid)
{
	int	status;

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(0);
}

void	execute_right_command(t_minishell *mini, t_treenode *root,
			t_env *env, int pipefd[2])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 right cmd");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	execute_tree(mini, root->right, env);
}

void	execute_left_command(t_minishell *mini, t_treenode *root,
			t_env *env, int pipefd[2])
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 left cmd");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	execute_tree(mini, root->left, env);
}
