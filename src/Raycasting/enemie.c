/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:25:49 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 10:26:18 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_enemie        *new_enemie(const char *path, t_cub3D *cub)
{
        t_enemie                *new_enemie;
        mlx_texture_t           *enemie_texture;
        mlx_image_t             *enemie_img;

        new_enemie = o_malloc(sizeof(t_enemie), 0);
        enemie_texture = mlx_load_png(path);
        if (!enemie_texture)
                ft_error("Error\ntexture not found");
        enemie_img = mlx_texture_to_image(cub->__mlx, enemie_texture);
        if (!enemie_img)
                ft_error("Error\ncan't load texture");
        new_enemie->enemie = enemie_texture;
        new_enemie->enemie_img = enemie_img;
        new_enemie->next = NULL;
        return (new_enemie);
}

void    append_enemie(t_enemie **enemie, t_enemie *new_enemie)
{
        t_enemie        *head;

        if (!enemie)
                return ;
        if (!*enemie)
        {
               *enemie = new_enemie;
               return ; 
        }
        head = *enemie;
        while (head->next)
                head = head->next;
        head->next = new_enemie;
}

t_spirite_render        *init_sprit_render(t_cub3D *cub)
{
        t_spirite_render        *sprit;

        sprit = o_malloc(sizeof(t_spirite_render), 0);
        sprit->drawEndX = 0;
        sprit->drawEndY = 0;
        sprit->drawStartX = 0;
        sprit->drawStartY = 0;
        sprit->invDet = 0;
        sprit->spriteHeight = 0;
        sprit->spriteScreenX = 0;
        sprit->spriteWidth = 0;
        sprit->spriteX = 0;
        sprit->spriteY = 0;
        sprit->transformX = 0;
        sprit->transformY = 0;
        cub->sprit_render = sprit;
        return (sprit);
}

void    draw_spirites(t_cub3D *cub)
{
        (void)cub;
}
