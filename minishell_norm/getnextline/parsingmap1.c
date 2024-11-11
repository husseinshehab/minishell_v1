/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:02:37 by hshehab           #+#    #+#             */
/*   Updated: 2024/08/21 20:15:30 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**maptomatrix(char *filename)
{
	int		fd;
	char	*line;
	char	*line1;
	char	**matrix;
	int		height;

	line = NULL;
	line1 = NULL;
	height = heightoffile(filename);
	fd = openfile(filename);
	while (height > 0)
	{
		line1 = get_next_line(fd);
		line = ft_strjoin1(line, line1);
		height--;
	}
	close(fd);
	if (line == NULL)
	{
		return (NULL);
	}
	matrix = ft_split1(line, '\n');
	free(line);
	return (matrix);
}

void	free_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
	{
		return ;
	}
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

int	checkboarders(char **matrix, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i])
	{
		while (matrix[i][j] != '\0')
		{
			if (j == 0 || j == width - 1 || i == 0 || i == height - 1)
			{
				if (matrix[i][j] != '1')
					return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	printmatrix(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	if(matrix == NULL)
		return;
	printf("-------start matrix --------\n");
	while (matrix[i] != NULL)
	{
		j = 0;
		while (matrix[i][j] != '\0')
		{
			printf("%c", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("-------end matrix --------\n");
}