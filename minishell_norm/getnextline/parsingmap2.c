/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:43:11 by hshehab           #+#    #+#             */
/*   Updated: 2024/07/23 19:17:34 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	validpathep(char **matrix, struct s_hw couple)
{
	int	j;
	int	i;

	j = 0;
	while (j < couple.height)
	{
		i = 0;
		while (i < couple.width)
		{
			if (matrix[j][i] == 'E')
			{
				if (!validpath_helperep(matrix, j, i, couple))
				{
					return (0);
				}
			}
			i++;
		}
		j++;
	}
	return (1);
}

char	**copymatrix(char **matrix, int height, int width)
{
	char	**newmatrix;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newmatrix = (char **)malloc((height + 1) * sizeof(char *));
	newmatrix[height] = NULL;
	while (j < height)
	{
		newmatrix[j] = (char *)malloc((width + 1) * sizeof(char));
		j++;
	}
	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			newmatrix[j][i] = matrix[j][i];
			i++;
		}
		newmatrix[j++][width] = '\0';
	}
	return (newmatrix);
}

int	widthoffile(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[0][i] != '\0')
	{
		i++;
	}
	return (i);
}

int	containschars(char	**matrix)
{
	if (containschar(matrix, '1')
		&& containschar(matrix, '0')
		&& containschar(matrix, 'E')
		&& containschar(matrix, 'K')
		&& containschar(matrix, 'P'))
		return (1);
	return (0);
}
