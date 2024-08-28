/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:06:51 by damian            #+#    #+#             */
/*   Updated: 2023/12/05 16:12:52 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	open_img(t_data *data, t_img *img)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	img->img = mlx_xpm_file_to_image(data->mlx_ptr, img->path, &width, &height);
	if (!img->img)
		ft_error("Xpm to image failed\n", data);
	if (width != IMAGE_SIZE || height != IMAGE_SIZE)
		ft_error("The image format must be: 64x64\n", data);
	img->size_line = width;
	img->addr = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_line, &img->endian);
}

static void	ft_img(t_data *data)
{
	open_img(data, &data->no);
	open_img(data, &data->so);
	open_img(data, &data->ea);
	open_img(data, &data->we);
	if (BONUS == 1)
	{
		data->sprite = data->no;
		data->frame_counter = 0;
	}
}

void	init_win(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_error("Error ptr mlx", data);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		ft_error("Error window mlx", data);
	}
	ft_img(data);
}
