/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:48:02 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/13 14:37:00 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_error(char *err)
{
	ft_putstr("Error\n");
	ft_putstr(err);
	ft_putstr("\n");
	return (0);
}

int		extra_info(char *err)
{
	ft_putstr(err);
	ft_putstr("\n");
	return (1);
}

int		is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_whitespace(char **line)
{
	while (is_white_space(**line))
		(*line)++;
}

int		check_ref(char **line)
{
	skip_whitespace(line);
	if (**line == 'R')
		return (1);
	return (0);
}
