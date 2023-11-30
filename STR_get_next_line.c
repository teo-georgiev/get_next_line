/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   STR_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teogeorgiev <teogeorgiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:17:18 by teogeorgiev       #+#    #+#             */
/*   Updated: 2023/11/30 17:52:35 by teogeorgiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "STR_get_next_line.h"

static char *clean_text(char *source)
{
    char    *rem;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (source[i] && source[i] != '\n')
        i++;
    if (!source[i])
    {
        free(source);
        return (NULL);
    }
    rem = (char *)malloc((get_len(source) - i + 1) * sizeof(char));
    i++;
    while (source[i + j])
    {
        rem[j] = source[i + j];
        j++;
    }
    free(source);
    return (rem);
}

static char *get_line(char *source)
{
    char    *line;
    int     i;
    int     len;

    i = 0;
    len = 0;
    while (source[len] && source[len] != '\n')
        len++;
    line = (char *)malloc((len + 1) * sizeof(char));
    if (!line)
        return (NULL);
    while (source[i] && i < len)
    {
        if (source[i] == '\n')
        {
            line[i++] = '\n';
            break ;
        }
        line[i] = source[i];
    }
    line[i] = '\0';
    return (line);
}

static char *read_text(int fd, char *source)
{
    int     char_read;
    char    *buffer;

    char_read = 0;
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    if (!source)
        source = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    while (has_newline(buffer))
    {
        char_read = read(fd, buffer, BUFFER_SIZE);
        if (char_read < 0)
            return (NULL);
        buffer[char_read] = '\0';
        source = text_join(source, buffer);
        if (has_newline(source))
            break ;
    }
    free(buffer);
    return (source);
}

char    *get_next_line(int fd)
{
    static char *source;
    char        *new_line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    source = read_text(fd, source);
    if (source == NULL)
        return (NULL);
    new_line = get_line(source);
    clean_text(source);
    return (new_line);
}