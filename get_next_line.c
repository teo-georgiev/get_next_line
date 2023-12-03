/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teogeorgiev <teogeorgiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:17:18 by teogeorgiev       #+#    #+#             */
/*   Updated: 2023/12/03 20:58:02 by teogeorgiev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_text(char **source)
{
	char	*rem;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*source)[i] && (*source)[i] != '\n')
	    i++;
	if (!(*source)[i])
	{
		free((*source));
        (*source) = NULL;
		return (NULL);
	}
    if (!(rem = (char *)malloc((get_len((*source)) - i + 1) * sizeof(char))))
    {
        free((*source));
        (*source) = NULL;
        return (NULL);
    }    
	i++;
	while ((*source)[i])
		rem[j++] = (*source)[i++];
	rem[j] = '\0';
	free((*source));
    *source = NULL;
	return (rem);
}

static char	*get_line(char *source)
{
    char    *line;
    int     len;

    len = 0;
    if (!source[0])
        return (NULL);
    while (source[len] && source[len] != '\n')
        len++;
    if (source[len] != '\n')
        return (NULL);
    line = (char *)malloc((len + 2) * sizeof(char));
    if (!line)
        return (NULL);
    line = str_cpy(source, line, len);
    return (line);
}

static char *subst_temp(char *source, char *buffer)
{
    char    *temp;
    
    temp = source;
    source = text_join(source, buffer);
    free(temp);
    temp = NULL;
    return (source);
}

static char *read_text(int fd, char *source)
{
    int     char_read;
    char    *buffer;

    char_read = 1;
    if (source == NULL)
    {
        source = (char *)malloc(1);
        if (!source)
            return (NULL);
        *source = '\0';
    }
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (buffer == NULL)
    {
        free (source);
        return (NULL);
    }
    while (char_read > 0)
    {
        char_read = read(fd, buffer, BUFFER_SIZE);
        if (char_read == -1)
        {
            free (buffer);
            free(source);
            return (NULL);
        }
        buffer[char_read] = '\0';
        source = subst_temp(source, buffer);
        if (no_newline(source))
            break ;
    }
    free(buffer);
    return (source);
}

char    *get_next_line(int fd)
{
    static char *source = NULL;
    char        *new_line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    source = read_text(fd, source);
    if (source == NULL)
        return (NULL);
    new_line = get_line(source);    
    if (new_line == NULL && get_len(source) > 0)
        new_line = text_join("", source);
    source = clean_text(&source);
    return (new_line);
}
