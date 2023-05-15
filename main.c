/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:53:33 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/15 16:33:23 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
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

void	ft_game(t_game *game)
{
	double	perpWallDist;
	int	stepX;
	int	stepY;
	int	hit;
	int	side;
	int	lineheight;
	int	drawStart;
	int	drawEnd;
	double	deltaDistX, deltaDistY;
	double	sideDistX, sideDistY;
	double	posX, posY;


	game->pos.x = 10.5f;
	game->pos.y = 10.5f;
	game->dir.x = -1;
	game->dir.y = 0;
	game->cam.x = 0;
	game->cam.y = 0.66;

	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);

	for (int i = 0; i < WIDTH; i++)
	{
		double	cameraX = 2 * i / (double) WIDTH - 1;

		game->ray.x = game->dir.x + game->cam.x * cameraX;
		game->ray.y = game->dir.y + game->cam.y * cameraX;
		hit = 0;

		posX = game->pos.x;
		posY = game->pos.y;
		if (game->ray.x == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / game->ray.x);
		if (game->ray.y == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / game->ray.y);

		if (game->ray.x < 0)
		{
			stepX = -1;
			sideDistX = (posX - (int) posX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (1.0f + (int) posX - posX) * deltaDistX;
		}
		if (game->ray.y < 0)
		{
			stepY = -1;
			sideDistY = (posY - (int) posY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (1.0f + (int) posY - posY) * deltaDistY;
		}
		printf("ray: %d\n", i);
		//printf("X: %f\n", game->ray.x);
		//printf("Y: %f\n", game->ray.y);
		printf("deltadistX: %f\n", deltaDistX);
		printf("deltadistY: %f\n", deltaDistY);

		//DDA
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				posX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				posY += stepY;
				side = 1;
			}
			if (game->pars.mat[(int) posY][(int) posX] == '1')
				hit = 1;
		}
		if (!side)
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;
		//perpWallDist = sqrtf(sideDistY * sideDistY + sideDistX * sideDistX);
		printf("Dist: %f\n", perpWallDist);
		lineheight = (int) (HEIGHT / perpWallDist);
		drawStart = HEIGHT / 2 - lineheight / 2;
		if (drawStart < 0)
			drawStart  = 0;
		drawEnd = HEIGHT / 2 + lineheight / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		char *dst;
		while (drawStart <= drawEnd)
		{
			dst = game->addr + (i * (game->bpp / 8) + drawStart * game->line_length);
			*(unsigned int *)dst = 0xff0000; 
			drawStart++;
		}
	}
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: arguments\n", 17) - 16);
	game.pars.path = av[1];
	ft_init(&game);
	ft_parser(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	ft_game(&game);
	mlx_loop(game.mlx);
	//ft_die(&game);
	return (0);
}
