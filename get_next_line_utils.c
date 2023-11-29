/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:25:44 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/29 16:03:19 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  fn_has_newline(t_list *read_list)
{
    size_t  i;
    size_t  len;

    len = 0;
    if (!read_list)
        return (0);
    while (read_list)
    {
        i = 0;
        while (read_list->content[i] && i < BUFFER_SIZE)
        {
            if (read_list->content[i] == '\n')
                return (len + i);
            i++;
        }
        len += i;
        read_list = read_list->next;
    }
    return (0);
}

char *fn_strdup(char *source)
{
	size_t		i;
	size_t		len;
	char		*result;

	len = 0;
    if (!source)
        return (NULL);
    while (source[len])
        len++;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
    {
        free(result);
        return (NULL);
    }
	i = -1;
	while (source[++i] && i < len)
        result[i] = source[i];
    result[i] = '\0';
	return (result);
}

t_list   *fn_find_lastnode(t_list *read_list)
{
    t_list  *last_node;

    last_node = read_list;
    if (!read_list)
        return (NULL);
    while (last_node->next)
        last_node = last_node->next;
    return (last_node);
}

void  fn_add_node(char *buf, t_list **read_list)
{
    t_list  *new_node;
    t_list  *last_node;

    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return ;
    last_node = fn_find_lastnode(*read_list);
    if (last_node == NULL)
        *read_list = new_node;
    else
        last_node->next = new_node;
    new_node->content = fn_strdup(buf);
    new_node->next = NULL;
}
