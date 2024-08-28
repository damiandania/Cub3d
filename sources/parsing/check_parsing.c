/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arincon <arincon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:17:45 by arincon           #+#    #+#             */
/*   Updated: 2023/11/29 15:20:35 by arincon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_map_extension(char **argv)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	j = 0;
	str = ".cub";
	len = ft_strlen(argv[1]);
	i = ft_strlen(argv[1]) - 4;
	while (i < len)
		if (str[j++] != argv[1][i++])
			return (write(2, "Map file must have the extension .cub\n", 39), 1);
	return (0);
}

static int	check_img_extension(t_data *data, char *path)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	j = 0;
	str = ".xpm";
	len = ft_strlen(path);
	i = ft_strlen(path) - 4;
	while (i < len)
		if (str[j++] != path[i++])
			ft_error("Img file must have the extension .xpm\n", data);
	return (0);
}

static int	check_map_file(char **argv)
{
	int	fd_dir;
	int	fd_map;

	fd_dir = open(argv[1], O_DIRECTORY);
	if (fd_dir != -1)
	{
		close(fd_dir);
		return (write(2, "Map file is a directory\n", 25), 1);
	}
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map == -1)
		return (write(2, "Map file cannot be opened\n", 27), 1);
	close (fd_map);
	return (0);
}

static void	check_full_param(t_data *data)
{
	if (!data->no.path)
		ft_error("Missing NO path param\n", data);
	check_img_extension(data, data->no.path);
	if (!data->ea.path)
		ft_error("Missing EA path param\n", data);
	check_img_extension(data, data->ea.path);
	if (!data->we.path)
		ft_error("Missing WE path param\n", data);
	check_img_extension(data, data->we.path);
	if (!data->so.path)
		ft_error("Missing SO path param\n", data);
	check_img_extension(data, data->so.path);
	if (!data->c_color)
		ft_error("Missing C color param\n", data);
	if (!data->f_color)
		ft_error("Missing F color param\n", data);
}

void	check_parsing(t_data *data, char **argv)
{
	if (check_map_extension(argv) == 1 || check_map_file(argv) == 1)
		exit (1);
	file_stock(data, argv[1]);
	map_stock(data);
	player_stock(data, data->map.map);
	check_full_param(data);
	check_map(data);
}
