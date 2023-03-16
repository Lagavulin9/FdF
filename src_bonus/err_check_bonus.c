/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:36:12 by jinholee          #+#    #+#             */
/*   Updated: 2023/03/16 16:00:21 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

int	is_valid_value(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '-' || value[i] == '+')
			i++;
	while (value[i])
	{
		if ('0' > value[i] || value[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_rgb(char *value)
{
	int	i;
	int	len;

	i = 0;
	if (value)
	{
		len = ft_strlen(value);
		if (len != 4 && len != 6 && len != 8)
			return (0);
		if (value[i++] != '0')
			return (0);
		if (ft_tolower(value[i++]) != 'x')
			return (0);
		while (value[i])
		{
			value[i] = ft_tolower(value[i]);
			if (!('0' <= value[i] && value[i] <= '9')
				&& !('a' <= value[i] && value[i] <= 'f'))
				return (0);
			i++;
		}
	}
	return (1);
}

void	check_map_error(char **row, t_map map_info)
{
	int		w;
	char	**values;

	w = 0;
	while (row[w] && *row[w] != '\n')
	{
		values = ft_split(row[w], ",");
		if (!is_valid_value(values[0]))
			perror_exit("Invalid value in map\n");
		if (!is_valid_rgb(values[1]))
			perror_exit("Invalid rgb in map\n");
		free_split(values);
		w++;
	}
	if (w != map_info.width)
		perror_exit("Invalid map dimension\n");
}
