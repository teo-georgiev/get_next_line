/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   STR_get_next_line.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teogeorgiev <teogeorgiev@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:27:39 by teogeorgiev       #+#    #+#             */
/*   Updated: 2023/11/30 17:14:18 by teogeorgiev      ###   ########.fr       */
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
char    *text_join(char *s1, char *s2);
size_t  get_len(char *s);
size_t  has_newline(char *buf);
#endif