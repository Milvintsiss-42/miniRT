/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:56:35 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/18 21:38:49 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

// prints error for the program
int	ft_perror(t_mrt mrt, const char *error_str)
{
	ft_printf_fd(2, "%s: %s\n", mrt.bin_name, error_str);
	return (1);
}

// prints error for the file
int	ft_fperror(t_mrt mrt, const char *filename, const char *error_str)
{
	ft_printf_fd(2, "%s: %s: %s\n", mrt.bin_name, filename, error_str);
	return (1);
}

// prints error for the program
int	ft_perror_errno(t_mrt mrt)
{
	if (errno == 0)
		return (ft_perror(mrt, ERR_UNKNOWN));
	perror(mrt.bin_name);
	return (errno);
}

// prints error for the file
int	ft_fperror_errno(t_mrt mrt, const char *filename)
{
	if (errno == 0)
		return (ft_fperror(mrt, filename, ERR_UNKNOWN));
	ft_printf_fd(2, "%s: %s: %s\n",
		mrt.bin_name, filename, strerror(errno));
	return (errno);
}
