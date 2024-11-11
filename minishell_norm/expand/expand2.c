/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:12:23 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 12:31:33 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*quotes_helper(char *str, int *i, int *j, t_env *env)
{
	char	*sub;
	char	*result;

	(*i)++;
	*j = *i;
	while (str[*j] && str[*j] != '\"')
		(*j)++;
	sub = ft_substr(str, *i, *j - *i);
	result = expand(sub, env);
	free(sub);
	if (str[*j])
		*i = *j + 1;
	return (result);
}

char	*qoutes_helper1(char *str, int *i, int *j)
{
	char	*result;

	(*i)++;
	*j = *i;
	while (str[*j] && str[*j] != '\'')
		(*j)++;
	result = ft_substr(str, *i, *j - *i);
	if (str[*j])
		*i = *j + 1;
	return (result);
}

char	*quotes_helper2(char *str, int *i, int *j, t_env *env)
{
	char	*sub;
	char	*result;

	*j = *i;
	while (str[*j] && str[*j] != '\'' && str[*j] != '\"')
		(*j)++;
	sub = ft_substr(str, *i, *j - *i);
	result = expand(sub, env);
	free(sub);
	*i = *j;
	return (result);
}

void	free_quotes(char *temp, char *result, char *new, char **str)
{
	if (temp || result)
	{
		if (temp)
			free(temp);
		if (result)
			free(result);
		temp = NULL;
		result = NULL;
	}
	else
	{
		if (*str && new)
		{
			free(*str);
			*str = ft_strdup(new);
			free(new);
			new = NULL;
		}
	}
}

void	quotes(t_node *head, t_env *env)
{
	int		i;
	int		j;
	char	*result;
	char	*new;
	char	*temp;

	while (head)
	{
		new = ft_strdup("");
		i = 0;
		while (head->string[i])
		{
			if (head->string[i] == '\"')
				result = quotes_helper(head->string, &i, &j, env);
			else if (head->string[i] == '\'')
				result = qoutes_helper1(head->string, &i, &j);
			else
				result = quotes_helper2(head->string, &i, &j, env);
			temp = new;
			new = ft_strjoin(new, result);
			free_quotes(temp, result, NULL, NULL);
		}
		free_quotes(NULL, NULL, new, &head->string);
		head = head->next;
	}
}
