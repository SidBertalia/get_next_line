/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbertali <sbertali@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:11:32 by sbertali          #+#    #+#             */
/*   Updated: 2021/03/06 16:44:48 by sbertali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define MAX_FILE_DESCRIPTOR	RLIMIT_NOFILE//número maxímo de arquivos a serem lidos
# define BUFFER_SIZE 42//apagar antes de entregar

int		get_next_line(int fd, char **line);

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strjoin_free(char *dest, char *src);
size_t	ft_strclen(const char *str, const char chr);
void	ft_strdel(char **str);

#endif
