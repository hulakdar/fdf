/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:38:02 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 16:37:34 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	fdf_point(int x, int y, int z, int color)
{
	t_point result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.color = color;
	return (result);
}

size_t	fdf_count(char **tab)
{
	int cunt;

	cunt = 0;
	while (tab[cunt])
		cunt++;
	return (cunt);
}

void	fdf_tabtomap(t_vector *arr, char **tab, int y)
{
	int		x;
	char	**tmp;
	t_point	new;

	x = 0;
	while (tab[x])
	{
		tmp = ft_strsplit(tab[x], ',');
		if (fdf_count(tmp) > 1)
			new = fdf_point(x, y, ft_atoi(tmp[0]), ft_atoi_b(tmp[1] + 2, 16));
		else
			new = fdf_point(x, y, ft_atoi(tab[x]), 0x00ffffff);
		ft_tabdel(&tmp);
		ft_vectorpushback(arr, &new);
		free(tab[x]);
		x++;
	}
	free(tab);
}

t_map	fdf_parse(t_vector lines)
{
	size_t	cunt;
	size_t	count;
	char	**tmp;
	char	**tab;
	t_map	map;

	cunt = 0;
	count = 0;
	map.arr = ft_vectornew(sizeof(t_point), 100);
	tmp = (char **)lines.array;
	while (tmp[cunt])
	{
		tab = ft_strsplit(tmp[cunt], ' ');
		if (!count)
			count = fdf_count(tab);
		else if (count != fdf_count(tab))
			fdf_error("Invalid map", &map);
		fdf_tabtomap(&(map.arr), tab, cunt);
		cunt++;
	}
	map.height = lines.back;
	map.width = count;
	ft_vectordestruct(&lines);
	return (map);
}

t_map	fdf_read(int fd)
{
	t_vector	lines;
	size_t		width;
	char		*line;
	int			status;

	width = 0;
	lines = ft_vectornew(sizeof(char *), 1);
	while ((status = get_next_line(fd, &line)) > 0)
		ft_vectorpushback(&lines, &line);
	if (status == -1)
	{
		ft_vectordestruct(&lines);
		fdf_error("Error while reading file", NULL);
	}
	return (fdf_parse(lines));
}
