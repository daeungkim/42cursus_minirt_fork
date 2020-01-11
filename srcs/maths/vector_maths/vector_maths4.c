/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:44:20 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/11 14:49:29 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector3   reflect_vector(t_vector3 ray, t_vector3 normal)
{
    return (sub_vect(ray, scalar_vect(normal, 2 * dot(ray, normal))));
}