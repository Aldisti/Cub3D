/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:35:37 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 11:56:42 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free(void **elem)
{
	if (*elem)
		free(*elem);
	*elem = NULL;
	return ;
}

void	ft_free_mat(void ***mat)
{
	int	i;

	if (!(*mat))
		return ;
	i = 0;
	while ((*mat)[i])
		ft_free(&(*mat)[i++]);
	*mat = NULL;
	return ;
}
