/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:53:33 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/18 18:14:19 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_game(void *param);

int	create_trgb(int t, int r, int g, int b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b);
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

	double	deltaDistX, deltaDistY;
	double	sideDistX, sideDistY;
	double	posX, posY;
	t_game	*game;

	game = (t_game *)param;

	if (game->move_x || game->move_y || game->rotate || game->z == 16)
	{
		game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);

		ft_rotate(game, game->rotate, M_PI / 180.0f);
		// move
		ft_move(game);

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
				if (ft_in(game->pars.mat[(int) posY][(int) posX], WALLS))
					hit = 1 + (game->pars.mat[(int) posY][(int) posX] == 'D');
			}
			if (!side)
				perpWallDist = sideDistX - deltaDistX;
			else
				perpWallDist = sideDistY - deltaDistY;
			//perpWallDist = sqrtf(sideDistY * sideDistY + sideDistX * sideDistX);
			//printf("Dist: %f\n", perpWallDist);
			lineheight = (int) ( game->z * HEIGHT / perpWallDist);
			drawStart = HEIGHT / 2 - lineheight / 2;
			if (drawStart < 0)
				drawStart  = 0;
			drawEnd = HEIGHT / 2 + lineheight / 2;
			if (drawEnd >= HEIGHT)
				drawEnd = HEIGHT - 1;
			char *dst;
			int	n;
			double	wallx;
			double	texpos;
			int	texx;
			int	texy;
			float	step;

			if (!side)
				wallx = game->pos.y + perpWallDist * game->ray.y;
			else
				wallx = game->pos.x + perpWallDist * game->ray.x;
			wallx -= floor(wallx);

			//img
			t_img	cur;

			if (hit == 2)
				cur = game->dr; 
			else if (side == 0 && game->ray.x < 0)
				cur = game->ea;
			else if (side == 0 && game->ray.x > 0)
				cur = game->we;
			else if (side == 1 && game->ray.y < 0)
				cur = game->no;
			else if (side == 1 && game->ray.y > 0)
				cur = game->so;

			texx = (int) (wallx * (double) cur.w);

			//inversion?
			if ((side == 0 && game->ray.x < 0) || (side == 1 && game->ray.y > 0))
				texx = cur.w - texx - 1;
			step = cur.h / (float) lineheight;
			texpos = (drawStart - HEIGHT / 2 + lineheight / 2) * step;
			n = 0;
			while (n < HEIGHT)
			{
				if (n >= drawStart && n <= drawEnd)
				{
					texy = (int) texpos;
					texpos += step;
					dst = game->addr + (i * (game->bpp / 8) + n * game->line_length);
					*(unsigned int *)dst = *(unsigned int *)(cur.addr +
							(texx * (cur.bpp / 8) + texy * cur.line_length));
				}
				else if (n < drawStart)
				{
					dst = game->addr + (i * (game->bpp / 8) + n * game->line_length);
					*(unsigned int *)dst = create_trgb(1, game->c[0], game->c[1], game->c[2]);
				}
				else if (n >= drawEnd)
				{
					dst = game->addr + (i * (game->bpp / 8) + n * game->line_length);
					*(unsigned int *)dst = create_trgb(1, game->f[0], game->f[1], game->f[2]);
				}
				n++;	
			}
		}
	//	mlx_clear_window(game->mlx, game->win);
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
	game.mlx = mlx_init();
	if (ft_parser(&game))
	{
		ft_die(&game);
		return (1);
	}
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_do_sync(game.mlx);
	mlx_hook(game.win, 2, 1L<<0, key_down, &game);
	mlx_hook(game.win, 3, 1L<<1, key_up, &game);
	mlx_hook(game.win, 17, 0, ft_close, &game);
	mlx_hook(game.win, 6, 1L<<6,ft_mouse, &game);
	//mlx_key_hook(game.win, key_hook, &game);
	mlx_loop_hook(game.mlx, ft_game, &game);
	mlx_loop(game.mlx);
	//ft_die(&game);
	return (0);
}
