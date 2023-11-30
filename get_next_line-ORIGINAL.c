/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:20:36 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/29 16:11:43 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    fn_dealloc_list(t_list *rem_node, t_list **read_list, char *buf_rem)
{
    t_list  *temp;

    // if (!rem_node || !read_list || !*read_list)
    //     return ;
    if (*read_list == NULL)
        return ;
    while (*read_list)
    {
        temp = (*read_list)->next;
        free((*read_list)->content);
        free(*read_list);
        *read_list = temp;
    }
    *read_list = NULL;
    if (rem_node->content[0])
        *read_list = rem_node;
    else 
    {
        free(buf_rem);
        free(rem_node);
    }
}

void fn_clean_list(t_list **read_list)
{
    size_t  i;
    size_t  j;
    char    *buf_rem;
    t_list  *last_node;
    t_list  *rem_node;

    i = 0;
    j = 0;
    buf_rem = (char *)malloc(BUFFER_SIZE + 1);
    rem_node = (t_list *)malloc(sizeof(t_list));
    if (buf_rem == NULL || rem_node == NULL)
        return ;
    last_node = fn_find_lastnode(*read_list);
    while (last_node->content[i] && last_node->content[i] != '\n')
        ++i;
    while (last_node->content[i] && last_node->content[++i])
        buf_rem[j++] = last_node->content[i];
    buf_rem[j] = '\0';
    rem_node->content = buf_rem;
    rem_node->next = NULL;
    fn_dealloc_list(rem_node, read_list, buf_rem);
}

char    *fn_get_line(t_list *read_list)
{
    char    *new_line;
    size_t  i;
    size_t  j;
    size_t  len;
    
    if (!read_list)
        return (NULL);
    len = fn_len_newline(read_list);
    new_line = (char *)malloc((len + 1) * sizeof(char));
    if (!new_line)
        return (NULL);
    j = 0;
    while (read_list)
    {
        i = 0;
        while (read_list->content[i])
        {
            if (read_list->content[i] == '\n')
            {
                new_line[j++] = '\n';
                new_line[j] = '\0';
                return (new_line);
            }
            new_line[j++] = read_list->content[i++];
        }
        read_list = read_list->next;
    }
    new_line[j] = '\0';
    return (new_line);
}

t_list   *fn_read_list(int fd, t_list **read_list)
{
    char    *buf;
    int     nbr_read;

    // nbr_read = 0;
    while (!fn_has_newline(*read_list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return (NULL);
        nbr_read = read(fd, buf, BUFFER_SIZE);
        if (!nbr_read)
        {
            free(buf);
            return (NULL);
        }
        buf[nbr_read] = '\0';
        fn_add_node(buf, read_list);
    }
    return (*read_list);
}

char    *get_next_line(int fd)
{
    static t_list   *read_list = NULL;
    char            *new_line;

    if (fd < 0 || read(fd, &new_line, 0) < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    read_list = fn_read_list(fd, &read_list);
    if (!read_list)
        return (NULL);
    new_line = fn_get_line(read_list);
    fn_clean_list(&read_list);
    return (new_line);
}
