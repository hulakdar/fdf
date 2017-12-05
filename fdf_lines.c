/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:31:19 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 17:09:35 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_dx(t_ints ints, t_map *map)
{
	int x;
	int y;
	int i;
	int col;

	x = ints.x0 + ints.sx;
	y = ints.y0;
	i = 1;
	while (i++ < ints.dx)
	{
		if (ints.d > 0)
		{
			ints.d += ints.d2;
			y += ints.sy;
		}
		else
			ints.d += ints.d1;
		col = fdf_linter(ints.col, ints.cola, (double)(x - ints.x0) / ints.dx);
		if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
			mlx_pixel_put(map->mlx, map->window, x, y, col);
		x += ints.sx;
	}
}

void	fdf_draw_dy(t_ints ints, t_map *map)
{
	int x;
	int y;
	int i;
	int col;

	y = ints.y0 + ints.sy;
	x = ints.x0;
	i = 1;
	while (i++ < ints.dy)
	{
		if (ints.d > 0)
		{
			ints.d += ints.d2;
			x += ints.sx;
		}
		else
			ints.d += ints.d1;
		col = fdf_linter(ints.col, ints.cola, (double)(y - ints.y0) / ints.dy);
		if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
			mlx_pixel_put(map->mlx, map->window, x, y, col);
		y += ints.sy;
	}
}

void	fdf_draw_line(t_pixel a, t_pixel b, t_map *map)
{
	t_ints	ints;

	ints.x0 = a.x;
	ints.y0 = a.y;
	ints.dx = abs(a.x - b.x);
	ints.dy = abs(a.y - b.y);
	ints.sx = b.x >= a.x ? 1 : -1;
	ints.sy = b.y >= a.y ? 1 : -1;
	ints.col = b.color;
	ints.cola = a.color;
	if (ints.dy <= ints.dx)
	{
		ints.d = (ints.dy << 1) - ints.dx;
		ints.d1 = ints.dy << 1;
		ints.d2 = (ints.dy - ints.dx) << 1;
		fdf_draw_dx(ints, map);
	}
	else
	{
		ints.d = (ints.dx << 1) - ints.dy;
		ints.d1 = ints.dx << 1;
		ints.d2 = (ints.dx - ints.dy) << 1;
		fdf_draw_dy(ints, map);
	}
}
