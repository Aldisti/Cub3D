/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:20:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/18 14:30:43 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_info(t_game *game)
{
	int	i;

	if (!game->no.img)
		return (ft_error(NO_MISS, 2));
	if (!game->so.img)
		return (ft_error(SO_MISS, 3));
	if (!game->we.img)
		return (ft_error(WE_MISS, 4));
	if (!game->ea.img)
		return (ft_error(EA_MISS, 5));
	if (game->pos.x == -1 || game->pos.y == -1
		|| (!game->dir.x && !game->pos.y))
		return (ft_error(PL_MISS, 6));
	if (!game->dr.img)
		return (ft_error(DR_MISS, 7));
	i = -1;
	while (++i < 3)
		if (game->f[i] > 255 || game->c[i] > 255)
			return (ft_error(INV_COL, 1));
	return (0);
}

int	ft_check_num(const char *num)
{
	int	i;

	i = -1;
	while (num[++i])
		if (num[i] > 57 || num[i] < 48)
			return (1);
	if (i > 3)
		return (1);
	return (0);
}

/*
DESCRIPTION
this function will will make sure that for every space in s1 there is a wall in
s2 and viceversa
*/
int	ft_space_cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == 32 && s2[i] != 32 && (!ft_in(s2[i + 1], " 1")
				|| !ft_in(s2[i], " 1") || (i > 0 && !ft_in(s2[i - 1], " 1"))))
			return (1);
		if (s2[i] == 32 && s1[i] != 32 && (!ft_in(s1[i + 1], " 1")
				|| !ft_in(s1[i], " 1") || (i > 0 && !ft_in(s1[i - 1], " 1"))))
			return (1);
		i++;
	}
	return (0);
}

/*
DESCRIPTION
this function makes sure that every line starts and ends
with ones and/or spaces
*/
int	ft_check_se(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = -1;
	while (s1[++i])
		if (!ft_in(s1[i], SYMBOLS))
			return (1);
	i = 0;
	j = 0;
	while (s2[j] && s2[j] == 32)
		j++;
	if (j >= i)
		while (s1[i] && i <= j)
			if (!ft_in(s1[i++], " 1"))
				return (1);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (j >= 0 && s2[j] == 32)
		j--;
	if (i >= j)
		while (i >= 0 && i >= j)
			if (!ft_in(s1[i--], " 1"))
				return (1);
	return (0);
}

/*
CODES
31 - first and last line check
32 - all spaces are surrounded by ones
33 - every line doesn't contain weird chars and every line starts and ends
		with ones or spaces
*/
int	ft_check_mat(t_pars *pars)
{
	int	i;
	int	j;

	j = -1;
	while (pars->mat[++j])
	{
		ft_get_pos(pars->game, j);
		i = 0;
		if (j == 0 || j == pars->height - 1)
			while (pars->mat[j][i])
				if (!ft_in(pars->mat[j][i++], " 1"))
					return (31);
		if (j < pars->height - 1
			&& ft_space_cmp(pars->mat[j], pars->mat[j + 1]))
			return (32);
		if (j < pars->height - 1 && ft_check_se(pars->mat[j], pars->mat[j + 1]))
			return (33);
		if (j < pars->height - 1 && ft_check_se(pars->mat[j + 1], pars->mat[j]))
			return (33);
		//if (j && j < pars->height - 1 && ft_check_door(pars, j))
		//	return (34);
	}
	return (0);
}
