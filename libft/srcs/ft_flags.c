/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:50:17 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 11:53:44 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_setflag(int *flags, int flag)
{
	*flags |= flag;
}

int	ft_checkflag(int flags, int flag)
{
	return ((flags & flag) > 0);
}

void	ft_resetflag(int *flags, int flag)
{
	*flags &= ~flag;
}

void	ft_toggleflag(int *flags, int flag)
{
	*flags ^= flag;
}
