/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:47:00 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 18:55:46 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_mouse(int keycode, int x, int y, t_map *map)
{
	if (keycode == 5)
		map->rot.x += 0.2;
	else if (keycode == 4)
		map->rot.x -= 0.2;
	else if (keycode == 7)
		map->rot.y += 0.2;
	else if (keycode == 6)
		map->rot.y -= 0.2;
	else if (keycode == 1)
	{
		map->camera.x = (double)((x - (WIDTH >> 1)) >> 5);
		map->camera.y = (double)((y - (HEIGHT >> 1)) >> 5);
	}
	fdf_draw(map);
	return (0);
}

void	fdf_init(t_map *map)
{
	if (!(map->mlx = mlx_init()))
		fdf_error("Something went completely wrong", map);
	if (!(map->window = mlx_new_window(map->mlx,
					WIDTH, HEIGHT, "FdF")))
		fdf_error("Something went completely wrong", map);
	mlx_hook(map->window, 2, 5, fdf_key, map);
	map->camera = vtx(0.0, 0.0, 20.0, 1.0);
	map->rot = vtx(-0.6, -0.7, 0.0, 1.0);
	map->f *= 0.6;
	map->help = 1;
	map->proj = 0;
	map->flatness = -0.7;
	mlx_hook(map->window, 17, 1L << 17, fdf_exit_x, map);
	mlx_mouse_hook(map->window, (int (*)())fdf_mouse, map);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_map	map;

	if (argc != 2)
		fdf_usage();
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		fdf_error("Error opening file", NULL);
	map = fdf_read(fd);
	fdf_center(&map);
	fdf_init(&map);
	fdf_draw(&map);
	mlx_loop(map.mlx);
}
