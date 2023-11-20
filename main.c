/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:32:41 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/20 08:34:21 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line[1024];

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        close(fd);
        return (0);
    }
    *line = malloc(1 * sizeof(char));
    while (*line)
    {
        free(*line);
        *line = get_next_line(fd);
    }
    printf("%s", *line);
    return (0);
}