/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:42:40 by jinholee          #+#    #+#             */
/*   Updated: 2023/03/16 15:57:29 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	perror_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(0);
}

void	free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}

void	info_init(t_mlx *mlx)
{
	t_info	*info;

	info = &mlx->info;
	info->x_scale = (float)W_SIZE / (float)(mlx->map.width * 4);
	info->y_scale = (float)H_SIZE / (float)(mlx->map.height * 4);
	info->z_scale = 1;
	info->x_angle = 0;
	info->y_angle = 0;
	info->z_angle = 0;
	info->scale = 1;
	info->x_offset = (W_SIZE / 2);
	info->y_offset = mlx->map.height * info->y_scale;
}
