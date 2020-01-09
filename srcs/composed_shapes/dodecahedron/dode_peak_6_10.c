/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dode_peak_6_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:53:07 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 14:07:28 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

t_list	*generate_triangles_peak_6(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[5], v[9], v[1], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[5], v[1], v[13], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[5], v[13], v[14], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[5], v[14], v[6], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[5], v[6], v[9], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_7(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[6], v[10], v[2], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[6], v[2], v[13], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[6], v[13], v[14], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[6], v[14], v[5], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[6], v[5], v[10], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_8(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[7], v[15], v[12], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[7], v[12], v[3], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[7], v[3], v[11], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[7], v[11], v[4], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[7], v[4], v[15], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_9(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[8], v[15], v[7], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[8], v[7], v[19], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[8], v[19], v[18], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[8], v[18], v[4], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[8], v[4], v[15], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_10(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[9], v[7], v[8], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[9], v[8], v[9], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[9], v[9], v[6], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[9], v[6], v[19], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[9], v[19], v[7], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}
