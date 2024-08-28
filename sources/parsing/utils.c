/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arincon <arincon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:54:12 by arincon           #+#    #+#             */
/*   Updated: 2023/12/04 15:01:25 by arincon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_height(char **file, int y)
{
	int	ret;
	int	x;

	ret = 0;
	while (file[y])
	{
		x = 0;
		while (file[y][x] == ' ')
			x++;
		if (file[y][x] == '\n' || file[y][x] == '\0')
			break ;
		y++;
		ret++;
	}
	return (ret);
}

int	get_map_width(char **file, int y, int end)
{
	size_t	len;

	len = ft_strlen(file[y]);
	while (end--)
	{
		if (ft_strlen(file[y]) > len)
			len = ft_strlen(file[y]);
		y++;
	}
	return (len);
}

void	check_map_char_bonus(t_data *data)
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
			if (!ft_strchr("210NWSE", data->map.map[i][j]))
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

int	check_map_case_bonus(t_map m, int i, int j)
{
	int	width;

	width = ft_strlen(m.map[i]);
	if ((i + 1 >= m.height || !m.map[i + 1][j]
		|| !ft_strchr("210NWSE", m.map[i + 1][j]))
		|| (i - 1 < 0 || !m.map[i - 1][j]
		|| !ft_strchr("210NWSE", m.map[i - 1][j]))
		|| (j + 1 >= width || !m.map[i][j + 1]
		|| !ft_strchr("210NWSE", m.map[i][j + 1]))
		|| (j - 1 < 0 || !m.map[i][j - 1]
		|| !ft_strchr("210NWSE", m.map[i][j - 1]))
		|| (i + 1 >= m.height || j + 1 >= width || !m.map[i + 1][j + 1]
		|| !ft_strchr("210NWSE", m.map[i + 1][j + 1]))
		|| (i - 1 < 0 || j - 1 < 0 || !m.map[i - 1][j - 1]
		|| !ft_strchr("210NWSE", m.map[i - 1][j - 1]))
		|| (i + 1 >= m.height || j - 1 < 0 || !m.map[i + 1][j - 1]
		|| !ft_strchr("210NWSE", m.map[i + 1][j - 1]))
		|| (i - 1 < 0 || j + 1 >= width || !m.map[i - 1][j + 1]
		|| !ft_strchr("210NWSE", m.map[i - 1][j + 1])))
		return (1);
	return (0);
}
