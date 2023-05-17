/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:35:37 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/16 11:32:49 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_error(char *str, int code)
{
	int	i;

	write(2, BLKRED, 7);
	write(2, "error", 5);
	write(2, RESET, 8);
	write(2, RED, 5);
	write(2, ": ", 2);
	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	write(2, RESET, 8);
	return (code);
}

int	ft_free(void **elem)
{
	if (*elem)
		free(*elem);
	*elem = NULL;
	return (0);
}

int	ft_free_mat(void ***mat)
{
	int	i;

	if (!(*mat))
		return (0);
	i = 0;
	while ((*mat)[i])
		ft_free(&(*mat)[i++]);
	ft_free((void **)mat);
	*mat = NULL;
	return (0);
}

void	ft_die(t_game *game)
{
	int	i;

	if (game->no.img)
		mlx_destroy_image(game->mlx, game->no.img);
	if (game->so.img)
		mlx_destroy_image(game->mlx, game->so.img);
	if (game->we.img)
		mlx_destroy_image(game->mlx, game->we.img);
	if (game->ea.img)
		mlx_destroy_image(game->mlx, game->ea.img);
	if (game->pars.line)
		ft_free((void **)&game->pars.line);
	if (game->pars.mat)
		ft_free_mat((void ***)&game->pars.mat);
	i = 0;
	while (i < 6)
		ft_free((void **)&game->pars.ids[i++]);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	return ;
}
