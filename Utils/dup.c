/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:38:55 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 15:45:38 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(char const *str)
{
	char	*out;
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str && str[i])
		i++;
	out = (char *)malloc((i + 1) * sizeof(char));
	if (!out)
		return (0);
	i = -1;
	while (str && str[++i])
		out[i] = str[i];
	out[i] = 0;
	return (out);
}
