/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:49:28 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/19 14:37:06 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_zoom(t_game *game)
{
	game->cam.x /= 8;
	game->cam.y /= 8;
	game->z = 16;
	ft_draw(game);
	return ;
}

void	ft_update_wall(t_game *game)
{
	if (game->pars.mat[(int) game->pos.y + 1][(int) game->pos.x] == 'D')
		game->pars.mat[(int) game->pos.y + 1][(int) game->pos.x] = 'd';
	else if (game->pars.mat[(int) game->pos.y + 1][(int) game->pos.x] == 'd')
		game->pars.mat[(int) game->pos.y + 1][(int) game->pos.x] = 'D';
	if (game->pars.mat[(int) game->pos.y - 1][(int) game->pos.x] == 'D')
		game->pars.mat[(int) game->pos.y - 1][(int) game->pos.x] = 'd';
	else if (game->pars.mat[(int) game->pos.y - 1][(int) game->pos.x] == 'd')
		game->pars.mat[(int) game->pos.y - 1][(int) game->pos.x] = 'D';
	if (game->pars.mat[(int) game->pos.y][(int) game->pos.x + 1] == 'D')
		game->pars.mat[(int) game->pos.y][(int) game->pos.x + 1] = 'd';
	else if (game->pars.mat[(int) game->pos.y][(int) game->pos.x + 1] == 'd')
		game->pars.mat[(int) game->pos.y][(int) game->pos.x + 1] = 'D';
	if (game->pars.mat[(int) game->pos.y][(int) game->pos.x - 1] == 'D')
		game->pars.mat[(int) game->pos.y][(int) game->pos.x - 1] = 'd';
	else if (game->pars.mat[(int) game->pos.y][(int) game->pos.x - 1] == 'd')
		game->pars.mat[(int) game->pos.y][(int) game->pos.x - 1] = 'D';
	ft_draw(game);
	return ;
}

int	key_down(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (keycode == 'w')
		game->move_y = 1;
	else if (keycode == 's')
		game->move_y = -1;
	else if (keycode == 'd')
		game->move_x = 1;
	else if (keycode == 'a')
		game->move_x = -1;
	else if (keycode == 65361)
		game->rotate = -1;
	else if (keycode == 65363)
		game->rotate = 1;
	else if (keycode == 'z')
		ft_zoom(game);
	else if (keycode == ' ')
		ft_update_wall(game);
	else if (keycode == 65307)
		ft_close(param);
	return (0);
}

int	key_up(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (keycode == 'w' || keycode == 's')
		game->move_y = 0;
	else if (keycode == 'd' || keycode == 'a')
		game->move_x = 0;
	else if (keycode == 65361 || keycode == 65363)
		game->rotate = 0;
	else if (keycode == 'z')
	{
		game->cam.x *= 8;
		game->cam.y *= 8;
		game->z = 2;
	}
	return (0);
}

int	focus(void *param)
{
	t_game	*game;

	game = (t_game *) param;
	game->move_y = 0;
	game->move_x = 0;
	game->rotate = 0;
	if (game->z == 16)
	{
		game->cam.x *= 8;
		game->cam.y *= 8;
		game->z = 2;
	}
	return (0);
}
