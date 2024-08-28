/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arincon <arincon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:39:57 by ddania-c          #+#    #+#             */
/*   Updated: 2023/11/29 16:54:14 by arincon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_player_y(t_player *player, char c)
{
	if (c == 'N')
	{
		player->ang = 90;
		player->dx = 0;
		player->dy = -1;
		player->px = 0.66;
		player->py = 0;
	}
	else if (c == 'S')
	{
		player->ang = 270;
		player->dx = 0;
		player->dy = 1;
		player->px = -0.66;
		player->py = 0;
	}
	else
		return ;
}

static void	fill_player_x(t_player *player, char c)
{
	if (c == 'W')
	{
		player->ang = 180;
		player->dx = -1;
		player->dy = 0;
		player->px = 0;
		player->py = -0.66;
	}
	else if (c == 'E')
	{
		player->ang = 0;
		player->dx = 1;
		player->dy = 0;
		player->px = 0;
		player->py = 0.66;
	}
	else
		return ;
}

void	player_stock(t_data *data, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'W' || map[y][x] == 'E')
			{
				data->player.y = (double)y + 0.5;
				data->player.x = (double)x + 0.5;
				fill_player_y(&data->player, map[y][x]);
				fill_player_x(&data->player, map[y][x]);
			}
			x++;
		}
		y++;
	}
}
