/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_stock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arincon <arincon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:26:42 by damian            #+#    #+#             */
/*   Updated: 2023/12/04 14:41:15 by arincon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*texture_stock(char *line, t_data *data, char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	if (str)
		ft_error("Multiples textures for the same input\n", data);
	i = 0;
	j = 0;
	len = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	len = ft_strlen(line) - i;
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		ft_error("Wrong texture path\n", data);
	while (line[i])
	{
		ret[j] = line[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static void	fill_map(t_data *data, char **file, int y)
{
	int	i;
	int	x;

	i = 0;
	while (i < data->map.height)
	{
		x = 0;
		data->map.map[i] = malloc(sizeof(char) * (data->map.width + 1));
		if (!data->map.map)
			ft_error("Error: malloc: fill_map\n", data);
		while (file[y][x])
		{
			data->map.map[i][x] = file[y][x];
			x++;
		}
		data->map.map[i][x] = '\0';
		y++;
		i++;
	}
	data->map.map[i] = NULL;
}

static void	create_map(t_data *data, char **file, int y)
{
	data->map.height = get_map_height(file, y);
	data->map.width = get_map_width(file, y, data->map.height);
	data->map.map = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.map)
		ft_error("Error: malloc: create_map\n", data);
	fill_map(data, file, y);
}

int	ft_get_info(t_data *data, char **file, int y, int x)
{
	if (file[y])
	{
		x = 0;
		while (file[y][x] == ' ')
			x++;
		if (file[y][x] == 'N' && file[y][x + 1] == 'O')
			data->no.path = texture_stock(file[y] + x + 2, data, data->no.path);
		else if (file[y][x] == 'S' && file[y][x + 1] == 'O')
			data->so.path = texture_stock(file[y] + x + 2, data, data->so.path);
		else if (file[y][x] == 'W' && file[y][x + 1] == 'E')
			data->we.path = texture_stock(file[y] + x + 2, data, data->we.path);
		else if (file[y][x] == 'E' && file[y][x + 1] == 'A')
			data->ea.path = texture_stock(file[y] + x + 2, data, data->ea.path);
		else if (file[y][x] == 'F')
			data->f_color = texture_stock(file[y] + x + 1, data, data->f_color);
		else if (file[y][x] == 'C')
			data->c_color = texture_stock(file[y] + x + 1, data, data->c_color);
		else if (file[y][x] == '1')
		{
			create_map(data, file, y);
			return (1);
		}
	}
	return (0);
}

void	map_stock(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (data->file.file[y])
	{
		if (ft_get_info(data, data->file.file, y, x) == 1)
			break ;
		y++;
	}
	if (!data->map.map)
		ft_error("No map found in .cub file\n", data);
}
