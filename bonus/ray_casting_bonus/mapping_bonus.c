/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:15:12 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:11:50 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_horizontal_line(t_game *g, int y, uint32_t color)
{
	int	x;

	x = 0;
	while (x < g->screen_width)
	{
		mlx_put_pixel(g->img, x, y, color);
		x++;
	}
}

void	draw_ceiling(t_game *g)
{
	int			y;
	double		dist;
	double		light;
	uint32_t	color;

	y = 0;
	while (y < g->screen_height / 2)
	{
		dist = (1.5 * g->screen_height)
			/ (g->screen_height / 2.0 - y + 0.001);
		light = clamp_light(1.0 - (dist / 10.0));
		color = apply_lighting(0xFFfeee68, light * 0.7);
		draw_horizontal_line(g, y, color);
		y++;
	}
}

void	draw_floor(t_game *g)
{
	int			y;
	double		dist;
	double		light;
	uint32_t	color;

	y = g->screen_height / 2;
	while (y < g->screen_height)
	{
		dist = (1.5 * g->screen_height)
			/ (y - g->screen_height / 2.0 + 0.001);
		light = clamp_light(1.0 - (dist / 10.0));
		color = apply_lighting(0xFFfadac4, light);
		draw_horizontal_line(g, y, color);
		y++;
	}
}

t_wall	get_wall(t_game *g, t_ray *ray)
{
	t_wall	w;

	w.line_h = (int)(g->screen_height / ray->perp_wall_dist);
	w.start = -w.line_h / 2 + g->screen_height / 2;
	if (w.start < 0)
		w.start = 0;
	w.end = w.line_h / 2 + g->screen_height / 2;
	if (w.end >= g->screen_height)
		w.end = g->screen_height - 1;
	if (ray->side == 0)
		w.color = 0x000880FF;
	else
		w.color = 0x088000FF;
	return (w);
}

void	draw_wall(t_game *g, int x, t_ray *ray)
{
	t_wall	w;
	t_vline	l;

	w = get_wall(g, ray);
	l.g = g;
	l.x = x;
	l.start = 0;
	l.end = w.start;
	l.color = 0x333333FF;
	draw_vertical_line(g, &l);
	l.start = w.start;
	l.end = w.end;
	l.color = w.color;
	draw_vertical_line(g, &l);
	l.start = w.end;
	l.end = g->screen_height;
	l.color = 0x666666FF;
	draw_vertical_line(g, &l);
}
