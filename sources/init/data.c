/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:36:43 by arincon           #+#    #+#             */
/*   Updated: 2023/12/05 16:09:56 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img(t_img *image)
{
	image->img = NULL;
	image->path = NULL;
	image->addr = 0;
	image->bpp = 0;
	image->size_line = 0;
	image->endian = 0;
}

static void	init_file(t_file *file)
{
	file->file = NULL;
	file->path = NULL;
	file->n_lines = 0;
}

static void	init_map(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->offx = 0;
	map->offy = 0;
}

static void	init_player(t_player *player)
{
	player->ang = -1;
	player->x = 0.0;
	player->y = 0.0;
	player->dx = 0.0;
	player->dy = 0.0;
	player->px = 0.0;
	player->py = 0.0;
	player->moved = 0;
	player->mini_x = 0;
	player->mini_y = 0;
	player->mx = 0;
	player->my = 0;
	player->rotate = 0;
}

void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	init_file(&data->file);
	init_map(&data->map);
	init_player(&data->player);
	init_img(&data->no);
	init_img(&data->ea);
	init_img(&data->we);
	init_img(&data->so);
	data->f_color = NULL;
	data->c_color = NULL;
	data->f_color_hex = 0;
	data->c_color_hex = 0;
	data->pixel_tab = NULL;
}
