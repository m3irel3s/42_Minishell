/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_intro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:37:43 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/31 11:05:18 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_display_infos(void);
static void	ft_print_banner_line(const char *banner[]);

/**
 * @brief Display the startup banner and information in the terminal.
 */
void	ft_display_startup_banner(void)
{
	const char	*banner[18];

	banner[0] = BBLU " /*************************************/ " RESET;
	banner[1] = BMAG " /                                     / " RESET;
	banner[2] = BGRN " /    ███╗   ███╗██╗███╗   ██╗██╗      / " RESET;
	banner[3] = HYEL " /    ████╗ ████║██║████╗  ██║██║      / " RESET;
	banner[4] = HCYN " /    ██╔████╔██║██║██╔██╗ ██║██║      / " RESET;
	banner[5] = HRED " /    ██║╚██╔╝██║██║██║╚██╗██║██║      / " RESET;
	banner[6] = HMAG " /    ██║ ╚═╝ ██║██║██║ ╚████║██║      / " RESET;
	banner[7] = BYEL " /                                     / " RESET;
	banner[8] = HMAG " /   ███████╗██   ██╗ ██████╗ ██╗██╗   / " RESET;
	banner[9] = HRED " /   ███╔═══╝██╔══██╗ ██╔══██╗██║██║   / " RESET;
	banner[10] = HCYN " /   ███████╗███████║ ██████╔╝██║██║   / " RESET;
	banner[11] = HYEL " /   ╚════██║██╔══██║ ██╔═══╝ ██║██║   / " RESET;
	banner[12] = BGRN " /   ███████╗██   ██║ ███████╗██║██║   / " RESET;
	banner[13] = BMAG " /   ╚══════╝╚══════╝ ╚══════╝╚═╝╚═╝   / " RESET;
	banner[14] = HYEL " /                                     / " RESET;
	banner[15] = HCYN " /       Welcome to MINISHELL!         / " RESET;
	banner[16] = BBLU " /*************************************/ " RESET;
	banner[17] = NULL;
	ft_print_banner_line(banner);
	ft_display_infos();
}

/**
 * @brief Helper function to print each line of the banner.
 */
static void	ft_print_banner_line(const char *banner[])
{
	int	i;

	i = 0;
	while (banner[i] != NULL)
	{
		ft_printf("%s\n", banner[i]);
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
	ft_printf("\n%s+-----------------------------+%s\n", BYEL, RESET);
	ft_printf("%s|        MINISHELL INFO       |%s\n", BMAG, RESET);
	ft_printf("%s+-----------------------------+%s\n", BYEL, RESET);
	ft_printf("\n%s[ Welcome to Minishell! ]%s\n", BGRN, RESET);
	ft_printf("%sA minimalistic shell implementation for 42 School.%s\n\n",
		HYEL, RESET);
	ft_printf("%sFeatures:%s\n", BBLU, RESET);
	ft_printf(" - %sBasic commands:%s ls, cd, echo, pwd, etc.\n", HGRN, RESET);
	ft_printf(" - %sEnvironment variables:%s export, unset, env.\n",
		HGRN, RESET);
	ft_printf(" - %sRedirections:%s <, >, >>.\n", HGRN, RESET);
	ft_printf(" - %sPipes:%s |.\n\n", HGRN, RESET);
	ft_printf("%sExamples:%s\n", BBLU, RESET);
	ft_printf(" - %secho $HOME%s\n", HYEL, RESET);
	ft_printf(" - %scat < file.txt > output.txt%s\n", HYEL, RESET);
	ft_printf(" - %sls -l | grep .c%s\n\n", HYEL, RESET);
	ft_printf("%sType 'authors' for credits.%s\n", HCYN, RESET);
	ft_printf("%sType 'exit' or press Ctrl+D to quit.%s\n", HCYN, RESET);
}

/**
 * @brief Prints the authors of the program.
 */
int	ft_authors(void)
{
	const char	*authors[10];
	int			i;

	authors[0] = BYEL "\n+-------------------------------------------+" RESET;
	authors[1] = BMAG "|                AUTHORS                    |" RESET;
	authors[2] = BYEL "+-------------------------------------------+" RESET;
	authors[3] = BGRN "| Minishell - 42 School Project             |" RESET;
	authors[4] = HCYN "| Created by:                               |" RESET;
	authors[5] = HRED "| > Miguel Meirele <jmeirele@student.42porto.com> |"
		RESET;
	authors[6] = HRED "| > Melanie Reis <meferraz@student.42porto.com> |" RESET;
	authors[7] = HYEL "| February 2025                             |" RESET;
	authors[8] = BYEL "+-------------------------------------------+\n" RESET;
	authors[9] = NULL;
	i = 0;
	while (authors[i] != NULL)
	{
		ft_printf("%s\n", authors[i]);
		i++;
	}
	return (0);
}
