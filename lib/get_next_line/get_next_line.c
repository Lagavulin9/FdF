/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:41:28 by jinholee          #+#    #+#             */
/*   Updated: 2022/10/26 16:16:03 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static t_gnl_info	info = {"", BUFFER_SIZE, 0, 0, BUFFER_SIZE};
	char				*line;

	if (!init(fd, &line, &info))
		return (0);
	while (1)
	{
		if ((size_t)info.rbyte == info.index)
		{
			line = join(line, &info);
			info.rbyte = read(fd, info.buffer, BUFFER_SIZE);
			if (buf_end(&line, &info))
				return (line);
			info.index = 0;
		}
		if (info.buffer[info.index] == '\n')
		{
			info.index++;
			info.len++;
			return (join(line, &info));
		}
		info.index++;
		info.len++;
	}
}
