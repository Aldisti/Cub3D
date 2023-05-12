/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:56:51 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 15:53:45 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct s_pars
{
	const char	*path;
	char		*line;
	char		*identifiers[6];
	char		**mat;
	int			width;
	int			height;
}	t_pars;

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
	pars->width = 0;
	pars->height = 0;
	pars->line = NULL;
	while (42)
	{
		ft_free((void **)&pars->line);
		pars->line = get_next_line(fd);
		if (!pars->line)
			break ;
		if (pars->line[0] == 10)
			continue ;
		if (i == 6 && ++pars->height)
			continue ;
		pars->identifiers[i++] = ft_strdup(pars->line);
		if (!pars->identifiers[i - 1])
			exit(10);
	}
	return (0);
}

int	ft_parser(char *path)
{
	t_pars	pars;

	if (ft_getdim(&pars))
		return (1);
	
	return (0);
}
