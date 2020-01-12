/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:27:34 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/12 16:31:00 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	decode_rgb(int colour, int *red, int *green, int *blue)
{
	*red = get_red(colour);
	*green = get_green(colour);
	*blue = get_blue(colour);
}

int		apply_intensity_rgb(int colour, double intensity)
{
	int red;
	int green;
	int blue;

	decode_rgb(colour, &red, &green, &blue);
	red = (double)red * intensity;
	green = (double)green * intensity;
	blue = (double)blue * intensity;
	return (encode_rgb(red, green, blue));
}

int		filter_colours_rgb(int source, t_geo * obj, int lvl)
{
	t_rgb	src;
	t_rgb	surf;

	decode_rgb(source, &(src.r), &(src.g), &(src.b));
	decode_rgb(obj->colour, &(surf.r), &(surf.g), &(surf.b));
	if (surf.r > src.r)
		surf.r = src.r;
	if (surf.g > src.g)
		surf.g = src.g;
	if (surf.b > src.b)
		surf.b = src.b;
	if (lvl)
	{
		surf.r = (double)surf.r * pow(0.995, lvl);
		surf.g = (double)surf.g * pow(0.995, lvl);
		surf.b = (double)surf.b * pow(0.995, lvl);
	}
	return (encode_rgb(surf.r, surf.g, surf.b));
}

int		add_lights(int a, int b)
{
	t_rgb l_a;
	t_rgb l_b;

	decode_rgb(a, &(l_a.r), &(l_a.g), &(l_a.b));
	decode_rgb(b, &(l_b.r), &(l_b.g), &(l_b.b));
	l_a.r += l_b.r;
	l_a.g += l_b.g;
	l_a.b += l_b.b;
	if (l_a.r > 255)
		l_a.r = 255;
	if (l_a.g > 255)
		l_a.g = 255;
	if (l_a.b > 255)
		l_a.b = 255;
	return (encode_rgb(l_a.r, l_a.g, l_a.b));
}
