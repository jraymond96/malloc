/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:33:17 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/02 22:02:13 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_buff_fill_line(char **line, char *buff)
{
	char	*ret_chr;
	int		res;

	if (!(ret_chr = ft_strchr(buff, '\n')))
	{
		*line = ft_strjoin_free(*line, buff, 1);
		ft_bzero(buff, BUFF_SIZE);
		return (0);
	}
	else
	{
		*ret_chr = '\0';
		*line = ft_strjoin_free(*line, buff, 1);
		res = ++ret_chr - buff;
		ft_strncpy(buff, &buff[res], BUFF_SIZE);
		return (1);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char	buff[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || !line || !(*line = ft_strnew(BUFF_SIZE)) || BUFF_SIZE < 0)
		return (-1);
	while (1)
	{
		if (!buff[0])
			ft_bzero(buff, BUFF_SIZE + 1);
		if ((check_buff_fill_line(line, buff)) == 1)
			return (1);
		if (!buff[0] && (ret = read(fd, buff, BUFF_SIZE) < 0))
			return (-1);
		if (!buff[0] && ret == 0 && **line)
			return (1);
		if (!buff[0] && ret == 0 && !**line)
			return (0);
	}
}
