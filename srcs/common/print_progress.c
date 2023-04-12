/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_progress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:38:54 by ple-stra          #+#    #+#             */
/*   Updated: 2023/04/12 17:52:42 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_progress(int progress, int total)
{
	static int	last_print_len = 0;
	char		*cariage_back;

	if (last_print_len > 0)
	{
		cariage_back = malloc(sizeof(char) * (last_print_len + 1));
		if (!cariage_back)
			return ;
		ft_memset(cariage_back, '\b', last_print_len);
		cariage_back[last_print_len] = '\0';
		write(1, cariage_back, last_print_len);
		free(cariage_back);
	}
	last_print_len = ft_printf("%.2d%%", (int)(progress * 100 / total));
	if (progress != total)
		return ;
	write(1, "\n", 1);
	last_print_len = 0;
}
