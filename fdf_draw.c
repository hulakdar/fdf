/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:05:34 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 17:07:55 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel		fdf_project(t_map map, t_vertex vtx)
{
	t_pixel	pix;

	pix.x = vtx.x * map.f;
	pix.y = vtx.y * map.f;
	return (pix);
}

t_vertex	fdf_to_vtx(t_point point)
{
	t_vertex	vtx;

	vtx.x = (double)point.x;
	vtx.y = (double)point.y;
	vtx.z = (double)point.z;
	vtx.w = 1.0;
	return (vtx);
}

void		fdf_line_generate(t_pixel *ptr, t_map map)
{
	size_t		y;
	size_t		x;
	t_pixel		pix[2];

	y = 0;
	while (y + 1 < map.height)
	{
		pix[0] = ptr[(y * map.width)];
		pix[1] = ptr[((y + 1) * map.width)];
		fdf_draw_line(pix[0], pix[1], &map);
		x = 1;
		while (x < map.width)
			fdf_line(ptr, x++, y, map);
		y++;
	}
	x = 0;
	while (x + 1 < map.width)
	{
		pix[0] = ptr[(y * map.width) + x];
		pix[1] = ptr[(y * map.width) + x + 1];
		fdf_draw_line(pix[0], pix[1], &map);
		x++;
	}
}

void		fdf_render(t_map map, t_matrix rotations)
{
	t_point		point;
	t_point		*ptr;
	t_pixel		new;
	t_vector	vect;

	vect = ft_vectornew(sizeof(t_pixel), (map.height + 1) * map.width);
	while ((ptr = ft_vectorpopback(&(map.arr))))
	{
		point = *ptr;
		point.z *= map.flatness;
		new = fdf_project(map, mtx_vtx_mult(rotations, fdf_to_vtx(point)));
		new.color = point.color;
		new.x += WIDTH >> 1;
		new.y += HEIGHT >> 1;
		mlx_pixel_put(map.mlx, map.window, new.x, new.y, new.color);
		ft_vectorpushback(&vect, &new);
	}
	fdf_line_generate(vect.array, map);
	ft_vectordel(&vect);
}

void		fdf_draw(t_map *map)
{
	t_matrix		camera;
	t_matrix		rotations;

	mlx_clear_window(map->mlx, map->window);
	rotations = mtx_compose(mtx_compose(mtx_rot_y(map->rot.y),
				mtx_rot_x(map->rot.x)), mtx_rot_z(map->rot.z));
	camera = mtx_translation(map->camera.x, map->camera.y, map->camera.z);
	rotations = mtx_compose(camera, rotations);
	fdf_render(*map, rotations);
	fdf_help(map);
}
