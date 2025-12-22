/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/21 11:36:55 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	loop_hook(void *param)
{
	t_game	*g;

	g = param;
	handle_movement(g);
	memset(g->img->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	cast_rays(g);
}

void	lll(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_game	g;

	g.my_map = map_fill(argc, argv);
	if (g.my_map == NULL)
		return (1);
	get_map_dimensions(&g);
	init_player(&g.player, &g);
	if (fill_textur(g.my_map, &g) == 1)
	{
		free_mymap(g.my_map);
		free_texturs(&g);
		return (1);
	}
	g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(g.mlx, g.img, 0, 0);
	atexit(lll);
	mlx_loop_hook(g.mlx, loop_hook, &g);
	mlx_loop(g.mlx);
	free_mymap(g.my_map);
	free_texturs(&g);
	return (0);
}
