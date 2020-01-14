/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherocylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:03:54 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/14 12:21:35 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

int	create_endings(t_data *data, t_cylindre *cy, int colour)
{
	t_list		*sp;
	t_vector3	new;

	if (!(sp = ft_lstnew(sphere_factory(cy->centre, cy->diametre, colour))) ||
		!((t_geo *)(sp->content)))
		return (parse_error("Malloc for sphere ending failed"));
	ft_lstadd_back(&(data->objects), sp);
	new = point_from_ray(cy->centre, cy->orient, cy->height);
	if (!(sp = ft_lstnew(sphere_factory(new, cy->diametre, colour))) ||
		!((t_geo *)(sp->content)))
		return (parse_error("Malloc for sphere ending failed"));
	ft_lstadd_back(&(data->objects), sp);
	return (1);
}
