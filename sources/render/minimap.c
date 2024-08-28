/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:22:37 by ddania-c          #+#    #+#             */
/*   Updated: 2023/12/05 16:57:32 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_square_mini(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SQUARE_SIZE)
	{
		j = 0;
		while (j < SQUARE_SIZE)
		{
			if (y >= 0 && x >= 0)
				data->pixel_tab[y + j + 5][x + i + 5] = color;
			j++;
		}
		i++;
	}
}

void	calculate_offset(t_data *data)
{
	int		m_width;
	int		m_height;

	data->player.mini_x = round(data->player.x - 0.5);
	data->player.mini_y = round(data->player.y - 0.5);
	m_width = (data->map.width - 1) * SQUARE_SIZE;
	m_height = (data->map.height - 1) * SQUARE_SIZE;
	data->map.offx = 8 * SQUARE_SIZE / 2 - data->player.mini_x * SQUARE_SIZE;
	data->map.offy = 8 * SQUARE_SIZE / 2 - data->player.mini_y * SQUARE_SIZE;
	if (data->player.mini_x * SQUARE_SIZE < 8 * SQUARE_SIZE / 2)
		data->map.offx = 0;
	else if (data->player.mini_x * SQUARE_SIZE > m_width - 8 * SQUARE_SIZE / 2)
		data->map.offx = 8 * SQUARE_SIZE - m_width;
	if (data->player.mini_y * SQUARE_SIZE < 8 * SQUARE_SIZE / 2)
		data->map.offy = 0;
	else if (data->player.mini_y * SQUARE_SIZE > m_height - 8 * SQUARE_SIZE / 2)
		data->map.offy = 8 * SQUARE_SIZE - m_height;
}

static void	draw_frame(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < 9 * SQUARE_SIZE + 10)
	{
		x = 0;
		while (x < 9 * SQUARE_SIZE + 10)
		{
			data->pixel_tab[y][x] = BLACK;
			x++;
		}
		y++;
	}
}

void	render_minimap(t_data *data, int offx, int offy)
{
	int		x;
	int		y;
	char	**map;

	draw_frame(data);
	y = 0;
	map = data->map.map;
	while (map[y] && y <= 8 - offy / SQUARE_SIZE)
	{
		x = 0;
		while (map[y][x] && x <= 8 - offx / SQUARE_SIZE)
		{
			if (map[y][x] == '1' || map[y][x] == '2')
				draw_square_mini(data, x * SQUARE_SIZE + offx,
					y * SQUARE_SIZE + offy, data->f_color_hex);
			else if (map[y][x] == '0')
				draw_square_mini(data, x * SQUARE_SIZE + offx,
					y * SQUARE_SIZE + offy, data->c_color_hex);
			x++;
		}
		y++;
	}
}
