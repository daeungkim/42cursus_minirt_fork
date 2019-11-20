/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:25:46 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/20 18:52:49 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>
#include <stdio.h>
/*
** To avoid catastrophic cancellation between b and discriminant,
** we will use a sign functin
*/
int solve_quadratic(t_vector3 abc, double *t0, double *t1)
{
	double disc;
	double q;

	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (0);
	if (disc == 0)
		*t0 = -abc.y / (2 * abc.x);
	q = -0.5 * (abc.y + ((abc.y > 0) ? sqrt(disc) : - sqrt(disc)));
	*t0 = q / abc.x;
	*t1 = abc.z / q;
	if (*t0 > *t1)
		*t0 = *t1;
	return (1);
}