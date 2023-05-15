/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:49:28 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 11:56:32 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_matlen(char const **mat)
{
	size_t	i;

	if (!mat)
		return (0);
	i = 0;
	while (mat[i])
		i++;
	return (i);
}
