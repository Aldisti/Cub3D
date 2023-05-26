/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:09:47 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/26 16:24:00 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
s_c.x -> cos of alpha
s_c.y -> sin of alpha
*/
void	ft_draw_line(t_game *g)
{
	double	length;
	double	d[2];
	double	i;
	t_vect	s_c;

	g->pwd = (g->sdx - g->ddx) * (!g->side) + (g->sdy - g->ddy) * (g->side);
	d[0] = (g->ray.x * g->pwd) * BLOCK;
	d[1] = (g->ray.y * g->pwd) * BLOCK;
	length = sqrt(d[0] * d[0] + d[1] * d[1]);
	s_c.x = cos(atan(d[1] / d[0]) + M_PI * (d[0] < 0));
	s_c.y = sin(atan(d[1] / d[0]) + M_PI * (d[0] < 0));
	i = -1;
	while (++i < length)
		*(unsigned int *)((char *)(g->map.addr
					+ (((int)(g->pos.x * BLOCK + i * s_c.x))
						* (g->map.bpp / 8) + ((int)(g->pos.y * BLOCK + i
								* s_c.y)) * g->map.ll))) = MM_CV;
	return ;
}

int	ft_next_step_y(t_game game, t_game *g)
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
			game.posx = game.posx - game.stepx;
			// if (game.doors[(int) game.posy][(int) (game.posx - game.stepx)].type == 'o'
			// 		&& x < ft_gettime(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
			// 	return (1);
			// if (game.doors[(int) game.posy][(int) (game.posx - game.stepx)].type == 'c'
			// 		&& x > ft_gettime(game.doors[(int) game.posy][(int) (game.posx - game.stepx)].time) / (double) 1000)
			// 	return (1);
		}
	}
	else
	{
		game.pwd = game.sdy - game.ddy * (double) 3 / 2;
		x = game.ray.x * game.pwd + game.pos.x;
		x = (1 - (x - (int) x));
		game.posy = game.posy - game.stepy;
		// if (game.doors[(int) (game.posy - game.stepy)][(int) (game.posx)].type == 'o'
		// 		&& x < ft_gettime(game.doors[(int) (game.posy - game.stepy)][(int) (game.posx)].time) / (double) 1000)
		// 	return (1);
		// if (game.doors[(int) (game.posy - game.stepy)][(int) (game.posx)].type == 'c'
		// 		&& x > ft_gettime(game.doors[(int) (game.posy - game.stepy)][(int) (game.posx)].time) / (double) 1000)
		// 	return (1);
	}
	if (game.doors[(int) game.posy][(int) (game.posx)].type == 'o'
			&& x < ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000)
	{
		if (ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000 >= 1)
		{
			g->doors[(int) game.posy][(int) (game.posx)].time = -1;
			g->doors[(int) game.posy][(int) (game.posx)].type = 'O';
			g->pars.mat[(int) game.posy][(int) (game.posx)] = 'd';
		}
		return (1);
	}
	if (game.doors[(int) game.posy][(int) (game.posx)].type == 'c'
			&& x < 1 - ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000)
	{
		if (ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000 > 0.99f)
		{
			g->doors[(int) game.posy][(int) (game.posx)].time = -1;
			g->doors[(int) game.posy][(int) (game.posx)].type = 'C';
		}
		return (1);
	}
	return (0);
}

int	ft_next_step_x(t_game game, t_game *g)
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
			game.posy = game.posy - game.stepy;
		}
	}
	else
	{
		game.pwd = game.sdx - game.ddx * (double) 3 / 2;
		y = game.ray.y * game.pwd + game.pos.y;
		y = (1 - (y - (int) y));
		game.posx = game.posx - game.stepx;
	}
	if (game.doors[(int) game.posy][(int) (game.posx)].type == 'o'
			&& y < ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000)
	{
		if (ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000 >= 1)
		{
			g->doors[(int) game.posy][(int) (game.posx)].time = -1;
			g->doors[(int) game.posy][(int) (game.posx)].type = 'O';
			g->pars.mat[(int) game.posy][(int) (game.posx)] = 'd';
		}
		return (1);
	}
	if (game.doors[(int) game.posy][(int) (game.posx)].type == 'c'
			&& y < 1 - ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000)
	{
		if (ft_gettime(game.doors[(int) game.posy][(int) (game.posx)].time) / (double) 1000 > 0.99f)
		{
			g->doors[(int) game.posy][(int) (game.posx)].time = -1;
			g->doors[(int) game.posy][(int) (game.posx)].type = 'C';
		}
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
			if(ft_next_step_y(*g, g))
				continue ;
			else
				g->sdy += g->ddy / 2;
		}
		else if (ft_in(g->pars.mat[(int) g->posy][(int) g->posx], "D"))
		{
			if(ft_next_step_x(*g, g))
				continue ;
			else
				g->sdx += g->ddx / 2;
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

	if (game->pars.mat[(int) game->pos.y][(int)game->pos.x] == '1')
	{
		if (game->pos.y - (int)game->pos.y > 0.5f)
			game->pos.y = (int)game->pos.y + 1.5f;
		else
			game->pos.y = floor(game->pos.y) - 0.5f;
		if (game->pos.x - (int)game->pos.x > 0.5f)
			game->pos.x = (int)game->pos.x + 1.5f;
		else
			game->pos.x = floor(game->pos.x) - 0.5f;
	}
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
