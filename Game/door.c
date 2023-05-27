/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:25:12 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/27 11:48:34 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_update_door(t_game *game, int y, int x)
{
	long	t;
	long	t_0;

	t = ft_gettime(0);
	t_0 = game->doors[y][x].time;
	game->doors[y][x].time = 2 * t - t_0 - 1000;
	if (game->doors[y][x].type == 'C')
	{
		game->doors[y][x].type = 'o';
		game->doors[y][x].time = t;
	}
	else if (game->doors[y][x].type == 'c')
		game->doors[y][x].type = 'o';
	else if (game->doors[y][x].type == 'O')
	{
		game->pars.mat[y][x] = 'D';
		game->doors[y][x].type = 'c';
		game->doors[y][x].time = t;
	}
	else if (game->doors[y][x].type == 'o')
		game->doors[y][x].type = 'c';
}

void	ft_reset_time(t_game *g, int i, int j)
{
	if (ft_gettime(g->doors[i][j].time) / (double) 1000 > 0.99f
		&& g->doors[i][j].type == 'c')
	{
		g->doors[i][j].time = -1;
		g->doors[i][j].type = 'C';
	}
	else if (ft_gettime(g->doors[i][j].time) / (double) 1000 > 1
		&& g->doors[i][j].type == 'o')
	{
		g->doors[i][j].time = -1;
		g->doors[i][j].type = 'O';
		g->pars.mat[i][j] = 'd';
	}
}

void	ft_check_time(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g->pars.height)
	{
		j = -1;
		while (++j < g->pars.width)
			if (g->doors[i][j].type)
				ft_reset_time(g, i, j);
	}
}

void	ft_set_minimap(t_game *g)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	while (++i < g->map.h)
	{
		j = -1;
		while (++j < g->map.w)
		{
			dst = g->map.addr + (j * (g->map.bpp / 8) + i * g->map.ll);
			*(unsigned int *)dst = MM_BG;
			if (g->pars.mat[(int)(i / BLOCK)][(int)(j / BLOCK)] == 49)
				*(unsigned int *)dst = MM_WL;
			else if (g->pars.mat[(int)(i / BLOCK)][(int)(j / BLOCK)] == 'D')
				*(unsigned int *)dst = MM_CD;
			else if (g->pars.mat[(int)(i / BLOCK)][(int)(j / BLOCK)] == 'd')
				*(unsigned int *)dst = MM_OD;
			else if (powf((g->pos.x * BLOCK - j), 2)
				+ powf((g->pos.y * BLOCK - i), 2) <= 6.25f)
				*(unsigned int *)dst = MM_PC;
		}
	}
}
