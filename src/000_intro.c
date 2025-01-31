/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_intro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:37:43 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/31 08:55:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_infos(void);

/**
 * @brief Display the startup banner in the terminal.
 * 
 * This function displays the startup banner in the terminal, which includes
 * the name of the program, the version number, and the copyright information.
 */
void	ft_display_startup_banner(void)
{
	ft_putstr_fd("\n\
/* ************************************************************************** */\n\
/*                                                                            */\n\
/*   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗           */\n\
/*   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║           */\n\
/*   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║           */\n\
/*   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║           */\n\
/*   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗      */\n\
/*   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝      */\n\
/*                                                                            */\n\
/* ************************************************************************** */\n\
\n", 1);
	ft_infos();
}

/**
 * @brief Prints the welcome message to the user.
 * 
 * This function prints the welcome message to the user, which includes a brief
 * description of the program, the supported features, and some examples of how
 * to use it.
 */
static int	ft_infos(void)
{
	ft_putstr_fd("\n\
/* ************************************************************************** */\n\
/*                                                                            */\n\
/*   Welcome to Minishell!                                                    */\n\
/*   A minimalistic shell implementation for 42 School.                       */\n\
/*                                                                            */\n\
/*   Supported features:                                                      */\n\
/*    > Basic commands: ls, cd, echo, pwd, etc.                               */\n\
/*    > Environment variables: export, unset, env                             */\n\
/*    > Redirections: <, >, >>                                                */\n\
/*    > Pipes: |                                                              */\n\
/*                                                                            */\n\
/*   Try these examples:                                                      */\n\
/*    > ls -l | grep .c                                                       */\n\
/*    > echo $HOME                                                            */\n\
/*    > cat < file.txt > output.txt                                           */\n\
/*                                                                            */\n\
/*   Type 'authors' for credits.                                              */\n\
/*   Type 'exit' or press Ctrl+D to quit.                                     */\n\
/*                                                                            */\n\
/* ************************************************************************** */\n\
\n", 1);
	return (0);
}

/**
 * @brief Prints the authors of the program.
 * 
 * This function prints the authors of the program in a nice format.
 */
int	ft_authors(void)
{
	ft_putstr_fd("\n\
/* ************************************************************************** */\n\
/*                                                                            */\n\
/*   Minishell - 42 School Project                                            */\n\
/*   Created by:                                                              */\n\
/*   > Miguel Meirele <jmeirele@student.42porto.com>                          */\n\
/*   > Melanie Reis <meferraz@student.42porto.com>                            */\n\
/*                                                                            */\n\
/*   Fevereiro 2025                                                           */\n\
/*                                                                            */\n\
/* ************************************************************************** */\n\
\n", 1);
	return (0);
}
