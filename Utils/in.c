/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:29:34 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/18 13:55:35 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_count(char c, char *str)
{
	int	i;

	i = 0;
	while (str && *str)
		i += (*str++ == c);
	return (i);
}

/*
RETURN
[1] if c is in chars
[0] if c is not in chars
*/
int	ft_in(char c, const char *chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		if (chars[i] == c)
			return (1);
		i++;
	}
	return (0);
}
