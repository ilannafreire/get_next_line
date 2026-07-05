/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 00:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/04 22:29:45 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_extract_line(char **str)
{
	int		i;
	char	*ret;
	char	*aux;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[0][i] != '\n' && str[0][i] != '\0')
		i++;
	ret = ft_substr(str[0], 0, i + 1);
	aux = ft_substr(str[0], 0, ft_strlen(str[0]));
	ft_freethis(str);
	str[0] = ft_substr(aux, i + 1, ft_strlen(aux));
	ft_freethis(&aux);
	if (!ft_strchr(ret, '\n'))
	{
		if (!ft_strlen(ret))
			ft_freethis(&ret);
		ft_freethis(str);
	}
	return (ret);
}

static void	ft_append(char **str, char *buff)
{
	size_t	str_len;
	size_t	buff_len;
	char	*new_str;

	str_len = ft_strlen(*str);
	buff_len = ft_strlen(buff);
	new_str = malloc(str_len + buff_len + 1);
	if (!new_str)
		return ;
	if (*str)
		ft_strlcpy(new_str, *str, str_len + 1);
	else
		new_str[0] = '\0';
	ft_strlcpy(new_str + str_len, buff, buff_len + 1);
	ft_freethis(str);
	*str = new_str;
}

static int	ft_read_loop(int fd, char **str)
{
	char	*buff;
	int		size;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	size = read(fd, buff, BUFFER_SIZE);
	while (size > 0)
	{
		buff[size] = '\0';
		ft_append(str, buff);
		if (ft_strchr(buff, '\n'))
			break ;
		size = read(fd, buff, BUFFER_SIZE);
	}
	ft_freethis(&buff);
	return (size);
}

char	*get_next_line(int fd)
{
	int			size;
	static char	*str[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (!ft_strchr(str[fd], '\n'))
	{
		size = ft_read_loop(fd, &str[fd]);
		if (size < 0)
		{
			ft_freethis(&str[fd]);
			return (NULL);
		}
	}
	return (ft_extract_line(&str[fd]));
}
