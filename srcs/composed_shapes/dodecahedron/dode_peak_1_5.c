/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dode_peak_1_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:53:04 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 14:05:57 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

t_list	*generate_triangles_peak_1(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[0], v[0], v[16], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[0], v[0], v[12], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[0], v[3], v[17], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[0], v[3], v[12], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[0], v[17], v[16], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_2(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[1], v[0], v[16], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[1], v[0], v[8], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[1], v[8], v[9], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[1], v[9], v[1], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[1], v[1], v[0], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_3(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[2], v[17], v[16], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[2], v[16], v[1], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[2], v[1], v[13], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[2], v[13], v[2], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[2], v[2], v[17], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_4(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[3], v[11], v[3], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[3], v[3], v[17], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[3], v[17], v[2], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[3], v[2], v[10], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[3], v[10], v[11], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}

t_list	*generate_triangles_peak_5(t_vector3 *v, t_vector3 *p, int colour)
{
	t_list *ele;
	t_list *new;

	ele = 0;
	new = ft_lstnew(tri_factory(p[4], v[15], v[12], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[4], v[12], v[0], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[4], v[0], v[8], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[4], v[8], v[7], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	new = ft_lstnew(tri_factory(p[4], v[7], v[15], colour));
	if (!new || !(new->content))
		return (0);
	ft_lstadd_back(&(ele), new);
	return (ele);
}
