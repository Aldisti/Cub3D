/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:59:55 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/29 12:18:20 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_step_y(t_game *game, t_game *g)
{
	double	x;
	double	y;

	if (!game->side)
	{
		game->pwd = game->sdx - game->ddx;
		y = game->ray.y * game->pwd + game->pos.y;
		y = (1 - (y - (int) y))
			* (((game->pos.y > (int)game->posy + 1) * 2) - 1);
		if (y < 0.5f * (((game->pos.y > (int)game->posy + 1) * 2) - 1))
			return (0);
		game->pwd = game->sdy - game->ddy / 2;
		x = game->ray.x * game->pwd + game->pos.x;
		x = (1 - (x - (int) x));
		game->posx = game->posx - game->stepx;
	}
	else
	{
		game->pwd = game->sdy - game->ddy * (double) 3 / 2;
		x = game->ray.x * game->pwd + game->pos.x;
		x = (1 - (x - (int) x));
		game->posy = game->posy - game->stepy;
	}
	return (2 * !ft_check_door_time(game, g, x));
}

int	ft_step_x(t_game *game, t_game *g)
{
	double	x;
	double	y;

	if (game->side)
	{
		game->pwd = game->sdy - game->ddy;
		x = game->ray.x * game->pwd + game->pos.x;
		x = (1 - (x - (int) x))
			* (((game->pos.x > (int)game->posx + 1) * 2) - 1);
		if (x < 0.5f * (((game->pos.x > (int)game->posx + 1) * 2) - 1))
			return (0);
		game->pwd = game->sdx - game->ddx / 2;
		y = game->ray.y * game->pwd + game->pos.y;
		y = (1 - (y - (int) y));
		game->posy = game->posy - game->stepy;
	}
	else
	{
		game->pwd = game->sdx - game->ddx * (double) 3 / 2;
		y = game->ray.y * game->pwd + game->pos.y;
		y = (1 - (y - (int) y));
		game->posx = game->posx - game->stepx;
	}
	return (1 * !ft_check_door_time(game, g, y));
}

int	ft_next_step(t_game game, t_game *g)
{
	int		n;

	if (game.sdx < game.sdy)
	{
		game.sdx += game.ddx;
		game.posx += game.stepx;
		game.side = 0;
	}
	else
	{
		game.sdy += game.ddy;
		game.posy += game.stepy;
		game.side = 1;
	}
	n = 0;
	if (g->side)
		n = ft_step_y(&game, g);
	else
		n = ft_step_x(&game, g);
	if (n)
		ft_reset_time(g, (int) game.posy, (int) game.posx);
	return (n);
}

int	ft_dda2(t_game *g)
{
	int	n;

	if (!ft_in(g->pars.mat[(int) g->posy][(int) g->posx], "D"))
	{
		g->p = -1;
		return (0);
	}
	if (g->doors[(int) g->posy][(int) g->posx].type == 'O')
		return (1);
	n = ft_next_step(*g, g);
	if (n == 1)
		g->sdx += g->ddx / 2;
	else if (n == 2)
		g->sdy += g->ddy / 2;
	else
		return (1);
	return (0);
}

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
		if (ft_dda2(g))
			continue ;
		if (ft_in(g->pars.mat[(int) g->posy][(int) g->posx], WALLS))
			g->hit = 1 + (g->pars.mat[(int) g->posy][(int) g->posx] == 'D');
	}
	ft_draw_line(g);
	return ;
}
