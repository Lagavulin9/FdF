/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:18:09 by jinholee          #+#    #+#             */
/*   Updated: 2022/10/27 19:13:06 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf_bonus.h"

void	roll(t_point *point, double theta)
{
	double	dx;
	double	dy;
	double	dz;

	dx = point->x;
	dy = cos(theta) * point->y + sin(theta) * point->z;
	dz = -sin(theta) * point->y + cos(theta) * point->z;
	point->x = round(dx);
	point->y = round(dy);
	point->z = round(dz);
}

void	pitch(t_point *point, double theta)
{
	double	dx;
	double	dy;
	double	dz;

	dx = cos(theta) * point->x - sin(theta) * point->z;
	dy = point->y;
	dz = sin(theta) * point->y + cos(theta) * point->z;
	point->x = round(dx);
	point->y = round(dy);
	point->z = round(dz);
}

void	yaw(t_point *point, double theta)
{
	double	dx;
	double	dy;
	double	dz;

	dx = cos(theta) * point->x - sin(theta) * point->y;
	dy = sin(theta) * point->x + cos(theta) * point->y;
	dz = point->z;
	point->x = round(dx);
	point->y = round(dy);
	point->z = round(dz);
}

void	isometric_transform(t_point *point)
{
	int	dx;
	int	dy;

	dx = 2 * (point->x - point->y);
	dy = point->x + point->y - point->z;
	point->x = dx;
	point->y = dy;
}

t_point	calc_position(t_point *p, t_info *info)
{
	t_point	position;

	position.x = (float)p->x * info->x_scale * info->scale;
	position.y = (float)p->y * info->y_scale * info->scale;
	position.z = (float)p->z * info->z_scale * info->scale;
	isometric_transform(&position);
	roll(&position, info->x_angle);
	pitch(&position, info->y_angle);
	yaw(&position, info->z_angle);
	position.x += info->x_offset;
	position.y += info->y_offset;
	position.color = p->color;
	return (position);
}
