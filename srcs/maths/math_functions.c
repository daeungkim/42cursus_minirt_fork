/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:25:46 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/18 11:21:45 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>
#include <stdio.h>
/*
** To avoid catastrophic cancellation between b and discriminant,
** we will use a sign function
*/
int solve_quadratic(t_vector3 abc, double *t0, double *t1)
{
	double disc;
	double q;
	double temp;

	*t1 = -1.0;
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (0);
	if (disc == 0)
	{
		*t0 = -abc.y / (2 * abc.x);
		return (1);
	}
	q = -0.5 * (abc.y + ((abc.y > 0) ? sqrt(disc) : - sqrt(disc)));
	*t0 = q / abc.x;
	*t1 = abc.z / q;
	temp = *t0;
	if (*t0 > *t1)
	{
		*t0 = *t1;
		*t1 = temp;
	}
	return (2);
}

int solve_cubic(double *roots, double b, double c, double d)
{
	double q;
	double r;
    double omega;
    double s;

	q = -(b * b - 3 * c) / 9;
	r = -(-9 * b * c + 27 * d + 2 * pow(b, 3)) / 54;
    if (q * q * q <= -r * r )
    {
        omega = acos(-r / sqrt(-(q * q * q)));
        roots[0] = -2 * sqrt(-q) * cos(omega / 3) - b / 3;
        roots[1] = -2 * sqrt(-q) * cos((omega + 2 * M_PI) / 3) - b / 3;
        roots[2] = -2 * sqrt(-q) * cos((omega - 2 * M_PI) / 3) - b / 3;
        if (q * q * q + r * r < 1e-8 && q * q * q + r * r < -1e-8)
            return (2);
        return (3);
    }
    else
    {
        s = -cbrt(fabs(r) + sqrt(r * r + q * q * q));
        if (r > 0)
            s = -s;
        roots[0] = - (b / 3) + (s - (s == 0 ? 0 : (q / s)));
        return (1);
    }
}

void  CSqrt( double x, double y, double *a, double *b) // returns:  a+i*s = sqrt(x+i*y)
{
	double r  = sqrt(x*x+y*y);
	if( y==0 ) { 
		r = sqrt(r);
		if(x>=0) { *a=r; *b=0; } else { *a=0; *b=r; }
	} else {		// y != 0
		*a = sqrt(0.5*(x+r));
		*b = 0.5 * y / *a;
	}
}

#define SWAP(a,b) { t=b; b=a; a=t; }
static void  dblSort3( double *a, double *b, double *c) // make: a <= b <= c
{
	double t;
	if( *a>*b ) SWAP(*a,*b);	// now a<=b
	if( *c<*b ) {
		SWAP(*b,*c);			// now a<=b, b<=c
		if( *a>*b ) SWAP(*a,*b);// now a<=b
	}
}

int solve_quartic(t_quartic q, t_rt_param *p)
{
	t_vector3 pqr;
	double roots[4];
	int res;

	pqr.x = q.c - (3 * pow(q.b, 2)) / 8;
	pqr.y = q.d + (pow(q.b, 3) - 4 * q.b * q.c) / 8;
	pqr.z = q.e - q.b * q.d / 4 + (-3 * pow(q.b, 4) +
			16 * q.c * pow(q.b, 2)) / 256;

	res = solve_cubic(roots, 2 * pqr.x, pow(pqr.x, 2) - 4 * pqr.z, -pow(pqr.y, 2));

	if(res > 1)
	{				
		dblSort3(&(roots[0]), &(roots[1]), &(roots[2]));	// sort roots to x[0] <= x[1] <= x[2]
		// Note: x[0]*x[1]*x[2]= c*c > 0
		if(roots[0] > 0) // all roots are positive
		{
			double sz1 = sqrt(roots[0]);
			double sz2 = sqrt(roots[1]);
			double sz3 = sqrt(roots[2]);
			// Note: sz1*sz2*sz3= -c (and not equal to 0)
			if( q.d>0 )
			{
				p->i = (-sz1 -sz2 -sz3)/2;
				p->i_2 = (-sz1 +sz2 +sz3)/2;
				p->i_3 = (+sz1 -sz2 +sz3)/2;
				p->i_4 = (+sz1 +sz2 -sz3)/2;
				return 4;
			}
			p->i = (-sz1 -sz2 +sz3)/2;
			p->i_2 = (-sz1 +sz2 -sz3)/2;
			p->i_3 = (+sz1 -sz2 -sz3)/2;
			p->i_4 = (+sz1 +sz2 +sz3)/2;
			return 4;
		}
		return 0;
	} // if( res3>1 )	// 3 real roots, 
	// now resoventa have 1 real and pair of compex roots
	// x[0] - real root, and x[0]>0, 
	// x[1]�i*x[2] - complex roots, 
	// x[0] must be >=0. But one times x[0]=~ 1e-17, so:
	if (roots[0] < 0)
		roots[0] = 0;
	double sz1 = sqrt(roots[0]);
	double szr, szi;
	CSqrt(roots[1], roots[2], &szr, &szi);  // (szr+i*szi)^2 = x[1]+i*x[2]
	if( q.d>0 )	// sign = -1
	{
		p->i = -sz1/2-szr;			// 1st real root
		p->i_2 = -sz1/2+szr;			// 2nd real root
		roots[2] = sz1/2; 
		roots[3] = szi;
		return 2;
	}
	// now: c<0 , sign = +1
	p->i = sz1/2-szr;			// 1st real root
	p->i_2 = sz1/2+szr;			// 2nd real root
	roots[2] = -sz1/2;
	roots[3] = szi;
	return 2;
}

int solve_square_boundaries(t_rt_param *param, t_square *square)
{
	t_vector3	point;
	double		x_proj;
	double		z_proj;

	point = point_from_ray(param->origin, param->ray, param->i);
	point = direction_vector(point, square->centre);
	x_proj = dot(point, square->x) / square->height;
	z_proj = dot(point, square->z) / square->height;
	if ((x_proj < square->height && x_proj > 0) &&
		(z_proj < square->height && z_proj > 0))
		return (1);
	return (0);
}

int solve_disk_boundaries(t_rt_param *param, t_disk *disk)
{
	t_vector3	point;
	double		dist;

	point = point_from_ray(param->origin, param->ray, param->i);
	dist = distance(point, disk->centre);
	if (dist < disk->diametre / 2)
		return (1);
	return (0);
}

int solve_triangle_boundaries(t_rt_param *param, t_triangle *tri)
{
    t_vector3 inter;
    t_vector3 edge;
    t_vector3 vertice_inter;

    inter = point_from_ray(param->origin, param->ray, param->i);
    edge = direction_vector(tri->p1, tri->p2);
    vertice_inter = direction_vector(tri->p1, inter);
    if (dot(tri->normal, cross_prod(edge, vertice_inter)) > 0)
        return (0);
    edge = direction_vector(tri->p2, tri->p3);
    vertice_inter = direction_vector(tri->p2, inter);
    if (dot(tri->normal, cross_prod(edge, vertice_inter)) > 0)
        return (0);
    edge = direction_vector(tri->p3, tri->p1);
    vertice_inter = direction_vector(tri->p3, inter);
    if (dot(tri->normal, cross_prod(edge, vertice_inter)) > 0)
        return (0);
    return (1);
}
