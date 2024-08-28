/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:38:46 by arincon           #+#    #+#             */
/*   Updated: 2023/11/30 16:28:27 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray(t_ray *ray)
{
	ray->cam = 0.0;
	ray->dx = 0.0;
	ray->dy = 0.0;
	ray->x = 0;
	ray->y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_dx = 0.0;
	ray->side_dy = 0.0;
	ray->delta_dx = 0.0;
	ray->delta_dy = 0.0;
	ray->wall_dist = 0.0;
	ray->wall_x = 0.0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	set_raydata(int i, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->cam = 2 * i / (double)WIN_WIDTH - 1;
	ray->dx = player->dx + player->px * ray->cam;
	ray->dy = player->dy + player->py * ray->cam;
	ray->x = (int)player->x;
	ray->y = (int)player->y;
	ray->delta_dx = fabs(1 / ray->dx);
	ray->delta_dy = fabs(1 / ray->dy);
}
