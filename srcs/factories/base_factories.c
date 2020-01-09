/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_factories.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:04:33 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:54:58 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_camera	*camera_factory(t_vector3 pos, t_vector3 orient, double fov)
{
	t_camera *cam;

	if (!(cam = malloc(sizeof(t_camera))))
		return (NULL);
	cam->fov = fov;
	cam->pos.x = pos.x;
	cam->pos.y = pos.y;
	cam->pos.z = pos.z;
	cam->orient.x = orient.x;
	cam->orient.y = orient.y;
	cam->orient.z = orient.z;
	cam->vector_x = apply_orientation(create_vector(1, 0, 0), cam->orient);
	cam->vector_y = apply_orientation(create_vector(0, 1, 0), cam->orient);
	cam->vector_z = apply_orientation(create_vector(0, 0, 1), cam->orient);
	return (cam);
}

t_light		*light_factory(t_vector3 pos, double ratio, int colour)
{
	t_light *light;

	if (!(light = malloc(sizeof(t_light))))
		return (NULL);
	light->pos.x = pos.x;
	light->pos.y = pos.y;
	light->pos.z = pos.z;
	light->ratio = ratio;
	light->colour = colour;
	return (light);
}
