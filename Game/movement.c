/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:09:47 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/18 18:12:31 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	// bisogna ridisegnare la mappa
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

