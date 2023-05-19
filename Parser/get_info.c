/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:23:53 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/19 17:18:37 by adi-stef         ###   ########.fr       */
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
	if (game->pars.mat[y][i] == 'N' && --game->dir.y)
		game->cam.x = 0.66;
	else if (game->pars.mat[y][i] == 'S' && ++game->dir.y)
		game->cam.x = -0.66;
	else if (game->pars.mat[y][i] == 'E' && ++game->dir.x)
		game->cam.y = 0.66;
	else if (game->pars.mat[y][i] == 'W' && --game->dir.x)
		game->cam.y = -0.66;
	return ;
}

void	ft_get_data(t_game *game)
{
	if (game->no.img)
		game->no.addr = mlx_get_data_addr(game->no.img, &game->no.bpp,
				&game->no.ll, &game->no.endian);
	if (game->so.img)
		game->so.addr = mlx_get_data_addr(game->so.img, &game->so.bpp,
				&game->so.ll, &game->so.endian);
	if (game->we.img)
		game->we.addr = mlx_get_data_addr(game->we.img, &game->we.bpp,
				&game->we.ll, &game->we.endian);
	if (game->ea.img)
		game->ea.addr = mlx_get_data_addr(game->ea.img, &game->ea.bpp,
				&game->ea.ll, &game->ea.endian);
	game->dr.img = ft_xpm(game->mlx, DR_CLS, &game->dr.w, &game->dr.h);
	if (game->dr.img)
		game->dr.addr = mlx_get_data_addr(game->dr.img, &game->dr.bpp,
				&game->dr.ll, &game->dr.endian);
	return ;
}

int	ft_get_color(t_game *game, const char type, const char *rgb)
{
	char	**tmp;
	int		i;

	if (!rgb || !rgb[0])
		return (0);
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
	ft_get_data(pars->game);
	return (0);
}

int	ft_check_door(t_pars *pars, int j)
{
	char	tmp[5];
	int		i;

	i = 0;
	while (pars->mat[j][i] && !ft_in(pars->mat[j][i], "Dd"))
		i++;
	if (!pars->mat[j][i])
		return (0);
	tmp[0] = pars->mat[j][i - 1];
	tmp[1] = pars->mat[j][i + 1];
	tmp[2] = pars->mat[j - 1][i];
	tmp[3] = pars->mat[j + 1][i];
	tmp[4] = 0;
	if (ft_count(49, tmp) < 2)
		return (1);
	if ((ft_in(tmp[0], "1") && ft_in(tmp[1], "1"))
		|| (ft_in(tmp[2], "1") && ft_in(tmp[3], "1")))
		return (0);
	return (1);
}
