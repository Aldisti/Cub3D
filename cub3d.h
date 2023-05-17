/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:51:21 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/17 11:23:54 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define WIDTH 800
# define HEIGHT 600
# define SYMBOLS " 10NEWS"

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx/mlx.h"


typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_img
{
	void	*img;
	int		w;
	int		h;
}	t_img;

typedef struct s_pars
{
	const char	*path;
	char		*line;
	char		*ids[6];
	char		**mat;
	int			width;
	int			height;
	int			offset;
}	t_pars;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		z;
	int		move_x;
	int		move_y;
	int		rotate;
	int		bpp;
	int		line_length;
	int		endian;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	int		f[3];
	int		c[3];
	t_vect		pos;
	t_vect		dir;
	t_vect		cam;
	t_vect		ray;
	t_pars		pars;
}	t_game;

// Parser
// parser
int		ft_parser(t_game *game);
int		ft_getdim(t_pars *pars);
int		ft_getmat(t_pars *pars);
int		ft_get_info(t_game *g, t_pars *pars);
int		ft_get_color(t_game *game, const char type, const char *rgb);
// checker
int		ft_check_mat(t_pars *pars);
int		ft_check_info(t_game *game);
int		ft_check_num(const char *num);
int		ft_check_se(const char *s1, const char *s2);
int		ft_space_cmp(const char *s1, const char *s2);

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
void	ft_die(t_game *game);
int		ft_free(void **elem);
int		ft_free_mat(void ***mat);
// str
int		ft_atoi(const char *str);
void	ft_print_mat(char **mat);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// len
size_t	ft_strlen(char const *str);
size_t	ft_matlen(char const **mat);
// in
int		ft_in(char c, const char *chars);
// dup
char	*ft_strdup(char const *str);
// split
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t num, size_t dim);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
