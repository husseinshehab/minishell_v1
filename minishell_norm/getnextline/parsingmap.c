/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:51:56 by hshehab           #+#    #+#             */
/*   Updated: 2024/07/23 19:16:49 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	openfile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

int	heightoffile(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	rectmatrix(char **matrix)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen1(matrix[i]);
	i = 1;
	while (matrix[i])
	{
		if (size != ft_strlen1(matrix[i]))
			return (0);
		i++;
	}
	return (1);
}

int	containschar(char **matrix, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[j])
	{
		while (matrix[j][i] != '\0')
		{
			if (matrix[j][i] == c)
				return (1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}
