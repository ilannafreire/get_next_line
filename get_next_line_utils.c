/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 23:21:14 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/04 12:12:16 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	x;

	if (!s)
		return (0);
	x = 0;
	while (s[x] != '\0')
		x++;
	return (x);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *) &s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlcpy(char *dst,
	const char *src, size_t size)
{
	size_t			i;
	unsigned int	len;

	len = ft_strlen(src);
	i = 0;
	if (size == 0)
	{
		return (len);
	}
	else
	{
		while (i < (size - 1) && (i < len))
		{
			dst[i] = ((char *)src)[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

void	ft_freethis(char **str)
{
	if (str[0])
	{
		free(str[0]);
		str[0] = NULL;
	}
}

char	*ft_substr(char const *s,
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
