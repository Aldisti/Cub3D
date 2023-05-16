/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:56:10 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/16 10:40:57 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_xpm(void *mlx, char *str, int *w, int *h)
{
	return (mlx_xpm_file_to_image(mlx, str, w, h));	
}
