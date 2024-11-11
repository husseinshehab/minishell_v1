/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:51:43 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 16:41:38 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_path(const char *location, t_minishell *mini, int size)
{
	t_env	*ptr;
	char	*path;

	ptr = mini->env;
	path = NULL;
	while (ptr)
	{
		if (strncmp(location, ptr->string, size) == 0)
		{
			path = ft_substr(ptr->string, size, strlen(ptr->string) - size);
		}
		ptr = ptr->next;
	}
	return (path);
}

int	update_old_pwd(t_minishell *mini, const char *dir)
{
	t_env	*ptr;

	ptr = mini->env;
	while (ptr)
	{
		if (strncmp("OLDPWD=", ptr->string, 7) == 0)
		{
			free(ptr->string);
			ptr->string = ft_strjoin("OLDPWD=", dir);
			return (1);
		}
		ptr = ptr->next;
	}
	printf("error updating old pwd\n");
	return (0);
}

int	update_pwd(t_minishell *mini, const char *dir)
{
	t_env	*ptr;

	ptr = mini->env;
	while (ptr)
	{
		if (strncmp("PWD=", ptr->string, 4) == 0)
		{
			free(ptr->string);
			ptr->string = ft_strjoin("PWD=", dir);
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

int	go_to_home(t_minishell *mini)
{
	char	*home_path;
	char	currentpwd[BUFFER_SIZE];

	if (!getcwd(currentpwd, BUFFER_SIZE))
		return (0);
	if (!update_old_pwd(mini, currentpwd))
		return (0);
	home_path = get_env_path("HOME=", mini, 5);
	if (home_path == NULL)
	{
		printf("cd: HOME not set!\n");
		return (0);
	}
	if (chdir(home_path) == -1)
	{
		perror("cd");
		free(home_path);
		return (0);
	}
	if (!getcwd(currentpwd, BUFFER_SIZE))
		return (0);
	update_pwd(mini, currentpwd);
	free(home_path);
	return (1);
}

int	go_back(t_minishell *mini)
{
	char	currentpwd[BUFFER_SIZE];
	char	*prev_pwd;

	prev_pwd = get_env_path("PWD=", mini, 4);
	if (!prev_pwd)
	{
		if (chdir("..") == -1)
		{
			perror("chdir");
			free(prev_pwd);
		}
		return (0);
	}
	if (!update_old_pwd(mini, prev_pwd))
		return (free(prev_pwd), 0);
	if (chdir("..") == -1)
		return (perror("chdir"), free(prev_pwd), 0);
	if (getcwd(currentpwd, sizeof(currentpwd)) == NULL)
	{
		if (!go_back_helper(prev_pwd, currentpwd))
			return (0);
	}
	if (!update_pwd(mini, currentpwd))
		return (free(prev_pwd), 0);
	return (free(prev_pwd), 1);
}

// int	go_back(t_minishell *mini)
// {
// 	char	currentpwd[BUFFER_SIZE];
// 	char	*prev_pwd;

// 	prev_pwd = get_env_path("PWD=", mini, 4);
// 	if (!prev_pwd)
// 		return (printf("Error: PWD not found in environment\n"), 0);
// 	if (!update_old_pwd(mini, prev_pwd))
// 	{
// 		free(prev_pwd);
// 		return (0);
// 	}
// 	free(prev_pwd);
// 	if (chdir("..") == -1)
// 	{
// 		perror("chdir");
// 		return (0);
// 	}
// 	if (getcwd(currentpwd, sizeof(currentpwd)) == NULL)
// 	{
// 		perror("getcwd");
// 		return (0);
// 	}
// 	if (!update_pwd(mini, currentpwd))
// 		return (0);
// 	return (1);
// }