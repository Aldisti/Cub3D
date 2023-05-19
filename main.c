/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:53:33 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/19 16:35:08 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->move_x || game->move_y)
		ft_move(game);
	if (game->rotate)
		ft_rotate(game, game->rotate, M_PI / 180.0f);
	if (game->move_x || game->move_y || game->rotate)
		ft_draw(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: arguments\n", 17) - 16);
	game.pars.path = av[1];
	ft_init(&game);
	game.mlx = mlx_init();
	if (ft_parser(&game))
	{
		ft_die(&game);
		return (1);
	}
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	ft_draw(&game);
	mlx_do_sync(game.mlx);
	mlx_hook(game.win, 2, 1L << 0, key_down, &game);
	mlx_hook(game.win, 3, 1L << 1, key_up, &game);
	mlx_hook(game.win, 17, 0, ft_close, &game);
	mlx_hook(game.win, 6, 1L << 6, ft_mouse, &game);
	mlx_loop_hook(game.mlx, ft_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
