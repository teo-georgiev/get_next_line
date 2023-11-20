/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:32:31 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/20 09:43:20 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char *f_read_file(int fd)
{
    char    *line;
    char    buf;
    int     i;

    line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    i = 0;
    while (read(fd, &buf, BUFFER_SIZE))
    {
        line[i] = buf;
        i++;
    }
    return (line);
}

char    *get_next_line(fd)
{
    int         len;
    static char *line;

    if (BUFFER_SIZE <= 0 || fd <= 0)
        return (0);
    line = f_read_file(fd);
    return (line);
}

/*


*/