/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:20:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 16:59:48 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
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

int	ft_check_border(t_pars *pars)
{
	int	i;
	int	j;

	i = -1;
	while (pars->mat[0][++i])
		if (pars->mat[0][i] != 49 && pars->mat[0][i] != 32)
			return (1);
	i = -1;
	while (pars->mat[pars->height - 1][++i])
		if (pars->mat[pars->height - 1][i] != 49
			&& pars->mat[pars->height - 1][i] != 32)
			return (1);
	j = -1;
	while (pars->mat[++j])
	{
		i = 0;
		while (pars->mat[j][i] && pars->mat[j][i] == 32)
			i++;
		if (!pars->mat[j][i] || pars->mat[j][i] != 49)
			return (1);
		i = ft_strlen(pars->mat[j]) - 1;
		while (i >= 0 && pars->mat[j][i] == 32)
			i--;
		if (!pars->mat[j][i] || pars->mat[j][i] != 49)
			return (1);
	}
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
	int	j;
	
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == 32 && s2[i] != 49 && s2[i + 1] != 49 && s2[i + 1]
			&& (i == 0 || s2[i - 1] != 49))
			return (0);
	}
}

int	ft_check_space(t_pars *pars)
{
	int	i;
	int	j;

	j = -1;
	while (pars->mat[++j])
	{
		if (j == 0)
		{
			if (ft_strlen(pars->mat[j]) > ft_strlen(pars->mat[j + 1]))
			{
				
			}
		}
	}
	return (0);
}

int	ft_check_mat(t_pars *pars)
{
	if (ft_check_border(pars))
		return (1);
	if (ft_check_space(pars))
		return (1);
	return (0);
}
