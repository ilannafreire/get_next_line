/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 00:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/04 11:49:51 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_freethis(char **str)
{
	if (str[0])
	{
		free(str[0]);
		str[0] = NULL;
	}
}

static char	*ft_substr(char const *s,
	unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start > size)
	{
		len = 1;
		start = 0;
	}
	else if (start + len > size)
		len = size - start + 1;
	else
		len = len + 1;
	sub = malloc(len);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len);
	return (sub);
}

static char	*cut(char **str)
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
	aux = ft_strdup(str[0]);
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
	static char		*str[OPEN_MAX];
	static size_t	cap[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (!ft_strchr(str[fd], '\n'))
	{
		size = ft_read_loop(fd, &str[fd], &cap[fd]);
		if (size < 0)
		{
			ft_freethis(&str[fd]);
			cap[fd] = 0;
			return (NULL);
		}
	}
	cap[fd] = 0;
	return (cut(&str[fd]));
}
