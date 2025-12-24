/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:54:59 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/24 12:25:28 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	init_minimap(t_game *g, t_minimap *m)
{
	m->size = g->screen_width / 6;
	m->offset_x = 20;
	m->offset_y = 20;
	m->radius = m->size / 2;
	m->scale = m->size / 10;
	m->y = 0;
}

void	draw_minimap_bg(t_game *g, t_minimap *m)
{
	while (m->y < m->size)
	{
		m->x = 0;
		while (m->x < m->size)
		{
			m->dx = m->x - m->radius;
			m->dy = m->y - m->radius;
			draw_minimap_pixel(g, m);
			m->x++;
		}
		m->y++;
	}
}

void	draw_minimap_player(t_game *g, t_minimap *m)
{
	m->center_x = m->offset_x + m->radius;
	m->center_y = m->offset_y + m->radius;
	m->x1 = m->center_x + (int)(g->player.dir_x * 15);
	m->y1 = m->center_y + (int)(g->player.dir_y * 15);
	draw_filled_circle(g, m, m->size / 28, 0x0f0F6B40);
	draw_line(g, m, 0xffaa00FF);
}

void	draw_minimap(t_game *g)
{
	t_minimap	m;

	init_minimap(g, &m);
	draw_minimap_bg(g, &m);
	draw_minimap_player(g, &m);
}
