/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:15:18 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:09:34 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	calculate_step(t_ray *ray, t_game *g)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->player.y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_game *g)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (get_map_value(g, ray->map_x, ray->map_y) > 0)
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray, t_game *g)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - g->player.x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - g->player.y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
}

void	draw_vertical_line(t_game *g, t_vline *l)
{
	int	y;

	y = l->start;
	while (y < l->end)
	{
		if (y >= 0 && y < g->screen_height)
			mlx_put_pixel(l->g->img, l->x, y, l->color);
		y++;
	}
}

void	cast_rays(t_game *g)
{
	int		x;
	t_ray	ray;

	draw_ceiling_and_floor(g);
	x = 0;
	while (x < g->screen_width)
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
