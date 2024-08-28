/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arincon <arincon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:21:47 by arincon           #+#    #+#             */
/*   Updated: 2023/11/30 12:15:17 by arincon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	count_elements(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
		count++;
	return (count);
}

int	check_color_and_convert(t_data *data, char *color, int flag)
{
	char	**tab;
	int		r;
	int		g;
	int		b;

	tab = ft_split(color, ',');
	if (!tab || count_elements(tab) != 3)
	{
		if (count_elements(tab) != 3)
			ft_free_tab(tab);
		ft_error("Invalid RGB format\n", data);
	}
	r = atoi(tab[0]);
	g = atoi(tab[1]);
	b = atoi(tab[2]);
	ft_free_tab(tab);
	if ((r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255))
	{
		if (flag == 0)
			ft_error("Invalid RGB Ceiling value\n", data);
		else
			ft_error("Invalid RGB Floor value\n", data);
	}
	return ((r << 16) | (g << 8) | b);
}
