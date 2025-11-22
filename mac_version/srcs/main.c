// main.c
#include <stdlib.h>
#include "mlx.h"

typedef struct s_app
{
    void    *mlx;
    void    *win;
    int     width;
    int     height;
}   t_app;

int close_window(t_app *app)
{
    (void)app;
    // You can also destroy the window if you want:
    // mlx_destroy_window(app->mlx, app->win);
    exit(0);
    return (0);
}

int key_hook(int keycode, t_app *app)
{
    // On Mac with MLX, ESC key is usually 53
    if (keycode == 53)
        close_window(app);
    (void)app;
    return (0);
}

int main(void)
{
    t_app  app;
    int    x;
    int    y;

    app.width = 800;
    app.height = 600;

    // 1. Initialize MLX
    app.mlx = mlx_init();
    if (!app.mlx)
        return (1);

    // 2. Create a window
    app.win = mlx_new_window(app.mlx, app.width, app.height, "My first MLX");
    if (!app.win)
        return (1);

    // 3. Draw something (a simple gradient)
    y = 0;
    while (y < app.height)
    {
        x = 0;
        while (x < app.width)
        {
            int r = (x * 255) / app.width;    // red depends on x
            int g = (y * 255) / app.height;   // green depends on y
            int b = 128;                      // blue is constant

            int color = (r << 16) | (g << 8) | b; // 0xRRGGBB

            mlx_pixel_put(app.mlx, app.win, x, y, color);
            x++;
        }
        y++;
    }

    // 4. Hooks (events)
    // Close window with red cross
    mlx_hook(app.win, 17, 0, close_window, &app);
    // Close with ESC key
    mlx_key_hook(app.win, key_hook, &app);

    // 5. Start the event loop
    mlx_loop(app.mlx);

    return (0);
}
