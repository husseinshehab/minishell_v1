/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildtree3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:24:16 by hshehab           #+#    #+#             */
/*   Updated: 2024/08/20 16:41:36 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_rows(char **matrix)
{
	int	count;

	count = 0;
	while (matrix[count] != NULL)
		count++;
	return (count);
}

char	**copymatrix1(char **oldmatrix)
{
	int		num_rows;
	char	**newmatrix;
	int		i;
	int		length;

	if (oldmatrix == NULL)
		return (NULL);
	num_rows = count_rows(oldmatrix);
	newmatrix = (char **)malloc(sizeof(char *) * (num_rows + 1));
	if (newmatrix == NULL)
		return (NULL);
	i = 0;
	while (i < num_rows)
	{
		length = strlen(oldmatrix[i]) + 1;
		newmatrix[i] = (char *)malloc(length * sizeof(char));
		strcpy(newmatrix[i], oldmatrix[i]);
		i++;
	}
	newmatrix[num_rows] = NULL;
	return (newmatrix);
}


void	freematrix(char **matrix)
{
	int	i;

	if (matrix != NULL)
	{
		i = 0;
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	leftordertraversal(t_treenode *root)
{
	if (root == NULL)
		return ;
	printf("%d\n", root->type);
	printmatrix(root->value);
	leftordertraversal(root->left);
	leftordertraversal(root->right);
}

void	free_tree(t_treenode *root)
{
	if (root == NULL)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->value != NULL)
	{
		free_char_matrix(root->value);
	}
	free(root);
}
