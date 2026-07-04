/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 23:21:36 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/04 12:26:32 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static void	ft_grow_cap(char **str, size_t str_len,
	size_t *cap, size_t new_cap)
{
	char	*new_str;

	new_str = malloc(new_cap);
	if (!new_str)
		return ;
	if (*str)
	{
		ft_strlcpy(new_str, *str, str_len + 1);
		free(*str);
	}
	else
		new_str[0] = '\0';
	*str = new_str;
	*cap = new_cap;
}

static void	ft_append(char **str, char *buff, size_t *cap)
{
	size_t	str_len;
	size_t	buff_len;
	size_t	needed;
	size_t	new_cap;

	str_len = ft_strlen(*str);
	buff_len = ft_strlen(buff);
	needed = str_len + buff_len + 1;
	if (needed > *cap)
	{
		new_cap = *cap * 2;
		if (new_cap < needed)
			new_cap = needed * 2;
		ft_grow_cap(str, str_len, cap, new_cap);
		if (needed > *cap)
			return ;
	}
	ft_strlcpy(*str + str_len, buff, buff_len + 1);
}

static int	ft_read_loop(int fd, char **str, size_t *cap)
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
		ft_append(str, buff, cap);
		if (ft_strchr(buff, '\n'))
			break ;
		size = read(fd, buff, BUFFER_SIZE);
	}
	ft_freethis(&buff);
	return (size);
}

char	*get_next_line(int fd)
{
	int				size;
	static char		*str;
	static size_t	cap;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!ft_strchr(str, '\n'))
	{
		size = ft_read_loop(fd, &str, &cap);
		if (size < 0)
		{
			ft_freethis(&str);
			cap = 0;
			return (NULL);
		}
	}
	cap = 0;
	return (ft_extract_line(&str));
}
