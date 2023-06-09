/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:49:28 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/27 11:48:30 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_zoom(t_game *game)
{
	if (game->z == 1)
	{
		game->cam.x /= 8;
		game->cam.y /= 8;
		game->z = 8;
		ft_draw(game);
	}
	return ;
}

/*
for (int i = 0; i < game->pars.height; i++)
	{
		for (int j = 0; j < game->pars.width; j++)
			if (game->doors[i][j].type)
				write(1, &game->doors[i][j].type, 1);
			else
				write(1, ".", 1);
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
*/
void	ft_update_wall(t_game *game)
{
	if (ft_in(game->pars.mat[(int) game->pos.y + 1][(int) game->pos.x], "Dd"))
		ft_update_door(game, (int) game->pos.y + 1, (int) game->pos.x);
	if (ft_in(game->pars.mat[(int) game->pos.y - 1][(int) game->pos.x], "Dd"))
		ft_update_door(game, (int) game->pos.y - 1, (int) game->pos.x);
	if (ft_in(game->pars.mat[(int) game->pos.y][(int) game->pos.x + 1], "Dd"))
		ft_update_door(game, (int) game->pos.y, (int) game->pos.x + 1);
	if (ft_in(game->pars.mat[(int) game->pos.y][(int) game->pos.x - 1], "Dd"))
		ft_update_door(game, (int) game->pos.y, (int) game->pos.x - 1);
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
	else if (keycode == 'z' && game->z == 8)
	{
		game->cam.x *= 8;
		game->cam.y *= 8;
		game->z = 1;
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
	if (game->z == 8)
	{
		game->cam.x *= 8;
		game->cam.y *= 8;
		game->z = 1;
	}
	return (0);
}
