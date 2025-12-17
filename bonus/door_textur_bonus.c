/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_textur_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/13 20:23:46 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


int door_in_front(t_game *g, int *mx, int *my)
{
    int x = (int)floor(g->player.x + g->player.dir_x);
    int y = (int)floor(g->player.y + g->player.dir_y);

    if (x < 0 || x >= g->map_width || y < 0 || y >= g->map_height)
        return 0;
    char c = g->my_map->map[y][x];
    if (c == 'D' || c == 'd')
    {
        if (mx) *mx = x;
        if (my) *my = y;
        return 1;
    }
    return 0;
}

void	draw_textured_door(t_game *g, int x, t_ray *ray)
{
	t_calc			value;
	double			wall_x;
	mlx_texture_t	*tex;
	t_scalc			calc;

	if (!g)
		return ;
	value = refill(ray->perp_wall_dist);
	wall_x = wal_xx(ray, g);
	tex = g->texture_door;
	if (ray->perp_wall_dist <= 0.0 || !tex)
	{
		draw_wall(g, x, ray);
		return ;
	}
	calc = calculatin(wall_x, tex, value);
	while (value.draw_start <= value.draw_end)
	{
		mlx_put_pixel(g->img, x, value.draw_start, 
			color_pixwls_img(&calc, ray));
		value.draw_start++;
	}
}

void cast_rays(t_game *g)
{
    draw_ceiling_and_floor(g);
    int x = 0;
    t_ray ray;
    while (x < SCREEN_WIDTH)
    {
        init_ray(&ray, g, x);
        calculate_step(&ray, g);
        perform_dda(&ray, g);
        calculate_wall_distance(&ray, g);
        if (g->my_map->map[ray.map_y][ray.map_x] == 'D')
            draw_textured_door(g, x, &ray);
        else
            draw_textured_wall(g, x, &ray);
        x++;
    }
}
