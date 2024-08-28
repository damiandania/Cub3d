/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:25:19 by ddania-c          #+#    #+#             */
/*   Updated: 2023/12/05 14:10:21 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_sidedata(t_ray *ray, t_player *player)
{
	if (ray->dx < 0)
	{
		ray->step_x = -1;
		ray->side_dx = (player->x - ray->x) * ray->delta_dx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dx = (ray->x + 1.0 - player->x) * ray->delta_dx;
	}
	if (ray->dy < 0)
	{
		ray->step_y = -1;
		ray->side_dy = (player->y - ray->y) * ray->delta_dy;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dy = (ray->y + 1.0 - player->y) * ray->delta_dy;
	}
}

static void	dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->y += ray->step_y;
			ray->side = 1;
		}
		if (ray->y < 0.25
			|| ray->x < 0.25
			|| ray->y > data->map.height - 0.25
			|| ray->x > data->map.width - 1.25)
			break ;
		else if (data->map.map[ray->y][ray->x] > '0')
			hit = 1;
	}
}

static void	calculate_line_height(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dx - ray->delta_dx);
	else
		ray->wall_dist = (ray->side_dy - ray->delta_dy);
	ray->line_height = WIN_HEIGHT / ray->wall_dist;
	ray->draw_start = -(ray->line_height) / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	(void)player;
	if (ray->side == 0)
		ray->wall_x = player->y + ray->wall_dist * ray->dy;
	else
		ray->wall_x = player->x + ray->wall_dist * ray->dx;
	ray->wall_x -= floor(ray->wall_x);
}

void	raycasting(t_data *data, t_ray *ray, t_player *player)
{
	int	x;

	x = 0;
	init_ray(ray);
	while (x < WIN_WIDTH)
	{
		set_raydata(x, ray, player);
		set_sidedata(ray, player);
		dda(data, ray);
		calculate_line_height(ray, player);
		set_textures(data, ray, x);
		x++;
	}
}
