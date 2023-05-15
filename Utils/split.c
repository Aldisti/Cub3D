/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:29:51 by adi-stef          #+#    #+#             */
/*   Updated: 2023/05/13 12:35:25 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strnbr(char const *str, char chr)
{
	int		c;

	while (*str && *str == chr)
		str++;
	c = 0;
	while (*str)
	{
		if (*str == chr)
		{
			while (*str == chr && *str)
				str++;
			c++;
		}
		else
			str++;
	}
	if (*(--str) == chr && c)
		c--;
	return (c);
}

char	**ft_fill(char const *s, char c)
{
	char	**ptr;
	int		j;
	int		k;

	ptr = (char **) ft_calloc((ft_strnbr(s, c) + 2), sizeof (char *));
	if (!ptr)
		return (0);
	k = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (*s && *s != c && ++j)
				s++;
			ptr[k++] = ft_substr(s - j, 0, j);
		}
		else
			s++;
	}
	ptr[k] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s || !c)
		if (!s)
			return (0);
	if (!(*s))
	{
		ptr = (char **) malloc (2 * sizeof (char *));
		ptr[0] = 0;
		ptr[1] = 0;
	}
	else
		ptr = ft_fill(s, c);
	return (ptr);
}

void	*ft_calloc(size_t num, size_t dim)
{
	char	*ptr;
	size_t	i;

	if (num >= 1247483424)
		return (0);
	ptr = (char *) malloc (num * dim);
	if (!ptr)
		return (0);
	i = 0;
	while (i < (num * dim))
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ptr = (char *) malloc ((len + 1) * sizeof (char));
	if (!ptr)
		return (0);
	i = 0;
	while (len-- > 0 && s[start])
		ptr[i++] = s[start++];
	ptr[i] = 0;
	return (ptr);
}
