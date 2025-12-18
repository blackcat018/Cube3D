/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:15:12 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/18 12:22:35 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void draw_ceiling_and_floor(t_game *G)
{
    int x;
    int y;
    double distance;
    double light_intensity;
    double max_light_distance = 10.0;
    uint32_t color_c;
    uint32_t color_f;
    
    uint32_t base_ceiling = 0xFF0A0A0A;
    uint32_t base_floor = 0xFFEBCE87;

    y = 0;
    while (y < G->screen_height / 2)
    {
        distance = (1.5 * G->screen_height) / (G->screen_height / 2.0 - y + 0.001);
        light_intensity = 1.0 - (distance / max_light_distance);
        if (light_intensity < 0.1) light_intensity = 0.1;
        if (light_intensity > 1.0) light_intensity = 1.0;
        
        color_c = apply_lighting(base_ceiling, light_intensity * 0.7);
        
        x = 0;
        while (x < G->screen_width)
        {
            mlx_put_pixel(G->img, x, y, color_c);
            x++;
        }
        y++;
    }
    
    y = G->screen_height / 2;
    while (y < G->screen_height)
    {

        distance = (1.5 * G->screen_height) / (y - G->screen_height / 2.0 + 0.001);
        light_intensity = 1.0 - (distance / max_light_distance);
        if (light_intensity < 0.1) light_intensity = 0.1;
        if (light_intensity > 1.0) light_intensity = 1.0;
        
        color_f = apply_lighting(base_floor, light_intensity);
        
        x = 0;
        while (x < G->screen_width)
        {
            mlx_put_pixel(G->img, x, y, color_f);
            x++;
        }
        y++;
    }
}

void draw_wall(t_game *g, int x, t_ray *ray)
{
    int line_height = (int)(g->screen_height / ray->perp_wall_dist);
    int draw_start = -line_height / 2 + g->screen_height / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + g->screen_height / 2;
    if (draw_end >= g->screen_height)
        draw_end = g->screen_height - 1;
    uint32_t color;
    if (ray->side == 0)
    {
        color = 0x000880FF;
    }
    else
    {
        color = 0x088000FF;
    }
    draw_vertical_line(g, x, 0, draw_start, 0x333333FF);
    draw_vertical_line(g, x, draw_start, draw_end, color);
    draw_vertical_line(g, x, draw_end, g->screen_height, 0x666666FF);
}

