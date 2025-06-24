/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

static void	ft_print_introbanner(void);
static void	ft_print_introbanner_2(void);
static void	ft_print_introbanner_3(void);

void	ft_display_hud(void)
{
	write(STDOUT_FILENO, "\033[H\033[J", 6);
	ft_print_introbanner();
}

static void	ft_print_introbanner(void)
{
	printf(RED "\n\n\n\n\
		███╗   ███╗");
	printf(ORANGE "██╗");
	printf(YELLOW "███╗   ██╗");
	printf(GREEN "██╗");
	printf(TEAL "███████╗");
	printf(BLUE "██╗  ██╗");
	printf(PURPLE "███████╗");
	printf(MAGENTA "██╗     ");
	printf(VIOLET "██╗\n");
	printf(RED "\
		████╗ ████║");
	printf(ORANGE "██║");
	printf(YELLOW "████╗  ██║");
	printf(GREEN "██║");
	printf(TEAL "██╔════╝");
	printf(BLUE "██║  ██║");
	printf(PURPLE "██╔════╝");
	printf(MAGENTA "██║     ");
	printf(VIOLET "██║\n");
	ft_print_introbanner_2();
	ft_print_introbanner_3();
}

static void	ft_print_introbanner_2(void)
{
	printf(RED "\
		██╔████╔██║");
	printf(ORANGE "██║");
	printf(YELLOW "██╔██╗ ██║");
	printf(GREEN "██║");
	printf(TEAL "███████╗");
	printf(BLUE "███████║");
	printf(PURPLE "█████╗  ");
	printf(MAGENTA "██║     ");
	printf(VIOLET "██║\n");
	printf(RED "\
		██║╚██╔╝██║");
	printf(ORANGE "██║");
	printf(YELLOW "██║╚██╗██║");
	printf(GREEN "██║");
	printf(TEAL "╚════██║");
	printf(BLUE "██╔══██║");
	printf(PURPLE "██╔══╝  ");
	printf(MAGENTA "██║     ");
	printf(VIOLET "██║\n");
}

static void	ft_print_introbanner_3(void)
{
	printf(RED "\
		██║ ╚═╝ ██║");
	printf(ORANGE "██║");
	printf(YELLOW "██║ ╚████║");
	printf(GREEN "██║");
	printf(TEAL "███████║");
	printf(BLUE "██║  ██║");
	printf(PURPLE "███████╗");
	printf(MAGENTA "███████╗");
	printf(VIOLET "███████╗\n");
	printf(RED "\
		╚═╝     ╚═╝");
	printf(ORANGE "╚═╝");
	printf(YELLOW "╚═╝  ╚═══╝");
	printf(GREEN "╚═╝");
	printf(TEAL "╚══════╝");
	printf(BLUE "╚═╝  ╚═╝");
	printf(PURPLE "╚══════╝");
	printf(MAGENTA "╚══════╝");
	printf(VIOLET "╚══════╝\n\n\n\n" RESET);
}
