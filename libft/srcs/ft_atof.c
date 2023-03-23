/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:02:38 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 16:29:48 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	inv_pow10(double nb, int pow10)
{
	while (pow10 > 0)
	{
		nb /= 10;
		pow10--;
	}
	return (nb);
}

static void	skip_spaces(const char **nptr)
{
	while (ft_isspace(**nptr))
		(*nptr)++;
}

/// @brief Converts an alphabetic string to a double.
/// @param nptr 
/// @return Returns the double version of number contained by nptr.
/// This function is not able to handle overflow.
double	ft_atof(const char *nptr)
{
	double	nb;
	int		neg;
	int		nb_dec;

	nb = 0;
	nb_dec = 0;
	skip_spaces(&nptr);
	neg = 1 - (2 * (*nptr == '-'));
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr && (ft_isdigit(*nptr) || *nptr == '.'))
	{
		if (nb_dec > 0)
			nb_dec++;
		if (*nptr == '.')
		{
			if (nb_dec > 0)
				break ;
			if (!*++nptr)
				return (0);
			nb_dec++;
		}
		nb = nb * 10 + (*(nptr++) - '0') * neg;
	}
	return (inv_pow10(nb, nb_dec));
}

// int	main(void)
// {
// 	printf("%f\n\n", ft_atof("123.456"));
// 	printf("%f\n\n", ft_atof("0"));
// 	printf("%f\n\n", ft_atof("1."));
// 	printf("%f\n\n", ft_atof("-1"));
// 	printf("%f\n\n", ft_atof("-123.456"));
// 	printf("%f\n\n", ft_atof("-123.4567891234"));
// 	printf("%f\n\n", ft_atof("-123456789.1234"));
// 	return (0);
// }
