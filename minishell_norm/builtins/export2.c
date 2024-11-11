/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:35:20 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 16:10:11 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	belongstozabta(char *s)
{
	int	i;
	int	j;

	if (belongsto(s[0]))
		return (1);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!s[i])
		return (0);
	j = 0;
	while (j < i)
	{
		if (belongsto(s[j]))
			return (1);
		j++;
	}
	return (0);
}

void	remove_duplicates(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		remove_duplicate_from_node(current);
		current = current->next;
	}
}

void	remove_duplicate_from_node(t_env *current)
{
	t_env	*prev;
	t_env	*temp;

	prev = current;
	temp = current->next;
	while (temp != NULL)
	{
		if (strcmp(current->string, temp->string) == 0)
		{
			prev->next = temp->next;
			free(temp->string);
			free(temp);
			temp = prev->next;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}

// shelet joined = NULL
char	*process_nextpart(char *str, char *header)
{
	char	**nextpart;
	char	*temp;
	size_t	len;
	char	*joined;

	nextpart = ft_split1(str, '=');
	if (!nextpart)
		return (perror("ft_split1"), NULL);
	if (nextpart[1] && nextpart[1][0] == '\"'
		&& nextpart[1][ft_strlen1(nextpart[1]) - 1] == '\"')
	{
		len = ft_strlen1(nextpart[1]) - 2;
		temp = malloc(len + 1);
		if (!temp)
			return (perror("malloc"), free_char_matrix(nextpart), NULL);
		strncpy(temp, nextpart[1] + 1, len);
		temp[len] = '\0';
		joined = ft_strjoin(header, temp);
		free(temp);
	}
	else if (nextpart[1])
		joined = ft_strjoin(header, nextpart[1]);
	else
		joined = ft_strdup(header);
	return (free_char_matrix(nextpart), joined);
}

int	ft_export(char **command, t_minishell *mini)
{
	t_env	*new;
	int		flag;

	flag = 0;
	new = duplicate_env_list(mini);
	if (!command[1])
		return (bubble_sort_list(new), freelinkedlist_ev(new), 0);
	handle_command(command, mini, &flag);
	return (freelinkedlist_ev(new), flag);
}

// void	remove_duplicates(t_env *head)
// {
// 	t_env	*current;
// 	t_env	*prev;
// 	t_env	*temp;

// 	current = head;
// 	prev = NULL;
// 	temp = NULL;
// 	while (current != NULL && current->next != NULL)
// 	{
// 		prev = current;
// 		temp = current->next;
// 		while (temp != NULL)
// 		{
// 			if (ft_strcmp(current->string, temp->string) == 0)
// 			{
// 				prev->next = temp->next;
// 				free(temp->string);
// 				free(temp);
// 				temp = prev->next;
// 			}
// 			else
// 			{
// 				prev = temp;
// 				temp = temp->next;
// 			}
// 		}
// 		current = current->next;
// 	}
// }
