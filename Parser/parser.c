/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:56:51 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/13 12:49:24 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_get_color(t_game *game, const char type, const char *rgb)
{
	char	**tmp;
	int		i;

	tmp = ft_split(rgb, ',');
	i = 0;
	while (tmp[i])
		if (ft_check_num(tmp[i++]))
			return (ft_free_mat((void ***)&tmp) + 1);
	i = -1;
	if (type == 'F')
		while (++i < 3)
			game->f[i] = ft_atoi(tmp[i]);
	else if (type == 'C')
		while (++i < 3)
			game->c[i] = ft_atoi(tmp[i]);
	return (ft_free_mat((void ***)&tmp));
}

int	ft_get_info(t_game *g, t_pars *pars)
{
	char	**tmp;
	int		i;

	i = -1;
	while (++i < 6)
	{
		tmp = ft_split(pars->ids[i], 32);
		ft_print_mat(tmp);
		if (!tmp)
			exit(110);
		if (!ft_strcmp(tmp[0], "NO"))
			g->no = mlx_xpm_file_to_image(g->mlx, tmp[1], &g->no_w, &g->no_h);
		else if (!ft_strcmp(tmp[0], "SO"))
			g->so = mlx_xpm_file_to_image(g->mlx, tmp[1], &g->so_w, &g->so_h);
		else if (!ft_strcmp(tmp[0], "WE"))
			g->we = mlx_xpm_file_to_image(g->mlx, tmp[1], &g->we_w, &g->we_h);
		else if (!ft_strcmp(tmp[0], "EA"))
			g->ea = mlx_xpm_file_to_image(g->mlx, tmp[1], &g->ea_w, &g->ea_h);
		else if ((!ft_strcmp(tmp[0], "F") || !ft_strcmp(tmp[0], "C"))
			&& ft_get_color(g, tmp[0][0], tmp[1]))
			return (ft_free_mat((void ***)&tmp) + 1);
		ft_free_mat((void ***)&tmp);
	}
	return (0);
}

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
	if (ft_getdim(&game->pars))
		exit(11);
	if (ft_getmat(&game->pars))
		exit(12);
	if (ft_check_mat(&game->pars))
		printf("KO\n");
	else
		printf("OK\n");
	if (ft_get_info(game, &game->pars))
		exit(13);
	if (ft_check_info(game))
		exit(14);
	return (0);
}
