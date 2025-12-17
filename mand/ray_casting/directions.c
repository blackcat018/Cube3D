/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:07:42 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/17 12:23:05 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void rotate_player(t_player *p, double angle)
{
    double old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
    p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
    double old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
    p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

bool can_move_to(t_game *g, double x, double y, double r)
{
    int min_x = (int)floor(x - r);
    int max_x = (int)floor(x + r);
    int min_y = (int)floor(y - r);
    int max_y = (int)floor(y + r);
    double closest_x;
    double closest_y;
    double dx;
    double dy;

    int mx = min_x;
    while (mx <= max_x)
    {
        int my = min_y;
        while (my <= max_y)
        {
            if (get_map_value(g, mx, my) != 0)
            {
                closest_x = fmax((double)mx, fmin(x, (double)mx + 1.0));
                closest_y = fmax((double)my, fmin(y, (double)my + 1.0));
                dx = x - closest_x;
                dy = y - closest_y;
                if (dx * dx + dy * dy < r * r)
                    return false;
            }
            my++;
        }
        mx++;
    }
    return true;
}

void handle_mouse_rotation(t_game *g)
{
    static int32_t last_x = -1;
    int32_t mouse_x;
    int32_t mouse_y;
    int32_t delta_x;
    double rotation_speed;
    mlx_get_mouse_pos(g->mlx, &mouse_x, &mouse_y);    
    if (last_x == 1)
    {
        last_x = mouse_x;
        return;
    }    
    delta_x = mouse_x - last_x;    
    rotation_speed = 0.002;
    if (delta_x != 0)
        rotate_player(&g->player, delta_x * rotation_speed);
    last_x = mouse_x;
}
