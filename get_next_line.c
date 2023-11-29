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

char    *f_clear_string(char *s_read)
{
    char    *tmp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (s_read[i] && s_read[i] != '\n')
        i++;
    i++;
    tmp = (char *)malloc((f_strlen(&s_read[i]) + 1) * sizeof(char));
    while (s_read[i + j])
    {
        tmp[j] = s_read[i + j];
        j++;
    }
    tmp[j] = '\0';
    printf("\n1 --->\n%s\n", tmp);
    free(s_read);
    return (tmp);
}

char    *f_read_text(int fd, char *s_read)
{
    int     nbr_read;
    char    *buf;

    buf = NULL;
    nbr_read = 0;
    if (fd < 0 || read(0, buf, 0) < 0)
        return (NULL);
    while (!f_search_nl(buf))
    {
        buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
        nbr_read = read(fd, buf, BUFFER_SIZE);
        if (nbr_read <= 0)
        {
            free(buf);
            return (NULL);
        }
        buf[nbr_read] = '\0';
        s_read = f_strjoin(s_read, buf);
    }
    free(buf);
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
    s_read = f_clear_string(s_read);
    printf("\nnew line --->\n%s\n", new_line);
    printf("\n2 --->\n%s\n", s_read);
    return (new_line);
}

// read characters
// move characters from s_read to next_line
// empty chars that have been moved

