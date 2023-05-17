/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:14:19 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/17 11:01:40 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_pars(t_game *game)
{
	int	i;

	game->pars.game = game;
	game->pars.line = NULL;
	game->pars.mat = NULL;
	game->pars.width = 0;
	game->pars.height = 0;
	game->pars.offset = 0;
	i = 0;
	while (i < 6)
		game->pars.ids[i++] = NULL;
	return ;
}

void	ft_init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->no.img = NULL;
	game->so.img = NULL;
	game->we.img = NULL;
	game->ea.img = NULL;
	game->no.w = 0;
	game->no.h = 0;
	game->so.w = 0;
	game->so.h = 0;
	game->we.w = 0;
	game->we.h = 0;
	game->ea.w = 0;
	game->ea.h = 0;
	game->pos.x = -1;
	game->pos.y = -1;
	game->dir.x = 0;
	game->dir.y = 0;
	ft_init_pars(game);
	return ;
}