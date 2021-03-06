/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbertali <sbertali@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:11:39 by sbertali          #+#    #+#             */
/*   Updated: 2021/03/06 16:44:48 by sbertali         ###   ########.fr       */
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
		if (*str == (char)c)//se encontrar o caracter na string apontada por str
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	else
		return (NULL);//retorna o caracter, mesmo que seja NULL
}

/*
** Aloca memória suficiente para a cópia da string src, faz a cópia em dest e
** retorna um ponteiro para ela.
*/

static char	*ft_strdup(const char *src)
{
	char *dest;

	if (!(dest = (char *)malloc(ft_strlen(src) + 1)))//aloca memória para dest baseado no tamanho de src
		return (0);
	ft_memcpy(dest, src, ft_strlen(src) + 1);//como tamanho passado por strlen +1, aloca de uma área de memória para outra
	return (dest);
}

/*
** Retorna um trecho especifico, subtraido de uma string.
*/

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_str;

	sub_str = (char *)malloc((len + 1) * sizeof(char));//Aloca no tamanho(len +1) o espaço para sub_str
	if (!s || (sub_str == NULL))//se não for uma string ou sub_str for NULL retorna NULL
	{
		return (NULL);
	}
	i = 0;
	while ((i < len) && ((start + i) < ft_strlen(s)) && (s[start + i] != '\0'))
	{
		sub_str[i] = s[start + i];//Passa a string a partir do ponto start para a sub_string
		i++;
	}
	sub_str[i] = '\0';//acrescenta \0 no final
	return (sub_str);
}

/*
** Especifíca saídas de retorno [(-1)ERRO] - [(0)EOF] - [(1)EOL]
*/

static int	outputs(int n, char **buff, char **line)// V.A.R.(Verificação Automática do que deu Ruim)
{
	char *temp;

	if (n < 0)//Condição inicial, fd deve existir! Se fd for < 0, está errado
		return (-1);//ERRO
	*line = ft_substr(*buff, 0, ft_strclen(*buff, '\n'));// Procura \n na buff e marca a posição. Pega a substr e coloca na line, apontada. NOTA: 0 é pos incio substr.
	if (!line)//Se não encontrar a line, retorna erro.
		return (-1);//ERRO
	if (ft_strchr(*buff, '\n'))//Procura \n na buff.
	{
		temp = ft_strdup(ft_strchr(*buff, '\n') + 1);//duplica a buff +1 na temp.
		ft_strdel(&*buff);//Libera a buff, coloca a temp na buff e retorna (1).
		*buff = temp;
		return (1);//EOL(final da linha)
	}
	ft_strdel(&*buff);//Se não for nenhuma das alternativas, o arquivo acabou! Retorna (0).
	return (0);//EOF(final do arquivo)
}

/*
** Lê uma linha por vez de um fd, com tamanho determinado pelo BUFFER_SIZE
** NOTA: MAX_FILE_DESCRIPTOR = número maxímo de arquivos a serem lidos
** NOTA: BUFFER_SIZE = tamanho maxímo dos arquivos a serem lidos
*/

int			get_next_line(int fd, char **line)
{
	static char	*buff_line[MAX_FILE_DESCRIPTOR];//Buff_line do fd é limitado por MAX_FILE_DESCRIPTOR.
	char		*new_line;
	int			nbytes;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FILE_DESCRIPTOR || !line)//Caso uma das condições seja encontrada, retorna [(-1)ERRO]
		return (-1);//ERRO
	if (!(buff_line[fd]))
		if (!(buff_line[fd] = ft_strdup("")))//Se a buff_line estiver vazia, etá errada.
			return (-1);//ERRO
	new_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));//Aloca a string com tam do BUFFER +1 na new_line.
	if (!new_line)//Se uma new_line não foi alocada retorna erro.
		return (-1);//ERRO
	while ((nbytes = read(fd, new_line, BUFFER_SIZE)) > 0)//Enquanto nbytes(fd, new_line e BUFFER_SIZE) for maior que 0, continua lendo.
	{
		new_line[nbytes] = '\0';//Acrescenta \0 ao final da new_line
		buff_line[fd] = ft_strjoin_free(buff_line[fd], new_line);//Pega new_line, junta com buff_line, libera new_line e colaca tudo na buff_line.
		if (ft_strchr(buff_line[fd], '\n'))//Se achar \n na buff_line do fd, sai do loop e chama strdel.
			break ;//Sai do loop.
	}
	ft_strdel(&new_line);//Libera new_line.
	return (outputs(nbytes, &buff_line[fd], line));//Verifica opções de saída com função outputs.
}
