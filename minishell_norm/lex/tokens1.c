/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:35:41 by ldarsa            #+#    #+#             */
/*   Updated: 2024/08/30 22:35:53 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_pipe(char *str, int *i, int j, t_type *type)
{
	char	*rstr;

	*type = PIPE;
	rstr = NULL;
	rstr = trim_my_token(str, j, ((*i)));
	(*i)++;
	return (rstr);
}

char	*extract_redirectin(char *str, int *i, int j, t_type *type)
{
	char	*rstr;

	*type = REDIRECTION_IN;
	rstr = NULL;
	rstr = trim_my_token(str, j, ((*i)));
	(*i)++;
	return (rstr);
}

char	*extract_redirectout(char *str, int *i, int j, t_type *type)
{
	char	*rstr;

	*type = REDIRECTION_OUT;
	rstr = NULL;
	rstr = trim_my_token(str, j, ((*i)));
	(*i)++;
	return (rstr);
}

char	*extract_appendin(char *str, int *i, int j, t_type *type)
{
	char	*rstr;

	*type = REDIRECTION_APPEND;
	rstr = NULL;
	rstr = trim_my_token(str, j, ((*i) + 1));
	(*i) += 2;
	return (rstr);
}

char	*extract_heredoc(char *str, int *i, int j, t_type *type)
{
	char	*rstr;

	*type = REDIRECTION_HEREDOC;
	rstr = NULL;
	rstr = trim_my_token(str, j, ((*i) + 1));
	(*i) += 2;
	return (rstr);
}
