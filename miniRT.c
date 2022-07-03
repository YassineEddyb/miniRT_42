/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/03 23:22:24 by yed-dyb          ###   ########.fr       */
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

void print_vector(vector v)
{
	printf("x-> %f\ny-> %f\nz-> %f\nw-> %f\n\n", v.x, v.y, v.z, v.w);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	int i = 0;
	int x;
	int y;
	vector v;
	vector v1;
	vector v2;
	vector p;
	vector p1;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	
	p = vectorInit(0, 0, 0, 1);
	v2 = vectorInit(0, 100, 0, 1);
	p1 = translate(p, v2);

	print_vector(p);
	while(i < 12)
	{
		print_vector(p1);
		p1 = rotate_x(p1, M_PI/ 6);

		mlx_pixel_put(mlx, win, p1.y + WIDTH/2, p1.z+HEIGHT/2, create_trgb(1, 255, 255, 255));
		i++;
	}
	mlx_loop(mlx);
}
