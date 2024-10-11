/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:25:49 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/11 16:56:02 by omghazi          ###   ########.fr       */
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
        int     i;
        int     sprit_order;
        double     sprit_distance;
        t_spirite_render        *sprit_render;
        double  dirX;
        double  dirY;
        double  planX;
        double planY;
        
        dirX = 0.0;
        dirY = 0.0;
        sprit_render = init_sprit_render(cub);
        cub->sprites->texture = 1;
        i = 0;
        while (i < cub->sprites->texture)
        {
                sprit_order = i;
                sprit_distance = ((cub->player->pos.x - cub->sprites->x) * (cub->player->pos.x - cub->sprites->x) \
                        + (cub->player->pos.y - cub->sprites->y) * (cub->player->pos.y - cub->sprites->y));
                i++;
        }
        i = 0;
        while (i < cub->sprites->texture)
        {
                sprit_render->spriteX = cub->sprites[sprit_order].x - cub->player->pos.x;
                sprit_render->spriteY = cub->sprites[sprit_order].y - cub->player->pos.y;
                dirX = cos(cub->player->angle);
                dirY = sin(cub->player->angle);
                planX = -sin(cub->player->angle);
                planY = cos(cub->player->angle);
                sprit_render->invDet = 1.0 / (planX * dirX - dirX * planY);
                sprit_render->transformX = sprit_render->invDet * (dirY * sprit_render->spriteX - dirX * sprit_render->spriteY);
                sprit_render->transformY = sprit_render->invDet * (-planY * sprit_render->spriteX + planX * sprit_render->spriteY);

                sprit_render->spriteScreenX = (int)((cub->screen_width / 2) * (1 + sprit_render->transformX / sprit_render->transformY)); 
                sprit_render->spriteHeight = abs((int)(cub->screen_height / (sprit_render->transformY)));
                sprit_render->drawStartY = -sprit_render->spriteHeight / 2 + cub->screen_height / 2;
                if (sprit_render->drawStartY < 0)
                        sprit_render->drawStartY = 0;
                sprit_render->drawEndY = sprit_render->spriteHeight / 2 + cub->screen_height / 2;
                if (sprit_render->drawEndY > cub->max_height)
                        sprit_render->drawEndY = cub->screen_height - 1;
                sprit_render->spriteWidth = abs((int)(cub->screen_height / (sprit_render->transformY)));
                sprit_render->drawStartX = -sprit_render->spriteWidth / 2 + sprit_render->spriteScreenX;
                if (sprit_render->drawStartX < 0)
                        sprit_render->drawStartX = 0;
                sprit_render->drawEndX = sprit_render->spriteWidth / 2 + sprit_render->spriteScreenX;
                if (sprit_render->drawEndX >= cub->screen_width)
                        sprit_render->drawEndX = cub->screen_width - 1;
                for (int stripe = sprit_render->drawStartX; stripe < sprit_render->drawEndX; stripe++)
                {
                        int texX = (int)(256 * (stripe - (-sprit_render->spriteWidth / 2 + sprit_render->spriteScreenX)) * cub->texture->width / sprit_render->spriteWidth) / 256;
                        if (sprit_render->transformY > 0 && stripe > 0 && stripe < cub->screen_width && sprit_render->transformY < cub->ZBuffer[stripe])
                        {
                                for (int y = sprit_render->drawStartY; y < sprit_render->drawEndY; y++)
                                {
                                        int d = (y) * 256 - cub->screen_height * 128 + sprit_render->spriteHeight * 128;
                                        int texY = ((d * cub->texture->height) / sprit_render->spriteHeight) / 256;
                                        uint32_t color = cub->enemie->enemie_img->pixels[cub->enemie->enemie_img->width * texY + texX];
                                        if ((color & 0x00FFFFFF) != 0)
                                                cub->pixels[y * cub->screen_width + stripe] = color;
                                }
                        }
                }
                i++;
        }
}
