/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:00:47 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/13 12:49:49 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*str;
	int			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!(*buff))
		r = read(fd, buff, BUFFER_SIZE);
	else
		r = ft_strlen(buff);
	str = ft_get_first_str(buff);
	while (r && !ft_nlinstr(str))
	{
		if (r <= 0)
			break ;
		if (!(*buff))
			r = read(fd, buff, BUFFER_SIZE);
		if (r <= 0)
			break ;
		str = ft_realloc_get(str, buff);
	}
	if (str && *str)
		return (str);
	free(str);
	return (0);
}
