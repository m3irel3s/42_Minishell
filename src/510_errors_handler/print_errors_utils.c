/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:04:30 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 15:38:43 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_snprintf(char *buffer, size_t size, char *format, char *arg);

/**
 * @brief Prints an error message with an argument to the standard error stream
 * and sets the shell's exit status.
 *
 * This function formats an error message by inserting the provided argument
 * into the error message template and then writes the formatted message to
 * the standard error stream. It also updates the shell's exit status with
 * the provided status value.
 *
 * @param error_msg The error message template containing a placeholder for
 * the argument.
 * @param arg The argument to insert into the error message template.
 * @param status The exit status to set in the shell.
 *
 * @return Always returns ERROR, indicating that an error occurred.
 */
t_status	ft_print_error_w_arg(char *error_msg, char *arg, int status)
{
	char	buffer[256];
	int		len;

	len = ft_snprintf (buffer, sizeof(buffer), error_msg, arg);
	write(STDERR_FILENO, buffer, len);
	g_exit_status = status;
	return (ERROR);
}

/**
 * @brief Formats a string by replacing the first occurrence of "%s" in the
 * format string with the provided argument, and writes the result to the buffer.
 *
 * The function mimics the behavior of snprintf, writing at most `size` - 1
 * characters to `buffer`, ensuring it is null-terminated. The replacement
 * occurs only for the first "%s" found in the format string.
 *
 * @param buffer The destination buffer to write the formatted string.
 * @param size The maximum number of characters to write to the buffer,
 * including the null terminator.
 * @param format The format string containing the "%s" placeholder.
 * @param arg The string argument to replace the "%s" placeholder.
 *
 * @return The number of characters written to the buffer, excluding the
 * null terminator.
 */
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
