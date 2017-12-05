/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:36:35 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 18:56:17 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_help(t_map *map)
{
	if (map->help)
		mlx_string_put(map->mlx, map->window, 10, 10, 0xffffff,
				"Press 'Spacebar' for help");
	else
	{
		mlx_string_put(map->mlx, map->window, 10, 10, 0xffffff,
				"Mouse-wheel, arrows: rotations");
		mlx_string_put(map->mlx, map->window, 10, 30, 0xffffff,
				"Num +, Num -: Scaling");
		mlx_string_put(map->mlx, map->window, 10, 50, 0xffffff,
				"WASD: Moving camera");
		mlx_string_put(map->mlx, map->window, 10, 70, 0xffffff,
				"Q, E: Adjusting flatness");
		mlx_string_put(map->mlx, map->window, 10, 70, 0xffffff,
				"P: Change projection");
		mlx_string_put(map->mlx, map->window, 10, 90, 0xffffff,
				"Point && click: moves projection");
		mlx_string_put(map->mlx, map->window, 10, 110, 0xffffff,
				"Esc: Exit");
	}
}

void	fdf_line(t_pixel *ptr, int x, int y, t_map map)
{
	t_pixel		pix[2];

	pix[0] = ptr[(y * map.width) + x];
	pix[1] = ptr[((y + 1) * map.width) + x];
	fdf_draw_line(pix[0], pix[1], &map);
	pix[1] = ptr[(y * map.width) + x - 1];
	fdf_draw_line(pix[0], pix[1], &map);
}

int		fdf_linter(int a, int b, double k)
{
	int		red;
	int		green;
	int		blue;

	k = fabs(k);
	blue = a & 0xff;
	green = a & 0xff00;
	red = a & 0xff0000;
	k = k > 1.0 ? 1.0 : k;
	blue = 0xff & ((int)(blue + ((blue - (b & 0xff)) * k)));
	green = 0xff00 & ((int)(green + ((green - (b & 0xff00)) * k)));
	red = 0xff0000 & ((int)(red + ((red - (b & 0xff0000)) * k)));
	return (blue | green | red);
}

void	fdf_scale(t_map *map)
{
	if (map->width > map->height)
		map->f = WIDTH / map->width;
	else
		map->f = HEIGHT / map->height;
}

void	fdf_center(t_map *map)
{
	t_point *ptr;
	size_t	cunt;
	int		min_z;
	int		max_z;

	ptr = (t_point *)map->arr.array;
	min_z = ptr[0].z;
	max_z = ptr[0].z;
	cunt = 1;
	while (cunt < map->arr.back)
	{
		if (ptr[cunt].z < min_z)
			min_z = ptr[cunt].z;
		if (ptr[cunt].z > max_z)
			max_z = ptr[cunt].z;
		cunt++;
	}
	max_z = (max_z - min_z) >> 1;
	while (cunt-- > 0)
	{
		ptr[cunt].x -= map->width >> 1;
		ptr[cunt].y -= map->height >> 1;
		ptr[cunt].z -= max_z;
	}
	fdf_scale(map);
}
