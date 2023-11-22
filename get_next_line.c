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

// f_search_nl



char    *f_strjoin(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *new_s;

    i = 0;
    j = 0;
    new_s = (char *)malloc((f_strlen(s1) + f_strlen(s2) + 1) * sizeof(char *));
    while (s1[++i])
        new_s[i] = s1[i++];
    while (s2[j])
    {
        if (s2[j] == '\n')
        {
            new_s[i + j++] = '\n';
            new_s[i + j] = '\0';
            return(new_s);
        }
        new_s[i + j] = s2[j++];
    }
    new_s[i + j] = '\0';
    return (new_s);
}

size_t     f_search_nl(char *buf)
{
    int i;

    i = 0;
    while (buf[i])
    {
        if (buf[i++] == '\n')
            return (1);
    }
    return (0);
}

char    *f_read_text(int fd, char *s_read)
{
    int     nbr_read;
    char    *buf;

    if (fd < 0 || read(0, buf, BUFFER_SIZE) < 0)
        return (NULL);
    buf = 0;
    nbr_read = 0;
    while (f_search_nl(buf))
    {
        nbr_read = read(fd, buf, BUFFER_SIZE);
        if (nbr_read < 0)
            reutrn (NULL);
        s_read = f_strjoin(s_read, buf);
    }
    return (s_read);
}

char    *get_next_line(int fd)
{
    static char *s_read;
    char        *new_line;

    s_read = f_read_text(fd, s_read);
    new_line = f_get_line(s_read);
    f_clear_string(s_read);
    return (new_line);
}

// read characters
// move characters from s_read to next_line
// empty chars that have been moved