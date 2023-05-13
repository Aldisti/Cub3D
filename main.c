/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:53:33 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/13 11:57:31 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->no_w = 0;
	game->no_h = 0;
	game->so_w = 0;
	game->so_h = 0;
	game->we_w = 0;
	game->we_h = 0;
	game->ea_w = 0;
	game->ea_h = 0;
	game->pars.line = NULL;
	game->pars.mat = NULL;
	game->pars.width = 0;
	game->pars.height = 0;
	game->pars.offset = 0;
	return ;	
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: arguments\n", 17) - 16);
	game.pars.path = av[1];
	ft_init(&game);
	ft_parser(&game);
	return (0);
}
