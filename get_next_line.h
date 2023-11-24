/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:21:59 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/22 16:55:40 by tgeorgie         ###   ########.fr       */
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

/* GET_NEW_LIME control functions */
char    *get_next_line(int fd);

/* GET_NEW_LINE utility functions */
size_t  f_strlen(char *s);
size_t  f_search_nl(char *buf);
void	*f_memmove(void *dst, const void *src, size_t len);
char    *f_strjoin(char *s1, char *s2);
#endif