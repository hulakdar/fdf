/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:06:39 by skamoza           #+#    #+#             */
/*   Updated: 2017/11/30 16:27:56 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	mtx_rot_x(double angle)
{
	t_matrix res;

	res.row[0] = vtx(1.0, 0.0, 0.0, 0.0);
	res.row[1] = vtx(0.0, cos(angle), -sin(angle), 0.0);
	res.row[2] = vtx(0.0, sin(angle), cos(angle), 0.0);
	res.row[3] = vtx(0.0, 0.0, 0.0, 1.0);
	return (res);
}

t_matrix	mtx_rot_y(double angle)
{
	t_matrix res;

	res.row[0] = vtx(cos(angle), 0.0, sin(angle), 0.0);
	res.row[1] = vtx(0.0, 1.0, 0.0, 0.0);
	res.row[2] = vtx(-sin(angle), 0.0, cos(angle), 0.0);
	res.row[3] = vtx(0.0, 0.0, 0.0, 1.0);
	return (res);
}

t_matrix	mtx_rot_z(double angle)
{
	t_matrix res;

	res.row[0] = vtx(cos(angle), -sin(angle), 0.0, 0.0);
	res.row[1] = vtx(sin(angle), cos(angle), 0.0, 0.0);
	res.row[2] = vtx(0.0, 0.0, 1.0, 0.0);
	res.row[3] = vtx(0.0, 0.0, 0.0, 1.0);
	return (res);
}
