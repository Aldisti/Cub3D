/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:53:33 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/16 15:35:18 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_game *game)
{
	game->move_y = 0;
	game->move_x = 0;
	game->rotate = 0;

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
	else if (keycode == 65307)
		exit(1);
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
	return (0);
}

int	ft_game(void *param)
{
	double	perpWallDist;
	int	stepX;
	int	stepY;
	int	hit;
	int	side;
	int	lineheight;
	int	drawStart;
	int	drawEnd;
	double	dir_x, dir_y, cam_x, cam_y;
	double	deltaDistX, deltaDistY;
	double	sideDistX, sideDistY;
	double	posX, posY;
	t_game	*game;

	game = (t_game *)param;

	if (game->move_x || game->move_y || game->rotate)
	{
		game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);
		dir_x = game->dir.x;
		dir_y = game->dir.y;
		cam_x = game->cam.x;
		cam_y = game->cam.y;

		//rotate
		if (game->rotate == -1)
		{
			game->dir.x = dir_x * cos(M_PI / 180.0f) + dir_y * sin(M_PI / 180.0f);
			game->dir.y = (-1) * dir_x * sin(M_PI / 180.0f) + dir_y * cos(M_PI / 180.0f);
			game->cam.x = cam_x * cos(M_PI / 180.0f) + cam_y * sin(M_PI / 180.0f);
			game->cam.y = (-1) * cam_x * sin(M_PI / 180.0f) + cam_y * cos(M_PI / 180.0f);
		}
		else if (game->rotate == 1)
		{
			game->dir.x = dir_x * cos(M_PI / 180.0f) - dir_y * sin(M_PI / 180.0f);
			game->dir.y = dir_x * sin(M_PI / 180.0f) + dir_y * cos(M_PI / 180.0f);
			game->cam.x = cam_x * cos(M_PI / 180.0f) - cam_y * sin(M_PI / 180.0f);
			game->cam.y = cam_x * sin(M_PI / 180.0f) + cam_y * cos(M_PI / 180.0f);
		}
		// move
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
		if (game->move_y == 1 && game->dir.y)
		{
			game->pos.y += (game->dir.y * 0.05);
			game->pos.x += (game->dir.x * 0.05);
		}
		if (game->move_y == -1)
		{
			game->pos.y += ((-1) * game->dir.y * 0.05);
			game->pos.x += ((-1) * game->dir.x * 0.05);
		}

		// check boundary
		if (game->pars.mat[(int) game->pos.y][(int)game->pos.x + 1] == '1'
				&& game->pos.x > (int)game->pos.x + 1 - 0.25f)
			game->pos.x = (int)game->pos.x + 1 - 0.25f;
		if (game->pars.mat[(int) game->pos.y][(int)game->pos.x - 1] == '1'
				&& game->pos.x < (int)game->pos.x + 0.25f)
			game->pos.x = (int)game->pos.x + 0.25f;
		if (game->pars.mat[(int) game->pos.y + 1][(int)game->pos.x] == '1'
				&& game->pos.y > (int)game->pos.y + 1 - 0.25f)
			game->pos.y = (int)game->pos.y + 1 - 0.25f;
		if (game->pars.mat[(int) game->pos.y - 1][(int)game->pos.x] == '1'
				&& game->pos.y < (int)game->pos.y + 0.25f)
			game->pos.y = (int)game->pos.y + 0.25f;

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
			//printf("ray: %d\n", i);
			//printf("X: %f\n", game->ray.x);
			//printf("Y: %f\n", game->ray.y);
			//printf("deltadistX: %f\n", deltaDistX);
			//printf("deltadistY: %f\n", deltaDistY);

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
			//printf("Dist: %f\n", perpWallDist);
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
				*(unsigned int *)dst = 0xff0000 ; 
				drawStart++;
			}
		}
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
		mlx_destroy_image(game->mlx, game->img);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: arguments\n", 17) - 16);
	game.pars.path = av[1];
	ft_init(&game);
	ft_parser(&game);
	game.pos.x = 10.5f;
	game.pos.y = 10.5f;
	game.dir.x = 0;
	game.dir.y = 1;
	game.cam.x = -0.66;
	game.cam.y = 0;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_do_sync(game.mlx);
	mlx_hook(game.win, 2, 1L<<0, key_down, &game);
	mlx_hook(game.win, 3, 1L<<1, key_up, &game);
	//mlx_key_hook(game.win, key_hook, &game);
	mlx_loop_hook(game.mlx, ft_game, &game);
	mlx_loop(game.mlx);
	//ft_die(&game);
	return (0);
}
