/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:56:51 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/16 11:44:43 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_getdim(t_pars *pars)
{
	int	fd;
	int	i;

	fd = open(pars->path, O_RDONLY);
	i = 0;
	while (42)
	{
		ft_free((void **)&pars->line);
		pars->line = get_next_line(fd);
		if (!pars->line)
			break ;
		if (pars->line[0] == 10 && ++pars->offset)
			continue ;
		if (i == 6 && (int)ft_strlen(pars->line) > pars->width)
			pars->width = ft_strlen(pars->line);
		if ((i == 6 && ++pars->height) || !(++pars->offset))
			continue ;
		pars->ids[i++] = ft_strdup(pars->line);
		if (!pars->ids[i - 1])
			exit(10);
		pars->ids[i - 1][ft_strlen(pars->ids[i - 1]) - 1]
			*= !(pars->ids[i - 1][ft_strlen(pars->ids[i - 1]) - 1] == 10);
	}
	close(fd);
	return (0);
}

int	ft_getmat(t_pars *pars)
{
	int	fd;
	int	i;

	pars->mat = (char **)malloc((pars->height + 1) * sizeof(char *));
	if (!pars->mat)
		return (1);
	i = 0;
	fd = open(pars->path, O_RDONLY);
	while (42)
	{
		ft_free((void **)&pars->line);
		pars->line = get_next_line(fd);
		if (!pars->line)
			break ;
		if (pars->offset-- > 0)
			continue ;
		if (pars->line[ft_strlen(pars->line) - 1] == 10)
			pars->line[ft_strlen(pars->line) - 1] = 0;
		pars->mat[i++] = ft_strdup(pars->line);
		if (!pars->mat[i - 1])
			exit(13);
	}
	pars->mat[i] = 0;
	close(fd);
	return (0);
}

int	ft_parser(t_game *game)
{
	if (ft_getdim(&game->pars) || game->pars.height <= 2)
		return (ft_error(INV_MAP, 1));
	if (ft_getmat(&game->pars))
		return (ft_error(INV_MAP, 1));
	if (ft_check_mat(&game->pars))
		return (ft_error(INV_MAP, 1));
	if (ft_get_info(game, &game->pars))
		return (ft_error(INV_COL, 1));
	if (ft_check_info(game))
		return (1);
	return (0);
}
