/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/22 12:00:59 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	loop_hook(void *param)
{
	t_game	*g;

	g = param;
	handle_movement(g);
	memset(g->img->pixels, 0, g->screen_width * g->screen_height * 4);
	cast_rays(g);
	draw_minimap(g);
	draw_torch_sprite(g);
}

void	lll(void)
{
	system("leaks cub3D_bonus");
}

void	dynamic_resizing(int width, int height, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	mlx_delete_image(g->mlx, g->img);
	g->img = mlx_new_image(g->mlx, width, height);
	if (!g->img)
		return ;
	g->screen_height = height;
	g->screen_width = width;
	cast_rays(g);
	draw_minimap(g);
	draw_torch_sprite(g);
	mlx_image_to_window(g->mlx, g->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	g;

	g.screen_width = 800;
	g.screen_height = 600;
	g.my_map = map_fill(argc, argv);
	if (g.my_map == NULL)
		return (1);
	get_map_dimensions(&g);
	init_player(&g.player, &g);
	if (fill_textur(g.my_map, &g) == 1)
	{
		free_texturs(&g);
		atexit(lll);
		return (free_mymap(g.my_map), printf("fail to loade an image\n"), 1);
	}
	g.img = mlx_new_image(g.mlx, g.screen_width, g.screen_height);
	mlx_image_to_window(g.mlx, g.img, 0, 0);
	mlx_resize_hook(g.mlx, &dynamic_resizing, &g);
	mlx_set_cursor_mode(g.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(g.mlx, loop_hook, &g);
	mlx_loop(g.mlx);
	atexit(lll);
	free_mymap(g.my_map);
	free_texturs(&g);
	return (0);
}
