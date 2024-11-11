/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:46 by ldarsa            #+#    #+#             */
/*   Updated: 2024/09/16 13:16:58 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_quotes(char *str, int *i, int j, t_type *type)
{
	char	*rstr;
	char	*str1;

	*type = WORD;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '\"')
	{
		(*i)++;
	}
	if (str[*i] == '\0')
	{
		printf("UNCLOSED DOUBLE QOUTES!\n");
		return (NULL);
	}
	if (str[(*i) + 1] == '\"')
	{
		(*i)++;
		str1 = extract_quotes(str, i, j, type);
		free(str1);
	}
	if (str[(*i) + 1] == '\'')
	{
		(*i)++;
		str1 = extract_quotes1(str, i, j, type);
		free(str1);
	}
	if (str[(*i)] != '|' && str[(*i) ] != '>' && str[(*i)] != '<' && str[(*i)] != ' ')
	{
		str1 = extract_cmd(str, i, j, type);
		free(str1);
		rstr = trim_my_token(str, j, ((*i) - 1));
		return (rstr);
	}
	rstr = NULL;
	rstr = trim_my_token(str, j, ((*i) - 1));
	return (rstr);
}

char	*extract_quotes1(char *str, int *i, int j, t_type *type)
{
	char	*rstr;
	char	*str1;

	*type = WORD;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '\'')
	{
		(*i)++;
	}
	if (str[*i] == '\0')
	{
		printf("UNCLOSED SINGLE QOUTE!\n");
		return (NULL);
	}
	if(str[(*i)] != '|' && str[(*i)] != '>' && str[(*i)] != '<' && str[(*i)] != ' ')
	{
		str1 = extract_cmd(str, i, j, type);
		free(str1);
		rstr = trim_my_token(str, j, ((*i) - 1));
		return (rstr);
	}
	if (str[(*i) + 1] == '\"')
	{
		(*i)++;
		str1 = extract_quotes(str, i, j, type);
		free(str1);
	}
	if (str[(*i) + 1] == '\'')
	{
		(*i)++;
		str1 = extract_quotes1(str, i, j, type);
		free(str1);
	}
	rstr = NULL;
	rstr = trim_my_token(str, j, ((*i) - 1));
	return (rstr);
}

char	*extract_cmd(char *str, int *i, int j, t_type *type)
{
	char	*rstr;
	char	*tracker;

	tracker = NULL;
	*type = WORD;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '|' && str[*i] != '>' && str[*i] != '<'
		&& str[*i] != ' ')
	{
		if (str[*i] == '\'')
		{
			tracker = extract_quotes1(str, i, j, type);
			if (tracker == NULL)
				return (NULL);
			free(tracker);
		}
		else if (str[*i] == '\"')
		{
			tracker = extract_quotes(str, i, j, type);
			if (tracker == NULL)
				return (NULL);
			free(tracker);
		}
		else
			(*i)++;
	}
	rstr = trim_my_token(str, j, ((*i) - 1));
	return (rstr);
}
