/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teogeorgiev <teogeorgiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:17:43 by teogeorgiev       #+#    #+#             */
/*   Updated: 2023/12/03 20:57:01 by teogeorgiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t    no_newline(char *buf)
{
    int i;

    i = 0;
    
    if (buf == NULL)
        return (0);
    while (buf[i])
    {
        if (buf[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

size_t  get_len(char *s)
{
    size_t len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

char    *text_join(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *temp;

    i = 0;
    if (!s1 || !s2)
        return (NULL);
    if (!(temp = malloc((get_len(s1) + get_len(s2) + 1) * sizeof(char))))
        return (NULL);
    while (s1[i])
    {
        temp[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
        temp[i++] = s2[j++];
    temp[i] = '\0';
    return (temp);
}

char *str_cpy(char *source, char *line, int len)
{
    int i;

    i = 0;
    while (source[i] && i < len)
    {
        if (source[i] == '\n')
        {
            i++;
            break ;
        }
        line[i] = source[i];
        i++;
    }
    if (source[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}
