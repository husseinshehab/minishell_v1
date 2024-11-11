/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:59:30 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 16:29:52 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*returnvar(char *str, t_env *head)
{
	size_t	len;
	int		i;
	char	*result;
	char	*str_with_equals;

	result = NULL;
	str_with_equals = ft_strjoin(str, "=");
	len = ft_strlen(str_with_equals);
	while (head)
	{
		if (ft_strncmp(str_with_equals, head->string, len) == 0)
		{
			i = len - 1;
			result = ft_strdup(&head->string[i + 1]);
			break ;
		}
		head = head->next;
	}
	free(str_with_equals);
	if (result)
		return (result);
	else
		return (ft_strdup(""));
}

char	*handle_other_cases(char *str, int *i)
{
	int		j;
	char	*result;

	j = *i;
	if (str[j] == '$' && (str[j + 1] == ' ' || str[j
				+ 1] == '\t' || str[j + 1] == '\0'))
	{
		result = ft_strdup("$");
		*i += 1;
	}
	else
	{
		while (str[j] && str[j] != '$')
			j++;
		result = ft_substr(str, *i, j - *i);
		*i = j;
	}
	return (result);
}

char	*handle_variable(char *str, int *i, t_env *env)
{
	int		j;
	char	*sub;
	char	*result;

	j = *i;
	j++;
	while (str[j] && str[j] != '\'' && str[j] != '$' && str[j] != '+'
		&& str[j] != ' ' && str[j] != '?')
		j++;
	if (str[j] == '?')
		j++;
	sub = ft_substr(str, *i + 1, j - *i - 1);
	result = returnvar(sub, env);
	free(sub);
	*i = j;
	return (result);
}

char	*expand(char *str, t_env *env)
{
	int		i;
	char	*result;
	char	*new;
	char	*temp;

	i = 0;
	new = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i
				+ 1] != '\t' && str[i + 1] != '\0')
			result = handle_variable(str, &i, env);
		else
			result = handle_other_cases(str, &i);
		temp = new;
		new = ft_strjoin(new, result);
		free(temp);
		free(result);
	}
	return (new);
}

// char	*expand(char *str, t_env *env)
// {
// 	int		i;
// 	char	*result;
// 	char	*sub;
// 	char	*new;
// 	char	*temp;
// 	int		j;

// 	i = 0;
// 	new = ft_strdup("");
// 	while (str[i])
// 	{
// 		j = i;
// 		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\t' && str[i
// 			+ 1] != '\0')
// 		{
// 			j++;
// 			while (str[j] && str[j] != '\'' && str[j] != '$' && str[j] != '+'
// 				&& str[j] != ' ' && str[j] != '?')
// 				j++;
// 			if (str[j] == '?')
// 				j++;
// 			sub = ft_substr(str, i + 1, j - i - 1);
// 			result = returnvar(sub, env);
// 			free(sub);
// 			i = j;
// 		}
// 		else if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\t'
// 				|| str[i + 1] == '\0'))
// 		{
// 			result = ft_strdup("$");
// 			i++;
// 		}
// 		else
// 		{
// 			while (str[j] && str[j] != '$')
// 				j++;
// 			result = ft_substr(str, i, j - i);
// 			i = j;
// 		}
// 		temp = new;
// 		new = ft_strjoin(new, result);
// 		free(temp);
// 		free(result);
// 	}
// 	return (new);
// }