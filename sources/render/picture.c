/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:15:17 by ddania-c          #+#    #+#             */
/*   Updated: 2023/12/05 16:56:43 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_pixel(t_img *picture, int x, int y, int color)
{
	int	pixel;

	pixel = y * (picture->size_line / 4) + x;
	picture->addr[pixel] = color;
}

static void	set_picture_pixel(t_data *data, t_img *picture, int x, int y)
{
	if (data->pixel_tab[y][x] > 0)
		set_pixel(picture, x, y, data->pixel_tab[y][x]);
	else if (y < WIN_HEIGHT / 2)
		set_pixel(picture, x, y, data->c_color_hex);
	else if (y < WIN_WIDTH - 1)
		set_pixel(picture, x, y, data->f_color_hex);
}

static void	init_picture(t_data *data, t_img *picture)
{
	init_img(picture);
	picture->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (picture->img == NULL)
		ft_error("Error: picture", data);
	picture->addr = (int *)mlx_get_data_addr(picture->img, &picture->bpp,
			&picture->size_line, &picture->endian);
}

void	create_picture(t_data *data)
{
	t_img	picture;
	int		y;
	int		x;

	y = 0;
	picture.img = NULL;
	init_picture(data, &picture);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_picture_pixel(data, &picture, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, picture.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, picture.img);
}
