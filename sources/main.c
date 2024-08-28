/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddania-c <ddania-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:40:38 by arincon           #+#    #+#             */
/*   Updated: 2023/12/04 16:01:26 by ddania-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc != 2)
		return (write(2, "Program with 1 argument only\n", 30), 1);
	init_data(&data);
	check_parsing(&data, argv);
	init_win(&data);
	check_events(&data);
	render_image(&data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
}
// PARSING:
// doble textura

// BONUS:
// SPRITE
