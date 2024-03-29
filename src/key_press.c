/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:14:57 by jinholee          #+#    #+#             */
/*   Updated: 2023/03/16 15:56:18 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	mlx_exit(t_mlx *mlx)
{
	int	h;

	h = 0;
	while (h < mlx->map.height)
		free(mlx->map.matrix[h++]);
	free(mlx->map.matrix);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

void	scale_adjust(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		mlx->info.z_scale += 0.1;
	else if (keycode == KEY_S)
		mlx->info.z_scale -= 0.1;
	else if (keycode == KEY_A)
		mlx->info.x_scale -= 0.1;
	else if (keycode == KEY_D)
		mlx->info.x_scale += 0.1;
	else if (keycode == KEY_Q)
		mlx->info.y_scale -= 0.1;
	else if (keycode == KEY_E)
		mlx->info.y_scale += 0.1;
	else if (keycode == KEY_PLUS)
		mlx->info.scale += 0.1;
	else if (keycode == KEY_MINUS)
		mlx->info.scale -= 0.1;
}

void	angle_adjust(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_I)
		mlx->info.x_angle += M_PI / 12;
	else if (keycode == KEY_J)
		mlx->info.x_angle -= M_PI / 12;
	else if (keycode == KEY_O)
		mlx->info.y_angle += M_PI / 12;
	else if (keycode == KEY_K)
		mlx->info.y_angle -= M_PI / 12;
	else if (keycode == KEY_P)
		mlx->info.z_angle += M_PI / 12;
	else if (keycode == KEY_L)
		mlx->info.z_angle -= M_PI / 12;
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		mlx_exit(mlx);
	return (0);
}
