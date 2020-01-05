/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:18:21 by thberrid          #+#    #+#             */
/*   Updated: 2019/04/13 17:20:09 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t		get_nibble(unsigned char byte)
{
	size_t	i;
	size_t	nibble;

	i = 0;
	nibble = 0;
	while (i < (FT_BYTSIZE / 2))
	{
		if (byte >> i & 1)
			nibble += (1 << i);
		i += 1;
	}
	return (nibble);
}

static size_t		print_hexa(const void *addr, size_t size, size_t byt_head)
{
	size_t			i;
	unsigned char	byte;
	char			*hex_str;
	size_t			spaces;

	i = 0;
	spaces = FT_BYTSIZE * 5;
	hex_str = "0123456789abcdef";
	while (byt_head + i < size && i < (FT_BYTSIZE * 2))
	{
		byte = ((unsigned char *)addr)[byt_head + i];
		write(1, &hex_str[get_nibble(byte >> (FT_BYTSIZE / 2))], 1);
		write(1, &hex_str[get_nibble(byte)], 1);
		spaces -= 2;
		i += 1;
		if (!(i % 2))
		{
			write(1, " ", 1);
			spaces -= 1;
		}
	}
	return (spaces);
}

static size_t		print_ascii(const void *addr, size_t size, size_t byt_head)
{
	size_t			i;
	unsigned char	c;

	i = 0;
	while (byt_head + i < size && i < (FT_BYTSIZE * 2))
	{
		c = ((unsigned char *)addr)[byt_head + i];
		if (!(c >= 32 && c <= 126))
			c = '.';
		write(1, &c, 1);
		i += 1;
	}
	write(1, "\n", 1);
	return (i);
}

static void			print_spaces(size_t size)
{
	while (size)
	{
		write(1, " ", 1);
		size -= 1;
	}
}

void				print_memory(const void *addr, size_t size)
{
	size_t	byt_head;
	size_t	spaces;

	if (addr)
	{
		byt_head = 0;
		while (byt_head < size)
		{
			spaces = print_hexa(addr, size, byt_head);
			print_spaces(spaces);
			byt_head += print_ascii(addr, size, byt_head);
		}
	}
}
