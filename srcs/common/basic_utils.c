/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:42:10 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/19 20:45:26 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_basename(const char *path)
{
	const char	*last_separator;

	last_separator = 0;
	if (!path || !*path)
		return (0);
	if (ft_strncmp(path, "/", 2) == 0)
		return ("/");
	while (*path)
	{
		if (*path == '/' && *(path + 1) != '\0')
			last_separator = path;
		path++;
	}
	if (!last_separator)
		return (path);
	return (++last_separator);
}
