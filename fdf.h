/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:35:24 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 18:58:22 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define HEIGHT 1000
# define WIDTH 1000
# include <mlx.h>
# include <math.h>
# include "libft/includes/libft.h"

typedef	struct	s_ints
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			d;
	int			d1;
	int			d2;
	int			x0;
	int			y0;
	int			col;
	int			cola;
}				t_ints;
typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;
typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}				t_pixel;
typedef struct	s_vertex
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vertex;
typedef struct	s_matrix
{
	t_vertex	row[4];
}				t_matrix;
typedef struct	s_map
{
	t_vector	arr;
	size_t		width;
	size_t		height;
	t_vertex	rot;
	t_vertex	camera;
	double		f;
	double		flatness;
	void		*mlx;
	void		*window;
	char		help;
	char		proj;
}				t_map;

void			fdf_error(char *error, t_map *parameter);
void			fdf_usage(void);
void			fdf_help(t_map *map);
int				fdf_linter(int a, int b, double k);
void			fdf_center(t_map *map);
int				fdf_draw(t_map *parameter);
void			fdf_line(t_pixel *ptr, int x, int y, t_map map);
int				fdf_key(int keycode, t_map *parameter);
int				fdf_exit_x(t_map *parameter);
t_map			fdf_read(int fd);
void			fdf_destruct(t_map *map);
t_vertex		vtx(double x, double y, double z, double w);
t_matrix		mtx_rot_x(double anlge);
t_matrix		mtx_rot_y(double anlge);
t_matrix		mtx_rot_z(double anlge);
t_vertex		mtx_vtx_mult(t_matrix mtx, t_vertex vtx);
t_matrix		mtx_compose(t_matrix one, t_matrix two);
t_matrix		mtx_translation(double x, double y, double z);
void			fdf_draw_line(t_pixel a, t_pixel b, t_map *map);
#endif
