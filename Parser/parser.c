/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:56:51 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/27 11:50:26 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_set_doors(t_game *g)
{
	int	i;
	int	j;

	g->doors = (t_door **)ft_calloc(g->pars.height + 1, sizeof(t_door *));
	if (!g->doors)
		return (1);
	i = -1;
	while (++i < g->pars.height)
	{
		g->doors[i] = (t_door *)ft_calloc(g->pars.width + 1, sizeof(t_door));
		if (!g->doors[i])
			return (1);
		j = -1;
		while (++j < g->pars.width)
		{
			g->doors[i][j].type = 'C' * (g->pars.mat[i][j] == 'D');
			g->doors[i][j].time = -1;
		}
	}
	return (0);
}

int	ft_getdim(t_pars *pars)
{
	int	fd;
	int	i;

	fd = open(pars->path, O_RDONLY);
	i = 0;
	while (42)
	{
		ft_free((void **)&pars->line);
		pars->line = get_next_line(fd);
		if (!pars->line)
			break ;
		if (pars->line[0] == 10 && ++pars->offset)
			continue ;
		if (i == 6 && (int)ft_strlen(pars->line) > pars->width)
			pars->width = ft_strlen(pars->line)
				- (pars->line[ft_strlen(pars->line)] == 10);
		if ((i == 6 && ++pars->height) || !(++pars->offset))
			continue ;
		pars->ids[i++] = pars->line;
		pars->line = NULL;
		pars->ids[i - 1][ft_strlen(pars->ids[i - 1]) - 1]
			*= !(pars->ids[i - 1][ft_strlen(pars->ids[i - 1]) - 1] == 10);
	}
	close(fd);
	return (0);
}

int	ft_getmat(t_pars *pars)
{
	int	fd;
	int	i;

	pars->mat = (char **)ft_calloc((pars->height + 1), sizeof(char *));
	if (!pars->mat)
		return (1);
	i = 0;
	fd = open(pars->path, O_RDONLY);
	while (42)
	{
		ft_free((void **)&pars->line);
		pars->line = get_next_line(fd);
		if (!pars->line)
			break ;
		if (pars->offset-- > 0)
			continue ;
		if (pars->line[ft_strlen(pars->line) - 1] == 10)
			pars->line[ft_strlen(pars->line) - 1] = 0;
		pars->mat[i++] = pars->line;
		pars->line = NULL;
	}
	pars->mat[i] = 0;
	close(fd);
	return (0);
}

int	ft_parser(t_game *game)
{
	int	len;

	len = ft_strlen(game->pars.path);
	if (len < 5 || game->pars.path[len - 1] != 'b'
		|| game->pars.path[len - 2] != 'u' || game->pars.path[len - 3] != 'c'
		|| game->pars.path[len - 4] != '.')
		return (ft_error(INV_MAP, 1));
	if (ft_getdim(&game->pars) || game->pars.height <= 2)
		return (ft_error(INV_MAP, 1));
	if (ft_getmat(&game->pars))
		return (ft_error(INV_MAP, 1));
	if (ft_check_mat(&game->pars))
		return (ft_error(INV_MAP, 1));
	if (ft_get_info(game, &game->pars))
		return (ft_error(INV_COL, 1));
	if (ft_check_info(game))
		return (1);
	if (ft_set_doors(game))
		return (ft_error(MAC_ERR, 1));
	game->map.w = (game->pars.width - 1) * BLOCK;
	game->map.h = game->pars.height * BLOCK;
	game->map.img = mlx_new_image(game->mlx, game->map.w, game->map.h);
	game->map.addr = mlx_get_data_addr(game->map.img, &game->map.bpp,
			&game->map.ll, &game->map.endian);
	return (0);
}
