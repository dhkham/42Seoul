/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:43:12 by dkham             #+#    #+#             */
/*   Updated: 2022/12/28 13:13:38 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int print_c(t_flags *flags, int c) // what about spaces? (undefined bahavior ???)
{
    int count;

    count = 0;
    if (flags->minus == 1) // left justify
    {
        write(1, &c, 1); // print c first, then print spaces depending on width
        count++;
        while (flags->width-- > 1) // if width is 3, print 2 spaces after c
        {
            write(1, " ", 1);
            count++;
        }
    }
    else // right justify (default)
    {
        while (flags->width-- > 1) // print spaces first depending on width, then print c
        {
            write(1, " ", 1);
            count++;
        }
        write(1, &c, 1);
        count++;
    }
    return (count);
}

int print_s(t_flags *flags, char *s)
{
    int count;

    count = 0;
    // if (s == NULL)
    //     s = "(null)";
    if (flags->minus == 1) // left justify
    {
        // char string[] = "Hi, I'm kham!";
        // printf("%s\n", "good"); 
        // printf("%6.8s\n", "good"); 
        // printf("%4.8s\n", string); 

        //good          =>    
        //  good        => length 4 < min 6 (=width) -> add 2 spaces
        //Hi, I'm.      => length 13 > max 8 (=precision) -> print 8 characters
        while (*s && flags->precision--) // write s first, considering precision(max length)
        {
            write(1, s++, 1);
            count++;
        }
        while (flags->width-- > count) // add spaces after s, considering width(only if width > count)
        {
            write(1, " ", 1);
            count++;
        }
    }
    else // right justify (default)
    {
        //while (flags->width-- > count && flags->precision--) // add spaces first, considering width and precision
        // 문자열 길이(5:hello)가 width(6:최소길이) 보다 작을 때 -> width - 문자열 길이 만큼 공백 추가
        while (flags->width-- > ft_strlen(s)) // add spaces first, considering width
        {
            write(1, " ", 1);
            count++;
        }
        while (*s && flags->precision--) // write s after adding spaces, considering precision(max length)
        {
            write(1, s++, 1);
            count++;
        }
        // {
        //     write(1, s++, 1);
        //     count++;
        // }
    }
    return (count);
}

// 여기부터 보기!

// 주소는 16진수로 출력
// print_x도 10진수를 16진수로 출력
// print_p는 print_x 함수를 호출하고, 앞에 0x를 붙여야 한다.

int ft_nbrlen(long n, int base)
{
    int len;

    len = 0;
    if (n == 0)
        return (1);
    while (n)
    {
        n /= base;
        len++;
    }
    return (len);
}

// integer to string (+ base conversion to octal, decimal, hexadecimal)
char    *ft_itoa_base(char *type, int base)
{
    char    *str;
    int     i;
    int     len;
    int     sign;
    long    n;

    sign = 1;
    i = 0;
    n = (long)type;
    if (n < 0)
    {
        sign = -1;
        n *= -1;
    }
    len = ft_nbrlen(n, base);
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    str[len] = '\0';
    while (len--)
    {
        str[len] = n % base + '0';
        if (str[len] > '9')
            str[len] += 39;
        n /= base;
    }
    if (sign == -1)
        str[0] = '-';
    return (str);
}

int print_x(t_flags *flags, unsigned int x)
{
    int count;
    char *str;

    count = 0;
    if (flags->precision == 0 && x == 0)
        return (0);
    str = ft_itoa_base(x, 16);
    if (flags->hash == 1 && x != 0) // # : 16진수 앞에 0x 붙이기
    {
        write(1, "0x", 2);
        count += 2;
    }
    while (flags->precision-- > (int)ft_strlen(str))
    {
        write(1, "0", 1);
        count++;
    }
    while (*str)
    {
        write(1, str++, 1);
        count++;
    }
    return (count);
}

int ft_print_uu(t_flags *flags, unsigned int u)
{
    int count;
    char *str;

    count = 0;
    if (flags->precision == 0 && u == 0)
        return (0);
    str = ft_itoa_base(u, 10);
    while (flags->precision-- > (int)ft_strlen(str))
    {
        write(1, "0", 1);
        count++;
    }
    while (*str)
    {
        write(1, str++, 1);
        count++;
    }
    return (count);
}

int ft_print_d(t_flags *flags, int d)
{
    int count;
    char *str;

    count = 0;
    if (flags->precision == 0 && d == 0)
        return (0);
    if (d < 0)
        d *= -1;
    str = ft_itoa_base(d, 10);
    while (flags->precision-- > (int)ft_strlen(str))
    {
        write(1, "0", 1);
        count++;
    }
    while (*str)
    {
        write(1, str++, 1);
        count++;
    }
    return (count);
}

int print_p(t_flags *flags, unsigned long long p)
{
    int count;

    count = 0;
    if (flags->minus == 1) // left justify
    {
        write(1, "0x", 2);
        count += 2;
        count += print_x(flags, p); // write address first, then print spaces depending on width
        while (flags->width-- > count)
        {
            write(1, " ", 1);
            count++;
        }
    }
    else // right justify (default)
    {
        while (flags->width-- > count)
        {
            write(1, " ", 1);
            count++;
        }
        write(1, "0x", 2);
        count += 2;
        count += print_x(flags, p); // print spaces first depending on width, then write address
    }
    return (count);
}

int print_id(t_flags *flags, int d)
{
    int count;

    count = 0;
    if (flags->minus == 1) // - : 왼쪽 정렬
    {
        if (d < 0)
        {
            write(1, "-", 1);
            count++;
        }
        count += print_d(flags, d);
        while (flags->width-- > count)
        {
            write(1, " ", 1);
            count++;
        }
    }
    else
    {
        while (flags->width-- > count)
        {
            write(1, " ", 1);
            count++;
        }
        if (d < 0)
        {
            write(1, "-", 1);
            count++;
        }
        count += print_d(flags, d);
    }
    return (count);
}

int print_u(t_flags *flags, unsigned int u)
{
    int count;

    count = 0;
    if (flags->minus == 1) // - : 왼쪽 정렬
    {
        count += print_uu(flags, u);
        while (flags->width-- > count)
        {
            write(1, " ", 1);
            count++;
        }
    }
    else
    {
        while (flags->width-- > count)
        {
            write(1, " ", 1);
            count++;
        }
        count += print_uu(flags, u);
    }
    return (count);
}
