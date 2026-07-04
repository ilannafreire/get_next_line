/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 00:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/04 08:28:52 by ifreire          ###   ########.fr       */
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

static void	ft_append(char **str, char *buff)
{
	char	*aux;

	if (!*str)
		*str = ft_strdup(buff);
	else
	{
		aux = ft_strjoin(*str, buff);
		ft_freethis(str);
		*str = aux;
	}
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			size;
	static char	*str[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	while (size > 0)
	{
		buff[size] = '\0';
		ft_append(&str[fd], buff);
		if (ft_strchr(str[fd], '\n'))
			break ;
		size = read(fd, buff, BUFFER_SIZE);
	}
	ft_freethis(&buff);
	if (size < 0)
	{
		ft_freethis(&str[fd]);
		return (NULL);
	}
	return (cut(&str[fd]));
}
