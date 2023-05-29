/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:34:02 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/29 12:27:22 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_normalize(t_game *game)
{
	double	mod;

	mod = sqrtf(powf(game->ray.x, 2) + powf(game->ray.y, 2));
	game->ray.x /= mod;
	game->ray.y /= mod;
}

void	ft_draw(t_game *game)
{
	int		i;
	char	*fps;

	game->ot = ft_gettime(0);
	ft_set_minimap(game);
	i = -1;
	while (++i < WIDTH)
	{
		game->p = -1;
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
	game->ot = ft_gettime(game->ot);
	game->fps = 1000 / game->ot;
	fps = ft_itoa(game->fps);
	mlx_string_put(game->mlx, game->win, WIDTH - 30, 15, 0xFFFFFF, fps);
	ft_free((void **) &fps);
}

void	ft_set_draw_zone(t_game *game)
{
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
	if (game->p == -1)
		game->tex.texx = (int)(game->tex.wallx * (double) game->cur.w);
	else
		game->tex.texx = (int)((game->tex.wallx - game->p - 0.01f)
				* (double) game->cur.w);
	if ((game->side == 0 && game->ray.x < 0)
		|| (game->side == 1 && game->ray.y > 0))
		game->tex.texx = game->cur.w - game->tex.texx - 1;
	game->tex.step = game->cur.h / (float) game->lh;
	game->tex.texpos = (game->ds - HEIGHT / 2 + game->lh / 2) * game->tex.step;
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
		else if (n <= g->ds)
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
