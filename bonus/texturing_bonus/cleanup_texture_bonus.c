/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_texture_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:26:15 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:26:53 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	delete_texture(mlx_texture_t *tex)
{
	if (tex)
		mlx_delete_texture(tex);
}

void	delete_image(t_game *g, mlx_image_t *img)
{
	if (img)
		mlx_delete_image(g->mlx, img);
}

void	free_wall_textures(t_game *g)
{
	delete_texture(g->texture_east);
	delete_image(g, g->img_wall_east);
	delete_texture(g->texture_west);
	delete_image(g, g->img_wall_west);
	delete_texture(g->texture_north);
	delete_image(g, g->img_wall_north);
	delete_texture(g->texture_south);
	delete_image(g, g->img_wall_south);
	delete_texture(g->texture_door);
	delete_image(g, g->img_wall_door);
}

void	free_game_assets(t_game *g)
{
	delete_texture(g->texture_torch);
	delete_texture(g->texture_attack1);
	delete_image(g, g->img_attack1);
	delete_texture(g->texture_attack2);
	delete_image(g, g->img_attack2);
	delete_texture(g->texture_open1);
	delete_image(g, g->img_open1);
	delete_texture(g->texture_open2);
	delete_image(g, g->img_open2);
}

void	free_texturs(t_game *g)
{
	free_wall_textures(g);
	free_game_assets(g);
	delete_image(g, g->img);
}
