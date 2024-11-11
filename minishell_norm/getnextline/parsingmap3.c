/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:48:27 by hshehab           #+#    #+#             */
/*   Updated: 2024/07/23 19:17:21 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	validchars(char **matrix, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < height)
	{
		while (i < width)
		{
			if (matrix[j][i] != '1' && matrix[j][i] != '0'
				&& matrix[j][i] != 'P' && matrix[j][i] != 'C'
				&& matrix[j][i] != 'E' && matrix[j][i] != 'K')
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

void	validpath_helpercp(char **matrix, int row, int column,
						struct s_hw couple)
{
	if (row < 0 || row >= couple.height || column < 0 || column >= couple.width
		|| matrix[row][column] == '1' || matrix[row][column] == 'V')
	{
		return ;
	}
	matrix[row][column] = 'V';
	validpath_helpercp(matrix, row + 1, column, couple);
	validpath_helpercp(matrix, row, column + 1, couple);
	validpath_helpercp(matrix, row - 1, column, couple);
	validpath_helpercp(matrix, row, column - 1, couple);
	return ;
}

int	validpath_helperep(char **matrix, int row, int column, struct s_hw couple)
{
	char	temp;
	int		found;

	if (row < 0 || row >= couple.height || column < 0 || column >= couple.width
		|| matrix[row][column] == '1' || matrix[row][column] == 'F')
		return (0);
	if (matrix[row][column] == 'P')
		return (1);
	temp = matrix[row][column];
	matrix[row][column] = 'F';
	found = (validpath_helperep(matrix, row + 1, column, couple)
			|| validpath_helperep(matrix, row, column + 1, couple)
			|| validpath_helperep(matrix, row - 1, column, couple)
			|| validpath_helperep(matrix, row, column - 1, couple));
	matrix[row][column] = temp;
	return (found);
}

int	checkc(char **matrix, int height, int width)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			if (matrix[j][i] == 'C')
			{
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	validpathcp(char **matrix, struct s_hw couple)
{
	int		j;
	int		i;
	char	**newmatrix;

	newmatrix = copymatrix(matrix, couple.height, couple.width);
	j = -1;
	while (++j <= couple.height)
	{
		i = -1;
		while (++i <= couple.width)
		{
			if (newmatrix[j][i] == 'P')
			{
				validpath_helpercp(newmatrix, j, i, couple);
				if (!checkc(newmatrix, couple.height, couple.width))
				{
					free_char_matrix(newmatrix);
					return (0);
				}
				free_char_matrix(newmatrix);
				return (1);
			}
		}
	}
	return (0);
}
