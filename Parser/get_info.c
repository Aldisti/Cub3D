/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:23:53 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/17 12:01:23 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
/*
NORD
x: 0 y: -1
x: 0.66 y:0
SUD
x: 0 y: 1
x: -0.66 y: 0
EAST
x: 1 y: 0
x: 0 y: 0.66
WEST
x: -1 y: 0
x: 0 y: -0.66
*/
void	ft_get_pos(t_game *game, int y)
{
	int	i;

	i = 0;
	while (game->pars.mat[y][i] && !ft_in(game->pars.mat[y][i], "NEWS"))
		i++;
	if (!game->pars.mat[y][i] || (game->pos.x != -1 && game->pos.y != -1))
		return ;
	game->pos.x = (float)i + 0.5f;
	game->pos.y = (float)y + 0.5f;
	if (game->pars.mat[y][i] == 'N')
	{
		game->dir.y = -1;
		game->cam.x = 0.66;
	}
	else if (game->pars.mat[y][i] == 'S')
	{
		game->dir.y = 1;
		game->cam.x = -0.66;
	}
	else if (game->pars.mat[y][i] == 'E')
	{
		game->dir.x = 1;
		game->cam.y = 0.66;
	}
	else if (game->pars.mat[y][i] == 'W')
	{
		game->dir.x = -1;
		game->cam.y = -0.66;
	}
	printf("posX: %f - posY: %f - dirX: %f - dirY: %f\n", game->pos.x, game->pos.y, game->dir.x, game->dir.y);
	return ;
}

int	ft_get_color(t_game *game, const char type, const char *rgb)
{
	char	**tmp;
	int		i;

	tmp = ft_split(rgb, ',');
	i = 0;
	while (tmp[i])
		if (ft_check_num(tmp[i++]))
			return (ft_free_mat((void ***)&tmp) + 1);
	if (i != 3)
		return (ft_free_mat((void ***)&tmp) + 1);
	i = -1;
	if (type == 'F')
		while (++i < 3)
			game->f[i] = ft_atoi(tmp[i]);
	else if (type == 'C')
		while (++i < 3)
			game->c[i] = ft_atoi(tmp[i]);
	return (ft_free_mat((void ***)&tmp));
}

int	ft_get_info(t_game *g, t_pars *pars)
{
	char	**tmp;
	int		i;

	i = -1;
	while (++i < 6)
	{
		tmp = ft_split(pars->ids[i], 32);
		if (!tmp)
			exit(110);
		if (!ft_strncmp(tmp[0], "NO", 3))
			g->no.img = ft_xpm(g->mlx, tmp[1], &g->no.w, &g->no.h);
		else if (!ft_strncmp(tmp[0], "SO", 3))
			g->so.img = ft_xpm(g->mlx, tmp[1], &g->so.w, &g->so.h);
		else if (!ft_strncmp(tmp[0], "WE", 3))
			g->we.img = ft_xpm(g->mlx, tmp[1], &g->we.w, &g->we.h);
		else if (!ft_strncmp(tmp[0], "EA", 3))
			g->ea.img = ft_xpm(g->mlx, tmp[1], &g->ea.w, &g->ea.h);
		else if ((!ft_strncmp(tmp[0], "F", 2) || !ft_strncmp(tmp[0], "C", 2))
			&& ft_get_color(g, tmp[0][0], tmp[1]))
			return (ft_free_mat((void ***)&tmp) + 1);
		ft_free_mat((void ***)&tmp);
	}
	return (0);
}
