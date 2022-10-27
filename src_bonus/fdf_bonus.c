/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:43:34 by jinholee          #+#    #+#             */
/*   Updated: 2022/10/27 18:02:07 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf_bonus.h"

void	mlx_render(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx, W_SIZE, H_SIZE);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
					&mlx->line_length, &mlx->endian);
	draw_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc == 2)
	{
		create_map(argv[1], &mlx.map);
		parse_map(argv[1], &mlx.map);
		info_init(&mlx);
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, W_SIZE, H_SIZE, "FDF");
		mlx_render(&mlx);
		mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &mlx);
		mlx_loop(mlx.mlx);
	}
	return (0);
}
