/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:04:30 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/07 16:10:19 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_snprintf(char *buffer, size_t size, char *format, char *arg);

t_status	ft_print_error_w_arg(char *error_msg, char *arg, int status)
{
	char	buffer[256];
	int		len;

	len = ft_snprintf (buffer, sizeof(buffer), error_msg, arg);
	write(STDERR_FILENO, buffer, len);
	g_exit_status = status;
	return (ERROR);
}

static int	ft_snprintf(char *buffer, size_t size, char *format, char *arg)
{
	char	*dst;

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
