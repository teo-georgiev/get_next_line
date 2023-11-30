/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:32:41 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/29 15:56:18 by tgeorgie         ###   ########.fr       */
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
            printf("%d-> %s", i++, line);
    return (0);
}