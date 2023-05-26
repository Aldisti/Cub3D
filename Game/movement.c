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

int	ft_next_step_y(t_game game)
{
	double	x;
	double	y;

	if (game.doors[(int) game.posy][(int) game.posx].type == 'O')
		return (1);
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
	if (!game.side)
	{
		game.pwd = game.sdx - game.ddx;
		y = game.ray.y * game.pwd + game.pos.y;
		y = (1 - (y - (int) y)) * (((game.pos.y > (int)game.posy + 1) * 2) - 1);
		if (y < 0.5f * (((game.pos.y > (int)game.posy + 1) * 2) - 1))
		//if ((game.ray.y / game.ray.x) * (game.pos.x - ((int) game.posx + (game.posx <= game.pos.x)))
		//		- (game.pos.y - (int)game.posy - 1) > 0.5f)
			return (1);
		else
		{
			game.pwd = game.sdy - game.ddy / 2;
			x = game.ray.x * game.pwd + game.pos.x;
			x = (1 - (x - (int) x));
			if (game.doors[(int) game.posy][(int) (game.posx - game.stepx)].type == 'o'
					&& x < ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
				return (1);
			if (game.doors[(int) game.posy][(int) (game.posx - game.stepx)].type == 'c'
					&& x > ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
				return (1);
		}
	}
	else
	{
		game.pwd = game.sdy - game.ddy * (double) 3 / 2;
		x = game.ray.x * game.pwd + game.pos.x;
		x = (1 - (x - (int) x));
		if (game.doors[(int) game.posy - game.stepy][(int) (game.posx)].type == 'o'
				&& x < ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
			return (1);
		if (game.doors[(int) game.posy - game.stepy][(int) (game.posx)].type == 'c'
				&& x > ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
			return (1);
	}	
	return (0);
}

int	ft_next_step_x(t_game game)
{
	double	x;
	double	y;

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
	if (game.side)
	{
		game.pwd = game.sdy - game.ddy;
		x = game.ray.x * game.pwd + game.pos.x;
		x = (1 - (x - (int) x)) * (((game.pos.x > (int)game.posx + 1) * 2) - 1);
		if (x < 0.5f * (((game.pos.x > (int)game.posx + 1) * 2) - 1))
			return (1);
		else
		{
			game.pwd = game.sdx - game.ddx / 2;
			y = game.ray.y * game.pwd + game.pos.y;
			y = (1 - (y - (int) y));
			if (game.doors[(int) game.posy - game.stepy][(int) (game.posx)].type == 'o'
					&& y < ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
				return (1);
			if (game.doors[(int) game.posy - game.stepy][(int) (game.posx)].type == 'c'
					&& y > ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
				return (1);
		}
	}
	else
	{
		game.pwd = game.sdx - game.ddx * (double) 3 / 2;
		y = game.ray.y * game.pwd + game.pos.y;
		y = (1 - (y - (int) y));
		if (game.doors[(int) game.posy][(int) (game.posx - game.stepx)].type == 'o'
				&& y < ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
			return (1);
		if (game.doors[(int) game.posy][(int) (game.posx - game.stepx)].type == 'c'
				&& y > ft_get_time(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
			return (1);
	}
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
		if (g->side && ft_in(g->pars.mat[(int) g->posy][(int) g->posx], "D"))
		{
			if(ft_next_step_y(*g))
				continue ;
			else
				g->sdy += g->ddy / 2;
		}
		else if (ft_in(g->pars.mat[(int) g->posy][(int) g->posx], "D"))
		{
			if(ft_next_step_x(*g))
				continue ;
			else
				g->sdx += g->ddx / 2;
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
