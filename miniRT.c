/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/28 15:31:34 by yed-dyb          ###   ########.fr       */
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
// int intersectRaySphere(ray *r, sphere *s)
// {
// 	float A = vectorDot(&r->dir, &r->dir);
// 	vector dist = vectorSub(&r->start, &s->pos);
// 	float B = 2 * vectorDot(&r->dir, &dist);
// 	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
// 	float discr = B * B - 4 * A * C;

// 	if(discr < 0)
// 		return (-1);
// 	else {
// 		float sqrtdiscr = sqrtf(discr);
// 		float t0 = (-B + sqrtdiscr)/(2);
// 		float t1 = (-B - sqrtdiscr)/(2);
// 		if(t0 > t1)
// 			t0 = t1;
// 		return t0;
// 	}
// }

void print_vector(vector v)
{
	printf("x-> %f\ny-> %f\nz-> %f\nw-> %f\n\n", v.x, v.y, v.z, v.w);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}



// matrix get_transform_matrix(vector v, char t)
// {
// 	matrix m;
// 	m = matrixCreate(4, 4);
	
// }

int main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	float 	t;
	int x = 0, y = 0;
	float wall_size = 14.0;
	float half = wall_size / 2;
	float pixel_size = wall_size / WIDTH;
	float wall_z = 20;
	float t_close;
	

	ray r, r2;
	sphere s;
	vector v, n, v1, v2;
	light l;

	// shpere
	s = shpereInit();
	s.material.color = initColour(255, 0, 0);

	// ray
	r.start = vectorInit(0,0,-5,0);

	// light
	l = lightInit(vectorInit(10, 0, -10, 0), initColour(1, 1, 1));

	// mlx
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 800, "miniRT");

	while(y < HEIGHT) {
		float world_y = half - pixel_size * y;
		x = 0;
		while(x < WIDTH) {
			float world_x = - half + pixel_size * x;
			vector pos = vectorInit(world_x, world_y, wall_z,1);
			r.dir = normalize(vectorSub(pos, r.start));

			t = sphereIntersection(r, s);
			// printf("%f\n", t);
			if (t != -1)
			{
				vector point = position(r, t);
				vector normal = normal_at(s, point);
				vector eye = vectorScale(r.dir, -1);
				colour color = lightning(s.material, l, point, eye, normal);

				// printf("%f, %f, %f\n", color.red, color.green, color.blue);
				
				mlx_pixel_put(mlx, win, x, y, create_trgb(1, color.red , color.green , color.blue ));
			}
			x++;
		}
		y++;
	}

	mlx_loop(mlx);
}
