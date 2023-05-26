/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:51:21 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/26 13:51:41 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define WIDTH 1000
# define HEIGHT 700
# define BLOCK 5

# define SYMBOLS " 10NEWSD"
# define WALLS "1D"

# define DR_CLS "images/door.xpm"

// errors
# define NO_MISS "missing or invalid image for the north side"
# define SO_MISS "missing or invalid image for the south side"
# define WE_MISS "missing or invalid image for the west side"
# define EA_MISS "missing or invalid image for the east side"
# define DR_MISS "missing or invalid door image"
# define PL_MISS "player position missig"
# define INV_COL "invalid colors"
# define INV_MAP "invalid map"
# define MAC_ERR "malloc error"
// colors
# define RED "\033[31m"
# define BLKRED "\033[5;31m"
# define RESET "\033[0;0;0m"
# define MM_BG 0x2c2c2c
# define MM_PC 0x00ff00
# define MM_WL 0xffffff
# define MM_CD 0xff0000
# define MM_OD 0x00ffff
# define MM_CV 0xf9f876

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "mlx/mlx.h"

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_door
{
	char	type;
	long	time;
}	t_door;

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		w;
	int		h;
	int		bpp;
	int		ll;
	int		endian;
}	t_img;

typedef struct s_pars
{
	const char		*path;
	char			*line;
	char			*ids[6];
	char			**mat;
	int				width;
	int				height;
	int				offset;
	struct s_game	*game;
}	t_pars;

typedef struct s_tex
{
	double	wallx;
	double	texpos;
	int		texx;
	int		texy;
	double	step;
}	t_tex;

typedef struct s_game
{
	t_door	**doors;
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	t_img	map;
	long	ot;
	int		fps;
	int		x;
	int		z;
	int		move_x;
	int		move_y;
	int		rotate;
	int		bpp;
	int		ll;
	int		endian;
	double	ddx;
	double	ddy;
	double	sdx;
	double	sdy;
	double	posx;
	double	posy;
	int		stepx;
	int		stepy;
	int		side;
	int		hit;
	double	pwd;
	int		lh;
	int		ds;
	int		de;
	t_img	cur;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_img	dr;
	int		f[3];
	int		c[3];
	t_vect	pos;
	t_vect	dir;
	t_vect	cam;
	t_vect	ray;
	t_pars	pars;
	t_tex	tex;
}	t_game;

int		ft_game(void *param);
// Game
// key_hook
void	ft_zoom(t_game *game);
void	ft_update_wall(t_game *game);
int		key_up(int keycode, void *param);
int		key_down(int keycode, void *param);
int		focus(void *param);
// mouse_hook
int		ft_mouse(int x, int y, void *param);
void	ft_rotate(t_game *game, int type, double rad);
// movement
void	ft_dda(t_game *g);
void	ft_move(t_game *game);
void	ft_prepare_dda(t_game *game);
void	ft_check_boundary(t_game *game);
// images
void	ft_draw(t_game *game);
void	ft_set_img(t_game *game);
void	ft_set_minimap(t_game *g);
void	ft_put_line(t_game *g, int i);
void	ft_set_draw_zone(t_game *game);

// Parser
// parser
int		ft_set_doors(t_game *g);
int		ft_parser(t_game *game);
int		ft_getdim(t_pars *pars);
int		ft_getmat(t_pars *pars);
// checker
int		ft_check_mat(t_pars *pars);
int		ft_check_info(t_game *game);
int		ft_check_num(const char *num);
int		ft_check_se(const char *s1, const char *s2);
int		ft_space_cmp(const char *s1, const char *s2);
// get_info
void	ft_get_data(t_game *game);
void	ft_get_pos(t_game *game, int y);
int		ft_check_door(t_pars *pars, int j);
int		ft_get_info(t_game *g, t_pars *pars);
int		ft_get_color(t_game *game, const char type, const char *rgb);
// init
void	ft_init(t_game *game);
void	ft_init_pars(t_game *game);

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
int		ft_error(char *str, int code);
int		ft_close(void *param);
// str
int		ft_atoi(const char *str);
void	ft_print_mat(char **mat);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// len
size_t	ft_strlen(char const *str);
size_t	ft_matlen(char const **mat);
// in
int		ft_count(char c, char *str);
int		ft_in(char c, const char *chars);
// dup
char	*ft_strdup(char const *str);
// split
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t num, size_t dim);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// mlx_wrap
int		create_trgb(int t, int r, int g, int b);
void	*ft_xpm(void *mlx, char *str, int *w, int *h);
// time
long	ft_gettime(long time);
// itoa
char	*ft_itoa(int n);

#endif
