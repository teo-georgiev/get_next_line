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

void    fn_dealloc_list(t_list *remain_node, t_list **read_list)
{
    t_list  *temp;
    t_list  *current;

    if (!remain_node || !read_list || !*read_list)
        return ;
    current = *read_list;
    while (current)
    {
        temp = current;
        current = current->next;
        free(temp->content);
        free(temp);
    }
    *read_list = remain_node;
}

void fn_clean_list(t_list **read_list)
{
    size_t  i;
    char    *remain_str;
    t_list  *last_node;
    t_list  *remain_node;

    i = 0;
    last_node = fn_find_lastnode(*read_list);
    while (last_node->content[i] && last_node->content[i] != '\n')
        i++;
    remain_str = fn_strdup(&(last_node->content[++i]));
    remain_node = malloc(sizeof(t_list));
    if (!remain_node || !remain_str)
        return ;
    remain_node->content = remain_str;
    remain_node->next = NULL;
    fn_dealloc_list(remain_node, read_list);
}

char    *fn_get_line(t_list *read_list)
{
    char    *new_line;
    size_t  i;
    size_t  j;
    size_t  len;
    
    if (!read_list)
        return (NULL);
    j = 0;
    len = fn_has_newline(read_list);
    new_line = (char *)malloc((len + 1) * sizeof(char));
    if (!new_line)
        return (NULL);
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

    nbr_read = 0;
    while (!fn_has_newline(*read_list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (!buf)
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
    static t_list   *read_list;
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


// void fn_clean_list(t_list **read_list)
// {
//     size_t  i;
//     size_t  j;
//     char    *remain_str;
//     t_list  *last_node;
//     t_list  *remain_node;

//     i = 0;
//     j = 0;
//     remain_node = (t_list *)malloc(sizeof(t_list));
//     remain_str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
//     if (!remain_node || !remain_str)
//         return ;
//     last_node = fn_find_lastnode(*read_list);
//     while (last_node->content[i] && last_node->content[i] != '\n')
//         i++;
//     while (last_node->content[i] && last_node->content[++i])
//         remain_str[j++] = last_node->content[i];
//     remain_str[j] = '\0';
//     remain_node->content = remain_str;
//     remain_node->next = NULL;
//     fn_dealloc_list(remain_node, read_list);
// }