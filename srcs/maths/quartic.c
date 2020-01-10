/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quartic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:47:00 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/10 16:55:03 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

static int	return_3_roots(double *roots, double r, double q, double b)
{
	double omega;

	omega = r / sqrt((q * q * q));
	if (omega < -1)
		omega = -1;
	if (omega > 1)
		omega = 1;
	omega = acos(omega);
	roots[0] = -2 * sqrt(q) * cos(omega / 3) - b / 3;
	roots[1] = -2 * sqrt(q) * cos((omega + 2 * M_PI) / 3) - b / 3;
	roots[2] = -2 * sqrt(q) * cos((omega - 2 * M_PI) / 3) - b / 3;
	return (3);
}

static int	solve_cubic(double *roots, double b, double c, double d)
{
	double q;
	double r;
	double s;

	q = (b * b - 3 * c) / 9;
	r = (-9 * b * c + 27 * d + 2 * pow(b, 3)) / 54;
	if (q * q * q > r * r)
		return (return_3_roots(roots, r, q, b));
	else
	{
		s = -pow(fabs(r) + sqrt(r * r - q * q * q), 1.0 / 3);
		if (r < 0)
			s = -s;
		roots[0] = -(b / 3) + (s + (s == 0 ? 0 : (q / s)));
		roots[1] = -(b / 3) - 0.5 * (s + (s == 0 ? 0 : (q / s)));
		roots[2] = 0.5 * sqrt(3.0) * (s + (s == 0 ? 0 : (q / s)));
		if (fabs(roots[2]) < 1e-14)
		{
			roots[2] = roots[1];
			return (2);
		}
		return (1);
	}
}

static void	treat_param(t_quartic q, double *qps, double *d, double *y)
{
	if (fabs(*d) < 1e-14)
	{
		qps[0] = *y * 0.5;
		qps[1] = qps[0];
		*d = q.b * q.b - 4 * (q.c - *y);
		if (fabs(*d) < 1e-14)
		{
			qps[2] = q.b * 0.5;
			qps[3] = qps[2];
		}
		else
		{
			qps[4] = sqrt(*d);
			qps[2] = (q.b + qps[4]) * 0.5;
			qps[3] = (q.b - qps[4]) * 0.5;
		}
	}
	else
	{
		qps[4] = sqrt(*d);
		qps[0] = (*y + qps[4]) * 0.5;
		qps[1] = (*y - qps[4]) * 0.5;
		qps[2] = (q.b * qps[0] - q.d) / (qps[0] - qps[1]);
		qps[3] = (q.d - q.b * qps[1]) / (qps[0] - qps[1]);
	}
}

static int	complete_roots(t_rt_param *p, double *qps)
{
	double	d;
	int		res;

	res = 0;
	d = qps[2] * qps[2] - 4 * qps[0];
	if (d > 0.0)
	{
		qps[4] = sqrt(d);
		p->v = 1;
		p->v_2 = 1;
		p->i = (-qps[2] + qps[4]) * 0.5;
		p->i_2 = (-qps[2] - qps[4]) * 0.5;
		res += 2;
	}
	d = qps[3] * qps[3] - 4 * qps[1];
	if (d > 0.0)
	{
		qps[4] = sqrt(d);
		p->v_4 = 1;
		p->v_3 = 1;
		p->i_3 = (-qps[3] + qps[4]) * 0.5;
		p->i_4 = (-qps[3] - qps[4]) * 0.5;
		res += 2;
	}
	return (res);
}

int			solve_quartic(t_quartic q, t_rt_param *p)
{
	double	roots[3];
	double	y;
	int		res;
	double	d;
	double	qps[5];

	res = solve_cubic(roots, -q.c, q.b * q.d - 4. * q.e,
				-q.b * q.b * q.e - q.d * q.d + 4. * q.c * q.e);
	y = roots[0];
	if (res != 1)
	{
		if (fabs(roots[1]) > fabs(y))
			y = roots[1];
		if (fabs(roots[2]) > fabs(y))
			y = roots[2];
	}
	d = y * y - 4 * q.e;
	res = 0;
	treat_param(q, qps, &d, &y);
	res = complete_roots(p, qps);
	return (res);
}
