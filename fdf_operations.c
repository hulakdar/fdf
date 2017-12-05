/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:32:24 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/04 16:35:33 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vertex	vtx(double x, double y, double z, double w)
{
	t_vertex res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return (res);
}

t_vertex	mtx_vtx_mult(t_matrix mtx, t_vertex vtx)
{
	t_vertex result;

	result.x = mtx.row[0].x * vtx.x + mtx.row[0].y * vtx.y;
	result.x += mtx.row[0].z * vtx.z + mtx.row[0].w * vtx.w;
	result.y = mtx.row[1].x * vtx.x + mtx.row[1].y * vtx.y;
	result.y += mtx.row[1].z * vtx.z + mtx.row[1].w * vtx.w;
	result.z = mtx.row[2].x * vtx.x + mtx.row[2].y * vtx.y;
	result.z += mtx.row[2].z * vtx.z + mtx.row[2].w * vtx.w;
	result.w = mtx.row[3].x * vtx.x + mtx.row[3].y * vtx.y;
	result.w += mtx.row[3].z * vtx.z + mtx.row[3].w * vtx.w;
	return (result);
}

t_matrix	mtx_compose(t_matrix one, t_matrix two)
{
	t_matrix res;

	res.row[0] = mtx_vtx_mult(two, one.row[0]);
	res.row[1] = mtx_vtx_mult(two, one.row[1]);
	res.row[2] = mtx_vtx_mult(two, one.row[2]);
	res.row[3] = mtx_vtx_mult(two, one.row[3]);
	return (res);
}

t_matrix	mtx_translation(double x, double y, double z)
{
	t_matrix res;

	res.row[0] = vtx(1.0, 0.0, 0.0, x);
	res.row[1] = vtx(0.0, 1.0, 0.0, y);
	res.row[2] = vtx(0.0, 0.0, 1.0, z);
	res.row[3] = vtx(0.0, 0.0, 0.0, 1.0);
	return (res);
}
