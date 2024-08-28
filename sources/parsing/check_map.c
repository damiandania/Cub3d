/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:11:44 by arincon           #+#    #+#             */
/*   Updated: 2023/12/06 15:56:41 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_map_char(t_data *data)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			while (data->map.map[i][j] == ' ' && data->map.map[i][j])
				j++;
			if (!ft_strchr("10NWSE", data->map.map[i][j]))
				ft_error("Invalid character on the map\n", data);
			if (ft_strchr("NWSE", data->map.map[i][j]))
				player++;
			j++;
		}
		i++;
	}
	if (player > 1)
		ft_error("Multiples player on the map\n", data);
	if (player == 0)
		ft_error("No player on the map\n", data);
}

static int	check_map_case(t_map m, int i, int j)
{
	int	width;

	width = ft_strlen(m.map[i]);
	if ((i + 1 >= m.height || !m.map[i + 1][j]
		|| !ft_strchr("10NWSE", m.map[i + 1][j]))
		|| (i - 1 < 0 || !m.map[i - 1][j]
		|| !ft_strchr("10NWSE", m.map[i - 1][j]))
		|| (j + 1 >= width || !m.map[i][j + 1]
		|| !ft_strchr("10NWSE", m.map[i][j + 1]))
		|| (j - 1 < 0 || !m.map[i][j - 1]
		|| !ft_strchr("10NWSE", m.map[i][j - 1]))
		|| (i + 1 >= m.height || j + 1 >= width || !m.map[i + 1][j + 1]
		|| !ft_strchr("10NWSE", m.map[i + 1][j + 1]))
		|| (i - 1 < 0 || j - 1 < 0 || !m.map[i - 1][j - 1]
		|| !ft_strchr("10NWSE", m.map[i - 1][j - 1]))
		|| (i + 1 >= m.height || j - 1 < 0 || !m.map[i + 1][j - 1]
		|| !ft_strchr("10NWSE", m.map[i + 1][j - 1]))
		|| (i - 1 < 0 || j + 1 >= width || !m.map[i - 1][j + 1]
		|| !ft_strchr("10NWSE", m.map[i - 1][j + 1])))
		return (1);
	return (0);
}

static void	check_map_is_close(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if ((data->map.map[i][j] == '0' || data->map.map[i][j] == 'S'
					|| data->map.map[i][j] == 'N' || data->map.map[i][j] == 'E'
					|| data->map.map[i][j] == 'W') && !BONUS)
				if (check_map_case(data->map, i, j) == 1)
					ft_error("The map is not closed\n", data);
			if ((data->map.map[i][j] == '0' || data->map.map[i][j] == 'S'
					|| data->map.map[i][j] == 'N' || data->map.map[i][j] == 'E'
					|| data->map.map[i][j] == 'W') && BONUS == 1)
				if (check_map_case_bonus(data->map, i, j) == 1)
					ft_error("The map is not closed\n", data);
			j++;
		}
		i++;
	}
}

static void	map_swap(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = data->map.map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				map[y][x] = '1';
			if (ft_strchr("NWSE", map[y][x]))
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	check_map(t_data *data)
{
	if (BONUS == 1)
		check_map_char_bonus(data);
	else
		check_map_char(data);
	check_map_is_close(data);
	map_swap(data);
	data->c_color_hex = check_color_and_convert(data, data->c_color, 0);
	data->f_color_hex = check_color_and_convert(data, data->f_color, 1);
}
	// int i = 0;
	// printf("before swap\n");
	// while (data->map.map[i])
	// 	printf("%s\n", data->map.map[i++]);
	// int i2 = 0;
	// printf("\nafter swap\n");
	// while (data->map.map[i2])
	// 	printf("%s\n", data->map.map[i2++]);
