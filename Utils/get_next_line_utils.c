/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:00:32 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/12 12:00:02 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_realloc_get(char *str, char *buff)
{
	char	*new;
	int		len;
	int		j;
	int		i;

	len = ft_strlen(str) + ft_getnl(buff);
	new = (char *) malloc ((len + ft_strlen(str) + 1) * sizeof (char));
	if (!new)
		return (0);
	new[len] = 0;
	i = -1;
	while (str[++i])
		new[i] = str[i];
	free(str);
	j = 0;
	while (i < len)
		new[i++] = buff[j++];
	ft_memmove_get(buff, buff + j);
	return (new);
}

char	*ft_get_first_str(char *buff)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	len = ft_getnl(buff);
	str = (char *) malloc((len + 1) * sizeof (char));
	if (!str)
		return (0);
	str[len] = 0;
	i = 0;
	j = 0;
	while (i < len)
		str[i++] = buff[j++];
	ft_memmove_get(buff, buff + j);
	return (str);
}

void	ft_memmove_get(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (*src && i <= BUFFER_SIZE)
	{
		dst[i++] = *src;
		src++;
	}
	while (dst[i] && i <= BUFFER_SIZE)
		dst[i++] = 0;
}

int	ft_getnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != 10)
		i++;
	if (str[i] == 10)
		i++;
	return (i);
}

int	ft_nlinstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 10)
			return (1);
	}
	if (str[i] == 10)
		return (1);
	return (0);
}
