/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_sup_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:04:38 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:04:51 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_filled_circle(t_game *g, t_minimap	*f, int radius,
		uint32_t color)
{
	t_minimap	m;

	m.y = -radius;
	while (m.y <= radius)
	{
		m.x = -radius;
		while (m.x <= radius)
		{
			if (m.x * m.x + m.y * m.y <= radius * radius)
			{
				m.screen_x = f->center_x + m.x;
				m.screen_y = f->center_y + m.y;
				if (m.screen_x >= 0 && m.screen_x < g->screen_width
					&& m.screen_y >= 0 && m.screen_y < g->screen_height)
					mlx_put_pixel(g->img, m.screen_x, m.screen_y, color);
			}
			m.x++;
		}
		m.y++;
	}
}

void	init_line(t_line *l, t_minimap *m)
{
	l->dx = abs(m->x1 - m->center_x);
	l->dy = abs(m->y1 - m->center_y);
	l->sx = (m->center_x < m->x1) * 2 - 1;
	l->sy = (m->center_y < m->y1) * 2 - 1;
	l->err = l->dx - l->dy;
}

void	step_line(t_line *l, t_minimap *m)
{
	l->e2 = 2 * l->err;
	if (l->e2 > -l->dy)
	{
		l->err -= l->dy;
		m->center_x += l->sx;
	}
	if (l->e2 < l->dx)
	{
		l->err += l->dx;
		m->center_y += l->sy;
	}
}

void	draw_line(t_game *g, t_minimap *m, uint32_t color)
{
	t_line	l;

	init_line(&l, m);
	while (1)
	{
		if (m->center_x >= 0 && m->center_x < g->screen_width
			&& m->center_y >= 0 && m->center_y < g->screen_height)
			mlx_put_pixel(g->img, m->center_x, m->center_y, color);
		if (m->center_x == m->x1 && m->center_y == m->y1)
			break ;
		step_line(&l, m);
	}
}

void	draw_minimap_pixel(t_game *g, t_minimap *m)
{
	if (m->dx * m->dx + m->dy * m->dy <= m->radius * m->radius)
	{
		m->map_x = g->player.x + (float)m->dx / m->scale;
		m->map_y = g->player.y + (float)m->dy / m->scale;
		if (get_map_value(g, (int)m->map_x, (int)m->map_y) == 1)
			m->color = 0x1a1a1aAA;
		else
			m->color = 0x404040AA;
		m->screen_x = m->offset_x + m->x;
		m->screen_y = m->offset_y + m->y;
		if (m->screen_x < g->screen_width && m->screen_y < g->screen_height)
			mlx_put_pixel(g->img, m->screen_x, m->screen_y, m->color);
	}
	else if (m->dx * m->dx + m->dy * m->dy <= (m->radius + 2) * (m->radius + 2))
	{
		m->screen_x = m->offset_x + m->x;
		m->screen_y = m->offset_y + m->y;
		if (m->screen_x < g->screen_width && m->screen_y < g->screen_height)
			mlx_put_pixel(g->img, m->screen_x, m->screen_y, 0xffffffAA);
	}
}
