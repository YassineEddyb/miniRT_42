/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/04 18:50:29 by yed-dyb          ###   ########.fr       */
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



int main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	float *t;

	ray r;
	sphere s;
	vector v;
	ray r2;
	ray r3;

	v = vectorInit(2, 2, 2, 1);
	s.pos = vectorInit(0, 0, 0, 1);
	s.transform = vectorDot(s.pos, v)
	r.start = vectorInit(0, 0, -5, 1);
	r.dir = vectorInit(0, 0, 1, 0);
	
	// r2 = transform(r, v, 't');
	r3 = transform(r, v, 's');
	t = sphereIntersection(r3, s);

	printf("%f\n%f\n", t[0], t[1]);

	// print_vector(r3.start);
	// print_vector(r3.dir);
}
