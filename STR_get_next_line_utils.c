/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   STR_get_next_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teogeorgiev <teogeorgiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:17:43 by teogeorgiev       #+#    #+#             */
/*   Updated: 2023/11/30 17:43:00 by teogeorgiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "STR_get_next_line.h"

size_t    has_newline(char *buf)
{
    int i;

    i = -1;
    
    if (buf == NULL)
        return (0);        
    while (buf[++i])
    {
        if (buf[i] == '\n')
            return (1);
    }
    return (0);
}

size_t  get_len(char *s)
{
    int len;

    len = 0;
    if (!s)
        return (0);
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
    temp = (char *)malloc((get_len(s1) + get_len(s2) + 1) * sizeof(char));
    if (!s1 || !s2 || !temp)
        return (NULL);
    while (s1[i])
    {
        temp[i] = s1[i];
        i++;
    }
    j = -1;
    while (s2[++j])
        temp[i + j] = s2[j];
    temp[get_len(s1) + get_len(s2)] = '\0';
    free(s2);
    return (temp);
}