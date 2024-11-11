/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:20:31 by hshehab           #+#    #+#             */
/*   Updated: 2024/10/24 16:10:08 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_or_add_env(t_env *env, char *str, char *header)
{
	t_env	*ptr;
	char	*joined;

	ptr = env;
	while (ptr)
	{
		if (strncmp(ptr->string, header, ft_strlen1(header)) == 0)
		{
			joined = process_nextpart((char *)str, header);
			if (!joined)
			{
				free(header);
				return ;
			}
			free(ptr->string);
			ptr->string = joined;
			free(header);
			return ;
		}
		ptr = ptr->next;
	}
	pushtoback_env(env, str);
	free(header);
}

void	update_env(char *str, t_env *env)
{
	size_t	index;
	char	*header;

	index = find_equal_sign_index(str);
	header = create_header(str, index);
	if (!header)
		return ;
	update_or_add_env(env, str, header);
}

void	ft_exort_helper(char **command, t_minishell *mini, int i)
{
	if (foundenv(command[i], mini->env))
		update_env(command[i], mini->env);
	else
		pushtoback_env(mini->env, command[i]);
}

void	handle_env_name(char *name, t_minishell *mini, int *flag)
{
	if (!is_valid_env_name(name))
	{
		perror("export: not a valid identifier\n");
		*flag = 1;
		return ;
	}
	if (!foundenv(name, mini->env))
		pushtoback_env(mini->env, name);
	else
	{
		update_env(name, mini->env);
	}
}

void	handle_command(char **command, t_minishell *mini, int *flag)
{
	int	i;

	i = 1;
	while (command[i])
	{
		if (belongstozabta(command[i]))
		{
			perror("export");
			i++;
			*flag = 1;
			continue ;
		}
		if (ft_strchr(command[i], '='))
			ft_exort_helper(command, mini, i);
		else
			handle_env_name(command[i], mini, flag);
		i++;
	}
}

// int	ft_export(char **command, t_minishell *mini)
// {
// 	int		i;
// 	t_env	*new;
// 	int		flag;

// 	flag = 0;
// 	new = duplicate_env_list(mini);
// 	if (!command[1])
// 		return (bubble_sort_list(new), freelinkedlist_ev(new), 0);
// 	i = 1;
// 	while (command[i])
// 	{
// 		if (belongstozabta(command[i]))
// 		{
// 			perror("export");
// 			i++;
// 			flag = 1;
// 			continue ;
// 		}
// 		if (ft_strchr(command[i], '='))
// 			ft_exort_helper(command, mini, i);
// 		else
// 		{
// 			if (!is_valid_env_name(command[i]))
// 			{
// 				perror("export: not a valid identifier\n");
// 				i++;
// 				flag = 1;
// 				continue ;
// 			}
// 			if (!foundenv(command[i], mini->env))
// 				pushtoback_env(mini->env, command[i]);
// 			else
// 			{
// 				update_env(command[i], mini->env);
// 			}
// 		}
// 		i++;
// 	}
// 	return (freelinkedlist_ev(new), flag);
// }
