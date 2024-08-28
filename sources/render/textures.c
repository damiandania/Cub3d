/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:09:29 by ddania-c          #+#    #+#             */
/*   Updated: 2023/12/05 16:36:48 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_texture_dir(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dx < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->dy > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

static int	set_pixel_color(int dir, t_data *data, int y, int x)
{
	int	color;

	color = 5;
	if (data->map.map[data->ray.y][data->ray.x] == '2')
		color = data->sprite.addr[IMAGE_SIZE * y + x];
	else
	{
		if (dir == NORTH)
			color = data->no.addr[IMAGE_SIZE * y + x];
		else if (dir == SOUTH)
			color = data->so.addr[IMAGE_SIZE * y + x];
		else if (dir == WEST)
			color = data->we.addr[IMAGE_SIZE * y + x];
		else if (dir == EAST)
			color = data->ea.addr[IMAGE_SIZE * y + x];
	}
	if (color == 5)
		ft_error("Error: set_pixel_color", data);
	return (color);
}

void	set_textures(t_data *data, t_ray *ray, int x)
{
	int		color;
	int		y;
	int		dir;

	dir = set_texture_dir(ray);
	ray->text_x = (int)(ray->wall_x * IMAGE_SIZE);
	if ((ray->side == 0 && ray->dx < 0)
		|| (ray->side == 1 && ray->dy > 0))
		ray->text_x = IMAGE_SIZE - ray->text_x - 1;
	ray->step = 1.0 * IMAGE_SIZE / ray->line_height;
	ray->text_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * ray->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->text_y = (int)ray->text_pos & (IMAGE_SIZE - 1);
		ray->text_pos += ray->step;
		color = set_pixel_color(dir, data, ray->text_y, ray->text_x);
		if (dir == NORTH || dir == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0 && (!BONUS || (x > (9 * SQUARE_SIZE + 4)
					|| y > (9 * SQUARE_SIZE + 4))))
			data->pixel_tab[y][x] = color;
		y++;
	}
}
