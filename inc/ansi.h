/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:47:17 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/05 11:05:16 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSI_H
# define ANSI_H
/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 *
 * Source: https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
 *
 * this version has been adapted to be used in the project
 */

// ANSI Escape codes
//Regular text
# define BLK "\001\033[0;30m\002"	// RGB(0, 0, 0)
# define RED "\001\033[0;31m\002"	// RGB(255, 0, 0)
# define GRN "\001\033[0;32m\002"	// RGB(0, 255, 0)
# define YEL "\001\033[0;33m\002"	// RGB(255, 255, 0)
# define BLU "\001\033[0;34m\002"	// RGB(0, 0, 255)
# define MAG "\001\033[0;35m\002"	// RGB(255, 0, 255)
# define CYN "\001\033[0;36m\002"	// RGB(0, 255, 255)
# define WHT "\001\033[0;37m\002"	// RGB(255, 255, 255)

//Especial case for the project
#define BG_G "\001\033[102m\002"
#define BG_B "\001\033[104m\002"
#define BG_C "\001\033[106m\002"
#define BG_M "\001\033[105m\002"
#define MGT  "\001\033[91m\002"
#define YLW  "\001\033[93m\002"
#define RED2  "\001\033[91m\002"
#define GRN2  "\001\033[92m\002"
#define WHT2 "\001\033[37m\002"
#define RS   "\001\033[0m\002"

//Regular bold text
# define BBLK "\001\033[1;30m\002"
# define BRED "\001\033[1;31m\002"
# define BGRN "\001\033[1;32m\002"
# define BYEL "\001\033[1;33m\002"
# define BBLU "\001\033[1;34m\002"
# define BMAG "\001\033[1;35m\002"
# define BCYN "\001\033[1;36m\002"
# define BWHT "\001\033[1;37m\002"

//Regular underline text
# define UBLK "\001\033[4;30m\002"
# define URED "\001\033[4;31m\002"
# define UGRN "\001\033[4;32m\002"
# define UYEL "\001\033[4;33m\002"
# define UBLU "\001\033[4;34m\002"
# define UMAG "\001\033[4;35m\002"
# define UCYN "\001\033[4;36m\002"
# define UWHT "\001\033[4;37m\002"

//Regular background
# define BLKB "\001\033[40m\002"
# define REDB "\001\033[41m\002"
# define GRNB "\001\033[42m\002"
# define YELB "\001\033[43m\002"
# define BLUB "\001\033[44m\002"
# define MAGB "\001\033[45m\002"
# define CYNB "\001\033[46m\002"
# define WHTB "\001\033[47m\002"

//High intensty background
# define BLKHB "\001\033[0;100m\002"
# define REDHB "\001\033[0;101m\002"
# define GRNHB "\001\033[0;102m\002"
# define YELHB "\001\033[0;103m\002"
# define BLUHB "\001\033[0;104m\002"
# define MAGHB "\001\033[0;105m\002"
# define CYNHB "\001\033[0;106m\002"
# define WHTHB "\001\033[0;107m\002"

//High intensty text
# define HBLK "\001\033[0;90m\002"
# define HRED "\001\033[0;91m\002"
# define HGRN "\001\033[0;92m\002"
# define HYEL "\001\033[0;93m\002"
# define HBLU "\001\033[0;94m\002"
# define HMAG "\001\033[0;95m\002"
# define HCYN "\001\033[0;96m\002"
# define HWHT "\001\033[0;97m\002"

//Bold high intensity text
# define BHBLK "\001\033[1;90m\002"
# define BHRED "\001\033[1;91m\002"
# define BHGRN "\001\033[1;92m\002"
# define BHYEL "\001\033[1;93m\002"
# define BHBLU "\001\033[1;94m\002"
# define BHMAG "\001\033[1;95m\002"
# define BHCYN "\001\033[1;96m\002"
# define BHWHT "\001\033[1;97m\002"

//Reset
# define RESET "\001\033[0m\002"
# define CRESET "\001\033[0m\002"
# define COLOR_RESET "\001\033[0m\002"
# define NC "\001\033[0m\002"

#endif
