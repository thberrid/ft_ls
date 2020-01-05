/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 06:53:37 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 07:52:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
** 00 00 00 00
** A  R  B  G
**
** field = R | G | B | A
** value <= 0 && value >= 255
** ALPHA (0 <-> 255)  ==  (VISIBLE <-> UNVISIBLE)
*/

void	color_add(int *color, unsigned char value, unsigned char field)
{
	*color |= (value << field);
}

void	color_incr(int *color, unsigned char value, unsigned char field)
{
	*color += (value << field);
}

void	color_decr(int *color, unsigned char value, unsigned char field)
{
	*color -= (value << field);
}

void	color_remove(int *color, unsigned char value, unsigned char field)
{
	*color ^= (value << field);
}

void	color_setwhite(int *color)
{
	color_add(color, 255, GREEN);
	color_add(color, 255, BLUE);
	color_add(color, 255, RED);
}
