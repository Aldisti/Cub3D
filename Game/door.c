/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door..c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:25:12 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/26 15:33:32 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_reset_time(t_game *g, int i, int j)
{
	if (ft_gettime(g->doors[i][j].time) / (double) 1000 > 0.99f
		&& g->doors[i][j].type == 'c')
	{
		g->doors[i][j].time = -1;
		g->doors[i][j].type = 'C';
	}
	else if (ft_gettime(g->doors[i][j].time) / (double) 1000 > 1
		&& g->doors[i][j].type == 'o')
	{
		g->doors[i][j].time = -1;
		g->doors[i][j].type = 'O';
	}
}

void	ft_check_time(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g->pars.height)
	{
		j = -1;
		while (++j < g->pars.width)
			if (g->doors[i][j].type)
				ft_reset_time(g, i, j);
	}
}
