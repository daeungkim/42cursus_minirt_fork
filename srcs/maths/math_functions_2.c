/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:46:39 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/05 18:26:51 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

void d_swap(double *a, double *b)
{
	double t;

	t = *a;
	*a = *b;
	*b = t;
}

double solve_poly_2(double a, double b)
{
	return (a * a + b * b + 2 * (a * b));
}

double to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}
