/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:21:59 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/29 15:42:37 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#include <stdio.h> // <<<< REMOVE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct  s_list 
{
    char            *content;
    struct s_list   *next;
}   t_list;

/* GET_NEW_LINE utility functions */
size_t  fn_len_to_newline(t_list *read_list);
char    *fn_strdup(char *s1);
t_list  *fn_find_lastnode(t_list *read_text);
void    fn_add_node(char *buf, t_list **read_text);
size_t  fn_has_newline(t_list *read_text);

/* GET_NEW_LIME control functions */
char    *get_next_line(int fd);

#endif