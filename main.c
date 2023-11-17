/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorgie <tgeorgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:32:41 by tgeorgie          #+#    #+#             */
/*   Updated: 2023/11/17 10:04:05 by tgeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char **argv)
{
    int fd;
    char str[1024];

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        close(fd);
        return (NULL);
    }
    return (0);
}