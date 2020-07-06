/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakim <dakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:05:18 by cjaimes           #+#    #+#             */
/*   Updated: 2020/07/06 13:10:03 by dakim            ###   ########.fr       */
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

// 데이터 파싱함수를 tab에 저장하는 함수
void	populate_functions(int (*tab[256][256])(t_data *, char **))
{
	init_tab(tab);
	tab['R'][0] = &load_res;
	tab['R']['E'] = &load_max_reflection;
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
	tab['s']['c'] = &load_spherocylinder;
}

int		load_line(t_data *data, char *line)
{
	int (*parse_functions[256][256])(t_data *d, char **l);
	// 함수를 parse_function에 저장하는 변수로 추정
	// 리턴값은 int이고 매개변수는 t_data *d, char **l임

	skip_whitespace(&line);
	// 문장 맨 앞과 맨 뒤의 공백을 제거하는 함수로 추정
	populate_functions(parse_functions);
	// parse_functions에 데이터 파싱함수를 저장
	if (ft_strlen(line) < 2)
		return (1);
	// 줄바꿈인경우 다음문장으로 넘어감
	if (*line == '#')
		return (1);
	// 주석처리인경우 다음문장으로 넘어감
	if (is_white_space(line[1]))
	{
		// identifier가 한글자인경우
		return (parse_functions[(int)*line][0](data, &line));
	}
	else
	{
		// identifier가 두글자인경우
		return (parse_functions[(int)*line][(int)line[1]](data, &line));
	}
}

// 파일을 열고, 파일을 문장단위로 파싱하는 함수
int		load_data(t_data *data, char *rt_file)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(rt_file, O_RDONLY);
	// 파일 오픈 수행
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		// 문장단위로 데이터를 가져옴
		if (ret == -1)
		{
			// 문장단위로 데이터를 가져오는데 실패한경우
			free(line);
			return (0);
		}
		if (!load_line(data, line))
		{
			// 데이터 파싱 수행
			// 리턴값이 0인경우 에러발생 / 1인경우 파싱성공
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
