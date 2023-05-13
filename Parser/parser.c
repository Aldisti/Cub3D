/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:56:51 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/13 11:53:39 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
[0] -> for OK
[1] -> for error

NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
*/

int	ft_getdim(t_pars *pars)
{
	int	fd;
	int	i;

	fd = open(pars->path, O_RDONLY);
	if (fd == -1)
		return (1);
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
		pars->identifiers[i++] = ft_strdup(pars->line);
		if (!pars->identifiers[i - 1])
			exit(10);
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

int	ft_parser(t_pars *pars)
{
	if (ft_getdim(pars))
		exit(11);
	if (ft_getmat(pars))
		exit(12);
	if (ft_check_mat(pars))
		printf("KO\n");
	else
		printf("OK\n");
	// if (ft_check_info(pars))
	// 	exit(13);
	return (0);
}
