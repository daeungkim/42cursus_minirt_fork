/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:07:19 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:28:20 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	get_blue(int colour)
{
	return (colour & 0xFF);
}

int	get_green(int colour)
{
	return ((colour & 0xFF00) >> 8);
}

int	get_red(int colour)
{
	return ((colour & 0xFF0000) >> 16);
}

int	encode_rgb(int red, int green, int blue)
{
	return ((((red << 8) + green) << 8) + blue);
}
