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

size_t  fn_has_newline(t_list *scan_list)
{
    size_t  i;

    if (!scan_list)
        return (0);
    while (scan_list)
    {
        i = 0;
        while (scan_list->content[i] && i < BUFFER_SIZE)
        {
            if (scan_list->content[i] == '\n')
                return (1);
            i++;
        }
        scan_list = scan_list->next;
    }
    return (0);
}

size_t  fn_len_newline(t_list *scan_list)
{
    size_t  i;
    size_t  len;

    len = 0;
    if (!scan_list)
        return (0);
    while (scan_list)
    {
        i = 0;
        while (scan_list->content[i] && i < BUFFER_SIZE)
        {
            if (scan_list->content[i] == '\n')
                return (len + i);
            i++;
        }
        len += i;
        scan_list = scan_list->next;
    }
    return (len);
}

t_list   *fn_find_lastnode(t_list *scan_list)
{
    t_list  *last_node;

    last_node = scan_list;
    if (!scan_list)
        return (NULL);
    while (last_node->next)
        last_node = last_node->next;
    return (last_node);
}

void  fn_add_node(char *buf, t_list **scan_list)
{
    t_list  *new_node;
    t_list  *last_node;

    last_node = fn_find_lastnode(*scan_list);
    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return ;
    if (!last_node)
        *scan_list = new_node;
    else
        last_node->next = new_node;
    new_node->content = buf;
    new_node->next = NULL;
}
