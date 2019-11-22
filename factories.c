/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factories.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:07:36 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/22 18:01:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_camera *camera_factory(t_vector3 pos, t_vector3 vector, double fov)
{
	t_camera *cam;

	if (!(cam = malloc(sizeof(t_camera))))
		return (NULL);
	cam->fov = fov;
	cam->pos.x = pos.x;
	cam->pos.y = pos.y;
	cam->pos.z = pos.z;
	cam->vector.x = vector.x;
	cam->vector.y = vector.y;
	cam->vector.z = vector.z;
	return (cam);
}

t_light *light_factory(t_vector3 pos, double ratio, int colour)
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

t_sphere *sphere_factory(t_vector3 centre, double diametre, int colour)
{
	t_sphere *sp;

	if (!(sp = malloc(sizeof(t_sphere))))
		return (NULL);
	sp->centre.x = centre.x;
	sp->centre.y = centre.y;
	sp->centre.z = centre.z;
	sp->diametre = diametre;
	sp->colour = colour;
	return (sp);
}

t_plane *plane_factory(t_vector3 centre, t_vector3 normal, int colour)
{
	t_plane *plane;

	if (!(plane = malloc(sizeof(t_plane))))
		return (NULL);
	plane->colour = colour;
	plane->centre.x = centre.x;
	plane->centre.y = centre.y;
	plane->centre.z = centre.z;
	plane->normal.x = normal.x;
	plane->normal.y = normal.y;
	plane->normal.z = normal.z;
	return (plane);
}

