/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:31:19 by hshehab           #+#    #+#             */
/*   Updated: 2024/09/12 18:05:20 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

struct	s_hw
{
	int	width;
	int	height;
};

char	*get_next_line(int fd);
char	*read_from_file(int fd, char *buffer, int *size, int *pos);
char	*add_character(char c, char *res, int res_len);
size_t	read_from_file_new(int fd, char *buffer, int *new_size, int*pos);
int		count_str(char *s, char c);
int		count_letters(char *s, char c, int *i);
void	fill_matrix(char **matrix, char *s, char c);
char	**ft_split1(char *s, char c);
char	*ft_strjoin1(char *s1, char *c);
void	free_char_matrix(char **matrix);
void	printmatrix(char **matrix);
int		rectmatrix(char **matrix);
int		heightoffile(char *filename);
int		openfile(char *filename);
char	**maptomatrix(char *filename);
int		ft_strlen1(char *str);
int		widthoffile(char **matrix);
int		checkboarders(char **matrix, int height, int width);
void	validpath_helpercp(char **matrix, int row,
			int column, struct s_hw couple);
int		validpathcp(char **matrix, struct s_hw couple);
int		validpath_helperep(char **matrix, int row,
			int column, struct s_hw couple);
int		validpathep(char **matrix, struct s_hw couple);
int		validchars(char **matrix, int height, int width);
int		containschars(char	**matrix);
int		containschar(char **matrix, char c);
char	**copymatrix(char **matrix, int height, int width);
#endif
