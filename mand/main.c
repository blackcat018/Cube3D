#include "cube.h"

int check_collision_circle(t_game *g, double x, double y, double radius)
{
    if (get_map_value(g, (int)x, (int)y) != 0)
        return 1;    
    if (get_map_value(g, (int)(x + radius), (int)y) != 0)
        return 1;
    if (get_map_value(g, (int)(x - radius), (int)y) != 0)
        return 1;
    if (get_map_value(g, (int)x, (int)(y + radius)) != 0)
        return 1;
    if (get_map_value(g, (int)x, (int)(y - radius)) != 0)
        return 1;    
    double diag = radius * 2;
    if (get_map_value(g, (int)(x + diag), (int)(y + diag)) != 0)
        return 1;
    if (get_map_value(g, (int)(x + diag), (int)(y - diag)) != 0)
        return 1;
    if (get_map_value(g, (int)(x - diag), (int)(y + diag)) != 0)
        return 1;
    if (get_map_value(g, (int)(x - diag), (int)(y - diag)) != 0)
        return 1;
    
    return 0;
}

//add this shit to the bonus part you idiot!
void draw_filled_circle(t_game *g, int center_x, int center_y, int radius, uint32_t color)
{
    t_minimap m;
    
    m.y = -radius;
    while (m.y <= radius)
    {
        m.x = -radius;
        while (m.x <= radius)
        {
            if (m.x * m.x + m.y * m.y <= radius * radius)
            {
                m.screen_x = center_x + m.x;
                m.screen_y = center_y + m.y;
                if (m.screen_x >= 0 && m.screen_x < SCREEN_WIDTH && 
                    m.screen_y >= 0 && m.screen_y < SCREEN_HEIGHT)
                    mlx_put_pixel(g->img, m.screen_x, m.screen_y, color);
            }
            m.x++;
        }
        m.y++;
    }
}

void draw_line(t_game *g, int x0, int y0, int x1, int y1, uint32_t color)
{
    t_line l;
    
    l.dx = abs(x1 - x0);
    l.dy = abs(y1 - y0);
    l.sx = x0 < x1 ? 1 : -1;
    l.sy = y0 < y1 ? 1 : -1;
    l.err = l.dx - l.dy;
    
    while (1)
    {
        if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT)
            mlx_put_pixel(g->img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        l.e2 = 2 * l.err;
        if (l.e2 > -l.dy)
        {
            l.err -= l.dy;
            x0 += l.sx;
        }
        if (l.e2 < l.dx)
        {
            l.err += l.dx;
            y0 += l.sy;
        }
    }
}

void draw_minimap_pixel(t_game *g, t_minimap *m)
{
    if (m->dx * m->dx + m->dy * m->dy <= m->radius * m->radius)
    {
        m->map_x = g->player.x + (float)m->dx / m->scale;
        m->map_y = g->player.y + (float)m->dy / m->scale;
        if (get_map_value(g, (int)m->map_x, (int)m->map_y) == 1)
            m->color = 0x1a1a1aAA;
        else
            m->color = 0x404040AA ;
        m->screen_x = m->offset_x + m->x;
        m->screen_y = m->offset_y + m->y;
        if (m->screen_x < SCREEN_WIDTH && m->screen_y < SCREEN_HEIGHT)
            mlx_put_pixel(g->img, m->screen_x, m->screen_y, m->color);
    }
    else if (m->dx * m->dx + m->dy * m->dy <= (m->radius + 2) * (m->radius + 2))
    {
        m->screen_x = m->offset_x + m->x;
        m->screen_y = m->offset_y + m->y;
        if (m->screen_x < SCREEN_WIDTH && m->screen_y < SCREEN_HEIGHT)
            mlx_put_pixel(g->img, m->screen_x, m->screen_y, 0xffffffAA);
    }
}

void draw_minimap(t_game *g)
{
    t_minimap m;
    
    m.size = 200;
    m.offset_x = 20;
    m.offset_y = 20;
    m.radius = m.size / 2;
    m.scale = 20.0;
    m.y = 0;
    while (m.y < m.size)
    {
        m.x = 0;
        while (m.x < m.size)
        {
            m.dx = m.x - m.radius;
            m.dy = m.y - m.radius;
            draw_minimap_pixel(g, &m);
            m.x++;
        }
        m.y++;
    }
    m.center_x = m.offset_x + m.radius;
    m.center_y = m.offset_y + m.radius;
    draw_filled_circle(g, m.center_x, m.center_y, 4, 0x00aaffFF);
    draw_line(g, m.center_x, m.center_y, 
        m.center_x + (int)(g->player.dir_x * 15),
        m.center_y + (int)(g->player.dir_y * 15), 0xffaa00FF);
}
//seriously how did you survive this far!?
void loop_hook(void *param)
{
    t_game *g = param;

    handle_movement(g);
    memset(g->img->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
    cast_rays(g);
    draw_minimap(g);
    draw_torch_sprite(g);
}

void lll()
{
	system ("leaks Cube3d");
}

int main(int argc, char **argv)
{
    t_game g;
    
    g.my_map = map_fill(argc, argv);
    if (g.my_map == NULL)
        return 1;
    
    get_map_dimensions(&g);
    init_player(&g.player, &g);
    
    if (fill_textur(g.my_map, &g) == 1)
        return 1;
    
    g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_image_to_window(g.mlx, g.img, 0, 0);
    
    mlx_set_cursor_mode(g.mlx, MLX_MOUSE_HIDDEN);
    
    atexit(lll);
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);
    
    free_mymap(g.my_map);
    free_texturs(&g);
    return (0);
}
