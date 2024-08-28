/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arincon <arincon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:51:52 by arincon           #+#    #+#             */
/*   Updated: 2023/11/30 16:20:24 by arincon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_file_lines(char *argv, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		ft_error("Map file descriptor error\n", data);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			data->file.n_lines++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
}

static void	fill_file(int fd, t_data *data)
{
	char	*line;
	int		y;
	int		x;

	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->file.file[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!data->file.file[y])
			ft_error("Error: malloc: fill_file\n", data);
		x = 0;
		while (line[x] && line[x] != '\n')
		{
			data->file.file[y][x] = line[x];
			x++;
		}
		while (line[x])
			data->file.file[y][x++] = '\0';
		y++;
		free(line);
		line = get_next_line(fd);
	}
	data->file.file[y] = NULL;
}

void	file_stock(t_data *data, char *path)
{
	int	fd;

	fd = 0;
	get_file_lines(path, data);
	data->file.path = path;
	data->file.file = malloc(sizeof(char *) * (data->file.n_lines + 1));
	if (!data->file.file)
		ft_error("Error: malloc: file_stock\n", data);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error("Map file descriptor error\n", data);
	fill_file(fd, data);
	close(fd);
}
