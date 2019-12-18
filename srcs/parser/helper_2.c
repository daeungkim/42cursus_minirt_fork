/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:49:04 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/18 17:55:50 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>

int ft_atoi_live(char **line)
{
	int value;
	int sign;

	sign = 1;
	value = 0;
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	while (**line >= '0' && **line <= '9' && **line)
		value = 10 * value + *(*line)++ - '0';
	return (value * sign);
}

double ft_atof_live(char **line)
{
	double value;
	double fraction;
	int sign;

	sign = 1;
	value = 0;
	fraction = 0.1;
	skip_whitespace(line);
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	while (ft_isdigit(**line))
		value = 10 * value + *(*line)++ - '0';
	if (**line == '.')
	{
		(*line)++;
		while (ft_isdigit(**line))
		{
			value += (*(*line)++ - '0') * fraction;
			fraction *= 0.1;
		}
	}
	return (value * sign);
}

int get_rgb(char **line, int *colour, int value)
{
	skip_whitespace(line);
	*colour = 0;
	if (ft_isdigit(**line))
		value = ft_atoi_live(line);
	else
		return (0);
	if (value < 0 || value > 255 || *(*line)++ != ',')
		return (0);
	*colour = (*colour << 8) + value;
	if (ft_isdigit(**line))
		value = ft_atoi_live(line);
	else
		return (0);
	if (value < 0 || value > 255 || *(*line)++ != ',')
		return (0);
	*colour = (*colour << 8) + value;
	if (ft_isdigit(**line))
		value = ft_atoi_live(line);
	else
		return (0);
	if (value < 0 || value > 255)
		return (0);
	*colour = (*colour << 8) + value;
	return (1);
}

int get_vector3(char **line, t_vector3  *vector)
{
	skip_whitespace(line);
	if (ft_isdigit(**line) || **line == '-')
		vector->x = ft_atof_live(line);
	else
		return(0);
	if (*(*line)++ != ',')
		return (0);
	if (ft_isdigit(**line) || **line == '-')
		vector->y = ft_atof_live(line);
	else
		return(0);
	if (*(*line)++ != ',')
		return (0);
	if (ft_isdigit(**line) || **line == '-')
		vector->z = ft_atof_live(line);
	else
		return(0);
	return (1);
}

int check_points_unique(t_vector3 p1, t_vector3 p2, t_vector3 p3)
{
	if ((p1.x == p2.x && p1.y == p2.y && p1.z == p2.z) ||
		(p1.x == p3.x && p1.y == p3.y && p1.z == p3.z) ||
		(p2.x == p3.x && p2.y == p3.y && p2.z == p3.z))
		return (0);
	return (1);
}