/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:53:06 by jinholee          #+#    #+#             */
/*   Updated: 2022/10/27 18:02:45 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define W_SIZE 1280
# define H_SIZE 960

# define X_EVENT_KEY_PRESS 2 
# define X_EVENT_KEY_RELEASE 3

# define KEY_W 13        
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_R 15
# define KEY_I 34
# define KEY_O 31
# define KEY_P 35
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_ESC 53
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ARROW_UP 126
# define KEY_ARROW_DOWN 125
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124

typedef struct s_info
{
	float	x_scale;
	float	x_angle;
	float	y_scale;
	float	y_angle;
	float	z_scale;
	float	z_angle;
	float	scale;
	int		x_offset;
	int		y_offset;
	int		transformed;
}	t_info;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		min_value;
	int		max_value;
	t_point	**matrix;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	map;
	t_info	info;
}	t_mlx;

/* ************************************************************************** */
/* create_map.c */
int		get_color(char *rgb);
int		get_map_width(char *row);
void	add_point(t_map *map_info, int x, int y, char *data);
void	parse_map(char *to_read, t_map *map_info);
void	create_map(char *to_read, t_map *map_info);

/* ************************************************************************** */
/* err_check.c */
int		is_valid_value(char *value);
int		is_valid_rgb(char *value);
void	check_map_error(char **row, t_map map_info);

/* ************************************************************************** */
/* key_press.c */
void	mlx_exit(t_mlx *mlx);
void	scale_adjust(int keycode, t_mlx *mlx);
void	angle_adjust(int keycode, t_mlx *mlx);
int		key_press(int keycode, t_mlx *mlx);

/* ************************************************************************** */
/* transform.c */
void	roll(t_point *point, double theta);
void	pitch(t_point *point, double theta);
void	yaw(t_point *point, double theta);
void	isometric_transform(t_point *point);
t_point	calc_position(t_point *p, t_info *info);

/* ************************************************************************** */
/* render.c */
void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	plot_low(t_mlx *mlx, t_point from, t_point to);
void	plot_high(t_mlx *mlx, t_point from, t_point to);
void	draw_line(t_mlx *mlx, t_point from, t_point to);
void	draw_image(t_mlx *mlx);

/* ************************************************************************** */
/* utils.c */
void	perror_exit(char *msg);
void	free_split(char **splitted);
void	info_init(t_mlx *mlx);

/* ************************************************************************** */
/* fdf.c */
void	mlx_render(t_mlx *mlx);
int		main(int argc, char *argv[]);

#endif