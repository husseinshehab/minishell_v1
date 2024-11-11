/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:24:54 by ldarsa            #+#    #+#             */
/*   Updated: 2024/09/21 14:22:36 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trim_my_token(char *src, int j, int i)
{
	char	*rstr;
	int		k;

	if (j > i || j < 0 || i < 0)
	{
		rstr = malloc(sizeof(char));
		if (rstr == NULL)
			return (NULL);
		rstr[0] = '\0';
		return (rstr);
	}
	rstr = malloc(sizeof(char) * (i - j + 2));
	if (rstr == NULL)
		return (NULL);
	k = 0;
	while (j <= i)
	{
		rstr[k++] = src[j++];
	}
	rstr[k] = '\0';
	return (rstr);
}

char	*extract_token(char *str, int *i, t_type *type)
{
	int		j;
	char	*rstr;

	j = *i;
	if (str[*i] == '\"')
		rstr = extract_quotes(str, i, j, type);
	else if (str[*i] == '\'')
		rstr = extract_quotes1(str, i, j, type);
	else if (str[*i] == '|')
		rstr = extract_pipe(str, i, j, type);
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
		rstr = extract_redirectout(str, i, j, type);
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
		rstr = extract_redirectin(str, i, j, type);
	else if (str[*i] == '>' && str[(*i) + 1] == '>')
		rstr = extract_appendin(str, i, j, type);
	else if (str[*i] == '<' && str[(*i) + 1] == '<')
		rstr = extract_heredoc(str, i, j, type);
	else
		rstr = extract_cmd(str, i, j, type);
	return (rstr);
}

void	tokenize_input(t_minishell *mini, char *inputstr)
{
	int		i;
	char	*tokenstr;
	t_type	type;

	tokenstr = NULL;
	i = 0;
	type = -1;
	if (inputstr == NULL || inputstr[0] == '\0')
		return ;
	while (inputstr[i] != '\0')
	{
		while (inputstr[i] == ' ' || inputstr[i] == '\t')
		{
			i++;
		}
		if (inputstr[i] == '\0')
			break ;
		tokenstr = extract_token(inputstr, &i, &type);
		if (tokenstr != NULL)
		{
			mini->head = pushtoback(mini->head, tokenstr, type);
			free(tokenstr);
		}
	}
}
