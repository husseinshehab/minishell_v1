/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:36:11 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 16:41:12 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	go_back_helper(char *prev_pwd, char *currentpwd)
{
	char	*joined;

	fprintf(stderr, "getcwd: cannot access parent directories\n");
	joined = ft_strjoin(prev_pwd, "/..");
	if (joined == NULL)
		return (fprintf(stderr, "Memory allocation error\n"), free(prev_pwd),
			0);
	strncpy(currentpwd, joined, sizeof(currentpwd) - 1);
	currentpwd[sizeof(currentpwd) - 1] = '\0';
	free(joined);
	return (1);
}
