# include "miniRT.h"


int distance(int x1, int y1, int x2, int y2)
{
	return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}

int	main()
{
	void	*mlx;
	void	*win;
	int sx, sy;
    float r = 50;
    float x, y;
    float tita;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
    sx = WIDTH / 2; sy = HEIGHT / 2;
    // x = sx - r;
    // y = sy;
    tita = 0.1;
    while (r > 0)
    {
        tita = 0.1;
        while(tita <= 360)
        {
            x = (cos(tita) * r + sx);
            y = (sin(tita) * r + sy);
            mlx_pixel_put(mlx, win, x, y, 0x00ffffff);
            tita += 0.001;
        }
        write(2, "l", 1);
        r -= 1;
    }

	mlx_loop(mlx);
}