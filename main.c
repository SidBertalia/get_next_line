/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbertali <sbertali@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:12:20 by sbertali          #+#    #+#             */
/*   Updated: 2021/03/05 22:36:28 by sbertali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    char *line;
    int read_return;

    int fd = open("alfabeto.txt", O_RDONLY);
    while ((read_return = get_next_line(fd, &line)) >= 0)
    {
        printf("%s\n", line);
        if (read_return == 0)
            break ;
        free(line);
    }
    free(line);
}
