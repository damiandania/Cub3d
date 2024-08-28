/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:18:08 by ddania-c          #+#    #+#             */
/*   Updated: 2023/12/06 14:17:07 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>

// MACROS__________________________________________________

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define SQUARE_SIZE 15
# define IMAGE_SIZE 64
# define SPEED_ROT 0.012
# define SPEED_MOV 0.012
# define SPEED_SPRITE 50

// COLORS__________________________________________________

# define BGREY 0x404040
# define GREY 0x808080
# define BLACK 0x010000
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define RED 0xFF0000
# define GREEN 0x7FFF00
# define BLUE 0x0066ff

//	STRUC__________________________________________________

typedef struct s_img
{
	void	*img;
	char	*path;
	int		*addr;
	int		bpp;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		dir;
	int		offx;
	int		offy;
}			t_map;

typedef struct s_file
{
	char	**file;
	char	*path;
	int		n_lines;
}			t_file;

typedef struct s_player
{
	int		ang;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		moved;
	int		mx;
	int		my;
	int		rotate;
	int		mini_x;
	int		mini_y;
}			t_player;

typedef struct s_ray
{
	double	cam;
	double	dx;
	double	dy;
	int		x;
	int		y;
	int		step_x;
	int		step_y;
	double	side_dx;
	double	side_dy;
	double	delta_dx;
	double	delta_dy;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		text_x;
	int		text_y;
	double	step;
	double	text_pos;
}			t_ray;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_file			file;
	t_map			map;
	t_player		player;
	t_img			no;
	t_img			ea;
	t_img			we;
	t_img			so;
	t_img			sprite;
	t_ray			ray;
	char			*f_color;
	char			*c_color;
	unsigned long	f_color_hex;
	unsigned long	c_color_hex;
	int				**pixel_tab;
	int				**text_pixel;
	int				frame_counter;
}			t_data;

enum e_text_dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

//	FUNTIONS_______________________________________________

// init
void	init_data(t_data *data);
void	init_win(t_data *data);
void	init_ray(t_ray *ray);
void	init_img(t_img *image);
void	set_raydata(int i, t_ray *ray, t_player *player);

//	parsing
void	check_parsing(t_data *data, char **argv);
void	check_map(t_data *data);
int		check_color_and_convert(t_data *data, char *color, int flag);
void	file_stock(t_data *data, char *path);
void	map_stock(t_data *data);
void	player_stock(t_data *data, char **map);

//	render
int		render(t_data *data);
void	render_image(t_data *data);
void	calculate_offset(t_data *data);
void	render_minimap(t_data *data, int offsetx, int offsety);
void	render_player(t_data *data, int offsetx, int offsety);
int		render_map(t_data *data);
void	raycasting(t_data *data, t_ray *ray, t_player *player);
void	set_textures(t_data *data, t_ray *ray, int x);
void	create_picture(t_data *data);

// events
void	check_events(t_data *data);
int		move_player(t_player *player, char **map);

// free
void	ft_error(char *str, t_data *data);
void	ft_destroy_free(t_data *data);
void	ft_free_tab(char **tab);
void	free_pixel_tab(int **tab);

// utils
int		get_map_height(char **file, int y);
int		get_map_width(char **file, int y, int end);

// bonus
int		check_map_case_bonus(t_map m, int i, int j);
void	check_map_char_bonus(t_data *data);

#endif
