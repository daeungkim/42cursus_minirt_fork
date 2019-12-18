/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dode_peak_11_12.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:53:09 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/11 20:46:02 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

t_list	*generate_triangles_peak_11(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;
	ele = 0;
	new = ft_lstnew(tri_factory(p[10], v[18], v[19], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[10], v[19], v[6], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[10], v[6], v[14], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[10], v[14], v[5], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[10], v[5], v[18], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_12(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;
	ele = 0;
	new = ft_lstnew(tri_factory(p[11], v[18], v[4], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[11], v[4], v[11], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[11], v[11], v[10], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[11], v[10], v[5], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[11], v[5], v[18], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list *generate_tri_1_5(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list		*ele;
	t_list		*new;

	ele = 0;
	if (!(new = generate_triangles_peak_1(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_2(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_3(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_4(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_5(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	return (ele);
}

t_list *generate_tri_6_10(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list		*ele;
	t_list		*new;

	ele = 0;
	if (!(new = generate_triangles_peak_6(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_7(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_8(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_9(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_10(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	return (ele);
}

t_list *generate_tri_11_12(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list		*ele;
	t_list		*new;

	ele = 0;
	if (!(new = generate_triangles_peak_11(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_triangles_peak_12(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	return (ele);
}