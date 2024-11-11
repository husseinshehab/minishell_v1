/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:18:04 by hshehab           #+#    #+#             */
/*   Updated: 2024/10/24 12:50:28 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	go_to_slash(t_minishell *mini)
{
	char	currentpwd[BUFFER_SIZE];
	char	*prev_pwd;

	prev_pwd = get_env_path("PWD=", mini, 4);
	if (!prev_pwd)
		return (printf("Error: PWD not found in environment\n"), 0);
	if (!update_old_pwd(mini, prev_pwd))
	{
		free(prev_pwd);
		return (0);
	}
	free(prev_pwd);
	if (chdir("/") == -1)
	{
		perror("chdir");
		return (0);
	}
	if (getcwd(currentpwd, sizeof(currentpwd)) == NULL)
	{
		perror("getcwd");
		return (0);
	}
	if (!update_pwd(mini, currentpwd))
		return (0);
	return (1);
}

int	go_to_last(t_minishell *mini)
{
	char	*last_path;
	char	currentpwd[BUFFER_SIZE];

	if (!getcwd(currentpwd, BUFFER_SIZE))
		return (0);
	last_path = get_env_path("OLDPWD=", mini, 7);
	if (last_path == NULL)
		return (printf("cd: OLDPWD not set!\n"), 0);
	if (chdir(last_path) == -1)
		return (perror("cd"), free(last_path), 0);
	if (!update_old_pwd(mini, currentpwd))
	{
		free(last_path);
		return (0);
	}
	if (!update_pwd(mini, currentpwd))
	{
		free(last_path);
		return (0);
	}
	free(last_path);
	return (1);
}

int	ft_cd(char **path, t_minishell *mini)
{
	struct stat	statbuf;
	char		cwd[BUFFER_SIZE];

	if (path[1] != NULL && path[2] != NULL)
	{
		perror("cd");
		return (1);
	}
	if (path[1] == NULL || ft_strncmp(path[1], "~", 2) == 0)
		return (!go_to_home(mini));
	else if (ft_strncmp(path[1], "..", 3) == 0)
		return (!go_back(mini));
	else if (ft_strncmp(path[1], "/", 2) == 0)
		return (!go_to_slash(mini));
	else if (ft_strncmp(path[1], "-", 2) == 0)
		return (!go_to_last(mini));
	if (stat(path[1], &statbuf) == -1)
		return (perror("cd"), 1);
	if (!S_ISDIR(statbuf.st_mode) || chdir(path[1]) == -1)
		return (perror("cd"), 1);
	if (!getcwd(cwd, BUFFER_SIZE) || !update_old_pwd(mini, cwd)
		|| !update_pwd(mini, cwd))
		return (1);
	return (0);
}
