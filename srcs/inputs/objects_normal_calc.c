/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_normal_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:17:58 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:42:01 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "key.h"

void	recalc_sq_vect(t_square *sq)
{
	sq->normal = apply_orientation(create_vector(0, 1, 0), sq->orient);
	sq->x = apply_orientation(create_vector(1, 0, 0), sq->orient);
	sq->x = scalar_vect(sq->x, sq->height);
	sq->z = apply_orientation(create_vector(0, 0, 1), sq->orient);
	sq->z = scalar_vect(sq->z, sq->height);
}

void	recalc_dk_norm(t_disk *dk)
{
	dk->normal = apply_orientation(create_vector(0, 1, 0), dk->orient);
}

void	recalc_pl_norm(t_plane *pl)
{
	pl->normal = apply_orientation(create_vector(0, 1, 0), pl->orient);
}

void	recalc_cy_norm(t_cylindre *cy)
{
	cy->orient = apply_orientation(create_vector(0, 1, 0), cy->real_ori);
}

void	recalc_cone_norm(t_cone *co)
{
	co->normal = apply_orientation(create_vector(0, 1, 0), co->orient);
}
