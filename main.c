/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:32:41 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/12/01 11:59:22 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    int fd;
    int i;
    char *line;

    fd = open("bible.txt", O_RDONLY);
    i = 1;
    if (fd == -1)
        close(fd);
    else 
        while ((line = get_next_line(fd)))
        {
            printf("%d->\t%s", i++, line);
            free(line);
        }
    return (0);
}