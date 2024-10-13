#include <stdio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <winuser.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "window.h"
#include <unistd.h>

//=====================================================
#include "control.h"
#include "animation.h"
#include "item.h"
//=====================================================

char* text_cn_path="轨迹";
char* text_cn_speed="速度";
char* text_cn_line="直线";
char* text_cn_rand="曲线";//"随机"
char* text_cn_apply="应用";

char* text_en_path="Path";
char* text_en_speed="Speed";
char* text_en_line="Line";
char* text_en_rand="Curve";//"Random"
char* text_en_apply="Apply";

char* text_jp_path="経路";
char* text_jp_speed="速度";
char* text_jp_line="直線";
char* text_jp_rand="曲線";//"乱数"
char* text_jp_apply="応用";

Animation pig_ani_fly;
Animation pig_ani_balloon;
Animation pig_ani_rocket;
Animation pig_ani_fly_light;
Animation pig_ani_balloon_light;
Animation pig_ani_rocket_light;
Animation pig_ani_fly_big;
Animation pig_ani_balloon_big;
Animation pig_ani_rocket_big;
Animation pig_ani_fly_light_big;
Animation pig_ani_balloon_light_big;
Animation pig_ani_rocket_light_big;
Animation Rani;


HWND hwnd = NULL;//预览小窗口的句柄

void loadTextSurface()//call after loadConfig()
{
    //清空上一次加载的Surface
    SDL_FreeSurface(AppData.textS_title);
    SDL_FreeSurface(AppData.textS_path);
    SDL_FreeSurface(AppData.textS_speed);
    SDL_FreeSurface(AppData.textS_line);
    SDL_FreeSurface(AppData.textS_random);
    SDL_FreeSurface(AppData.textS_en);
    SDL_FreeSurface(AppData.textS_cn);
    SDL_FreeSurface(AppData.textS_jp);
    SDL_FreeSurface(AppData.textS_en_w);
    SDL_FreeSurface(AppData.textS_cn_w);
    SDL_FreeSurface(AppData.textS_jp_w);
    SDL_FreeSurface(AppData.textS_1);
    SDL_FreeSurface(AppData.textS_2);
    SDL_FreeSurface(AppData.textS_3);
    SDL_FreeSurface(AppData.textS_4);
    SDL_FreeSurface(AppData.textS_5);
    SDL_FreeSurface(AppData.textS_apply);
    SDL_FreeSurface(AppData.textS_icon_setting);
    SDL_FreeSurface(AppData.textS_icon_start);
    SDL_FreeSurface(AppData.textS_icon_eye);
    SDL_FreeSurface(AppData.textS_icon_hide);
    
    TTF_Font* font_22=TTF_OpenFont("font/OPlusSans3-Regular.ttf",22);//OPlusSans3-Regular
    // TTF_SetFontStyle(noto_light,TTF_STYLE_BOLD);
    if (font_22==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_Font* font_24=TTF_OpenFont("font/OPlusSans3-Regular.ttf",24);//OPlusSans3-Regular
    if (font_24==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_Font* font_16=TTF_OpenFont("font/OPlusSans3-Regular.ttf",16);//OPlusSans3-Regular
    if (font_16==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_Font* font_14=TTF_OpenFont("font/OPlusSans3-Regular.ttf",14);//OPlusSans3-Regular
    if (font_14==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_Font* font_26=TTF_OpenFont("font/OPlusSans3-Regular.ttf",26);//OPlusSans3-Regular
    if (font_26==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_Font* silver=TTF_OpenFont("font/Silver.ttf",WINDOW_H*0.05);
    if (silver==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_Font* icon=TTF_OpenFont("font/test2.ttf",18);//NotoSansSymbols2-Regular.ttf
    if (icon==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_Font* icon2=TTF_OpenFont("font/test.ttf",22);//NotoEmoji-Bold.ttf
    if (icon2==NULL)
    {
        printf("OpenFont erro\n");
        exit(1);
    }
    TTF_SetFontStyle(silver,TTF_STYLE_BOLD|TTF_STYLE_ITALIC);

    SDL_Color fontcolor = {0, 0, 0};
    SDL_Color fontcolor_w = {255, 255, 255};
    SDL_Color iconcolor = {60, 60, 60};
    SDL_Color iconcolor_blue = {64, 72, 200};
    switch (AppData.language)
    {
    case 'e':
        AppData.textS_path = TTF_RenderUTF8_Blended(font_22, text_en_path, fontcolor);
        AppData.textS_speed = TTF_RenderUTF8_Blended(font_22, text_en_speed, fontcolor);
        AppData.textS_line = TTF_RenderUTF8_Blended(font_16, text_en_line, fontcolor);
        AppData.textS_random = TTF_RenderUTF8_Blended(font_16, text_en_rand, fontcolor);
        AppData.textS_apply = TTF_RenderUTF8_Blended(font_24, text_en_apply, iconcolor);
        break;
    case 'c':
        AppData.textS_path = TTF_RenderUTF8_Blended(font_22, text_cn_path, fontcolor);
        AppData.textS_speed = TTF_RenderUTF8_Blended(font_22, text_cn_speed, fontcolor);
        AppData.textS_line = TTF_RenderUTF8_Blended(font_16, text_cn_line, fontcolor);
        AppData.textS_random = TTF_RenderUTF8_Blended(font_16, text_cn_rand, fontcolor);
        AppData.textS_apply = TTF_RenderUTF8_Blended(font_26, text_cn_apply, iconcolor);
        break;
    case 'j':
        AppData.textS_path = TTF_RenderUTF8_Blended(font_22, text_jp_path, fontcolor);
        AppData.textS_speed = TTF_RenderUTF8_Blended(font_22, text_jp_speed, fontcolor);
        AppData.textS_line = TTF_RenderUTF8_Blended(font_16, text_jp_line, fontcolor);
        AppData.textS_random = TTF_RenderUTF8_Blended(font_16, text_jp_rand, fontcolor);
        AppData.textS_apply = TTF_RenderUTF8_Blended(font_26, text_jp_apply, iconcolor);
        break;

    default:
        AppData.textS_path = TTF_RenderUTF8_Blended(font_22, text_en_path, fontcolor);
        AppData.textS_speed = TTF_RenderUTF8_Blended(font_22, text_en_speed, fontcolor);
        AppData.textS_line = TTF_RenderUTF8_Blended(font_16, text_en_line, fontcolor);
        AppData.textS_random = TTF_RenderUTF8_Blended(font_16, text_en_rand, fontcolor);
        AppData.textS_apply = TTF_RenderUTF8_Blended(font_24, text_en_apply, iconcolor);
        break;
    }

    //"◲" 0x25f2 (H+6.5%) "▶" 0x25b6 (H+6.5%) "🔍" 0x1f50d (H+9.2%) "⚙" 0x2699 (H+0%)
    AppData.textS_icon_setting = TTF_RenderGlyph32_Blended(icon2,0x2699,iconcolor);//TTF_RenderUTF8_Blended(font_22, "⚙", iconcolor);
    AppData.textS_icon_start = TTF_RenderGlyph32_Blended(icon,0x25b6,fontcolor);//iconcolor_blue
    AppData.textS_icon_eye = TTF_RenderGlyph32_Blended(icon,0x1f50d,fontcolor);
    AppData.textS_icon_hide = TTF_RenderGlyph32_Blended(icon,0x25f2,fontcolor);

    AppData.textS_en = TTF_RenderUTF8_Blended(font_14, "EN", fontcolor);
    AppData.textS_cn = TTF_RenderUTF8_Blended(font_14, "ZH", fontcolor);
    AppData.textS_jp = TTF_RenderUTF8_Blended(font_14, "JA", fontcolor);

    AppData.textS_en_w = TTF_RenderUTF8_Blended(font_14, "EN", fontcolor_w);
    AppData.textS_cn_w = TTF_RenderUTF8_Blended(font_14, "ZH", fontcolor_w);
    AppData.textS_jp_w = TTF_RenderUTF8_Blended(font_14, "JA", fontcolor_w);

    TTF_SetFontStyle(font_14,TTF_STYLE_BOLD);
    AppData.textS_1 = TTF_RenderUTF8_Blended(font_14, "1", fontcolor);
    AppData.textS_2 = TTF_RenderUTF8_Blended(font_14, "2", fontcolor);
    AppData.textS_3 = TTF_RenderUTF8_Blended(font_14, "3", fontcolor);
    AppData.textS_4 = TTF_RenderUTF8_Blended(font_14, "4", fontcolor);
    AppData.textS_5 = TTF_RenderUTF8_Blended(font_14, "5", fontcolor);

    AppData.textS_title = TTF_RenderUTF8_Blended(silver, "Flying Pigs", fontcolor_w);
    //SDL_SaveBMP(AppData.textS_apply,"test_font_size.bmp");

    //=========to texture=========

    // SDL_Renderer* theRenderer=NULL;
    // switch (AppData.appMode)
    // {
    //     case 's':theRenderer=AppData.scrnsaverRenderer;break;
    //     case 'm':theRenderer=AppData.scrnsaverRenderer;break;
    //     case 'c':theRenderer=AppData.controlRenderer;break;
    //     case 'p':theRenderer=AppData.previewRenderer;break;
    //     default:break;
    // }

    // if (AppData.text_T_title!=NULL)
    // {
    //     SDL_DestroyTexture(AppData.text_T_title);
    //     SDL_DestroyTexture(AppData.text_T_path);
    //     SDL_DestroyTexture(AppData.text_T_speed);
    //     SDL_DestroyTexture(AppData.text_T_line);
    //     SDL_DestroyTexture(AppData.text_T_random);
    //     SDL_DestroyTexture(AppData.text_T_en);
    //     SDL_DestroyTexture(AppData.text_T_cn);
    //     SDL_DestroyTexture(AppData.text_T_jp);
    //     SDL_DestroyTexture(AppData.text_T_en_w);
    //     SDL_DestroyTexture(AppData.text_T_cn_w);
    //     SDL_DestroyTexture(AppData.text_T_jp_w);
    //     SDL_DestroyTexture(AppData.text_T_1);
    //     SDL_DestroyTexture(AppData.text_T_2);
    //     SDL_DestroyTexture(AppData.text_T_3);
    //     SDL_DestroyTexture(AppData.text_T_4);
    //     SDL_DestroyTexture(AppData.text_T_5);
    //     SDL_DestroyTexture(AppData.text_T_apply);
    //     SDL_DestroyTexture(AppData.text_T_icon_setting);
    //     SDL_DestroyTexture(AppData.text_T_icon_start);
    //     SDL_DestroyTexture(AppData.text_T_icon_eye);
    //     SDL_DestroyTexture(AppData.text_T_icon_hide);
    // }
    
    AppData.text_T_title=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_title);
    AppData.text_T_path=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_path);
    AppData.text_T_speed=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_speed);
    AppData.text_T_line=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_line);
    AppData.text_T_random=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_random);
    AppData.text_T_en=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_en);
    AppData.text_T_cn=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_cn);
    AppData.text_T_jp=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_jp);
    AppData.text_T_en_w=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_en_w);
    AppData.text_T_cn_w=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_cn_w);
    AppData.text_T_jp_w=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_jp_w);
    AppData.text_T_1=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_1);
    AppData.text_T_2=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_2);
    AppData.text_T_3=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_3);
    AppData.text_T_4=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_4);
    AppData.text_T_5=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_5);
    AppData.text_T_apply=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_apply);
    AppData.text_T_icon_setting=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_icon_setting);
    AppData.text_T_icon_start=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_icon_start);
    AppData.text_T_icon_eye=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_icon_eye);
    AppData.text_T_icon_hide=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.textS_icon_hide);

    //============================


    TTF_CloseFont(font_22);
    TTF_CloseFont(font_24);
    TTF_CloseFont(font_16);
    TTF_CloseFont(font_14);
    TTF_CloseFont(font_26);
    TTF_CloseFont(silver);
    TTF_CloseFont(icon);
}

void initWindowRes()
{   
    printf("initWindowRes[START] GetErro:%s\n",SDL_GetError());

    loadTextSurface();

    AppData.tmp_cpl_renderer=AppData.theRenderer;
    // if(AppData.controlTexture_temp!=NULL)SDL_DestroyTexture(AppData.controlTexture_temp);
    AppData.controlTexture_temp=SDL_CreateTexture(AppData.tmp_cpl_renderer,SDL_PIXELFORMAT_RGB888,SDL_TEXTUREACCESS_TARGET,WINDOW_W,WINDOW_H);

    // if(AppData.logo_T!=NULL)SDL_DestroyTexture(AppData.logo_T);
    AppData.logo_T=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.logo);

    // if(AppData.ui_T!=NULL)SDL_DestroyTexture(AppData.ui_T);
    // if(AppData.ui2_T!=NULL)SDL_DestroyTexture(AppData.ui2_T);
    AppData.ui_T=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.ui);
    AppData.ui2_T=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.ui2);

    // if(AppData.L_ani_T!=NULL)SDL_DestroyTexture(AppData.L_ani_T);
    AppData.L_ani_T=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.L_ani);

    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_fly);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_rocket);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_balloon);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_fly_light);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_rocket_light);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_balloon_light);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_fly_big);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_rocket_big);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_balloon_big);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_fly_light_big);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_rocket_light_big);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_balloon_light_big);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_apple);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_bulb);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_coin);
    AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_disc);
    AnimationCreateTextureFromSurface(AppData.tmp_cpl_renderer,&Rani);


    printf("initWindowRes[END] GetErro:%s\n",SDL_GetError());
}


void fillpixels(int x,int y,int w,int h,SDL_Surface* surface,int r,int g,int b) //for RGB888(SDL_PIXELTYPE_PACKED32)
{
    for (int i = 0; i < h; i++)
    {
        for (int ii = 0; ii < w; ii++)
        {
            if (x + ii < surface->w && y + i < surface->h)
            {
                *((Uint8*)(surface->pixels) + 4 * ((y + i) * surface->w + x + ii)) = (Uint8)b;
                *((Uint8*)(surface->pixels) + 4 * ((y + i) * surface->w + x + ii)+1) = (Uint8)g;
                *((Uint8*)(surface->pixels) + 4 * ((y + i) * surface->w + x + ii)+2) = (Uint8)r;
            }
        }
    }
}


//  todo窗口缩放自适应改造  ↓↓↓

void drawBottom()
{
    //fillpixels(0,0,WINDOW_W,WINDOW_H,AppData.controlSurface_temp,192,192,192);
    SDL_Rect rect={0,0,WINDOW_W,WINDOW_H};
    draw98button(rect,0,AppData.controlSurface_temp);
}

void drawTopbar()
{
    //fillpixels(WINDOW_W*0.02,WINDOW_H*0.012,WINDOW_W*0.96,WINDOW_H*0.05,AppData.controlSurface_temp,64,72,200);
    SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,64,72,200,255);
    SDL_Rect theRect={WINDOW_W*0.02,WINDOW_H*0.012,WINDOW_W*0.96,WINDOW_H*0.05};
    SDL_RenderFillRect(AppData.tmp_cpl_renderer,&theRect);
}

void drawCloseButton(Uint8 colormode)//0 正常 1 悬停 2 按住
{
    int gap=((int)(WINDOW_H*0.05*0.8)-3*(int)(WINDOW_H*0.05*0.8*0.25))/2;
    SDL_Rect r0={WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_H*0.05*0.8,WINDOW_H*0.05*0.8};

    if (colormode == 0)
    {
        //fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_H*0.05*0.8,WINDOW_H*0.05*0.8,AppData.controlSurface_temp,192,192,192);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,192,192,192,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r0);
    }
    else if (colormode == 1)
    {
        //fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_H*0.05*0.8,WINDOW_H*0.05*0.8,AppData.controlSurface_temp,209,15,32);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,209,15,32,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r0);
    }
    else if (colormode == 2)
    {
        //fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_H*0.05*0.8,WINDOW_H*0.05*0.8,AppData.controlSurface_temp,232,17,35);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,232,17,35,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r0);
    }
     

    // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap,WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap,WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
    // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap,WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
    // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
    // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap,WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
    // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);

    SDL_Rect r1={WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap,WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap,WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25};
    SDL_Rect r2={WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap,WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25};
    SDL_Rect r3={WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25};
    SDL_Rect r4={WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap,WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25};
    SDL_Rect r5={WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25};

    SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,0,0,0,255);
    SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r1);
    SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r2);
    SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r3);
    SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r4);
    SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r5);

}

void drawLogo()
{
    SDL_Rect dst;
    dst.x=AppData.controlSurface_temp->w/2-AppData.logo->w/2;
    dst.y=AppData.controlSurface_temp->h*0.012+AppData.controlSurface_temp->h*0.05/2-AppData.logo->h/2;
    //SDL_BlitSurface(AppData.logo,NULL,AppData.controlSurface_temp,&dst);
    SDL_QueryTexture(AppData.logo_T,NULL,NULL,&dst.w,&dst.h);
    SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.logo_T,NULL,&dst);
}

void BlitWithBound(SDL_Surface *srcSurface,SDL_Rect *srcRect,SDL_Surface *dstSurface,SDL_Rect *dstRect)
{
   //color rgb(0,0,0)  //！在同色背景下无法突出显示
   int Bwidth=3;
   
   int h=srcSurface->h;int w=srcSurface->w;
   SDL_Rect top={dstRect->x,dstRect->y,w,Bwidth<h?Bwidth:h};//三元运算防止超出
   SDL_Rect bottom={dstRect->x,Bwidth<h?dstRect->y+(h-Bwidth):dstRect->y,w,Bwidth<h?Bwidth:h};
   SDL_Rect left={dstRect->x,dstRect->y,Bwidth<w?Bwidth:w,h};
   SDL_Rect right={Bwidth<w?dstRect->x+(w-Bwidth):dstRect->x,dstRect->y,Bwidth<w?Bwidth:w,h};
   SDL_BlitSurface(srcSurface,srcRect,dstSurface,dstRect);
   SDL_FillRect(dstSurface,&top,SDL_MapRGB(dstSurface->format,255,255,255));
   SDL_FillRect(dstSurface,&bottom,SDL_MapRGB(dstSurface->format,255,255,255));
   SDL_FillRect(dstSurface,&left,SDL_MapRGB(dstSurface->format,255,255,255));
   SDL_FillRect(dstSurface,&right,SDL_MapRGB(dstSurface->format,255,255,255));
}

void drawLanguageButton()
{
    SDL_Rect pos={0};
    pos.x=AppData.controlSurface_temp->w*0.05;pos.y=AppData.controlSurface_temp->h-AppData.textS_en->h-3;
    if(AppData.language=='e')
    {
        // fillpixels(pos.x - 1, pos.y+3, AppData.textS_en->w + 2, AppData.textS_en->h-3, AppData.controlSurface_temp, 64, 72, 200);
        // SDL_BlitSurface(AppData.textS_en_w,NULL,AppData.controlSurface_temp,&pos);
        
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,64,72,200,255);
        SDL_Rect r1={pos.x-1,pos.y+3,AppData.textS_en_w->w+2,AppData.textS_en_w->h-3};
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r1);
        SDL_Rect r2={pos.x,pos.y,AppData.textS_en_w->w,AppData.textS_en_w->h};
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_en_w,NULL,&r2);
    }
    else 
    {
        // SDL_BlitSurface(AppData.textS_en,NULL,AppData.controlSurface_temp,&pos);

        SDL_Rect r2={pos.x,pos.y,AppData.textS_en->w,AppData.textS_en->h};
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_en,NULL,&r2);
    }
    pos.x+=(AppData.textS_en->w+AppData.controlSurface_temp->w*0.015);pos.y=AppData.controlSurface_temp->h-AppData.textS_cn->h-3;
    if(AppData.language=='c')
    {
        // fillpixels(pos.x - 1, pos.y+3, AppData.textS_cn->w + 2, AppData.textS_cn->h-3, AppData.controlSurface_temp, 64, 72, 200);
        // SDL_BlitSurface(AppData.textS_cn_w,NULL,AppData.controlSurface_temp,&pos);

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,64,72,200,255);
        SDL_Rect r1={pos.x-1,pos.y+3,AppData.textS_cn_w->w+2,AppData.textS_cn_w->h-3};
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r1);
        SDL_Rect r2={pos.x,pos.y,AppData.textS_cn_w->w,AppData.textS_cn_w->h};
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_cn_w,NULL,&r2);
    }
    else 
    {
        //SDL_BlitSurface(AppData.textS_cn,NULL,AppData.controlSurface_temp,&pos);

        SDL_Rect r2={pos.x,pos.y,AppData.textS_cn->w,AppData.textS_cn->h};
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_cn,NULL,&r2);
    }
    pos.x+=(AppData.textS_cn->w+AppData.controlSurface_temp->w*0.015);pos.y=AppData.controlSurface_temp->h-AppData.textS_jp->h-3;
    if(AppData.language=='j')
    {
        // fillpixels(pos.x - 1, pos.y+3, AppData.textS_jp->w + 2, AppData.textS_jp->h-3, AppData.controlSurface_temp, 64, 72, 200);
        // SDL_BlitSurface(AppData.textS_jp_w,NULL,AppData.controlSurface_temp,&pos);

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,64,72,200,255);
        SDL_Rect r1={pos.x-1,pos.y+3,AppData.textS_jp_w->w+2,AppData.textS_jp_w->h-3};
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r1);
        SDL_Rect r2={pos.x,pos.y,AppData.textS_jp_w->w,AppData.textS_jp_w->h};
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_jp_w,NULL,&r2);
    }
    else 
    {
        // SDL_BlitSurface(AppData.textS_jp,NULL,AppData.controlSurface_temp,&pos);

        SDL_Rect r2={pos.x,pos.y,AppData.textS_jp->w,AppData.textS_jp->h};
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_jp,NULL,&r2);
    }
}

void draw98button(SDL_Rect rect,Uint8 mode,SDL_Surface* dstSurface) // 0 up 1 down
{
    #define B1_COLOR 82,82,82
    #define B2_COLOR 110,110,110
    #define B3_COLOR 132,132,132
    #define W1_COLOR 220,220,220
    #define W2_COLOR 207,207,207
    #define W3_COLOR 196,196,196

    // #define B1_COLOR 10,10,10
    // #define B2_COLOR 84,84,84
    // #define B3_COLOR 144,144,144
    // #define W1_COLOR 255,255,255
    // #define W2_COLOR 235,235,235
    // #define W3_COLOR 215,215,215


    SDL_Rect b0=rect;      b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
    SDL_Rect b1_0=rect;    b1_0.w-=1;b1_0.h-=1;
    SDL_Rect b1_1=rect;

    if (mode != 1)
    {
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,B1_COLOR));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,W1_COLOR));
        
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,B1_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_1);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,W1_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_0);
    }
    else
    {
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,W1_COLOR));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,B1_COLOR));

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,W1_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_1);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,B1_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_0);
    }
    
    b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
    b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
    b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;

    if (mode != 1)
    {
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,B2_COLOR));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,W2_COLOR));

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,B2_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_1);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,W2_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_0);
    }
    else
    {
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,W2_COLOR));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,B2_COLOR));

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,W2_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_1);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,B2_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_0);
    }

    b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
    b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
    b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
    
    if (mode != 1)
    {
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,B3_COLOR));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,W3_COLOR));

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,B3_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_1);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,W3_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_0);
    }
    else
    {
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,W3_COLOR));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,B3_COLOR));

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,W3_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_1);
        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,B3_COLOR,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b1_0);
    }
    
    // SDL_FillRect(AppData.controlSurface_temp,&b0,SDL_MapRGB(AppData.controlSurface_temp->format,192,192,192));

    SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,192,192,192,255);
    SDL_RenderFillRect(AppData.tmp_cpl_renderer,&b0);

}

void drawSettingButton(Uint8 colormode)
{
    #define SettingButtonW AppData.controlSurface_temp->w*0.1
    #define SettingButtonH AppData.controlSurface_temp->h*0.1

    SDL_Rect Brect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW,AppData.controlSurface_temp->h*0.85,SettingButtonW,SettingButtonH};

    /*过时代码 用于绘制按钮相关
    SDL_Rect b0=Brect;      b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;//{Brect.x+1,Brect.y+1,Brect.w-2,Brect.h-2};
    SDL_Rect b1_0=Brect;    b1_0.w-=1;b1_0.h-=1;            //{Brect.x,Brect.y,Brect.w-1,Brect.h-1};
    SDL_Rect b1_1=Brect;

    if (colormode == 0)
    {
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,82,82,82));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,220,220,220));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,220,220,220));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,82,82,82));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,110,110,110));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,207,207,207));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,207,207,207));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,110,110,110));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,162,162,162));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,196,196,196));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,196,196,196));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,162,162,162));

        SDL_FillRect(AppData.controlSurface_temp,&b0,SDL_MapRGB(AppData.controlSurface_temp->format,192,192,192));

        SDL_Rect icon={Brect.x+Brect.w/2-AppData.textS_icon_setting->w/2,Brect.y+Brect.h/2-AppData.textS_icon_setting->h/2+AppData.textS_icon_setting->h*0.065};
        SDL_BlitSurface(AppData.textS_icon_setting,NULL,AppData.controlSurface_temp,&icon);
        //BlitWithBound(AppData.textS_icon_setting,NULL,AppData.controlSurface_temp,&icon);


    }
    else
    {
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,220,220,220));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,82,82,82));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,207,207,207));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,110,110,110));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,196,196,196));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,162,162,162));

        SDL_FillRect(AppData.controlSurface_temp,&b0,SDL_MapRGB(AppData.controlSurface_temp->format,192,192,192));

        SDL_Rect icon={Brect.x+Brect.w/2-AppData.textS_icon_setting->w/2,Brect.y+Brect.h/2-AppData.textS_icon_setting->h/2+AppData.textS_icon_setting->h*0.065};
        SDL_BlitSurface(AppData.textS_icon_setting,NULL,AppData.controlSurface_temp,&icon);

    }
    */

    draw98button(Brect,colormode,AppData.controlSurface_temp);
    SDL_Rect icon={Brect.x+Brect.w/2-AppData.textS_icon_setting->w/2,Brect.y+Brect.h/2-AppData.textS_icon_setting->h/2+AppData.textS_icon_setting->h*0.065};
    if(colormode==1){icon.x++;icon.y++;}
    // SDL_BlitSurface(AppData.textS_icon_setting,NULL,AppData.controlSurface_temp,&icon);

    icon.w=AppData.textS_icon_setting->w;icon.h=AppData.textS_icon_setting->h;
    SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_setting,NULL,&icon);
}

void drawApplyButton(Uint8 colormode)
{
    #define ApplyButtonW AppData.controlSurface_temp->w*0.25
    #define ApplyButtonH AppData.controlSurface_temp->h*0.1
    SDL_Rect Brect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW-ApplyButtonW-2,AppData.controlSurface_temp->h*0.85,ApplyButtonW,ApplyButtonH};

    /*过时代码 用于绘制按钮相关
    SDL_Rect b0=Brect;      b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;//{Brect.x+1,Brect.y+1,Brect.w-2,Brect.h-2};
    SDL_Rect b1_0=Brect;    b1_0.w-=1;b1_0.h-=1;            //{Brect.x,Brect.y,Brect.w-1,Brect.h-1};
    SDL_Rect b1_1=Brect;

    if (colormode == 0)
    {
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,82,82,82));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,220,220,220));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,220,220,220));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,82,82,82));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,110,110,110));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,207,207,207));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,207,207,207));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,110,110,110));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,162,162,162));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,196,196,196));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,196,196,196));
        // SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,162,162,162));

        SDL_FillRect(AppData.controlSurface_temp,&b0,SDL_MapRGB(AppData.controlSurface_temp->format,192,192,192));

        SDL_Rect icon={Brect.x+Brect.w/2-AppData.textS_apply->w/2,Brect.y+Brect.h/2-AppData.textS_apply->h/2};
        SDL_BlitSurface(AppData.textS_apply,NULL,AppData.controlSurface_temp,&icon);

    }
    else
    {
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,220,220,220));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,82,82,82));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,207,207,207));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,110,110,110));

        b0.x+=1;b0.y+=1;b0.w-=2;b0.h-=2;
        b1_0.x+=1;b1_0.y+=1;b1_0.w-=2;b1_0.h-=2;
        b1_1.x+=1;b1_1.y+=1;b1_1.w-=2;b1_1.h-=2;
        SDL_FillRect(AppData.controlSurface_temp,&b1_1,SDL_MapRGB(AppData.controlSurface_temp->format,196,196,196));
        SDL_FillRect(AppData.controlSurface_temp,&b1_0,SDL_MapRGB(AppData.controlSurface_temp->format,162,162,162));

        SDL_FillRect(AppData.controlSurface_temp,&b0,SDL_MapRGB(AppData.controlSurface_temp->format,192,192,192));

        SDL_Rect icon={Brect.x+Brect.w/2-AppData.textS_apply->w/2,Brect.y+Brect.h/2-AppData.textS_apply->h/2};
        SDL_BlitSurface(AppData.textS_apply,NULL,AppData.controlSurface_temp,&icon);

    }
    */

    draw98button(Brect,colormode,AppData.controlSurface_temp);
    //SDL_Rect icon={Brect.x+Brect.w/2-AppData.textS_apply->w/2,Brect.y+Brect.h/2-AppData.textS_apply->h/2};//原比例
    //SDL_Rect icon={Brect.x+Brect.w/2-AppData.textS_apply->w*0.75/2,Brect.y+Brect.h/2-AppData.textS_apply->h/2,AppData.textS_apply->w*0.75,AppData.textS_apply->h};//缩放
    SDL_Rect tmp={Brect.x+ApplyButtonW*0.1,Brect.y,ApplyButtonW*0.875,ApplyButtonH};
    SDL_Rect icon={tmp.x+tmp.w/2-AppData.textS_apply->w/2,tmp.y+tmp.h/2-AppData.textS_apply->h/2};//after add light
    icon.y-=1;//有点偏移,手工调整下
    if(colormode==1){icon.x++;icon.y++;}
    // SDL_BlitSurface(AppData.textS_apply,NULL,AppData.controlSurface_temp,&icon);//原比例
    // //SDL_BlitScaled(AppData.textS_apply,NULL,AppData.controlSurface_temp,&icon);//缩放
    icon.w=AppData.textS_apply->w;icon.h=AppData.textS_apply->h;
    SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_apply,NULL,&icon);

    //指示灯
    SDL_Rect lightRect={Brect.x+3+(Brect.w-6)*0.2*0.5-(Brect.w-6)*0.0595*0.5,Brect.y+3+(Brect.h-6)*0.5-(Brect.h-6)*0.500*0.5,(Brect.w-6)*0.0595,(Brect.h-6)*0.500};
    if (AppData.apply_flag==1)
    {
        // SDL_FillRect(AppData.controlSurface_temp,&lightRect,SDL_MapRGB(AppData.controlSurface_temp->format,0,224,0));

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,0,224,0,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&lightRect);
    }
    else 
    {
        // SDL_FillRect(AppData.controlSurface_temp,&lightRect,SDL_MapRGB(AppData.controlSurface_temp->format,97,105,97));

        SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,97,105,97,255);
        SDL_RenderFillRect(AppData.tmp_cpl_renderer,&lightRect);
    }
    
}

void drawStartButton(Uint8 colormode)
{
    SDL_Rect iconB={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*3,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
    SDL_Rect iconB2={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*2,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
    if(AppData.appMode=='c')iconB=iconB2;
    SDL_Rect iconT={iconB.x+iconB.w/2-AppData.textS_icon_start->w/2,iconB.y+iconB.h/2-AppData.textS_icon_start->h/2+AppData.textS_icon_start->h*0.065};
    
    if (colormode == 0) // 正常
    {
        // SDL_BlitSurface(AppData.textS_icon_start,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_start->w;iconT.h=AppData.textS_icon_start->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_start,NULL,&iconT);
    }
    else if (colormode == 1) // 悬停
    {
        draw98button(iconB,0,AppData.controlSurface_temp);
        // SDL_BlitSurface(AppData.textS_icon_start,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_start->w;iconT.h=AppData.textS_icon_start->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_start,NULL,&iconT);
    }
    else if (colormode == 2) // 按住
    {
        draw98button(iconB,1,AppData.controlSurface_temp);
        iconT.x++;iconT.y++;
        // SDL_BlitSurface(AppData.textS_icon_start,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_start->w;iconT.h=AppData.textS_icon_start->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_start,NULL,&iconT);
    }

}

void drawEyeButton(Uint8 colormode)
{
    SDL_Rect iconB={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*2,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
    SDL_Rect iconB2={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
    if(AppData.appMode=='c')iconB=iconB2;
    SDL_Rect iconT={iconB.x+iconB.w/2-AppData.textS_icon_eye->w/2,iconB.y+iconB.h/2-AppData.textS_icon_eye->h/2+AppData.textS_icon_eye->h*0.092};

    //已实现
    // if (AppData.appMode != 'c') // 不同模式按钮位置不一样
    // {

    // }
    
    if (colormode == 0) // 正常
    {
        //SDL_BlitSurface(AppData.textS_icon_eye,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_eye->w;iconT.h=AppData.textS_icon_eye->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_eye,NULL,&iconT);
    }
    else if (colormode == 1) // 悬停
    {
        draw98button(iconB,0,AppData.controlSurface_temp);
        //SDL_BlitSurface(AppData.textS_icon_eye,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_eye->w;iconT.h=AppData.textS_icon_eye->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_eye,NULL,&iconT);
    }
    else if (colormode == 2) // 按住
    {
        draw98button(iconB,1,AppData.controlSurface_temp);
        iconT.x++;iconT.y++;
        //SDL_BlitSurface(AppData.textS_icon_eye,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_eye->w;iconT.h=AppData.textS_icon_eye->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_eye,NULL,&iconT);
    }

}

void drawHideButton(Uint8 colormode)
{
    SDL_Rect iconB={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
    SDL_Rect iconT={iconB.x+iconB.w/2-AppData.textS_icon_hide->w/2,iconB.y+iconB.h/2-AppData.textS_icon_hide->h/2+AppData.textS_icon_hide->h*0.065};

    if(AppData.appMode=='c')return;
    
    if (colormode == 0) // 正常
    {
        //SDL_BlitSurface(AppData.textS_icon_hide,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_hide->w;iconT.h=AppData.textS_icon_hide->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_hide,NULL,&iconT);
    }
    else if (colormode == 1) // 悬停
    {
        draw98button(iconB,0,AppData.controlSurface_temp);
        //SDL_BlitSurface(AppData.textS_icon_hide,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_hide->w;iconT.h=AppData.textS_icon_hide->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_hide,NULL,&iconT);
    }
    else if (colormode == 2) // 按住
    {
        draw98button(iconB,1,AppData.controlSurface_temp);
        iconT.x++;iconT.y++;
        //SDL_BlitSurface(AppData.textS_icon_hide,NULL,AppData.controlSurface_temp,&iconT);

        iconT.w=AppData.textS_icon_hide->w;iconT.h=AppData.textS_icon_hide->h;
        SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_icon_hide,NULL,&iconT);
    }

}
//临时笔记 切换模式要记得装卸Area !update:不需要 可以延用 因为用的是相对坐标

//算了 还是单独处理吧 用已有的colormode参数区分 ...算了 直接加判断
// drawModeBar()//为应对不同模式按扭组合的不同,将绘制放在一个函数中统一处理    ...估计上面也要改了,不同模式位置不一样
// {

// }

void clearScreen()
{

}

int threadCLI(void * data)
{
    char buffer[100]={0};
    while (1)
    {
        scanf("%99s",buffer);
        if(!strcmp(buffer,"test"))
        {
            //exit(0);
            printf("Recv!\n");
            printf("SDL_GetErro:%s\n",SDL_GetError());
        }
        memset(&buffer,0,100);
    }
    
}

/*initScrn()-已废弃
void initScrn()
{
    float w,h,k;
    int timestep,offset;

    
    offset=w*0.1;
    timestep=300;

    AppData.scrnWindow=SDL_CreateWindow("flypig_scrn",0,0,0,0,SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);
    AppData.scrnSurface=SDL_GetWindowSurface(AppData.scrnWindow);

    w=AppData.scrnSurface->w;
    h=AppData.scrnSurface->h;
    AppData.k=-0.57735;//tan10du     //(h-0)/(0-w);

    // SDL_BlitSurface(AppData.logo,NULL,AppData.scrnSurface,NULL);
    // SDL_UpdateWindowSurface(AppData.scrnWindow);
    printf("scrnSurface w:%d h:%d\n",AppData.scrnSurface->w,AppData.scrnSurface->h);
}
*/

//暂时用黑屏处理
void multiScreen(int flag)// 0 清理 1 创建
{
    static SDL_Window *windows[99]={0};
    static int windowCount=0;

    static SDL_Renderer *renderers[99]={0};
    static int rendererCount=0;

    for (int i = 0; i < rendererCount; i++) 
    {
        SDL_DestroyRenderer(renderers[i]);
    }
    rendererCount=0;

    for (int i = 0; i < windowCount; i++) 
    {
        SDL_DestroyWindow(windows[i]);
    }
    windowCount=0;

    if(flag==0)return;

    int num=SDL_GetNumVideoDisplays();
    for (size_t i = 1; i < num; i++)
    {
        windows[windowCount]=SDL_CreateWindow("flypig_scrn",SDL_WINDOWPOS_UNDEFINED_DISPLAY(i),SDL_WINDOWPOS_UNDEFINED_DISPLAY(i),0,0,SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_ALWAYS_ON_TOP);
        renderers[rendererCount]=SDL_CreateRenderer(windows[windowCount],-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderers[rendererCount],0,0,0,255);
        SDL_RenderClear(renderers[rendererCount]);
        SDL_RenderPresent(renderers[rendererCount]);
        windowCount++;
        rendererCount++;
    }    
        
    
}

void AppInit(char mode)     //todo 要做记忆功能，切换窗口时控制面板位置保持不变
{
    printf("APP_Init[START] GetErro:%s\n",SDL_GetError());

    AppData.k=-0.57735;
    if(AppData.theRenderer!=NULL){SDL_DestroyRenderer(AppData.theRenderer);AppData.theRenderer=NULL;}
    if(AppData.scrnWindow!=NULL){SDL_DestroyWindow(AppData.scrnWindow);AppData.scrnWindow=NULL;}
    if(AppData.controlWindow!=NULL){SDL_DestroyWindow(AppData.controlWindow);AppData.controlWindow=NULL;}
    multiScreen(0);
    if(mode=='s')
    {
        AppData.scrnWindow=SDL_CreateWindow("flypig_scrn",0,0,0,0,SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_ALWAYS_ON_TOP);
        AppData.theWindow=AppData.scrnWindow;
        //AppData.scrnWindow=SDL_CreateWindowFrom(GetDesktopWindow());
        //AppData.scrnSurface=SDL_GetWindowSurface(AppData.scrnWindow);
        SDL_GetWindowSize(AppData.theWindow,&AppData.scrn_rect.w,&AppData.scrn_rect.h);

        AppData.theRenderer=SDL_CreateRenderer(AppData.scrnWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

        // printf("scrn w:%d h:%d\n",AppData.scrnSurface->w,AppData.scrnSurface->h);

        SDL_ShowCursor(SDL_DISABLE);
        //SDL_RaiseWindow(AppData.scrnWindow);
        // SDL_SetWindowAlwaysOnTop(AppData.scrnWindow,SDL_TRUE); 这个好像没用？

        // SDL_SysWMinfo info;
        // SDL_VERSION(&info.version);
        // if(SDL_GetWindowWMInfo(AppData.scrnWindow,&info))printf("GET INFO OK\n");
        // if(SetWindowPos(info.info.win.window,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE))printf("SET OK\n");
        initWindowRes();
        SDL_ShowWindow(AppData.theWindow);
        multiScreen(1);
    }
    else if(mode=='c')
    {
        AppData.controlWindow = SDL_CreateWindow("Flying Pigs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS); // printf("\nOK %d",AppData.controlWindow);SDL_Delay(5000);return 0;
        AppData.theWindow=AppData.controlWindow;
        // AppData.controlSurface = SDL_GetWindowSurface(AppData.controlWindow);

        AppData.theRenderer=SDL_CreateRenderer(AppData.controlWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

        // printf("controlSurface w:%d h:%d\n", AppData.controlSurface->w, AppData.controlSurface->h);

        SDL_RaiseWindow(AppData.controlWindow);

        deleteAreaNodeByName(&AppData.controlAreaList,"start");
        deleteAreaNodeByName(&AppData.controlAreaList,"eye");
        deleteAreaNodeByName(&AppData.controlAreaList,"hide");
        SDL_Rect startRect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*2,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        SDL_Rect eyeRect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        addArea(&AppData.controlAreaList,"start",startRect,clickStartCallback);
        addArea(&AppData.controlAreaList,"eye",eyeRect,clickEyeCallback);

        initWindowRes();
        SDL_ShowWindow(AppData.theWindow);
    }
    else if(mode=='m')
    {
        AppData.scrnWindow=SDL_CreateWindow("flypig_scrn",0,0,0,0,SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);
        AppData.theWindow=AppData.scrnWindow;
        // AppData.scrnSurface=SDL_GetWindowSurface(AppData.scrnWindow);
        SDL_GetWindowSize(AppData.theWindow,&AppData.scrn_rect.w,&AppData.scrn_rect.h);

        AppData.theRenderer=SDL_CreateRenderer(AppData.scrnWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

        // printf("scrnSurface w:%d h:%d\n",AppData.scrnSurface->w,AppData.scrnSurface->h);

        //===============Add Area================ noplaneAreaList (控制面板隐藏状态下的队列)
        clearArea(AppData.noplaneAreaList);
        AppData.noplaneAreaList=NULL;
        SDL_Rect logo={AppData.scrn_rect.w-AppData.logo->w,AppData.scrn_rect.h-AppData.logo->h,AppData.logo->w,AppData.logo->h};
        addArea(&AppData.noplaneAreaList,"\0",logo,clickLogoCallback);
        //===============Add Area================
        deleteAreaNodeByName(&AppData.controlAreaList,"start");
        deleteAreaNodeByName(&AppData.controlAreaList,"eye");
        deleteAreaNodeByName(&AppData.controlAreaList,"hide");
        SDL_Rect startRect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*3,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        SDL_Rect eyeRect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*2,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        SDL_Rect hideRect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        addArea(&AppData.controlAreaList,"start",startRect,clickStartCallback);
        addArea(&AppData.controlAreaList,"eye",eyeRect,clickEyeCallback);
        addArea(&AppData.controlAreaList,"hide",hideRect,clickHideCallback);
        //==============Init CPL pos==============
        static int init_flag=0;
        if (init_flag==0)
        {
            AppData.CWrect.x=AppData.scrn_rect.w*0.5-WINDOW_W*0.5;
            AppData.CWrect.y=AppData.scrn_rect.h*0.5-WINDOW_H*0.5;
            AppData.CWrect.w=WINDOW_W;
            AppData.CWrect.h=WINDOW_H;
            init_flag=1;
        }

        initWindowRes();
        SDL_ShowWindow(AppData.theWindow);
        multiScreen(1);
    }
    else if(mode=='p')
    {
        RECT rc={0};
        GetWindowRect(hwnd,&rc);//printf("RC: %d %d %d %d",rc.left,rc.top,rc.right,rc.bottom);
        AppData.preWindow=SDL_CreateWindow("scr preview",0,0,rc.right-rc.left,rc.bottom-rc.top,SDL_WINDOW_HIDDEN|SDL_WINDOW_BORDERLESS);
        AppData.theWindow=AppData.preWindow;
        //printf("E:%s  Rect:%d %d\n",SDL_GetError(),rc.right,rc.bottom);
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);
        if(SDL_GetWindowWMInfo(AppData.preWindow,&info))printf("GET INFO OK\n");
        if(SetWindowLongPtr(info.info.win.window,GWL_STYLE,WS_CHILD|WS_VISIBLE))printf("SET OK\n");
        //if(SetWindowLongPtr(info.info.win.window,GWL_STYLE,GetWindowLongPtr(info.info.win.window,GWL_STYLE)|WS_CHILD))printf("SET OK\n");
        if(SetParent(info.info.win.window,hwnd))printf("SET OK\n");
        //SDL_ShowWindow(theW);
        
        //AppData.preSurface=SDL_GetWindowSurface(AppData.preWindow);
        SDL_GetWindowSize(AppData.theWindow,&AppData.pre_rect.w,&AppData.pre_rect.h);
        AppData.theRenderer=SDL_CreateRenderer(AppData.preWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        //printf("E:%s  preSurface:%d\n",SDL_GetError(),AppData.preSurface);

        initWindowRes();
        SDL_ShowWindow(AppData.theWindow);
    }

    printf("APP_Init[END] GetErro:%s\n",SDL_GetError());
}

Uint32 LAni_timerCallback(Uint32 interval, void *Rect)
{
    SDL_Rect* aniRect=Rect;

    if (aniRect->x>=1214-576||aniRect->y<=0)
    {
        //printf("======> x: %d y: %d \n",aniRect->x,aniRect->y);
        aniRect->x=0;
        aniRect->y=956-352;
    }
    

    aniRect->x+=4;
    aniRect->y-=4;

    return interval;
}

//废案
// Uint32 RAni_timerCallback(Uint32 interval,void* data);
// struct RAni_record
// {
//     int count;
//     SDL_Rect pos; // w,h实际上被用来存储x,y的初始值
// }*r1,*r2,*r3,*r4,*r5;
// void RAni_Init()
// {
//     AppData.RAni_tempSurface=SDL_CreateRGBSurfaceWithFormat(0,576/2.5,352/2.5,32,SDL_PIXELFORMAT_RGB888);

//     r1=malloc(sizeof(struct RAni_record));
//     r1->count=0;
//     r1->pos.x=1.0*576.0/2.5/5*1;r1->pos.y=-100;
//     r1->pos.w=r1->pos.x;r1->pos.h=r1->pos.y;
//     SDL_AddTimer(100,RAni_timerCallback,r1);

//     r2=malloc(sizeof(struct RAni_record));
//     r2->count=5;//不必都是0,要有随机感
//     r2->pos.x=1.2*576.0/2.5/5*2;r2->pos.y=-100;
//     r2->pos.w=r2->pos.x;r2->pos.h=r2->pos.y;
//     SDL_AddTimer(100,RAni_timerCallback,r2);

//     r3=malloc(sizeof(struct RAni_record));
//     r3->count=11;
//     r3->pos.x=1.5*576.0/2.5/5*3;r3->pos.y=-100;
//     r3->pos.w=r3->pos.x;r3->pos.h=r3->pos.y;
//     SDL_AddTimer(100,RAni_timerCallback,r3);

//     r4=malloc(sizeof(struct RAni_record));
//     r4->count=6;
//     r4->pos.x=1.7*576.0/2.5/5*4;r4->pos.y=-100;
//     r4->pos.w=r4->pos.x;r4->pos.h=r4->pos.y;
//     SDL_AddTimer(100,RAni_timerCallback,r4);

//     r5=malloc(sizeof(struct RAni_record));
//     r5->count=3;
//     r5->pos.x=2.0*576.0/2.5/5*5;r5->pos.y=-100;
//     r5->pos.w=r5->pos.x;r5->pos.h=r5->pos.y;
//     SDL_AddTimer(100,RAni_timerCallback,r5);

// }

// void drawRAni()
// {
//     const SDL_Rect clips[15]={{28,18,110,54},{28,122,113,57},{37,196,111,68},{35,277,108,80},{36,384,102,91},{206,4,104,91},{213,107,107,91},{219,204,102,91},{207,302,107,91},{205,403,104,91},{372,7,102,91},{366,130,108,81},{363,228,111,69},{367,311,114,58},{368,397,108,54}};

//     SDL_FillRect(AppData.RAni_tempSurface,NULL,SDL_MapRGB(AppData.RAni_tempSurface->format,0,0,0));

//     SDL_BlitSurface(AppData.RAni_sprite,&clips[r1->count],AppData.RAni_tempSurface,&r1->pos);
//     SDL_BlitSurface(AppData.RAni_sprite,&clips[r2->count],AppData.RAni_tempSurface,&r2->pos);
//     SDL_BlitSurface(AppData.RAni_sprite,&clips[r3->count],AppData.RAni_tempSurface,&r3->pos);
//     SDL_BlitSurface(AppData.RAni_sprite,&clips[r4->count],AppData.RAni_tempSurface,&r4->pos);
//     SDL_BlitSurface(AppData.RAni_sprite,&clips[r5->count],AppData.RAni_tempSurface,&r5->pos);

// }

// Uint32 RAni_timerCallback(Uint32 interval,void* data)
// {
//     struct record
//     {
//         int count;
//         SDL_Rect pos;//w,h实际上被用来存储x,y的初始值
//     }*d;
//     d=data;
//     const int offset[15][3]/*(base_y_offset,x_offset,y_offset)*/={{36,0,0},{48,-5,12},{59,-1,11},{71,-4,12},{82,-6,11},{78,-12,-4},{71,-11,-7},{64,-8,-7},{58,-13,-6},{50,-8,-8},{43,-10,-7},{30,-12,-3},{28,-7,10},{29,-4,12},{36,0,11}};

//     if (d->count==14) 
//     {
//         d->count=1;//末尾的帧好像和第一帧重复了，所以跳过
//     }
    

//     if(d->pos.x<-120||d->pos.y>452)
//     {
//         d->count=0;
//         d->pos.x=d->pos.w;
//         d->pos.y=d->pos.h;
//         return interval;
//     }

//     d->pos.y+=offset[d->count][0];
//     d->count++;
//     d->pos.x+=offset[d->count][1];d->pos.y+=offset[d->count][2];
//     d->pos.y-=offset[d->count][0];
//     drawRAni();
//     return interval;
// }


extern Play* ppp;


//void initScrn();
PigNode* genPig(int x,int y);
void deletePig(PigNode** headP,PigNode* nodeToDel);
PigNode* PigStream(int initX,int initY,int gap,PigNode* thePig);
void Update(PigNode* pigs,char mode,Uint32 time);
void drawPigs(PigNode* pigs,SDL_Surface* dst);
void RandSin(PigNode* pigs,Uint32 time);
int checkApply();
Uint32 checkApplyCallback(Uint32 interval, void *param);

int main(int argc, char *argv[])
{   
    // // FILE *fp = freopen("C:\\Code\\flypig\\output.txt", "w", stdout);

    //printf("%d %d %d\n",(int)(TopBarW),(int)(CloseButtonX),(int)(CloseButtonPartLength));
    //printf("%d %d %d %d\n",(int)(AreaDragX),(int)(AreaDragY),(int)(AreaDragW),(int)(AreaDragH));
    char* path=getcwd(NULL,100);
    printf("getcwd:%s\n",path);
    free(path);
    //注意！: argv[0]不一定代表程序的完整路径
    printf("argv[0]:%s\n",argv[0]);
    //printf("strrchr:%s\n",strrchr(argv[0],'\\'));
    char* p=strrchr(argv[0],'\\');
    if(p!=NULL)
    {
        *p='\0';
        printf("mod:%s\n",argv[0]);
        printf("return%d\n",chdir(argv[0]));
    }
    path=getcwd(NULL,100);
    printf("getcwd:%s\n",path);
    free(path);

    printf("\n\n\n========argv list========\n");
    for (int i = 0; i < argc; i++)
    {
        printf("%d:%s\n",i, argv[i]);
    }
    printf("=========================\n\n\n");//system("pause");
    //注意：已发现在PS环境中执行.scr,会重新在新的命令行打开，并覆盖掉原本输入的参数,变成\S


    // //SDL_SetHint(SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT, //%p);
    // if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
    // {
    //     printf("SDL_Init erro\n");
    //     return 1;
    // }
    // printf("test1.....................\n");
    // RECT rc;
    // GetWindowRect((HWND)strtoull(argv[2],NULL,10),&rc); 
    // //SDL_Window* theW=SDL_CreateWindowFrom((HWND)strtoull(argv[2],NULL,10));
    // SDL_Window* theW=SDL_CreateWindow("scr preview",0,0,rc.right,rc.bottom,SDL_WINDOW_HIDDEN|SDL_WINDOW_BORDERLESS);
    // SDL_SysWMinfo info;
    // SDL_VERSION(&info.version);
    // if(SDL_GetWindowWMInfo(theW,&info))printf("GET INFO OK\n");
    // if(SetWindowLongPtr(info.info.win.window,GWL_STYLE,WS_CHILD|WS_VISIBLE))printf("SET OK\n");
    // //if(SetWindowLongPtr(info.info.win.window,GWL_STYLE,GetWindowLongPtr(info.info.win.window,GWL_STYLE)|WS_CHILD))printf("SET OK\n");
    // if(SetParent(info.info.win.window,(HWND)strtoull(argv[2],NULL,10)))printf("SET OK\n");
    // //SDL_ShowWindow(theW);
    

    // printf("%d %s\n",theW,SDL_GetError());
    // printf("test2.....................\n");
    // printf("sizeof:%zu %zu %zu %zu\n",sizeof(HWND),sizeof(void *),sizeof(unsigned long int),sizeof(unsigned long long));

    // // SDL_Window* theW=SDL_CreateWindow("test",50,50,200,200,SDL_WINDOW_SHOWN);
    // SDL_Surface* theS=SDL_GetWindowSurface(theW);
    // printf("smallwindow: w%dh%d\n",theS->w,theS->h);
    // SDL_Rect cube={0,0,10,10};
    // SDL_Rect bg={0,0,100,100};

    // Uint32 color=SDL_MapRGB(theS->format,255,255,255);
    // Uint32 color2=SDL_MapRGB(theS->format,0,0,0);

    // // fclose(fp);

    // int QUIT2 = 0;
    // SDL_Event e1;
    // while (!QUIT2)
    // {
    //     while (SDL_PollEvent(&e1))
    //     {   
    //         if(e1.type==SDL_WINDOWEVENT)
    //         {
    //             if (e1.window.event==SDL_WINDOWEVENT_CLOSE)
    //             {
    //                 QUIT2=1;
    //             }

    //         }
    //     }
    //     if (cube.x<90)cube.x++;
    //     else cube.x=0;  
    //     SDL_FillRect(theS,&bg,color2);
    //     SDL_FillRect(theS,&cube,color);
    //     SDL_UpdateWindowSurface(theW);
    //     SDL_Delay(1000/60);
    // }


    // exit(0);

    if (argc < 2)
    {
        AppData.appMode='c';
    }
    else
    {
        //char *c = argv[1];
        char *c = GetCommandLine();
        if (*c == '\"')
        {
            c++;
            while (*c != 0 && *c != '\"')
                c++;
        }
        else
        {
            while (*c != 0 && *c != ' ')
                c++;
        }
        if (*c != 0)
            c++;
        while (*c == ' ')
            c++;
        if (*c == '-' || *c == '/')
            c++;
        if (*c == 'p' || *c == 'P' || *c == 'l' || *c == 'L')
        {
            c++;
            while (*c == ' ' || *c == ':')
                c++;
            hwnd = (HWND)strtoull(c,NULL,10);
            AppData.appMode='p';
        }
        else if (*c == 's' || *c == 'S')
        {
            AppData.appMode='s';
        }
        // else if (*c == 'c' || *c == 'C')
        // {
        //     AppData.appMode='c';
        // }
        else AppData.appMode='c';
    }


// SetProcessDPIAware(); 有 SDL_HINT_WINDOWS_DPI_AWARENESS 替代
loadConfig();
srand(time(NULL));

SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitor"); // 避免系统缩放
SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"best");
// SDL_SetHint(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP,"0"); just test...不知道有什么用

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL_Init erro\n");
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("IMG_Init erro\n");
        return 1;
    }
    if (TTF_Init() == -1)
    {
        printf("TTF_Init erro\n");
        return 1;
    }

    SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");//聚焦时穿透点击（避免当焦点在别处时,无法获得点击的问题）
    //没用...SDL_SetHint(SDL_HINT_FORCE_RAISEWINDOW,"1");//强制置顶


    SDL_Thread* thread = SDL_CreateThread(threadCLI, "cli", NULL);
    if (thread == NULL) {
        printf("无法创建线程：%s\n", SDL_GetError());
        return 1;
    }

    // SDL_Surface *Wsurface = NULL;
    // AppData.controlWindow = SDL_CreateWindow("Flying Pigs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);//printf("\nOK %d",AppData.controlWindow);SDL_Delay(5000);return 0;
    // Wsurface = SDL_GetWindowSurface(AppData.controlWindow);printf("wsurface w:%d h:%d\n",Wsurface->w,Wsurface->h);
    AppData.controlSurface_temp=SDL_CreateRGBSurfaceWithFormat(0,WINDOW_W,WINDOW_H,24,SDL_PIXELFORMAT_RGB888);
    //initScrn();

    //char mode='s';//'s' scrnsave  'c' control 'm' mixed
    //about hint 启动方式对表现形式的影响 屏保启动-no 控制面板 no 右下角logo 手动启动-有控制面板和logo

    // //读取参数
    // if (!(argc<2))
    // {
    //     if (!strcmp("s",argv[1]))
    //     {
    //         AppData.appMode='s';
    //     }
    //     else if (!strcmp("c",argv[1]))
    //     {
    //         AppData.appMode='c';
    //     }
    //     else if (!strcmp("m",argv[1]))
    //     {
    //         AppData.appMode='m';
    //     }
    //     else if (!strcmp("p",argv[1]))
    //     {
    //         AppData.appMode='p';
    //     }
    //     else AppData.appMode='s';
    // }
    // else AppData.appMode='s';


    //APP初始化-创建窗口、添加响应区域
    // AppInit(AppData.appMode);
    
    // printf("=======>  w: %d h: %d \n",(int)(AppData.controlSurface_temp->w/2*0.8),(int)(AppData.controlSurface_temp->w/2*0.8*0.618));

    // AppData.tmp_cpl_renderer=SDL_CreateRenderer(AppData.theWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
    // AppData.tmp_cpl_renderer=AppData.theRenderer;
    // AppData.controlTexture_temp=SDL_CreateTexture(AppData.tmp_cpl_renderer,SDL_PIXELFORMAT_RGB888,SDL_TEXTUREACCESS_TARGET,WINDOW_W,WINDOW_H);

    AppData.logo=IMG_Load("pig.png");
    // AppData.logo_T=SDL_CreateTextureFromSurface(AppData.theRenderer,AppData.logo);
    
    AppData.apply_flag=checkApply();
    SDL_AddTimer(500,checkApplyCallback,NULL);

    /*  字体加载测试
    TTF_Font* noto=TTF_OpenFont("noto.ttf",16);
    if (noto==NULL)
    {
        printf("OpenFont erro\n");
        return 1;
    }
    SDL_Color fontcolor = {0, 0, 0};
    SDL_Surface* textSurface=TTF_RenderUTF8_Solid(noto,"你好，世界",fontcolor);

    // TTF_Font* Black =TTF_OpenFont("font/NotoSansSC-Black.ttf",16);SDL_Surface* textSurface1=TTF_RenderUTF8_Solid(Black,"你好，世界",fontcolor);
    // TTF_Font* Bold =TTF_OpenFont("font/NotoSansSC-Bold.ttf",16);SDL_Surface* textSurface2=TTF_RenderUTF8_Solid(Bold,"你好，世界",fontcolor);
    // TTF_Font* Light =TTF_OpenFont("font/NotoSansSC-Light.ttf",16);SDL_Surface* textSurface3=TTF_RenderUTF8_Solid(Light,"*你好，世界",fontcolor); // *
    // TTF_Font* Medium =TTF_OpenFont("font/NotoSansSC-Medium.ttf",16);SDL_Surface* textSurface4=TTF_RenderUTF8_Solid(Medium,"你好，世界",fontcolor);
    // TTF_Font* Thin =TTF_OpenFont("font/NotoSansSC-Thin.ttf",16);SDL_Surface* textSurface5=TTF_RenderUTF8_Solid(Thin,"你好，世界",fontcolor);
    // TTF_Font* Sliver =TTF_OpenFont("font/Silver.ttf",16);SDL_Surface* textSurface6=TTF_RenderUTF8_Solid(Thin,"你好，世界",fontcolor);
    */
    //SDL_SetWindowResizable(AppData.controlWindow,SDL_TRUE);


    AppData.ui=IMG_Load("ui_speed.png");
    AppData.ui2=IMG_Load("ui_speed_s.png");

    // SDL_Texture* ui_T=SDL_CreateTextureFromSurface(AppData.theRenderer,ui);
    // SDL_Texture* ui2_T=SDL_CreateTextureFromSurface(AppData.theRenderer,ui2);

    SDL_Surface* L_ani_raw=IMG_Load("L.png");
    // SDL_Surface* R_ani_raw=IMG_Load("R.png");
    AppData.L_ani=SDL_ConvertSurfaceFormat(L_ani_raw,SDL_PIXELFORMAT_RGB888,0);
    // SDL_Surface* R_ani=SDL_ConvertSurfaceFormat(R_ani_raw,SDL_PIXELFORMAT_RGB888,0);
    SDL_FreeSurface(L_ani_raw);
    // SDL_FreeSurface(R_ani_raw);
    SDL_Rect L_ani_Rect={0,956-352,576,352};
    SDL_AddTimer(50,LAni_timerCallback,&L_ani_Rect);

    // SDL_Texture* L_ani_T=SDL_CreateTextureFromSurface(AppData.theRenderer,L_ani);

    // AppData.RAni_sprite=R_ani;
    // SDL_SetColorKey(AppData.RAni_sprite,SDL_TRUE,SDL_MapRGB(AppData.RAni_sprite->format,0,0,0));
    // RAni_Init();

    pig_ani_fly=loadAnimation("Animation\\fly");
    pig_ani_rocket=loadAnimation("Animation\\rocket");
    pig_ani_balloon=loadAnimation("Animation\\balloon");
    pig_ani_fly_light=loadAnimation("Animation\\fly_light");
    pig_ani_rocket_light=loadAnimation("Animation\\rocket_light");
    pig_ani_balloon_light=loadAnimation("Animation\\balloon_light");
    item_ani_apple=loadAnimation("Animation\\apple");
    item_ani_bulb=loadAnimation("Animation\\bulb");
    item_ani_coin=loadAnimation("Animation\\coin");
    item_ani_disc=loadAnimation("Animation\\disc");
    //effect_ani=loadAnimation("Animation\\effect");

    SDL_Rect screenRect={0};
    if (AppData.appMode!='p')
    {
        SDL_GetDisplayBounds(0,&screenRect);
        AppData.zoom=screenRect.w/2560.0<screenRect.h/1440.0?screenRect.w/2560.0:screenRect.h/1440.0;
    }
    else
    {
        RECT rc={0};
        GetWindowRect(hwnd,&rc);
        screenRect.w=rc.right-rc.left;screenRect.h=rc.bottom-rc.top;
        AppData.zoom=screenRect.w/2560.0<screenRect.h/1440.0?screenRect.w/2560.0:screenRect.h/1440.0;
        //已废
        // screenRect.w=AppData.pre_rect.w;screenRect.h=AppData.pre_rect.h;
        // AppData.zoom=screenRect.w/2560.0<screenRect.h/1440.0?screenRect.w/2560.0:screenRect.h/1440.0;
    }
    //big版本放到前面来,不然在后面的话是基于已经缩放过的版本再缩放,会增加劣化程度
    pig_ani_fly_big=scaleAnimation(pig_ani_fly,2*256*1.2*AppData.zoom,2*256*1.2*AppData.zoom);
    pig_ani_rocket_big=scaleAnimation(pig_ani_rocket,2*256*1.2*AppData.zoom,2*256*1.2*AppData.zoom);
    pig_ani_balloon_big=scaleAnimation(pig_ani_balloon,2*256*1.2*AppData.zoom,2*256*1.2*AppData.zoom);
    pig_ani_fly_light_big=scaleAnimation(pig_ani_fly_light,2*256*1.2*AppData.zoom,2*256*1.2*AppData.zoom);
    pig_ani_rocket_light_big=scaleAnimation(pig_ani_rocket_light,2*256*1.2*AppData.zoom,2*256*1.2*AppData.zoom);
    pig_ani_balloon_light_big=scaleAnimation(pig_ani_balloon_light,2*256*1.2*AppData.zoom,2*256*1.2*AppData.zoom);

    pig_ani_fly=scaleAnimation(pig_ani_fly,256*1.2*AppData.zoom,256*1.2*AppData.zoom); //!!!缩放基准值不同样式不一样！fly/rocket/balloon 120、150、...
    pig_ani_rocket=scaleAnimation(pig_ani_rocket,256*1.2*AppData.zoom,256*1.2*AppData.zoom);
    pig_ani_balloon=scaleAnimation(pig_ani_balloon,256*1.2*AppData.zoom,256*1.2*AppData.zoom);
    pig_ani_fly_light=scaleAnimation(pig_ani_fly_light,256*1.2*AppData.zoom,256*1.2*AppData.zoom);
    pig_ani_rocket_light=scaleAnimation(pig_ani_rocket_light,256*1.2*AppData.zoom,256*1.2*AppData.zoom);
    pig_ani_balloon_light=scaleAnimation(pig_ani_balloon_light,256*1.2*AppData.zoom,256*1.2*AppData.zoom);

    item_ani_apple=scaleAnimation(item_ani_apple,32*1.6*1.1*AppData.zoom,32*1.6*1.1*AppData.zoom);
    item_ani_bulb=scaleAnimation(item_ani_bulb,32*1.6*AppData.zoom,32*1.6*AppData.zoom);
    item_ani_coin=scaleAnimation(item_ani_coin,32*1.2*1.1*AppData.zoom,32*1.2*1.1*AppData.zoom);
    item_ani_disc=scaleAnimation(item_ani_disc,96*0.425*1.1*AppData.zoom,96*0.425*1.1*AppData.zoom);
    //effect_ani=scaleAnimation(effect_ani,256*1.2*AppData.zoom,256*1.2*AppData.zoom);

    AppData.itemCallbackLock=SDL_CreateSemaphore(1);
    startItemGen();//须在加载动画后调用,因为生成需要用到尺寸数据
    
    Rani=loadAnimation("R");
    Play* Rplay=playAnimation(&Rani,1,1);

    // AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_fly);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_rocket);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_balloon);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_fly_light);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_rocket_light);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&pig_ani_balloon_light);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_apple);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_bulb);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_coin);
    // AnimationCreateTextureFromSurface(AppData.theRenderer,&item_ani_disc);
    // AnimationCreateTextureFromSurface(AppData.tmp_cpl_renderer,&Rani);
    

    // printf("%f %f %f %f %f",WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_W*0.02+WINDOW_W*0.96*0.92+WINDOW_H*0.05*0.8*0.05,WINDOW_H*0.012+WINDOW_H*0.05*0.1+WINDOW_H*0.05*0.8*0.05,WINDOW_H*0.05*0.8*0.05);
    //printf("%d %d %d\n",(int)(WINDOW_H*0.05*0.8*0.125),(int)(WINDOW_H*0.05*0.8),(int)(WINDOW_H*0.05*0.8*0.25));

    AppInit(AppData.appMode);
    //===============Add Area================
    SDL_Rect topbarRect={WINDOW_W*0.02,WINDOW_H*0.012,WINDOW_W*0.96,WINDOW_H*0.05};
    addArea(&AppData.controlAreaList,"\0",topbarRect,clickTopBarCallback);

    SDL_Rect closeRect={WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_H*0.05*0.8,WINDOW_H*0.05*0.8};
    addArea(&AppData.controlAreaList,"\0",closeRect,clickCloseCallback);

    int w1 = AppData.controlSurface_temp->w / 2 * 0.8;
    int h1 = AppData.controlSurface_temp->w / 2 * 0.8 * 0.618;
    int gap1 = w1 * 0.035;

    SDL_Rect lineModeRect={(AppData.controlSurface_temp->w / 2 - w1) / 2, AppData.controlSurface_temp->h * 0.16, w1, h1};
    addArea(&AppData.controlAreaList,"\0",lineModeRect,clickLineModeCallback);

    SDL_Rect randModeRect={(AppData.controlSurface_temp->w / 2 - w1) / 2 * 3 + w1, AppData.controlSurface_temp->h * 0.16, w1, h1};
    addArea(&AppData.controlAreaList,"\0",randModeRect,clickRandModeCallback);

    int gap_ui=AppData.controlSurface_temp->w/5;
    SDL_Rect uir={gap_ui/2,AppData.controlSurface_temp->h*0.455,32,32};
    uir.x-=(uir.w/2);

    SDL_Rect speedLv1Rect=uir;
    addArea(&AppData.controlAreaList,"\0",speedLv1Rect,clickSpeedLv1Callback);
    uir.x+=gap_ui;
    SDL_Rect speedLv2Rect=uir;
    addArea(&AppData.controlAreaList,"\0",speedLv2Rect,clickSpeedLv2Callback);
    uir.x+=gap_ui;
    SDL_Rect speedLv3Rect=uir;
    addArea(&AppData.controlAreaList,"\0",speedLv3Rect,clickSpeedLv3Callback);
    uir.x+=gap_ui;
    SDL_Rect speedLv4Rect=uir;
    addArea(&AppData.controlAreaList,"\0",speedLv4Rect,clickSpeedLv4Callback);
    uir.x+=gap_ui;
    SDL_Rect speedLv5Rect=uir;
    addArea(&AppData.controlAreaList,"\0",speedLv5Rect,clickSpeedLv5Callback);

    SDL_Rect languageBaseRect={AppData.controlSurface_temp->w*0.05,AppData.controlSurface_temp->h-AppData.textS_en->h-3};
    SDL_Rect enRect={languageBaseRect.x,languageBaseRect.y,AppData.textS_en->w,AppData.textS_en->h};
    languageBaseRect.x+=(AppData.textS_en->w+AppData.controlSurface_temp->w*0.015);languageBaseRect.y=AppData.controlSurface_temp->h-AppData.textS_cn->h-3;
    SDL_Rect cnRect={languageBaseRect.x,languageBaseRect.y,AppData.textS_cn->w,AppData.textS_cn->h};
    languageBaseRect.x+=(AppData.textS_cn->w+AppData.controlSurface_temp->w*0.015);languageBaseRect.y=AppData.controlSurface_temp->h-AppData.textS_jp->h-3;
    SDL_Rect jpRect={languageBaseRect.x,languageBaseRect.y,AppData.textS_jp->w,AppData.textS_jp->h};
    addArea(&AppData.controlAreaList,"\0",enRect,clickEnCallback);
    addArea(&AppData.controlAreaList,"\0",cnRect,clickCnCallback);
    addArea(&AppData.controlAreaList,"\0",jpRect,clickJpCallback);

    SDL_Rect applyRect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW-ApplyButtonW-2,AppData.controlSurface_temp->h*0.85,ApplyButtonW,ApplyButtonH};
    SDL_Rect settingRect={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW,AppData.controlSurface_temp->h*0.85,SettingButtonW,SettingButtonH};
    addArea(&AppData.controlAreaList,"\0",applyRect,clickApplyCallback);
    addArea(&AppData.controlAreaList,"\0",settingRect,clickSettingCallback);
    //===============Add Area================


    // genPig(800,100);genPig(1200,100);genPig(1600,100);
    PigNode* pig1=NULL;
    PigNode* pig2=NULL;
    PigNode* pig3=NULL;
    PigNode* pig4=NULL;
    PigNode* pig5=NULL;
    // AppData.moveMode='l';
    // AppData.speed='1';

    int frameCount = 0;
    Uint32 startTime = SDL_GetTicks();
    Uint32 lastFrameTime = SDL_GetTicks();
    
    int QUIT = 0;
    SDL_Event e;
    while (!QUIT)
    {
        while (SDL_PollEvent(&e))
        {   
            if(e.type==SDL_WINDOWEVENT)
            {
                if (e.window.event==SDL_WINDOWEVENT_CLOSE)
                {
                    QUIT=1;
                }
                else if (e.window.event==SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    // AppData.controlSurface = SDL_GetWindowSurface(AppData.controlWindow);
                    // AppData.scrnSurface = SDL_GetWindowSurface(AppData.scrnWindow);
                    // AppData.preSurface=SDL_GetWindowSurface(AppData.preWindow);
                }


            }
            if (AppData.appMode=='s')
            {
                if (e.type==SDL_MOUSEMOTION)
                {
                    if (AppData.bufferTime_flag==0)
                    {
                        if (e.motion.xrel>1||e.motion.yrel>1)
                        {
                            QUIT=1;
                        }
                    }
                      
                }
                else if (e.type==SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEBUTTONUP)
                {
                    QUIT=1;
                }
                else if (e.type==SDL_KEYDOWN || e.type==SDL_KEYUP)
                {
                    QUIT=1;
                }
                //手柄
            }

            
            
        }
        
        
        if(AppData.appMode=='c' || AppData.appMode=='m')
        {
            SDL_SetRenderTarget(AppData.tmp_cpl_renderer,AppData.controlTexture_temp);

            drawBottom();
            drawTopbar();
            drawLogo();
            drawCloseButton(0);
            drawLanguageButton();
            drawApplyButton(0);
            drawSettingButton(0);
            drawStartButton(0);
            drawEyeButton(0);
            drawHideButton(0);
            

            SDL_Rect titleRect={WINDOW_W*0.02*2,WINDOW_H*0.012+WINDOW_H*0.05/2-AppData.textS_title->h/2.0*0.85,AppData.textS_title->w,AppData.textS_title->h};
            //SDL_BlitSurface(AppData.textS_title,NULL,AppData.controlSurface_temp,&titleRect);
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_title,NULL,&titleRect);

            SDL_Rect textR={AppData.controlSurface_temp->w*0.02,AppData.controlSurface_temp->h*0.075,AppData.textS_path->w,AppData.textS_path->h};
            //SDL_BlitSurface(AppData.textS_path,NULL,AppData.controlSurface_temp,&textR);
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_path,NULL,&textR);
            textR.x=AppData.controlSurface_temp->w/4-AppData.textS_line->w/2;textR.y=AppData.controlSurface_temp->h*0.325;
            //SDL_BlitSurface(AppData.textS_line,NULL,AppData.controlSurface_temp,&textR);
            textR.w=AppData.textS_line->w;textR.h=AppData.textS_line->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_line,NULL,&textR);
            textR.x=AppData.controlSurface_temp->w/4*3-AppData.textS_random->w/2;textR.y=AppData.controlSurface_temp->h*0.325;
            //SDL_BlitSurface(AppData.textS_random,NULL,AppData.controlSurface_temp,&textR);
            textR.w=AppData.textS_random->w;textR.h=AppData.textS_random->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_random,NULL,&textR);
            textR.x=AppData.controlSurface_temp->w*0.02;textR.y=AppData.controlSurface_temp->h*0.375;
            // SDL_BlitSurface(AppData.textS_speed,NULL,AppData.controlSurface_temp,&textR);
            textR.w=AppData.textS_speed->w;textR.h=AppData.textS_speed->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_speed,NULL,&textR);

            /*字体绘制测试
            // SDL_Rect a={0,30,0,0};
            // SDL_BlitSurface(textSurface1,NULL,AppData.controlSurface_temp,&a);
            // a.y+=30;
            // SDL_BlitSurface(textSurface2,NULL,AppData.controlSurface_temp,&a);
            // a.y+=30;
            // SDL_BlitSurface(textSurface3,NULL,AppData.controlSurface_temp,&a);
            // a.y+=30;
            // SDL_BlitSurface(textSurface4,NULL,AppData.controlSurface_temp,&a);
            // a.y+=30;
            // SDL_BlitSurface(textSurface5,NULL,AppData.controlSurface_temp,&a);
            // a.y+=30;
            // SDL_BlitSurface(textSurface6,NULL,AppData.controlSurface_temp,&a);
            */
            
            int w1 = AppData.controlSurface_temp->w/2*0.8;int h1=AppData.controlSurface_temp->w/2*0.8*0.618;
            int gap1=w1*0.035;
            // SDL_Rect LR={(AppData.controlSurface_temp->w/2-w1)/2,AppData.controlSurface_temp->h*0.16,w1,h1};
            // SDL_Rect RR={(AppData.controlSurface_temp->w/2-w1)/2*3+w1,AppData.controlSurface_temp->h*0.16,w1,h1};
            // draw98button(LR,1,AppData.controlSurface_temp);
            // draw98button(RR,1,AppData.controlSurface_temp);
            if(AppData.moveMode=='r')
            {
                //fillpixels((AppData.controlSurface_temp->w/2-w1)/2*3+w1-gap1          ,AppData.controlSurface_temp->h*0.16-gap1  ,w1+gap1*2,h1+gap1*2  ,AppData.controlSurface_temp,64,72,200);

                SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,64,72,200,255);
                SDL_Rect r={(AppData.controlSurface_temp->w/2-w1)/2*3+w1-gap1,AppData.controlSurface_temp->h*0.16-gap1,w1+gap1*2,h1+gap1*2};
                SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r);
            }
            else 
            {
                // fillpixels((AppData.controlSurface_temp->w/2-w1)/2-gap1          ,AppData.controlSurface_temp->h*0.16-gap1  ,w1+gap1*2,h1+gap1*2  ,AppData.controlSurface_temp,64,72,200);

                SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,64,72,200,255);
                SDL_Rect r={(AppData.controlSurface_temp->w/2-w1)/2-gap1,AppData.controlSurface_temp->h*0.16-gap1,w1+gap1*2,h1+gap1*2};
                SDL_RenderFillRect(AppData.tmp_cpl_renderer,&r);
            }
            // fillpixels((AppData.controlSurface_temp->w/2-w1)/2           ,AppData.controlSurface_temp->h*0.16   ,w1 ,h1   ,AppData.controlSurface_temp,0,0,0);
            // // fillpixels((AppData.controlSurface_temp->w/2-w1)/2*3+w1-5   ,AppData.controlSurface_temp->h*0.16-5  ,w1+10,h1+10  ,AppData.controlSurface_temp,64,72,200);
            // fillpixels((AppData.controlSurface_temp->w/2-w1)/2*3+w1    ,AppData.controlSurface_temp->h*0.16   ,w1 ,h1   ,AppData.controlSurface_temp,0,0,0);

            SDL_SetRenderDrawColor(AppData.tmp_cpl_renderer,0,0,0,255);
            SDL_Rect rect_linemode={(AppData.controlSurface_temp->w/2-w1)/2,AppData.controlSurface_temp->h*0.16,w1,h1};
            SDL_Rect rect_curvemode={(AppData.controlSurface_temp->w/2-w1)/2*3+w1,AppData.controlSurface_temp->h*0.16,w1,h1};
            SDL_RenderFillRect(AppData.tmp_cpl_renderer,&rect_linemode);
            SDL_RenderFillRect(AppData.tmp_cpl_renderer,&rect_curvemode);

            
            
            int gap_ui=AppData.controlSurface_temp->w/5;
            SDL_Rect uir={gap_ui/2,AppData.controlSurface_temp->h*0.455,32,32};SDL_Rect textr={gap_ui/2,AppData.controlSurface_temp->h*0.455+32*1.05};
            uir.x-=(uir.w/2);textr.x=gap_ui/2*1-AppData.textS_1->w/2;
            // SDL_BlitScaled(ui,NULL,AppData.controlSurface_temp,&uir);
            // SDL_BlitSurface(AppData.textS_1,NULL,AppData.controlSurface_temp,&textr);

            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.ui_T,NULL,&uir);
            textr.w=AppData.textS_1->w;textr.h=AppData.textS_1->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_1,NULL,&textr);

            uir.x+=gap_ui;   textr.x=gap_ui/2*3-AppData.textS_2->w/2;
            // SDL_BlitScaled(ui,NULL,AppData.controlSurface_temp,&uir);
            // SDL_BlitSurface(AppData.textS_2,NULL,AppData.controlSurface_temp,&textr);

            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.ui_T,NULL,&uir);
            textr.w=AppData.textS_2->w;textr.h=AppData.textS_2->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_2,NULL,&textr);

            uir.x+=gap_ui;   textr.x=gap_ui/2*5-AppData.textS_3->w/2;
            // SDL_BlitScaled(ui,NULL,AppData.controlSurface_temp,&uir);
            // SDL_BlitSurface(AppData.textS_3,NULL,AppData.controlSurface_temp,&textr);

            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.ui_T,NULL,&uir);
            textr.w=AppData.textS_3->w;textr.h=AppData.textS_3->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_3,NULL,&textr);

            uir.x+=gap_ui;   textr.x=gap_ui/2*7-AppData.textS_4->w/2;
            // SDL_BlitScaled(ui,NULL,AppData.controlSurface_temp,&uir);
            // SDL_BlitSurface(AppData.textS_4,NULL,AppData.controlSurface_temp,&textr);

            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.ui_T,NULL,&uir);
            textr.w=AppData.textS_4->w;textr.h=AppData.textS_4->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_4,NULL,&textr);

            uir.x+=gap_ui;   textr.x=gap_ui/2*9-AppData.textS_5->w/2;
            // SDL_BlitScaled(ui,NULL,AppData.controlSurface_temp,&uir);
            // SDL_BlitSurface(AppData.textS_5,NULL,AppData.controlSurface_temp,&textr);

            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.ui_T,NULL,&uir);
            textr.w=AppData.textS_5->w;textr.h=AppData.textS_5->h;
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.text_T_5,NULL,&textr);

            char str[2]={0};str[0]=AppData.speed;
            uir.x-=gap_ui*(5-atoi(str));//选中项位置计算
            // SDL_BlitScaled(ui2,NULL,AppData.controlSurface_temp,&uir);//绘制选中项
            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.ui2_T,NULL,&uir);

            //SDL_BlitSurface(L_ani,&L_ani_Rect,AppData.controlSurface,NULL);
            SDL_Rect r1={(AppData.controlSurface_temp->w/2-w1)/2           ,AppData.controlSurface_temp->h*0.16   ,w1 ,h1   };
            SDL_Rect r2={(AppData.controlSurface_temp->w/2-w1)/2*3+w1    ,AppData.controlSurface_temp->h*0.16   ,w1 ,h1   };
            // SDL_BlitScaled(L_ani,&L_ani_Rect,AppData.controlSurface_temp,&r1);//太蠢了,直接在源上缩放啊,循环里就Blit,减少性能消耗
            // // SDL_BlitScaled(AppData.RAni_tempSurface,NULL,AppData.controlSurface,&r2);
            // //printf("E:%s\n",SDL_GetError());
            // SDL_BlitSurface(Rplay->animation->frame[Rplay->counter].surface,NULL,AppData.controlSurface_temp,&r2);

            SDL_RenderCopy(AppData.tmp_cpl_renderer,AppData.L_ani_T,&L_ani_Rect,&r1);
            SDL_RenderCopy(AppData.tmp_cpl_renderer,Rplay->animation->frame[Rplay->counter].texture,NULL,&r2);

        }
        





        //窗口已改为一个，不再需要判断哪个窗口
        // if(SDL_GetMouseFocus()==AppData.controlWindow)CheckMouse(AppData.controlAreaList);
        // RunJob(AppData.joblist);
        
        if (AppData.appMode=='c' || AppData.appMode=='m')
        {
            if (AppData.hide_flag==1)
            {
                CheckMouse(AppData.noplaneAreaList);
            }
            else CheckMouse(AppData.controlAreaList);

        }
        //if (AppData.appMode=='c')CheckMouse(AppData.controlAreaList);

        RunJob(AppData.joblist);

        if(AppData.appMode=='c' || AppData.appMode=='m')SDL_SetRenderTarget(AppData.tmp_cpl_renderer,NULL);
        if(AppData.appMode=='c')
        {
            // SDL_BlitSurface(AppData.controlSurface_temp,NULL,AppData.controlSurface,NULL);
            // SDL_UpdateWindowSurface(AppData.controlWindow);

            SDL_Rect r={0,0,AppData.controlSurface_temp->w,AppData.controlSurface_temp->h};
            SDL_RenderCopy(AppData.theRenderer,AppData.controlTexture_temp,NULL,&r);
            SDL_RenderPresent(AppData.theRenderer);
        }
        else if(AppData.appMode=='m' || AppData.appMode=='s')
        {
            //===============Pig===================
            int base_b=0.5*AppData.scrn_rect.h-0.5*AppData.k*AppData.scrn_rect.w;//过中心点的线的b
            pig1=PigStream(1.2*AppData.scrn_rect.w,1.2*AppData.scrn_rect.w*AppData.k+base_b-base_b*0.33333*2,AppData.scrn_rect.w*0.5,pig1);
            pig2=PigStream(1.2*AppData.scrn_rect.w,1.2*AppData.scrn_rect.w*AppData.k+base_b-base_b*0.33333*1,AppData.scrn_rect.w*0.35,pig2);
            pig3=PigStream(1.2*AppData.scrn_rect.w,1.2*AppData.scrn_rect.w*AppData.k+base_b,AppData.scrn_rect.w*0.3,pig3);
            pig4=PigStream(1.2*AppData.scrn_rect.w,1.2*AppData.scrn_rect.w*AppData.k+base_b+base_b*0.33333*1,AppData.scrn_rect.w*0.35,pig4);
            pig5=PigStream(1.2*AppData.scrn_rect.w,1.2*AppData.scrn_rect.w*AppData.k+base_b+base_b*0.33333*2,AppData.scrn_rect.w*0.5,pig5);
            Update(AppData.pigs,AppData.moveMode,SDL_GetTicks()-lastFrameTime);
            lastFrameTime = SDL_GetTicks();
            // SDL_FillRect(AppData.scrnSurface,NULL,SDL_MapRGB(AppData.scrnSurface->format,0,0,0));
            SDL_SetRenderDrawColor(AppData.theRenderer,0,0,0,255);
            SDL_RenderClear(AppData.theRenderer);
            // drawItems(AppData.items,AppData.scrnSurface);
            // drawPigs(AppData.pigs,AppData.scrnSurface);
            drawItems(AppData.items,NULL);
            drawPigs(AppData.pigs,NULL);
            //drawEffects(AppData.effects,AppData.scrnSurface);
            //===============Pig===================
            if(AppData.appMode=='m')
            {
                
                if(AppData.hide_flag==1)
                {
                    SDL_Rect logot={AppData.scrn_rect.w-AppData.logo->w,AppData.scrn_rect.h-AppData.logo->h,AppData.logo->w,AppData.logo->h};
                    // SDL_BlitSurface(AppData.logo,NULL,AppData.scrnSurface,&logot); 
                    SDL_RenderCopy(AppData.theRenderer,AppData.logo_T,NULL,&logot);
                }
                else 
                {
                    // SDL_BlitSurface(AppData.controlSurface_temp,NULL,AppData.scrnSurface,&AppData.CWrect); //AppData.CWrect是否会被修改？是否会有影响？ yes,blit和rendercopy有差异
                    SDL_RenderCopy(AppData.theRenderer,AppData.controlTexture_temp,NULL,&AppData.CWrect);
                }
            }
            //SDL_UpdateWindowSurface(AppData.scrnWindow);
            SDL_RenderPresent(AppData.theRenderer);
        }
        else if(AppData.appMode=='p')
        {
            // printf("================ E:%s ================\n",SDL_GetError());
            int base_b=0.5*AppData.pre_rect.h-0.5*AppData.k*AppData.pre_rect.w;//过中心点的线的b

            //printf("\nPre base_b:%d W:%d H:%d\n",base_b,AppData.preSurface->w,AppData.preSurface->h);

            pig1=PigStream(1.2*AppData.pre_rect.w,1.2*AppData.pre_rect.w*AppData.k+base_b-base_b*0.33333*2,AppData.pre_rect.w*0.5,pig1);
            pig2=PigStream(1.2*AppData.pre_rect.w,1.2*AppData.pre_rect.w*AppData.k+base_b-base_b*0.33333*1,AppData.pre_rect.w*0.35,pig2);
            pig3=PigStream(1.2*AppData.pre_rect.w,1.2*AppData.pre_rect.w*AppData.k+base_b,AppData.pre_rect.w*0.3,pig3);
            pig4=PigStream(1.2*AppData.pre_rect.w,1.2*AppData.pre_rect.w*AppData.k+base_b+base_b*0.33333*1,AppData.pre_rect.w*0.35,pig4);
            pig5=PigStream(1.2*AppData.pre_rect.w,1.2*AppData.pre_rect.w*AppData.k+base_b+base_b*0.33333*2,AppData.pre_rect.w*0.5,pig5);
            Update(AppData.pigs,AppData.moveMode,SDL_GetTicks()-lastFrameTime);
            lastFrameTime = SDL_GetTicks();
            // printf("================ now ================\n");
            // system("pause");
            // SDL_FillRect(AppData.preSurface,NULL,SDL_MapRGB(AppData.preSurface->format,0,0,0));
            SDL_SetRenderDrawColor(AppData.theRenderer,0,0,0,255);
            SDL_RenderClear(AppData.theRenderer);

                // SDL_Rect testR={0,0,50,50};
                // SDL_FillRect(AppData.preSurface,&testR,SDL_MapRGB(AppData.preSurface->format,0,255,0));
            // drawItems(AppData.items,AppData.preSurface);
            // drawPigs(AppData.pigs,AppData.preSurface);
            drawItems(AppData.items,NULL);
            drawPigs(AppData.pigs,NULL);
            // //drawEffects(AppData.effects,AppData.preSurface);
            //SDL_UpdateWindowSurface(AppData.preWindow);
            SDL_RenderPresent(AppData.theRenderer);
        }
        

        //int x9,y9;SDL_GetMouseState(&x9, &y9);printf("\nmouse:%d %d f:%d w1:%d w2:%d\n",x9,y9,SDL_GetMouseFocus(),AppData.controlWindow,AppData.scrnWindow);
        frameCount++;
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime >= 1000)
        {
            float fps = frameCount / (elapsedTime / 1000.0f);
            printf("FPS: %.2f ", fps);
            printf("Erro:%s ",SDL_GetError());

            
            // typedef struct pignode
            // {
            //     Uint8 type_id; // 111 dont_show 0 fly_pig 1 rocket_pig 2 balloon_pig 3 fly_pig_light 4 rocket_pig_light 5 balloon_pig_light 6 fly_pig(BIG) 7 rocket_pig(BIG) 8 balloon_pig(BIG) 9 fly_pig_light(BIG) 10 rocket_pig_light(BIG) 11 balloon_pig_light(BIG)
            //     float x, y;
            //     Play *ani;
            //     float RandSin_Xzoom;
            //     float RandSin_Yzoom;
            //     float RandSin_p;
            //     // float RandSin_gap;
            //     // float RandSin_times;
            //     struct pignode *next;
            // } PigNode;
            // typedef struct itemnode
            // {
            //     Uint8 id;
            //     SDL_Rect pos;
            //     Play *record;
            //     struct itemnode *next;

            // } ItemNode;
            // // typedef struct effectnode
            // // {
            // //     Uint8 id;
            // //     PigNode *pig;
            // //     Play *record;
            // //     struct effectnode *next;

            // // } EffectNode;
            // typedef struct jobnode
            // {
            //     void (*fun)(void *data);
            //     void *data;
            //     struct jobnode *next;
            // } JobNode;

            // int count_pig=0;
            // PigNode *pigs=AppData.pigs;
            // while (pigs != NULL)
            // {  
            //     count_pig++;
            //     printf(" (%.1f,%.1f) ",pigs->x,pigs->y);
            //     pigs = pigs->next;
            // }
            // printf("Pigs:%d ",count_pig);

            // int count_item=0;
            // ItemNode *items=AppData.items;
            // while (items != NULL)
            // {  
            //     count_item++;
            //     items = items->next;
            // }
            // printf("Items:%d ",count_item);

            // // int count_effect=0;
            // // EffectNode *effects=AppData.effects;
            // // while (effects != NULL)
            // // {  
            // //     count_effect++;
            // //     effects = effects->next;
            // // }
            // // printf("Effects:%d ",count_effect);

            // int count_job=0;
            // JobNode *jobs=AppData.joblist;
            // while (jobs != NULL)
            // {  
            //     count_job++;
            //     jobs = jobs->next;
            // }
            // printf("Jobs:%d ",count_job);

            printf("\n");

            frameCount = 0;
            startTime = SDL_GetTicks();
        }
        // SDL_Delay(1000/90);
    }


    /*
    free xxxxxx
    */
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}




typedef struct pignode {
    Uint8 type_id; //111 dont_show 0 fly_pig 1 rocket_pig 2 balloon_pig 3 fly_pig_light 4 rocket_pig_light 5 balloon_pig_light 6 fly_pig(BIG) 7 rocket_pig(BIG) 8 balloon_pig(BIG) 9 fly_pig_light(BIG) 10 rocket_pig_light(BIG) 11 balloon_pig_light(BIG)
    float x,y;
    Play* ani;
    float RandSin_Xzoom;
    float RandSin_Yzoom;
    float RandSin_p;
    //float RandSin_gap;
    //float RandSin_times;
    struct pignode* next;
}PigNode;

// 在链表末尾添加一个节点
void appendPigNode(PigNode** head, PigNode* newNode) {
    PigNode* p = *head;
    if(p!=NULL)
    {
       while (p->next != NULL) {
        p = p->next;
       }
       p->next = newNode;
    }
    else
    {
       *head = newNode;
    }
}

// 删除链表中指定位置的节点
void deletePigNode(PigNode** headP, PigNode* nodeToDel) {
    PigNode* p = *headP;
    if (p==NULL||nodeToDel==NULL)return;
    if (nodeToDel==p)
    {
        *headP=p->next;
        free(nodeToDel);
        return;
    }
    while (p->next != NULL && p->next != nodeToDel) {
        p = p->next;
    }
    if (p->next == NULL) {
        return;
    }

    PigNode* q=p->next;
    p->next=q->next;
    free(q);
    return;
}

PigNode* createPig(int x,int y,int typeid)
{
    PigNode* newpig=malloc(sizeof(PigNode));
    memset(newpig,0,sizeof(PigNode));

    newpig->type_id=typeid;

    if (newpig->type_id==0)newpig->ani=playAnimation(&pig_ani_fly,1,1);
    else if(newpig->type_id==1)newpig->ani=playAnimation(&pig_ani_rocket,1,1);
    else if(newpig->type_id==2)newpig->ani=playAnimation(&pig_ani_balloon,1,1);
    else if(newpig->type_id==3)newpig->ani=playAnimation(&pig_ani_fly_light,1,1);
    else if(newpig->type_id==4)newpig->ani=playAnimation(&pig_ani_rocket_light,1,1);
    else if(newpig->type_id==5)newpig->ani=playAnimation(&pig_ani_balloon_light,1,1);
       
    newpig->x=x;
    newpig->y=y;
    newpig->RandSin_Xzoom=(100+50*(rand()%5))/100.0;
    newpig->RandSin_Yzoom=(100+50*(rand()%5))/100.0;
    newpig->next=NULL;
    appendPigNode(&AppData.pigs,newpig);
    return newpig;
}

PigNode* genPig(int x,int y)
{
    PigNode* newpig=malloc(sizeof(PigNode));
    memset(newpig,0,sizeof(PigNode));

    int random_number=rand()%100;
    if (random_number>90)newpig->type_id=2;
    else if (random_number>80)newpig->type_id=1;
    else newpig->type_id=0;

    if (newpig->type_id==0)newpig->ani=playAnimation(&pig_ani_fly,1,1);
    else if(newpig->type_id==1)newpig->ani=playAnimation(&pig_ani_rocket,1,1);
    else if(newpig->type_id==2)newpig->ani=playAnimation(&pig_ani_balloon,1,1);
    
    //  ? 好像不修正,偏移一点观感好一点,不会太密?
    newpig->x=x-newpig->ani->animation->frame[0].surface->w/2;   //?神秘卡顿 定时器回调 线程锁?  ...??直接给值也卡,渲染范围的问题?统计下数量  结论:pigs太密导致无法生成item遂陷入重试的死循环
    newpig->y=y-newpig->ani->animation->frame[0].surface->h/2;
    newpig->RandSin_Xzoom=(100+50*(rand()%5))/100.0;
    newpig->RandSin_Yzoom=(100+50*(rand()%5))/100.0;
    newpig->next=NULL;
    appendPigNode(&AppData.pigs,newpig);
    return newpig;
}

PigNode* PigStream(int initX,int initY,int gap,PigNode* thePig) //todo:添加出生点随机漂移功能，增加最大漂移值参数（如果为0相当于不漂移） add:动画状态漂移   增加随机感
{
    int randvalue=(rand()-rand())%66*AppData.zoom*1.3;//printf("randvalue:%d\n",randvalue);
    //printf("\ninitX-gap:%d initX:%d gap:%d randvalue:%d\n",initX-gap,initX,gap,randvalue);
    if (thePig==NULL)
    {
        return genPig(initX+randvalue,initY+randvalue);
    }
    if (thePig->x < (initX-gap))//*AppData.zoom !我操了,这里不需要缩放,因为我gap参数填的就是w*0.25,而不是写死的,我说怎么换分辨率不对劲了
    {
        return genPig(initX+randvalue,initY+randvalue);
    }
    return thePig;
}

void deletePig(PigNode** headP,PigNode* nodeToDel)
{
    freePlay(nodeToDel->ani);
    deletePigNode(headP,nodeToDel);
}

void movePig(float x_offset,float y_offset,PigNode* pig) //改变小猪坐标
{
    char str[2]={0};
    str[0]=AppData.speed;
    float speed=atoi(str)*0.75*0.75;
    //再根据屏幕尺寸进行速度校准,W*1%？
    float size_map=1;
    if (AppData.appMode!='p')size_map=AppData.scrn_rect.w/2560.0;
    else size_map=AppData.pre_rect.w/2560.0;

    pig->x+=x_offset*speed*size_map;
    pig->y+=y_offset*speed*size_map;
    if (AppData.appMode!='p')
    {
        if (pig->x<(-AppData.scrn_rect.w*0.5)||pig->y>(AppData.scrn_rect.h*1.5))//todo全方向超出判断
        {
            deletePig(&AppData.pigs,pig);
        }
        else
        {
            ItemNode* item = NULL;
            item = checkHit_list(pig,AppData.items);
            if (item != NULL)HitHandle(item,pig);
        }
    }
    else
    {
        if (pig->x<(-AppData.pre_rect.w*0.5)||pig->y>(AppData.pre_rect.h*1.5))//todo全方向超出判断
        {
            deletePig(&AppData.pigs,pig);
        }
        else
        {
            ItemNode* item = NULL;
            item = checkHit_list(pig,AppData.items);
            if (item != NULL)HitHandle(item,pig);
        }
    }
    
    
}

void Update(PigNode* pigs,char mode,Uint32 time)
{
    SDL_SemWait(AppData.itemCallbackLock);
    static int f_count=0;

    //if(moveMode==?)...
    //printf("\n");
    while (pigs != NULL)
    {   //printf("P ");

        //制造浮动效果
        // switch (f_count)
        // {
        //     case 0:时间相关的位移而不是直接操作会与帧数相关;f_count++;break;
        //     case 1:f_count++;break;
        //     case 2:f_count=0;break;
        //     default:break;
        // }

        PigNode* tmp;
        tmp = pigs;
        pigs = pigs->next; // 先保存好下一节点指针，以防节点被删找不到下一节点（free后内存被格式化）
        if (mode == 'r')RandSin(tmp,time);
        else movePig((time/5.0) * -0.75, (time/5.0) * -0.75 * AppData.k, tmp);

        //检测item碰撞不宜放在这里,如果上面更新位置时删除了,这边就会段错误了
    }
    //printf("\n");
    SDL_SemPost(AppData.itemCallbackLock);
}

void drawPigs(PigNode* pigs,SDL_Surface* dst)
{
    while (pigs != NULL)
    {  
        if(pigs->type_id!=111)
        {
            SDL_Rect pos={pigs->x,pigs->y,pigs->ani->animation->frame[0].surface->w,pigs->ani->animation->frame[0].surface->h};
            // //SDL_BlitSurface(AppData.logo,NULL,AppData.scrnSurface,&pos);
            // SDL_BlitSurface(pigs->ani->animation->frame[pigs->ani->counter].surface,NULL,dst,&pos);
            SDL_RenderCopy(AppData.theRenderer,pigs->ani->animation->frame[pigs->ani->counter].texture,NULL,&pos);
        }
        
        pigs = pigs->next;
    }
}


void freePig() //好像没用？
{

}

void RandSin(PigNode* pigs,Uint32 time)
{
    if (pigs->RandSin_p>=M_PI*2)
    {
        pigs->RandSin_p=0;
        pigs->RandSin_Xzoom=(100+50*(rand()%5))/100.0;//(100+rand()%300)/100.0
        pigs->RandSin_Yzoom=(100+50*(rand()%5))/100.0;//(100+rand()%300)/100.0
    }
    
    float temp=sin(pigs->RandSin_p);
    pigs->RandSin_p+=M_PI/180*1;

    // pigs->x-=M_PI/180*1;
    // pigs->y-=cos(pigs->RandSin_p)-temp;
    //movePig(-100*M_PI/180*1,-100*(cos(pigs->RandSin_p)-temp),pigs);

    double radian=atan(AppData.k);
    float x1=pigs->RandSin_p-M_PI/180*1;float y1=temp;                  x1*=pigs->RandSin_Xzoom;y1*=pigs->RandSin_Yzoom;
    float x2=pigs->RandSin_p;           float y2=sin(pigs->RandSin_p);  x2*=pigs->RandSin_Xzoom;y2*=pigs->RandSin_Yzoom;
    float x_offset=(x2*cos(radian)-y2*sin(radian))-(x1*cos(radian)-y1*sin(radian));//x_offset*=pigs->RandSin_Xzoom;
    float y_offset=(x2*sin(radian)+y2*cos(radian))-(x1*sin(radian)+y1*cos(radian));//y_offset*=pigs->RandSin_Yzoom;
    movePig((time/5.0)*-30*x_offset,(time/5.0)*-30*y_offset,pigs);
    // movePig(-50*x_offset*((100+rand()%200)/100.0),-50*y_offset*((100+rand()%200)/100.0),pigs);
}

int checkApply()
{
    //启用返回1,未启用返回0
    int returnValue=0;
    HKEY hkey;
    RegOpenKeyEx(HKEY_CURRENT_USER,"Control Panel\\Desktop",0,KEY_QUERY_VALUE,&hkey);

    char self_path[MAX_PATH]={0};
    char reg_path[MAX_PATH]={0};
    long unsigned int reg_path_size=MAX_PATH;

    //验证屏幕保护程序路径
    if(ERROR_SUCCESS==RegGetValue(hkey,NULL,"SCRNSAVE.EXE",RRF_RT_REG_SZ,NULL,reg_path,&reg_path_size))
    {
        GetModuleFileName(NULL,self_path,MAX_PATH);
        if (!strcmp(self_path,reg_path))
        {
            //验证是否启用屏保功能
            char str[2]={0};
            long unsigned int str_size=sizeof(str);

            if (ERROR_SUCCESS == RegGetValue(hkey,NULL,"ScreenSaveActive",RRF_RT_REG_SZ,NULL,str,&str_size))
            {
                if (!strcmp("1", str))
                {
                    returnValue = 1;
                }
            }
        }
        
        
    }

    RegCloseKey(hkey);
    return returnValue;
}

Uint32 checkApplyCallback(Uint32 interval, void *param) //定时器回调 然后还要去改画图逻辑
{
    AppData.apply_flag=checkApply();
    return interval;
}

//todo 显示模式及其控制（屏保模式（显示屏保动画以及当有输入时关闭）、手动模式（单控制面板、控制面板和屏保动画混合、控制面板最小化（缩为屏保动画右下角的logo）、跳转为屏保模式）） 窗口合并（同一窗口下绘制屏保动画和控制面板）
//     多屏幕支持
//     速度差异。速度一样，太统一太死板。（pig新建speed成员，updatepig修改）
// 三消- !!!游戏性！ 通过运动模式切换来干预猪的位置，当三个猪连成一个直线时可以消除，实现这个功能并设置相应的成就，增加趣味性

//流星召唤
void callMeteor()
{

}





//todo 曲线模式的高度变化其实和动画中的翅膀摆动并不同步,有违和感

//todo 把自己写着玩的fillpixels替换成更Pro的SDL_FillRect

// 流星 Meteor 是指运行在星际空间的流星体（通常包括宇宙尘埃和固体块等空间物质）接近地球时被地球引力吸引，在高速穿越地球大气层时发生电子跃迁所产生的光迹。
// 陨星 流星体经过地球大气层时没有完全烧毁而落在地面上的部分叫作陨星。含铁质多的叫陨铁，含石质多的叫陨石。


//屏保启动后关于桌面的状态,是进入一个独立的环境还是仍然使用原来的桌面背景,是否和设置屏幕保护状态的系统函数有关系？ 这是个关键问题对于具有透明属性的屏保程序来说

//容错！ 沉默期、无响应  进入ScreenSave Mode后刚开始的一段时间内应忽略鼠标移动,防止不经意间移动鼠标造成的立刻退出