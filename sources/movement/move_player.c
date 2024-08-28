/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arincon <arincon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:11:11 by ddania-c          #+#    #+#             */
/*   Updated: 2023/11/30 17:16:19 by arincon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_pos(char **map, double x, double y)
{
	int	y1;
	int	x1;

	y1 = floor(y);
	x1 = floor(x);
	if (map[y1][x1] != '0')
		return (1);
	return (0);
}

static int	move_y(t_player *player, char **map)
{
	if (player->my == 1)
	{
		if (!BONUS || check_pos(map, player->x + player->dx * SPEED_MOV,
				player->y + player->dy * SPEED_MOV) == 0)
		{
			player->x += player->dx * SPEED_MOV;
			player->y += player->dy * SPEED_MOV;
		}
	}
	if (player->my == -1)
	{
		if (!BONUS || check_pos(map, player->x - player->dx * SPEED_MOV,
				player->y - player->dy * SPEED_MOV) == 0)
		{
			player->x -= player->dx * SPEED_MOV;
			player->y -= player->dy * SPEED_MOV;
		}
	}
	return (1);
}

static int	move_x(t_player *player, char **map)
{
	if (player->mx == -1)
	{
		if (!BONUS || check_pos(map, player->x + player->dy * SPEED_MOV,
				player->y - player->dx * SPEED_MOV) == 0)
		{
			player->x += player->dy * SPEED_MOV;
			player->y -= player->dx * SPEED_MOV;
		}
	}
	if (player->mx == 1)
	{
		if (!BONUS || check_pos(map, player->x - player->dy * SPEED_MOV,
				player->y + player->dx * SPEED_MOV) == 0)
		{
			player->x -= player->dy * SPEED_MOV;
			player->y += player->dx * SPEED_MOV;
		}
	}
	return (1);
}

int	move_rotate(t_player *player)
{
	double	tmp_x;
	double	rotspeed;

	rotspeed = SPEED_ROT * player->rotate;
	tmp_x = player->dx;
	player->dx = player->dx * cos(rotspeed) - player->dy * sin(rotspeed);
	player->dy = tmp_x * sin(rotspeed) + player->dy * cos(rotspeed);
	tmp_x = player->px;
	player->px = player->px * cos(rotspeed) - player->py * sin(rotspeed);
	player->py = tmp_x * sin(rotspeed) + player->py * cos(rotspeed);
	return (1);
}

int	move_player(t_player *player, char **map)
{
	int	moved;

	moved = 0;
	if (player->my != 0)
		moved += move_y(player, map);
	if (player->mx != 0)
		moved += move_x(player, map);
	if (player->rotate != 0)
		moved += move_rotate(player);
	return (moved);
}
