/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbertali <sbertali@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:11:39 by sbertali          #+#    #+#             */
/*   Updated: 2021/06/03 21:28:46 by sbertali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Procura por caracter espicifico(convertido em char) na string.
*/

static char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	else
		return (NULL);
}

/*
** Aloca memória suficiente para a cópia da string src, faz a cópia em dest e
** retorna um ponteiro para ela.
*/

static char	*ft_strdup(const char *src)
{
	char *dest;

	if (!(dest = (char *)malloc(ft_strlen(src) + 1)))
		return (0);
	ft_memcpy(dest, src, ft_strlen(src) + 1);
	return (dest);
}

/*
** Retorna um trecho especifico, subtraido de uma string.
*/

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_str;

	sub_str = (char *)malloc((len + 1) * sizeof(char));
	if (!s || (sub_str == NULL))
	{
		return (NULL);
	}
	i = 0;
	while ((i < len) && ((start + i) < ft_strlen(s)) && (s[start + i] != '\0'))
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

/*
** Especifíca saídas de retorno [(-1)ERRO] - [(0)EOF] - [(1)EOL]
*/

static int	outputs(int n, char **buff, char **line)
{
	char *temp;

	if (n < 0)
		return (-1);
	*line = ft_substr(*buff, 0, ft_strclen(*buff, '\n'));
	if (!line)
		return (-1);
	if (ft_strchr(*buff, '\n'))
	{
		temp = ft_strdup(ft_strchr(*buff, '\n') + 1);
		ft_strdel(&*buff);
		*buff = temp;
		return (1);
	}
	ft_strdel(&*buff);
	return (0);
}

/*
** Lê uma linha por vez de um fd, com tamanho determinado pelo BUFFER_SIZE
** NOTA: MAX_FILE_DESCRIPTOR = número maxímo de arquivos a serem lidos
** NOTA: BUFFER_SIZE = tamanho maxímo dos arquivos a serem lidos
*/

int			get_next_line(int fd, char **line)
{
	static char	*buff_line[MAX_FILE_DESCRIPTOR];
	char		*new_line;
	int			nbytes;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FILE_DESCRIPTOR || !line)
		return (-1);
	if (!(buff_line[fd]))
		if (!(buff_line[fd] = ft_strdup("")))
			return (-1);
	new_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_line)
		return (-1);
	while ((nbytes = read(fd, new_line, BUFFER_SIZE)) > 0)
	{
		new_line[nbytes] = '\0';
		buff_line[fd] = ft_strjoin_free(buff_line[fd], new_line);
		if (ft_strchr(buff_line[fd], '\n'))
			break ;
	}
	ft_strdel(&new_line);
	return (outputs(nbytes, &buff_line[fd], line));
}
