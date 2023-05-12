/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:20:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 19:13:59 by adi-stef         ###   ########.fr       */
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

	i = -1;
	while (pars->mat[0][++i])
		if (pars->mat[0][i] != 49 && pars->mat[0][i] != 32)
			return (1);
	i = -1;
	while (pars->mat[pars->height - 1][++i])
		if (pars->mat[pars->height - 1][i] != 49
			&& pars->mat[pars->height - 1][i] != 32)
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
this function makes sure that every line ends with ones or spaces
*/
int	ft_check_end(const char *s1, const char *s2)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(s1) - 1;
	l2 = ft_strlen(s2) - 1;
	while (l2 >= 0 && s2[l2] == 32)
		l2--;
	if (l1 >= l2)
		while (l1 >= 0 && l1 >= l2)
			if (!ft_in(s1[l1--], " 1"))
				return (1);
	l1 = ft_strlen(s1) - 1;
	l2 = ft_strlen(s2) - 1;
	while (l1 >= 0 && s1[l1] == 32)
		l1--;
	if (l2 >= l1)
		while (l2 >= 0 && l2 >= l1)
			if (!ft_in(s2[l2--], " 1"))
				return (1);
	return (0);
}

int	ft_check_start(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[j] && s2[j] == 32)
		j++;
	if (j >= i)
		while (s1[i] && i <= j)
			if (!ft_in(s1[i++], " 1"))
				return (1);
	i = 0;
	j = 0;
	if (i >= j)
		while (s2[j] && j <= i)
			if (!ft_in(s2[j++], " 1"))
				return (1);
	return (0);
}

int	ft_check_space(t_pars *pars)
{
	int	j;

	j = -1;
	while (pars->mat[++j])
	{
		printf("%d\n", j);
		if (j < pars->height - 1 && ft_space_cmp(pars->mat[j], pars->mat[j + 1]))
			return (1);
		if (j < pars->height - 1 && ft_check_end(pars->mat[j], pars->mat[j + 1]))
			return (1);
		if (j < pars->height - 1 && ft_check_start(pars->mat[j], pars->mat[j + 1]))
			return (1);
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
