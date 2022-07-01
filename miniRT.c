/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/06/30 21:53:22 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

colour initColour(float red, float green, float blue)
{
	colour rgb;
	rgb.red = red;
	rgb.green = green;
	rgb.blue = blue;
	return (rgb);
}

/* Check if the ray and sphere intersect */
int intersectRaySphere(ray *r, sphere *s)
{
	float A = vectorDot(&r->dir, &r->dir);
	vector dist = vectorSub(&r->start, &s->pos);
	float B = 2 * vectorDot(&r->dir, &dist);
	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
	float discr = B * B - 4 * A * C;

	if(discr < 0)
		return (-1);
	else {
		float sqrtdiscr = sqrtf(discr);
		float t0 = (-B + sqrtdiscr)/(2);
		float t1 = (-B - sqrtdiscr)/(2);
		if(t0 > t1)
			t0 = t1;
		return t0;
	}
}

int main(int argc, char **argv){
	void	*mlx;
	void	*win;
	int c_x, c_y;

	sphere s;
	ray r;
	light light;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");

	light.pos = vectorInit(0, 0, -10);
	light.rgb = initColour(1, 1, 1);

	s.pos = vectorInit(300, 300, 100);
	s.rgb = initColour(244, 32, 1);
	s.radius = 12 * 10;

	r.start = vectorInit(0, 0, 1);

	int x = 0;
	int y;
	while(x < WIDTH)
	{
		y = 0;
		while(y < HEIGHT)
		{
			float f;
			float ratio;
			float imageAspectRatio = WIDTH / (float)HEIGHT;  //assuming width > height
			float scale = tan(deg2rad(70 * 0.5));
			
			r.dir.x = (2 * ((x + 0.5) / WIDTH) - 1) * tan(70 / 2 * M_PI / 180) * imageAspectRatio; 
			r.dir.y = (1 - 2 * ((y + 0.5) / HEIGHT) * tan(70 / 2 * M_PI / 180)) * scale;
			r.dir.z = -1;
			
			if((f = intersectRaySphere(&r, &s)) != -1)
			{
				vector p = vectorAdd(r.start, vectorScale(f,  normalize(r.dir)));
				vector v1 = vectorSub(&light.pos, &p);
				vector v2 = vectorSub(&s.pos, &p);
				ratio = vectorDot(&v1, &v2);
	
				s.rgb = initColour(s.rgb.red * 1, s.rgb.green * 1, s.rgb.blue * 1);
				mlx_pixel_put(mlx, win, x, y, create_trgb(1, s.rgb.red, s.rgb.green, s.rgb.blue));
			}
			y++;
		}
		x++;
	}
	mlx_loop(mlx);
}