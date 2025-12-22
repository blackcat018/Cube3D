/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:07:01 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/21 11:36:23 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	fill_tex(t_pars *my_map, t_game *g)
{
	g->texture_south = mlx_load_png(my_map->so);
	if (!g->texture_south)
		return (1);
	g->img_wall_south = mlx_texture_to_image(g->mlx, g->texture_south);
	if (!(g->img_wall_south))
		return (1);
	g->texture_west = mlx_load_png(my_map->we);
	if (!g->texture_west)
		return (1);
	g->img_wall_west = mlx_texture_to_image(g->mlx, g->texture_west);
	if (!(g->img_wall_west))
		return (1);
	return (0);
}

void	inicial_g(t_game *g)
{
	g->texture_east = NULL;
	g->img_wall_east = NULL;
	g->texture_west = NULL;
	g->img_wall_west = NULL;
	g->texture_north = NULL;
	g->img_wall_north = NULL;
	g->texture_south = NULL;
	g->img_wall_south = NULL;
}

int	fill_textur(t_pars *my_map, t_game *g)
{
	inicial_g(g);
	g->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	if (!g->mlx)
		return (1);
	g->texture_east = mlx_load_png(my_map->ea);
	if (!g->texture_east)
		return (1);
	g->img_wall_east = mlx_texture_to_image(g->mlx, g->texture_east);
	if (!(g->img_wall_east))
		return (1);
	g->texture_north = mlx_load_png(my_map->no);
	if (!g->texture_north)
		return (1);
	g->img_wall_north = mlx_texture_to_image(g->mlx, g->texture_north);
	if (!(g->img_wall_north))
		return (1);
	if (fill_tex(my_map, g) == 1)
		return (1);
	return (0);
}

void	free_texturs(t_game *g)
{
	if (g->texture_east)
		mlx_delete_texture(g->texture_east);
	if (g->img_wall_east)
		mlx_delete_image(g->mlx, g->img_wall_east);
	if (g->texture_west)
		mlx_delete_texture(g->texture_west);
	if (g->img_wall_west)
		mlx_delete_image(g->mlx, g->img_wall_west);
	if (g->texture_north)
		mlx_delete_texture(g->texture_north);
	if (g->img_wall_north)
		mlx_delete_image(g->mlx, g->img_wall_north);
	if (g->texture_south)
		mlx_delete_texture(g->texture_south);
	if (g->img_wall_south)
		mlx_delete_image(g->mlx, g->img_wall_south);
	if (g->img)
		mlx_delete_image(g->mlx, g->img);
}
