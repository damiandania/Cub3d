/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:39:56 by arincon           #+#    #+#             */
/*   Updated: 2023/12/05 16:56:06 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_img(t_data *data)
{
	if (data->so.path)
		free(data->so.path);
	if (data->ea.path)
		free(data->ea.path);
	if (data->we.path)
		free(data->we.path);
	if (data->no.path)
		free(data->no.path);
	if (data->c_color)
		free(data->c_color);
	if (data->f_color)
		free(data->f_color);
}

static void	destroy_img(t_data *data)
{
	if (data->no.img)
		mlx_destroy_image(data->mlx_ptr, data->no.img);
	if (data->so.img)
		mlx_destroy_image(data->mlx_ptr, data->so.img);
	if (data->we.img)
		mlx_destroy_image(data->mlx_ptr, data->we.img);
	if (data->ea.img)
		mlx_destroy_image(data->mlx_ptr, data->ea.img);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while ((tab)[i])
	{
		free((tab)[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_error(char *str, t_data *data)
{
	write (2, str, ft_strlen(str));
	ft_destroy_free(data);
	exit (EXIT_FAILURE);
}

void	ft_destroy_free(t_data *data)
{
	if (data->pixel_tab)
		free_pixel_tab(data->pixel_tab);
	if (data->file.file)
		ft_free_tab(data->file.file);
	if (data->map.map)
		ft_free_tab(data->map.map);
	destroy_img(data);
	free_img(data);
	if (data->mlx_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}
