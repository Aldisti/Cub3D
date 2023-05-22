/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:34:02 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/22 22:14:42 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw(t_game *game)
{
	int	i;

	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp,
			&game->ll, &game->endian);
	ft_set_minimap(game);
	i = -1;
	while (++i < WIDTH)
	{
		game->ray.x = game->dir.x + game->cam.x * (2 * i / (double) WIDTH - 1);
		game->ray.y = game->dir.y + game->cam.y * (2 * i / (double) WIDTH - 1);
		ft_prepare_dda(game);
		ft_dda(game);
		ft_set_draw_zone(game);
		ft_set_img(game);
		ft_put_line(game, i);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->map.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
	return ;
}

void	ft_set_draw_zone(t_game *game)
{
	if (!game->side)
		game->pwd = game->sdx - game->ddx;
	else
		game->pwd = game->sdy - game->ddy;
	game->lh = (int)(game->z * HEIGHT / game->pwd);
	game->ds = HEIGHT / 2 - game->lh / 2;
	if (game->ds < 0)
		game->ds = 0;
	game->de = HEIGHT / 2 + game->lh / 2;
	if (game->de >= HEIGHT)
		game->de = HEIGHT - 1;
	return ;
}

void	ft_set_img(t_game *game)
{
	if (!game->side)
		game->tex.wallx = game->pos.y + game->pwd * game->ray.y;
	else
		game->tex.wallx = game->pos.x + game->pwd * game->ray.x;
	game->tex.wallx -= floor(game->tex.wallx);
	if (game->hit == 2)
		game->cur = game->dr;
	else if (game->side == 0 && game->ray.x < 0)
		game->cur = game->ea;
	else if (game->side == 0 && game->ray.x > 0)
		game->cur = game->we;
	else if (game->side == 1 && game->ray.y < 0)
		game->cur = game->no;
	else if (game->side == 1 && game->ray.y > 0)
		game->cur = game->so;
	game->tex.texx = (int)(game->tex.wallx * (double) game->cur.w);
	if ((game->side == 0 && game->ray.x < 0)
		|| (game->side == 1 && game->ray.y > 0))
		game->tex.texx = game->cur.w - game->tex.texx - 1;
	game->tex.step = game->cur.h / (float) game->lh;
	game->tex.texpos = (game->ds - HEIGHT / 2 + game->lh / 2) * game->tex.step;
	return ;
}

void	ft_put_line(t_game *g, int i)
{
	char	*dst;
	int		n;

	n = -1;
	while (++n < HEIGHT)
	{
		if (n >= g->ds && n <= g->de)
		{
			g->tex.texy = (int) g->tex.texpos;
			g->tex.texpos += g->tex.step;
			dst = g->addr + (i * (g->bpp / 8) + n * g->ll);
			*(unsigned int *)dst = *(unsigned int *)(g->cur.addr + (g->tex.texx
						* (g->cur.bpp / 8) + g->tex.texy * g->cur.ll));
		}
		else if (n < g->ds)
		{
			dst = g->addr + (i * (g->bpp / 8) + n * g->ll);
			*(unsigned int *)dst = create_trgb(1, g->c[0], g->c[1], g->c[2]);
		}
		else if (n >= g->de)
		{
			dst = g->addr + (i * (g->bpp / 8) + n * g->ll);
			*(unsigned int *)dst = create_trgb(1, g->f[0], g->f[1], g->f[2]);
		}
	}
}

void	ft_set_minimap(t_game *game)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			dst = game->map.addr + (j * (game->map.bpp / 8) + i * game->map.ll);
			*(unsigned int *)dst = 0x2c2c2c;
			if (game->pars.mat[i / BLOCK][j / BLOCK] == 49)
				*(unsigned int *)dst = MM_WL;
			else if (game->pars.mat[i / BLOCK][j / BLOCK] == 'D')
				*(unsigned int *)dst = MM_CD;
			else if (game->pars.mat[i / BLOCK][j / BLOCK] == 'd')
				*(unsigned int *)dst = MM_OD;
			else if (powf((game->pos.x * 5 - j), 2)
				+ powf((game->pos.y * 5 - i), 2) <= powf(2.5f, 2))
				*(unsigned int *)dst = MM_PC;
		}
	}
}
