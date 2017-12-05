/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 18:00:30 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 19:00:42 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_destruct(t_map *map)
{
	free(map->arr.array);
}

void	fdf_error(char *error, t_map *parameter)
{
	ft_putendl(error);
	if (parameter)
		fdf_destruct(parameter);
	exit(0);
}

void	fdf_usage(void)
{
	ft_putendl("usage: ./fdf target_file");
	exit(0);
}

int		fdf_key(int keycode, t_map *map)
{
	if (keycode == 53)
		fdf_exit_x(map);
	else if (keycode == 123 || keycode == 124)
		map->rot.y += keycode - 123 ? -0.1 : 0.1;
	else if (keycode == 78 || keycode == 69)
		map->f -= (double)(keycode - 74);
	else if (keycode == 126 || keycode == 125)
		map->rot.x -= keycode - 125 ? 0.1 : -0.1;
	else if (keycode == 2 || keycode == 0)
		map->camera.x += (keycode - 1) << 2;
	else if (keycode == 1 || keycode == 13)
		map->camera.y += keycode - 13 ? 1 : -1;
	else if (keycode == 5 || keycode == 4)
		map->camera.z += keycode == 5 ? 0.1 : -0.1;
	else if (keycode == 6)
		map->rot.z += 0.1;
	else if (keycode == 7)
		map->rot.z -= 0.1;
	else if (keycode == 12 || keycode == 14)
		map->flatness -= keycode == 12 ? 0.1 : -0.1;
	else if (keycode == 49)
		map->help = map->help ? 0 : 1;
	else if (keycode == 35)
		map->proj = map->proj ? 0 : 1;
	return (fdf_draw(map));
}

int		fdf_exit_x(t_map *parameter)
{
	fdf_destruct(parameter);
	exit(0);
	return (0);
}
