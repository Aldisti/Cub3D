/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:56:03 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/19 12:15:06 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
type [1] [-1]
*/
void	ft_rotate(t_game *game, int type, double rad)
{
	double	dir_x;
	double	dir_y;
	double	cam_x;
	double	cam_y;

	dir_x = game->dir.x;
	dir_y = game->dir.y;
	cam_x = game->cam.x;
	cam_y = game->cam.y;
	game->dir.x = dir_x * cos(rad) + (-type) * dir_y * sin(rad);
	game->dir.y = (type) * dir_x * sin(rad) + dir_y * cos(rad);
	game->cam.x = cam_x * cos(rad) + (-type) * cam_y * sin(rad);
	game->cam.y = (type) * cam_x * sin(rad) + cam_y * cos(rad);
	return ;
}

int	ft_mouse(int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	(void) y;
	mlx_mouse_hide(game->mlx, game->win);
	if (x > game->x)
		ft_rotate(game, 1, 2 * M_PI / (double) WIDTH);
	else if (x < game->x)
		ft_rotate(game, -1, 2 * M_PI / (double) WIDTH);
	game->x = x;
	ft_draw(game);
	return (0);
}
