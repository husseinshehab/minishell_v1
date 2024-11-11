/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:06:08 by hshehab           #+#    #+#             */
/*   Updated: 2024/07/23 19:17:11 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *s1)
{
	int		i;
	char	*cpy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	cpy = malloc(sizeof(char) * (i + 1));
	if (cpy == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin1_helper(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL)
	{
		str = ft_strcpy(s2);
		free(s2);
		return (str);
	}
	else if (s2 == NULL)
	{
		str = ft_strcpy(s1);
		free(s1);
		return (str);
	}
	return (NULL);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (ft_strjoin1_helper(s1, s2));
	str = malloc(sizeof(char) * (ft_strlen1(s1) + ft_strlen1(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1 [i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
