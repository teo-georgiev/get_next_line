/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:25:44 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/22 16:54:32 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  f_strlen(char *s)
{
    int len;

    len = 0;
    if (!s)
        return (0);
    while (s[len])
        len++;
    return (len);
}

void	*f_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;

	i = 0;
	if (dst > src)
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	else if (dst < src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char    *f_strjoin(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *new_s;

    i = -1;
    j = -1;
    new_s = (char *)malloc((f_strlen(s1) + f_strlen(s2) + 1) * sizeof(char));
    if (!s1)
        return (new_s = s2);
    while (s1[++i])
        new_s[i] = s1[i];
    while (s2[++j])
    {
        new_s[i + j] = s2[j];
        if (s2[j] == '\n')
            break ;
    }
    new_s[i + j + 1] = '\0';
    return (new_s);
}

size_t     f_search_nl(char *buf)
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