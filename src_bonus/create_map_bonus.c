/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:41:14 by jinholee          #+#    #+#             */
/*   Updated: 2022/10/27 18:38:51 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "fdf_bonus.h"
#include "libft.h"
#include "get_next_line.h"

int	get_color(char *rgb)
{
	const char	*hex = "0123456789abcdef";
	int			i;
	int			color;

	color = 0;
	while (*rgb)
	{
		i = 0;
		*rgb = ft_tolower(*rgb);
		while (i < 16)
		{
			if (hex[i] == *rgb)
			{
				color = (color * 16) + i;
				break ;
			}
			i++;
		}
		rgb++;
	}
	return (color);
}

int	get_map_width(char *row)
{
	int		width;
	char	**splitted;

	width = 0;
	splitted = ft_split(row, " \n");
	while (splitted[width])
		width++;
	free_split(splitted);
	return (width);
}

void	add_point(t_map *map_info, int x, int y, char *data)
{
	char	**values;
	t_point	*point;

	point = &map_info->matrix[y][x];
	values = ft_split(data, ",");
	point->x = x;
	point->y = y;
	point->z = ft_atoi(values[0]);
	if (map_info->min_value > point->z)
		map_info->min_value = point->z;
	if (map_info->max_value < point->z)
		map_info->max_value = point->z;
	point->color = 0x00ffffff;
	if (values[1])
		point->color = get_color(values[1]);
	free_split(values);
}

void	parse_map(char *to_read, t_map *map_info)
{
	int		fd;
	int		h;
	int		w;
	char	*line;
	char	**splitted;

	fd = open(to_read, O_RDONLY);
	if (fd < 0)
		perror_exit("Could not open rgb file\n");
	h = 0;
	while (h < map_info->height)
	{
		w = 0;
		line = get_next_line(fd);
		splitted = ft_split(line, " \n");
		check_map_error(splitted, *map_info);
		while (w < map_info->width)
		{
			add_point(map_info, w, h, splitted[w]);
			w++;
		}
		free_split(splitted);
		free(line);
		h++;
	}
}

void	create_map(char *to_read, t_map *map_info)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(to_read, O_RDONLY);
	if (fd < 0)
		perror_exit(to_read);
	map_info->height = 0;
	line = get_next_line(fd);
	map_info->width = get_map_width(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		map_info->height++;
	}
	free(line);
	map_info->matrix = malloc(sizeof(t_point *) * map_info->height);
	i = 0;
	while (i < map_info->height)
		map_info->matrix[i++] = malloc(sizeof(t_point) * map_info->width);
	map_info->min_value = 2147483647;
	map_info->max_value = -2147483648;
	close(fd);
}
