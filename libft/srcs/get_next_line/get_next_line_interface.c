/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:18:14 by ple-stra          #+#    #+#             */
/*   Updated: 2022/12/07 20:26:50 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	return (get_next_line_interface(fd, 0));
}

void	clean_gnl_for_fd(int fd)
{
	get_next_line_interface(fd, 1);
}
