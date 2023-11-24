/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:20:36 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/22 16:55:45 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char    *f_clear_string(char *s_read)
{
    // char    *tmp;
    int     i;

    i = 0;
    while (s_read[i] || s_read[i] == '\n')
        i++;
    // tmp = (char *)malloc((f_strlen(&s_read[i]) + 1) * sizeof(char));
    // tmp = f_memmove(tmp, &s_read[i], f_strlen(&s_read[i]));
    // s_read = tmp; 
    // free(tmp);
    return (&s_read[i + 1]);
}

char    *f_read_text(int fd, char *s_read)
{
    int     nbr_read;
    char    *buf;

    if (fd < 0 || read(0, buf, 0) < 0)
        return (NULL);
    nbr_read = 0;
    buf = NULL;
    while (!f_search_nl(buf))
    {
        buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
        nbr_read = read(fd, buf, BUFFER_SIZE);
        if (nbr_read < 0)
            return (NULL);
        s_read = f_strjoin(s_read, buf);
    }
    return (s_read);
}

char    *get_next_line(int fd)
{
    static char *s_read;
    char        *new_line;

    s_read = f_read_text(fd, s_read);
    
    if (s_read == NULL)
        return (NULL);
    new_line = (char *)malloc((f_strlen(s_read) + 1) * sizeof(char));
    new_line = f_memmove(new_line, s_read, f_strlen(s_read));
    printf("%s\n", new_line);
    s_read = f_clear_string(s_read);
    return (new_line);
}

// read characters
// move characters from s_read to next_line
// empty chars that have been moved