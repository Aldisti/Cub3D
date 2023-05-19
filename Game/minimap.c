/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:58:06 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/19 16:33:54 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_minimap(t_game *game)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			dst = game->map.addr + (j * (game->map.bpp / 8) + i * game->map.ll);
			*(unsigned int *)dst = 0x2b2c2c;
			if (game->pars.mat[i / BLOCK][j / BLOCK] == 49)
				*(unsigned int *)dst = 0xffffff;
			else if (game->pars.mat[i / BLOCK][j / BLOCK] == 'D')
				*(unsigned int *)dst = 0x00ffff;
			else if (game->pars.mat[i / BLOCK][j / BLOCK] == 'd')
				*(unsigned int *)dst = 0xffff00;
			else if (powf((game->pos.x * 5 - j), 2)
				+ powf((game->pos.y * 5 - i), 2) <= powf(2.5f, 2))
				*(unsigned int *)dst = 0xff0000;
		}
	}
}
