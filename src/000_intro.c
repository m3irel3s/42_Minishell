/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_intro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:37:43 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/21 13:50:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_display_infos(void);
static void	ft_print_banner_line(char *banner[]);

/**
 * @brief Display the startup banner and information in the terminal.
 */
void	ft_display_startup_banner(void)
{
	char	*banner[17];

	banner[0] = BBLU " /******************************************/ " RESET;
	banner[1] = BMAG " /                                          / " RESET;
	banner[2] = BGRN " /       ███╗   ███╗██╗███╗   ██╗██╗        / " RESET;
	banner[3] = HYEL " /       ████╗ ████║██║████╗  ██║██║        / " RESET;
	banner[4] = HCYN " /       ██╔████╔██║██║██╔██╗ ██║██║        / " RESET;
	banner[5] = HRED " /       ██║╚██╔╝██║██║██║╚██╗██║██║        / " RESET;
	banner[6] = HMAG " /       ██║ ╚═╝ ██║██║██║ ╚████║██║        / " RESET;
	banner[7] = BYEL " /                                          / " RESET;
	banner[8] = HMAG " /   ███████╗██╗  ██╗███████╗██╗    ██╗     / " RESET;
	banner[9] = HRED " /   ██╔════╝██║  ██║██╔════╝██║    ██║     / " RESET;
	banner[10] = HCYN " /   ███████╗███████║█████╗  ██║    ██║     / " RESET;
	banner[11] = HYEL " /   ╚════██║██╔══██║██╔══╝  ██║    ██║     / " RESET;
	banner[12] = BGRN " /   ███████║██║  ██║███████╗██████╗██████╗ / " RESET;
	banner[13] = BMAG " /   ╚══════╝╚═╝  ╚═╝╚══════╝╚═════╝╚═════╝ / " RESET;
	banner[14] = HYEL " /                                          / " RESET;
	banner[15] = BBLU " /******************************************/ " RESET;
	banner[16] = NULL;
	ft_print_banner_line(banner);
	ft_printf(1, "\n\n%s[ Welcome to Minishell! ]%s\n", BGRN, RESET);
	ft_printf(1, "%sA minimalistic shell implementation for 42 School.%s\n\n",
		HYEL, RESET);
	ft_display_infos();
}

/**
 * @brief Helper function to print each line of the banner.
 */
static void	ft_print_banner_line(char *banner[])
{
	int	i;

	i = 0;
	while (banner[i] != NULL)
	{
		ft_printf(1, "%s\n", banner[i]);
		i++;
	}
}

/**
 * @brief Displays information about the Minishell implementation.
 *
 * This function displays a banner with information about the
 * Minishell implementation, including features and examples.
 *
 * @return void
 */
static void	ft_display_infos(void)
{
	ft_printf(1, "\n%s+-----------------------------+%s\n", BYEL, RESET);
	ft_printf(1, "%s|        MINISHELL INFO       |%s\n", BMAG, RESET);
	ft_printf(1, "%s+-----------------------------+%s\n\n", BYEL, RESET);
	ft_printf(1, "%sFeatures:%s\n", BBLU, RESET);
	ft_printf(1, " %s- Basic commands:%s ls, cd, echo, pwd, etc.\n",
		HGRN, RESET);
	ft_printf(1, " - %sEnvironment variables:%s export, unset, env.\n",
		HGRN, RESET);
	ft_printf(1, " - %sRedirections:%s <, >, >>.\n", HGRN, RESET);
	ft_printf(1, " - %sPipes:%s |.\n\n", HGRN, RESET);
	ft_printf(1, "%sExamples:%s\n", BBLU, RESET);
	ft_printf(1, " %s- echo $HOME%s\n", HYEL, RESET);
	ft_printf(1, " - %scat < file.txt > output.txt%s\n", HYEL, RESET);
	ft_printf(1, " - %sls -l | grep .c%s\n\n", HYEL, RESET);
	ft_printf(1, "%sType 'authors' for credits.%s\n", HCYN, RESET);
	ft_printf(1, "%sType 'exit' or press Ctrl+D to quit.%s\n\n", HCYN, RESET);
}

/**
 * @brief Prints the authors of the program.
 */
int	ft_authors(void)
{
	char	*authors[14];
	int			i;

	authors[0] = BYEL "\n+-------------------------------------------+" RESET;
	authors[1] = BMAG "|                AUTHORS                    |" RESET;
	authors[2] = BYEL "+-------------------------------------------+" RESET;
	authors[3] = BGRN "| Minishell - 42 School Project             |" RESET;
	authors[4] = BYEL "|                                           |" RESET;
	authors[5] = HCYN "| Created by:                               |" RESET;
	authors[6] = BMAG "| > Miguel Meireles                         |" RESET;
	authors[7] = HRED "| <jmeirele@student.42porto.com>            |" RESET;
	authors[8] = BMAG "| > Melanie Reis                            |" RESET;
	authors[9] = HRED "| <meferraz@student.42porto.com>            |" RESET;
	authors[10] = BYEL "|                                           |" RESET;
	authors[11] = HYEL "| February 2025                             |" RESET;
	authors[12] = BYEL "+-------------------------------------------+\n" RESET;
	authors[13] = NULL;
	i = 0;
	while (authors[i] != NULL)
	{
		ft_printf(1, "%s\n", authors[i]);
		i++;
	}
	return (0);
}
