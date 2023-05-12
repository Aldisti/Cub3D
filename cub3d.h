/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:51:21 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 16:22:33 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx/mlx.h"

typedef struct s_pars
{
	const char	*path;
	char		*line;
	char		*identifiers[6];
	char		**mat;
	int			width;
	int			height;
	int			offset;
}	t_pars;

// Parser
// parser
int		ft_parser(char *path);
int		ft_getmat(t_pars *pars);
// Utils
// get_next_line
char	*get_next_line(int fd);
// get_next_line_utils
int		ft_getnl(char *str);
int		ft_nlinstr(char *str);
char	*ft_get_first_str(char *buff);
void	ft_memmove_get(char *dst, char *src);
char	*ft_realloc_get(char *str, char *buff);
// free
void	ft_free(void **elem);
void	ft_free_mat(void ***mat);
// len
size_t	ft_strlen(char const *str);
size_t	ft_matlen(char const **mat);
// dup
char	*ft_strdup(char const *str);

#endif
