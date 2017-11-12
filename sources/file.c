/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 03:39:32 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 01:29:28 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "particle.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = NULL;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if ((str = (char *)malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t		ft_strchr(const char *str, const char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void		ft_strcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	if (!src || !dest)
		return ;
	i = -1;
	while (++i < size)
		dest[i] = src[i];
}

char		*get_file_content(const char *path, size_t *size)
{
	char	buf[BUFF_SIZE + 1];
	int		fd;
	char	*str;
	char	*tmp;
	int		i;

	*size = 0;
	if ((fd = open(path, O_RDONLY)) > 2)
	{
		str = NULL;
		while ((i = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[i] = '\0';
			tmp = str;
			str = ft_strjoin(str, buf);
			if (tmp)
				free(tmp);
			*size += i;
		}
		close(fd);
		return (str);
	}
	return (NULL);
}

size_t		get_str_line(char *str, char **line)
{
	size_t	i;

	*line = NULL;
	if ((i = ft_strchr(str, '\n')) <= 0)
		return (0);
	if (!((*line) = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strcpy(*line, str, i);
	(*line)[i] = '\0';
	return (i);
}
