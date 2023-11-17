/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:32:31 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/17 10:42:20 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *f_line_len(int fd)
{
    char    *line;
    char    buf;

    line = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
    line += read(fd, &buf, BUFFER_SIZE);
    return (line);
}

char    *get_next_line(fd)
{
    int         len;
    static char *line;

    if (BUFFER_SIZE <= 0 || fd <= 0)
        return (NULL);
    line = f_line_len(fd);
    return (line);
}