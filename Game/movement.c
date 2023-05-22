/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:09:47 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/22 22:20:03 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_point(t_game *game, double x, double y)
{
	if ((int)x >= game->map.w || (int)y >= game->map.h)
		return ;
	// *(unsigned int *)((char *)(game->map.addr + (((int)x)
	// 				* (game->map.bpp / 8) + ((int)y) * game->map.ll)))
	// 	= MM_BG;
	int	i;
	int	j;

	j = -1;
	while (++j < BLOCK)
	{
		i = -1;
		while (++i < BLOCK)
		{
			if ((int)x + i >= game->map.w - 5 || (int)y + j >= game->map.h - 5)
				continue ;
			*(unsigned int *)((char *)(game->map.addr + (((int)x + i)
					* (game->map.bpp / 8) + ((int)y + j) * game->map.ll)))
				= MM_BG;
		}
	}
}

void	ft_draw_line(t_game *g)
{
	double	i;
	double	d[2];
	double	length;
	double	alpha;
	t_vect	n_p;

	d[0] = (g->posx - g->pos.x) * BLOCK;
	d[1] = (g->posy - g->pos.y) * BLOCK;
	length = sqrt(d[0] * d[0] + d[1] * d[1]);
	alpha = atan(d[1] / d[0]);
	if (d[0] < 0)
		alpha += M_PI;
	i = -1;
	while (++i < length)
	{
		n_p.x = g->pos.x * BLOCK + i * cos(alpha);
		n_p.y = g->pos.y * BLOCK + i * sin(alpha);
		// ft_draw_point(g, n_p.x, n_p.y);
		*(unsigned int *)((char *)(g->map.addr + (((int)n_p.x)
					* (g->map.bpp / 8) + ((int)n_p.y) * g->map.ll)))
			= MM_BG;
		i++;
	}
}

void	ft_dda(t_game *g)
{
	g->hit = 0;
	g->posx = g->pos.x;
	g->posy = g->pos.y;
	while (!g->hit)
	{
		// if (g->posx != g->pos.x || g->posy != g->pos.y)
		// 	ft_draw_point(g, g->posx, g->posy);
		if (g->sdx < g->sdy)
		{
			g->sdx += g->ddx;
			g->posx += g->stepx;
			g->side = 0;
		}
		else
		{
			g->sdy += g->ddy;
			g->posy += g->stepy;
			g->side = 1;
		}
		if (ft_in(g->pars.mat[(int) g->posy][(int) g->posx], WALLS))
			g->hit = 1 + (g->pars.mat[(int) g->posy][(int) g->posx] == 'D');
	}
	ft_draw_line(g);
	return ;
}

void	ft_prepare_dda(t_game *game)
{
	game->ddx = 1e30;
	game->ddy = 1e30;
	if (game->ray.x != 0)
		game->ddx = fabs(1 / game->ray.x);
	if (game->ray.y != 0)
		game->ddy = fabs(1 / game->ray.y);
	game->stepx = -1;
	game->stepy = -1;
	if (game->ray.x < 0)
		game->sdx = (game->pos.x - (int) game->pos.x) * game->ddx;
	else
	{
		game->stepx = 1;
		game->sdx = (1.0f + (int) game->pos.x - game->pos.x) * game->ddx;
	}
	if (game->ray.y < 0)
		game->sdy = (game->pos.y - (int) game->pos.y) * game->ddy;
	else
	{
		game->stepy = 1;
		game->sdy = (1.0f + (int) game->pos.y - game->pos.y) * game->ddy;
	}
	return ;
}

void	ft_check_boundary(t_game *game)
{
	if (ft_in(game->pars.mat[(int) game->pos.y][(int)game->pos.x + 1], WALLS)
			&& game->pos.x > (int)game->pos.x + 1 - 0.25f)
		game->pos.x = (int)game->pos.x + 1 - 0.25f;
	if (ft_in(game->pars.mat[(int) game->pos.y][(int)game->pos.x - 1], WALLS)
			&& game->pos.x < (int)game->pos.x + 0.25f)
		game->pos.x = (int)game->pos.x + 0.25f;
	if (ft_in(game->pars.mat[(int) game->pos.y + 1][(int)game->pos.x], WALLS)
			&& game->pos.y > (int)game->pos.y + 1 - 0.25f)
		game->pos.y = (int)game->pos.y + 1 - 0.25f;
	if (ft_in(game->pars.mat[(int) game->pos.y - 1][(int)game->pos.x], WALLS)
			&& game->pos.y < (int)game->pos.y + 0.25f)
		game->pos.y = (int)game->pos.y + 0.25f;
	return ;
}

void	ft_move(t_game *game)
{
	if (game->move_x == 1)
	{
		game->pos.x += ((-1) * game->dir.y * 0.05);
		game->pos.y += (game->dir.x * 0.05);
	}
	if (game->move_x == -1)
	{
		game->pos.x += (game->dir.y * 0.05);
		game->pos.y += ((-1) * game->dir.x * 0.05);
	}
	if (game->move_y == 1)
	{
		game->pos.y += (game->dir.y * 0.05);
		game->pos.x += (game->dir.x * 0.05);
	}
	if (game->move_y == -1)
	{
		game->pos.y += ((-1) * game->dir.y * 0.05);
		game->pos.x += ((-1) * game->dir.x * 0.05);
	}
	ft_check_boundary(game);
	return ;
}
