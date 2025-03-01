/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:30:00 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 15:30:00 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// t_status	ft_print_error_w_arg(char *error_msg, char *arg)
// {
	// ft_printf(STDERR_FILENO, error_msg, arg);
	// g_exit_status = EXIT_FAILURE;
	// return (ERROR);
// }

static int ft_snprintf(char *buffer, size_t size, char *format, char *arg);

t_status ft_print_error_w_arg(char *error_msg, char *arg)
{
	char buffer[256];
	int len;

	len = ft_snprintf(buffer, sizeof(buffer), error_msg, arg);
	write(STDERR_FILENO, buffer, len);
	g_exit_status = EXIT_FAILURE;
	return (ERROR);
}

static int ft_snprintf(char *buffer, size_t size, char *format, char *arg)
{
	char *dst;
	dst = buffer;

	while (*format && size > 1)
	{
		if (format[0] == '%' && format[1] == 's')
		{
			while (*arg && size > 1)
			{
				*dst++ = *arg++;
				size--;
			}
			format += 2;
		}
		else
		{
			*dst++ = *format++;
			size--;
		}
	}
	if (size > 0)
		*dst = '\0';
	return (dst - buffer);
}
