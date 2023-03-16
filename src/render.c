/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:16:52 by jinholee          #+#    #+#             */
/*   Updated: 2023/03/16 16:14:25 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= W_SIZE || y < 0 || y >= H_SIZE)
		return ;
	offset = (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	dst = mlx->img_addr + offset;
	*(unsigned int *)dst = color;
}

void	plot_low(t_mlx *mlx, t_point from, t_point to)
{
	int	dx;
	int	dy;
	int	yi;
	int	p;

	dx = to.x - from.x;
	dy = to.y - from.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	p = 2 * dy - dx;
	while (from.x < to.x)
	{
		ft_mlx_pixel_put(mlx, from.x++, from.y, from.color);
		if (p > 0)
		{
			from.y += yi;
			p += 2 * (dy - dx);
		}
		else
			p += 2 * dy;
	}
}

void	plot_high(t_mlx *mlx, t_point from, t_point to)
{
	int	dx;
	int	dy;
	int	xi;
	int	p;

	dx = to.x - from.x;
	dy = to.y - from.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	p = 2 * dx - dy;
	while (from.y < to.y)
	{
		ft_mlx_pixel_put(mlx, from.x, from.y++, from.color);
		if (p > 0)
		{
			from.x += xi;
			p += 2 * (dx - dy);
		}
		else
			p += 2 * dx;
	}
}

void	draw_line(t_mlx *mlx, t_point from, t_point to)
{
	int	dx;
	int	dy;

	dx = to.x - from.x;
	dy = to.y - from.y;
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	if (dy < dx)
	{
		if (from.x > to.x)
			plot_low(mlx, to, from);
		else
			plot_low(mlx, from, to);
	}
	else
	{
		if (from.y > to.y)
			plot_high(mlx, to, from);
		else
			plot_high(mlx, from, to);
	}
}

void	draw_image(t_mlx *mlx)
{
	int		x;
	int		y;
	t_map	*map_info;
	t_point	from;
	t_point	to;

	map_info = &mlx->map;
	y = 0;
	while (y < map_info->height)
	{
		x = 0;
		while (x < map_info->width)
		{
			from = calc_position(&map_info->matrix[y][x], &mlx->info);
			to = calc_position(&map_info->matrix[y][x], &mlx->info);
			if (x < map_info->width - 1)
				to = calc_position(&map_info->matrix[y][x + 1], &mlx->info);
			draw_line(mlx, from, to);
			if (y < map_info->height - 1)
				to = calc_position(&map_info->matrix[y + 1][x], &mlx->info);
			draw_line(mlx, from, to);
			x++;
		}
		y++;
	}
}
