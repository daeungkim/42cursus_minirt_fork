/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:05:18 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:50:07 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		wrong_obj(t_data *data, char **line)
{
	data = 0;
	line = 0;
	return (parse_error("wrong input in .rt file"));
}

void	init_tab(int (*tab[256][256])(t_data *, char **))
{
	int i;
	int j;

	i = 0;
	while (i < 256)
	{
		j = 0;
		while (j < 256)
			tab[i][j++] = &wrong_obj;
		i++;
	}
}

void	populate_functions(int (*tab[256][256])(t_data *, char **))
{
	init_tab(tab);
	tab['R'][0] = &load_res;
	tab['A'][0] = &load_amb;
	tab['l'][0] = &load_light;
	tab['c'][0] = &load_camera;
	tab['s']['p'] = &load_sphere;
	tab['p']['l'] = &load_plane;
	tab['s']['q'] = &load_square;
	tab['c']['u'] = &load_cube;
	tab['t']['r'] = &load_triangle;
	tab['d']['k'] = &load_disk;
	tab['d']['o'] = &load_dodecahedron;
	tab['t']['o'] = &load_torus;
	tab['c']['o'] = &load_cone;
	tab['c']['y'] = &load_cylinder;
	tab['p']['y'] = &load_pyramid;
}

int		load_line(t_data *data, char *line)
{
	int (*parse_functions[256][256])(t_data *d, char **l);

	populate_functions(parse_functions);
	if (ft_strlen(line) < 2)
		return (1);
	if (*line == '#')
		return (1);
	if (is_white_space(line[1]))
		return (parse_functions[(int)*line][0](data, &line));
	else
		return (parse_functions[(int)*line][(int)line[1]](data, &line));
}

int		load_data(t_data *data, char *rt_file)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(rt_file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			free(line);
			return (0);
		}
		if (!load_line(data, line))
		{
			extra_info("Parsing stopped.");
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}
