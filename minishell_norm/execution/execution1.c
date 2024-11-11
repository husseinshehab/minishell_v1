/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:36:32 by hshehab           #+#    #+#             */
/*   Updated: 2024/11/05 11:21:52 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(char *start, t_env *env)
{
	int		j;
	char	*first_part;

	while (env)
	{
		j = 0;
		while (env->string[j] && env->string[j] != '=')
			j++;
		first_part = ft_substr(env->string, 0, j);
		if (env->string[j] == '=')
		{
			if (ft_strcmp(first_part, start) == 0)
			{
				free(first_part);
				return (env->string + j + 1);
			}
		}
		free(first_part);
		env = env->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env *my_env)
{
	int		i;
	char	*executable_path;
	char	**all_paths;
	char	*temp_path;

	i = -1;
	temp_path = get_env("PATH", my_env);
	if (!temp_path)
		return (NULL);
	all_paths = ft_split1(temp_path, ':');
	while (all_paths[++i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		executable_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(executable_path, F_OK | X_OK) == 0)
			return (free_char_matrix(all_paths), executable_path);
		free(executable_path);
	}
	return (free_char_matrix(all_paths), ft_strdup(cmd));
}

char	*get_command_path(char *cmd, t_env *my_env)
{
	char	*path;
	char	*temp;

	(void)my_env;
	path = NULL;
	if (is_builtin(cmd))
		path = ft_strdup(cmd);
	else
	{
		temp = get_path(cmd, my_env);
		if (!temp)
			return (NULL);
		path = ft_strdup(temp);
		if (access(path, X_OK) == 0)
		{
			if (temp)
				free(temp);
			return (path);
		}
		else
			free(temp);
	}
	if (path)
		free(path);
	return (NULL);
}

void	execute_pipe(t_minishell *mini, t_treenode *root, t_env *env)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	create_pipe(pipefd);
	left_pid = fork_process();
	if (left_pid == 0)
	{
		execute_left_command(mini, root, env, pipefd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	right_pid = fork_process();
	if (right_pid == 0)
	{
		execute_right_command(mini, root, env, pipefd);
	}
	close_pipe_and_wait(pipefd, left_pid, right_pid);
}

void	execute_tree(t_minishell *mini, t_treenode *root, t_env *env)
{
	int		status;
	pid_t	pid;

	if (!root)
		return ;
	while (type_exists(root, REDIRECTION_HEREDOC))
	{
		signal(SIGINT, quit_heredoc);
		signal(SIGQUIT, SIG_IGN);
		execute_here_doc_main(mini, root, env);
	}
	if (root->type != PIPE)
	{
		pid = fork_process();
		if (pid == 0)
			perform_execution(mini, root, env);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
		else
			mini->exit_code = 0;
		exit(mini->exit_code);
	}
	else if (root->type == PIPE)
		execute_pipe(mini, root, env);
}
