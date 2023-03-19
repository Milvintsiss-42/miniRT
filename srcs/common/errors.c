/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:56:35 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/19 14:32:17 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

// prints error for the program
// ex: bin_name: error_str
int	ft_perror(t_mrt mrt, const char *error_str)
{
	ft_printf_fd(2, "%s: %s\n", mrt.bin_name, error_str);
	return (1);
}

// prints error for the context
// ex: bin_name: context: error_str
int	ft_ctxtperror(t_mrt mrt, const char *context, const char *error_str)
{
	ft_printf_fd(2, "%s: %s: %s\n", mrt.bin_name, context, error_str);
	return (1);
}

// prints error for the program using errno
// ex: bin_name: error_str
int	ft_perror_errno(t_mrt mrt)
{
	if (errno == 0)
		return (ft_perror(mrt, ERR_UNKNOWN));
	perror(mrt.bin_name);
	return (errno);
}

// prints error for the context using errno
// ex: bin_name: context: error_str
int	ft_ctxtperror_errno(t_mrt mrt, const char *context)
{
	if (errno == 0)
		return (ft_ctxtperror(mrt, context, ERR_UNKNOWN));
	ft_printf_fd(2, "%s: %s: %s\n",
		mrt.bin_name, context, strerror(errno));
	return (errno);
}
