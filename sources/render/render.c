/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:29:40 by ddania-c          #+#    #+#             */
/*   Updated: 2023/12/05 16:56:35 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_pixel_tab(int **tab)
{
	size_t	i;

	i = 0;
	while (i < WIN_HEIGHT + 1)
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	init_pixel_tab(t_data *data)
{
	int	i;

	i = 0;
	if (data->pixel_tab)
		free_pixel_tab(data->pixel_tab);
	data->pixel_tab = ft_calloc(sizeof(int *), WIN_HEIGHT + 1);
	if (!data->pixel_tab)
		ft_error("Error:  init_pixel_tab", data);
	while (i < WIN_HEIGHT + 1)
	{
		data->pixel_tab[i] = ft_calloc(sizeof(int), WIN_WIDTH + 1);
		if (!data->pixel_tab)
			ft_error("Error:  init_pixel_tab", data);
		i++;
	}
}

static void	set_sprite(t_data *data)
{
	if (data->frame_counter <= SPEED_SPRITE)
		data->sprite = data->no;
	else if (data->frame_counter <= SPEED_SPRITE * 2)
		data->sprite = data->so;
	else if (data->frame_counter <= SPEED_SPRITE * 3)
		data->sprite = data->ea;
	else if (data->frame_counter <= SPEED_SPRITE * 4)
		data->sprite = data->we;
	else if (data->frame_counter > SPEED_SPRITE * 5)
		data->frame_counter = 0;
	data->frame_counter++;
}

void	render_image(t_data *data)
{
	init_pixel_tab(data);
	raycasting(data, &data->ray, &data->player);
	if (BONUS == 1)
	{
		calculate_offset(data);
		render_minimap(data, data->map.offx, data->map.offy);
		render_player(data, data->map.offx, data->map.offy);
	}
	create_picture(data);
}

int	render(t_data *data)
{
	if (BONUS == 1)
		set_sprite(data);
	data->player.moved += move_player(&data->player, data->map.map);
	render_image(data);
	data->player.moved = 0;
	return (0);
}
