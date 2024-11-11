/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:06:56 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 13:04:57 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*substring_before(char *str, char *ptr)
{
	char	*substr;
	size_t	length;

	if (ptr < str || ptr > str + ft_strlen(str))
		return (NULL);
	length = ptr - str;
	substr = (char *)malloc(length + 1);
	if (substr == NULL)
		return (NULL);
	strncpy(substr, str, length);
	substr[length] = '\0';
	return (substr);
}

t_env	*str_in_env(char *str, t_env *env)
{
	char	*temp;
	char	*pos;

	while (env)
	{
		if (!ft_strcmp(env->string, str))
			return (env);
		pos = ft_strchr(env->string, '=');
		temp = substring_before(env->string, pos);
		if (temp && !ft_strcmp(str, temp))
		{
			free(temp);
			return (env);
		}
		free(temp);
		env = env->next;
	}
	return (NULL);
}

void	remove_from_env(t_minishell *mini, t_treenode *ptr, int i)
{
	t_env	*temp;
	t_env	*prev;
	t_env	*current;

	while (ptr->value[i])
	{
		temp = str_in_env(ptr->value[i], mini->env);
		if (temp)
		{
			current = mini->env;
			prev = NULL;
			while (current && current != temp)
			{
				prev = current;
				current = current->next;
			}
			if (prev)
				prev->next = temp->next;
			else
				mini->env = temp->next;
			free(temp->string);
			free(temp);
		}
		i++;
	}
}

int	doable_unset(t_treenode *ptr, int i)
{
	while (ptr->value[i])
	{
		if (ft_strchr(ptr->value[i], '!'))
			return (ft_printf("unset: %s: event not found\n", ptr->value[i]), 0);
		else if (ft_strchr(ptr->value[i], '(') || ft_strchr(ptr->value[i], ')'))
			return (ft_printf("unset: %s: syntax error near unexpected token\n",
					ptr->value[i]), 0);
		i++;
	}
	return (1);
}

int	ft_unset(t_minishell *mini)
{
	t_treenode	*ptr;
	int			i;

	ptr = mini->tree;
	i = 1;
	if (!ptr->value[i])
	{
		return (0);
	}
	if (!doable_unset(ptr, i))
		return (2);
	remove_from_env(mini, ptr, i);
	return (0);
}
