/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:09:47 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/22 16:08:45 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_dda(t_game *g)
{
	g->hit = 0;
	g->posx = g->pos.x;
	g->posy = g->pos.y;
	while (!g->hit)
	{
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
			&& game->pos.x > (int)game->pos.x + 1 - 0.50f)
		game->pos.x = (int)game->pos.x + 1 - 0.50f;
	if (ft_in(game->pars.mat[(int) game->pos.y][(int)game->pos.x - 1], WALLS)
			&& game->pos.x < (int)game->pos.x + 0.50f)
		game->pos.x = (int)game->pos.x + 0.50f;
	if (ft_in(game->pars.mat[(int) game->pos.y + 1][(int)game->pos.x], WALLS)
			&& game->pos.y > (int)game->pos.y + 1 - 0.50f)
		game->pos.y = (int)game->pos.y + 1 - 0.50f;
	if (ft_in(game->pars.mat[(int) game->pos.y - 1][(int)game->pos.x], WALLS)
			&& game->pos.y < (int)game->pos.y + 0.50f)
		game->pos.y = (int)game->pos.y + 0.50f;
	return ;
}

void	ft_move(t_game *game)
{
	if (game->move_x == 1)
	{
		game->pos.x += ((-1) * game->dir.y * 5.0f / game->fps);
		game->pos.y += (game->dir.x * 5.0f / game->fps);
	}
	if (game->move_x == -1)
	{
		game->pos.x += (game->dir.y * 5.0f / game->fps);
		game->pos.y += ((-1) * game->dir.x * 5.0f / game->fps);
	}
	if (game->move_y == 1)
	{
		game->pos.y += (game->dir.y * 5.0f / game->fps);
		game->pos.x += (game->dir.x * 5.0f / game->fps);
	}
	if (game->move_y == -1)
	{
		game->pos.y += ((-1) * game->dir.y * 5.0f / game->fps);
		game->pos.x += ((-1) * game->dir.x * 5.0f / game->fps);
	}
	ft_check_boundary(game);
	return ;
}
