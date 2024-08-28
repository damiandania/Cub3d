/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damian <damian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:40:08 by arincon           #+#    #+#             */
/*   Updated: 2023/12/01 12:55:45 by damian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_destroy_free(data);
		data->win_ptr = NULL;
		exit(EXIT_SUCCESS);
	}
	if (keysym == XK_Left)
		data->player.rotate = -1;
	if (keysym == XK_Right)
		data->player.rotate = 1;
	if (keysym == XK_w)
		data->player.my = 1;
	if (keysym == XK_a)
		data->player.mx = -1;
	if (keysym == XK_s)
		data->player.my = -1;
	if (keysym == XK_d)
		data->player.mx = 1;
	return (0);
}

static int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_destroy_free(data);
		data->win_ptr = NULL;
		exit(EXIT_SUCCESS);
	}
	if (keysym == XK_Left && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (keysym == XK_Right && data->player.rotate >= -1)
		data->player.rotate = 0;
	if (keysym == XK_w && data->player.my == 1)
		data->player.my = 0;
	if (keysym == XK_s && data->player.my == -1)
		data->player.my = 0;
	if (keysym == XK_a && data->player.mx == -1)
		data->player.mx += 1;
	if (keysym == XK_d && data->player.mx == 1)
		data->player.mx -= 1;
	return (0);
}

static int	handle_mouse(int x, int y, t_data *data)
{
	int	pos;

	pos = WIN_WIDTH / 5;
	if (x > WIN_WIDTH || x < 0)
	{
		x = 0;
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, x, y);
	}
	if (x < pos * 3 && x > pos * 2)
	{
		data->player.rotate = 0;
		return (0);
	}
	else if (x > 0 && x < pos)
		data->player.rotate = -1 * 2;
	else if (x > pos && x < pos * 2)
		data->player.rotate = -1;
	else if (x > pos * 3 && x < pos * 4)
		data->player.rotate = 1;
	else if (x > pos * 4 && x < WIN_WIDTH)
		data->player.rotate = 1 * 2;
	return (0);
}

static int	handle_cross_icon(t_data *data)
{
	ft_destroy_free(data);
	data->win_ptr = NULL;
	exit(EXIT_SUCCESS);
	return (0);
}

void	check_events(t_data *data)
{
	mlx_hook(data->win_ptr,
		ClientMessage, NoEventMask, &handle_cross_icon, data);
	mlx_hook(data->win_ptr,
		KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr,
		KeyRelease, KeyReleaseMask, handle_keyrelease, data);
	if (BONUS == 1)
		mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask,
			handle_mouse, data);
}
