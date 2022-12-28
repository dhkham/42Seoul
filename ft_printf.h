/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:34:35 by dkham             #+#    #+#             */
/*   Updated: 2022/12/28 13:41:55 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"

typedef struct s_flags // before specifier(cspiduxX%)
{
    int minus;
    int zero;
    int dot;
    int hash;
    int plus;
    //int space;
    int width;
    int precision;
}   t_flags;

int     ft_printf(const char *format, ...);
int     ft_vprintf(const char *format, va_list args);
int     ft_parse(const char **format, va_list args);
void    ft_init_flags(t_flags *flags);
void    ft_parse_flags(t_flags *flags, const char **format);
int     ft_parse_type(t_flags *flags, const char **format, va_list ap);
int     print_c(t_flags *flags, int c);
int     print_s(t_flags *flags, char *s);
int     print_p(t_flags *flags, unsigned long long p);
int     print_di(t_flags *flags, int d);
int     print_u(t_flags *flags, unsigned int u);
int     print_x(t_flags *flags, unsigned int x);
int     print_xx(t_flags *flags, unsigned int xx);
int     print_percent(t_flags *flags);




#endif