/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:55:32 by ddania-c          #+#    #+#             */
/*   Updated: 2023/12/05 17:11:42 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_line(t_data *data, double x, double y, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		if (y >= 0 && x >= 0)
		{
			y = y + data->player.dy;
			x = x + data->player.dx;
			data->pixel_tab[(int)y][(int)x] = RED;
		}
		i++;
	}
}

void	render_player(t_data *data, int offsetx, int offsety)
{
	double	px;
	double	px1;
	double	py;
	double	py1;
	int		size;

	size = SQUARE_SIZE * 0.90;
	py = data->player.y * SQUARE_SIZE + offsety;
	px = data->player.x * SQUARE_SIZE + offsetx;
	px1 = px;
	py1 = py;
	draw_line(data, px, py, size);
	while (size > 0)
	{
		draw_line(data, px += data->player.px, py += data->player.py, size);
		draw_line(data, px1 -= data->player.px, py1 -= data->player.py, size);
		size = size - 2;
	}
}
