/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:04:34 by ldarsa            #+#    #+#             */
/*   Updated: 2024/10/24 13:04:38 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	belongsto(char c)
{
	char	*str;

	str = "*/=-~!@#&^()";
	while (*str != '\0')
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int	is_valid_env_name(char *str)
{
	int	i;

	i = 0;
	if (belongsto(str[0]) || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (belongsto(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '=')
		return (0);
	return (1);
}

int	foundenv(char *str, t_env *env)
{
	t_env	*ptr;
	char	*header;
	int		i;

	ptr = env;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	header = ft_substr(str, 0, i + 1);
	while (ptr)
	{
		if (!ft_strncmp(ptr->string, header, ft_strlen1(header)))
		{
			free(header);
			return (1);
		}
		ptr = ptr->next;
	}
	free(header);
	return (0);
}

size_t	find_equal_sign_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	*create_header(char *str, size_t index)
{
	char	*header;

	header = ft_substr(str, 0, index + 1);
	if (!header)
		perror("ft_substr");
	return (header);
}
