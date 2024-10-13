//不合理：clickxxx函数实际上不仅处理点击，也会对悬停作出反应，有违字面意思（但是我不改，先这么用着吧）
/*
    新设计： ButtonA(Uint8 state)
            {
                state 0(悬停),1(按住),2(松开-原位),3(松开-异位) !!改成宏！

                if(state == ...)
                {
                    ...
                }
                else ...
                ...
            }
*/
#include <stdio.h>
#include <SDL.h>
#include <windows.h>
#include "control.h"
#include "window.h"
#include "animation.h"

void AppInit(char mode);

void drawCloseButton(Uint8 colormode);
void drawSettingButton(Uint8 colormode);
void drawApplyButton(Uint8 colormode);
void drawStartButton(Uint8 colormode);
void drawEyeButton(Uint8 colormode);
void drawHideButton(Uint8 colormode);


struct appdata AppData={0};

//KeyContext
#define SceneA (1U << 0)
#define SceneB (1U << 1)
#define SceneC (1U << 2)


typedef struct jobnode {
    void (*fun)(void* data);
    void* data;
    struct jobnode* next;
}JobNode;

//创建空列表
//JobNode* list=NULL;

typedef struct areanode {
    char* name;
    SDL_Rect area;
    void (*callback)(Uint32 state);
    void* data;
    struct areanode* next;
}AreaNode;

struct AppSettings
{
    char mode;
    char Lv;
    char language;
};

int CheckHit(SDL_Rect A,SDL_Rect B)
{
    
}

void GetInput()
{
    const Uint8* state=SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A])
    {
        printf("!\n");
    }
    
}



void CheckMouse(AreaNode* list)
{   
    if (!SDL_GetMouseState(NULL,NULL))AppData.ClickLock=0; //松开置0
    
    if (AppData.ClickLock==1)return;
    
    if(SDL_GetMouseState(NULL,NULL))AppData.ClickLock=1; //锁定

    while (list != NULL)
    {
        int x, y;
        Uint32 state;
        state = SDL_GetMouseState(&x, &y);
        if(AppData.appMode!='c' && AppData.hide_flag!=1) //混合模式时转换成相对坐标
        {
            x-=AppData.CWrect.x;
            y-=AppData.CWrect.y;
        }

        if (x >= list->area.x && x <= list->area.x + list->area.w)
        {
            if (y >= list->area.y && y <= list->area.y + list->area.h)
            {
                if (list->callback != NULL)
                {
                    list->callback(state);
                }
                return;
            }
        }
        

        list = list->next;
    }
    

}




void clickTopBarCallback(Uint32 state)
{
    struct data
    {
        SDL_Window *window;
        JobNode *jobnode;
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        JobNode* job=NULL;
        if(AppData.appMode=='c')job=addJob(&AppData.joblist,dragWindow);
        else job=addJob(&AppData.joblist,dragWindow_m);

        d=malloc(sizeof(struct data));
        d->jobnode=job;
        d->window=AppData.controlWindow;

        job->data=d;
    }
    
    

}

void clickCloseCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        
        JobNode* job=addJob(&AppData.joblist,closeButton);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;

        job->data=d;
    }
    else
    {

        // fillpixels(AreaCloseX                          ,AreaCloseY                          ,AreaCloseW+1         ,AreaCloseH           ,wS,232,17,35);
        // fillpixels(CloseButtonX                        ,CloseButtonY                        ,CloseButtonPartLength,CloseButtonPartLength,wS,0,0,0);
        // fillpixels(CloseButtonX+CloseButtonPartLength*2,CloseButtonY                        ,CloseButtonPartLength,CloseButtonPartLength,wS,0,0,0);
        // fillpixels(CloseButtonX+CloseButtonPartLength  ,CloseButtonY+CloseButtonPartLength  ,CloseButtonPartLength,CloseButtonPartLength,wS,0,0,0);
        // fillpixels(CloseButtonX                        ,CloseButtonY+CloseButtonPartLength*2,CloseButtonPartLength,CloseButtonPartLength,wS,0,0,0);
        // fillpixels(CloseButtonX+CloseButtonPartLength*2,CloseButtonY+CloseButtonPartLength*2,CloseButtonPartLength,CloseButtonPartLength,wS,0,0,0);

        // int gap=((int)(WINDOW_H*0.05*0.8)-3*(int)(WINDOW_H*0.05*0.8*0.25))/2;
        // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_H*0.05*0.8,WINDOW_H*0.05*0.8,AppData.controlSurface_temp,232,17,35);
        // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap,WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap,WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
        // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap,WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
        // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
        // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap,WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);
        // fillpixels(WINDOW_W*0.02+WINDOW_W*0.96*0.92+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.012+WINDOW_H*0.05*0.1+gap+2*(int)(WINDOW_H*0.05*0.8*0.25),WINDOW_H*0.05*0.8*0.25,WINDOW_H*0.05*0.8*0.25,AppData.controlSurface_temp,0,0,0);

        drawCloseButton(1);
    }
    
    

}

void clickBtCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
    } *d;
    
    if (SDL_BUTTON_LMASK&state)
    {
        
        JobNode* job=addJob(&AppData.joblist,clickBt);


        d = malloc(sizeof(struct data));
        d->jobnode = job;

        job->data=d;
    }
}

void dragWindow(void *data)
{
    struct data
    {
        SDL_Window* window;
        JobNode* jobnode;
    }*d=data;



    
    static int x=-1,y=-1;//设为负值以跳过第一次执行
    int tempX,tempY,windowX,windowY;
    tempX=x;tempY=y;
    if (SDL_BUTTON_LMASK & SDL_GetGlobalMouseState(&x, &y))
    {   
        if(tempX<0)return;
        SDL_GetWindowPosition(d->window,&windowX,&windowY);
        windowX+=(x-tempX);windowY+=(y-tempY);
        SDL_SetWindowPosition(d->window,windowX,windowY);
    }
    else
    {
        deleteJob(&AppData.joblist,d->jobnode);
        x=-1,y=-1;
        
    }
}

void dragWindow_m(void *data)
{
    struct data
    {
        SDL_Window* window;
        JobNode* jobnode;
    }*d=data;



    
    static int x=-1,y=-1;//设为负值以跳过第一次执行
    int tempX,tempY;
    tempX=x;tempY=y;
    if (SDL_BUTTON_LMASK & SDL_GetGlobalMouseState(&x, &y))
    {   
        if(tempX<0)return;
        AppData.CWrect.x+=(x-tempX);AppData.CWrect.y+=(y-tempY);
    }
    else
    {
        deleteJob(&AppData.joblist,d->jobnode);
        x=-1,y=-1;
    }
}

void closeButton(void *data)
{
    struct data
    {
        JobNode *jobnode;
    } *d = data;

    drawCloseButton(2);

    SDL_Rect closeRect={WINDOW_W*0.02+WINDOW_W*0.96*0.92,WINDOW_H*0.012+WINDOW_H*0.05*0.1,WINDOW_H*0.05*0.8,WINDOW_H*0.05*0.8};
    if(AppData.appMode!='c')
    {
        closeRect.x+=AppData.CWrect.x;
        closeRect.y+=AppData.CWrect.y;
    }
    int x,y;
    if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
    {
        if ((x >= closeRect.x && x <= closeRect.x + closeRect.w)&&(y >= closeRect.y && y <= closeRect.y + closeRect.h))
        {
            SDL_Delay(100); // 防止关闭太快，添加氛围感
            exit(1);
        }
        deleteJob(&AppData.joblist, d->jobnode);
    }
}
Play* ppp;
void clickBt(void *data)
{
    struct data
    {
        JobNode *jobnode;
    } *d = data;

    SDL_Rect a;
    int x,y;
    if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
    {
        a.x = 100;              //仅测试，后续设计更好的实现 area作为成员整合进component
        a.y = 100;
        a.h = 50;
        a.w = 50;
        if ((x >= a.x && x <= a.x + a.w)&&(y >= a.y && y <= a.y + a.h))
        {
            printf("Ding!");//ppp->speed*=1.2;
        }
        deleteJob(&AppData.joblist, d->jobnode);

    }
}


void clickLineModeCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        char mode;
    } *d;
    
    if (SDL_BUTTON_LMASK&state)
    {
        
        JobNode* job=addJob(&AppData.joblist,changePathMode);


        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->mode = 'l';

        job->data = d;
    }
}

void clickRandModeCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        char mode;
    } *d;
    
    if (SDL_BUTTON_LMASK&state)
    {
        
        JobNode* job=addJob(&AppData.joblist,changePathMode);


        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->mode = 'r';

        job->data = d;
    }
}

void clickEnCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        char language;
    } *d;
    
    if (SDL_BUTTON_LMASK&state)
    {
        
        JobNode* job=addJob(&AppData.joblist,changeLanguage);


        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->language = 'e';

        job->data = d;
    }
}

void clickCnCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        char language;
    } *d;
    
    if (SDL_BUTTON_LMASK&state)
    {
        
        JobNode* job=addJob(&AppData.joblist,changeLanguage);


        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->language = 'c';

        job->data = d;
    }
}

void clickJpCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        char language;
    } *d;
    
    if (SDL_BUTTON_LMASK&state)
    {
        
        JobNode* job=addJob(&AppData.joblist,changeLanguage);


        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->language = 'j';

        job->data = d;
    }
}

void settings()//应用当前状态至配置文件
{
    FILE* config=fopen("config.txt","wb");
    struct AppSettings set;
    set.mode=AppData.moveMode;
    set.Lv=AppData.speed;
    set.language=AppData.language;

    fwrite(&set,sizeof(struct AppSettings),1,config);
    fclose(config);
}

void loadConfig()
{
    char tmpChar=-1;//不期望值
    FILE* file=fopen("config.txt","rb");
    
    fread(&tmpChar,1,1,file);
    if(tmpChar=='l' || tmpChar=='r')AppData.moveMode=tmpChar;
    else AppData.moveMode='l'; //当无法正确读取配置时的缺省行为
    tmpChar=-1;//复位，避免影响后续判断
    fread(&tmpChar,1,1,file);
    if(tmpChar=='1' || tmpChar=='2' || tmpChar=='3' || tmpChar=='4' || tmpChar=='5')AppData.speed=tmpChar;
    else AppData.speed='3';
    tmpChar=-1;
    fread(&tmpChar,1,1,file);
    if(tmpChar=='e' || tmpChar=='c' || tmpChar=='j')AppData.language=tmpChar;
    else AppData.language='e';
    tmpChar=-1;
    fclose(file);
    settings();//当内容不合法时起校正作用
}

void changePathMode(void *data)
{
    struct data
    {
        JobNode *jobnode;
        char mode;
    } *d = data;

    int w1 = AppData.controlSurface_temp->w / 2 * 0.8;
    int h1 = AppData.controlSurface_temp->w / 2 * 0.8 * 0.618;
    int gap1 = w1 * 0.035;

    SDL_Rect lineRect = {(AppData.controlSurface_temp->w / 2 - w1) / 2, AppData.controlSurface_temp->h * 0.16, w1, h1};
    SDL_Rect randRect = {(AppData.controlSurface_temp->w / 2 - w1) / 2 * 3 + w1, AppData.controlSurface_temp->h * 0.16, w1, h1};
    int x,y;
    if(AppData.appMode!='c')
    {
        lineRect.x+=AppData.CWrect.x;
        lineRect.y+=AppData.CWrect.y;
        randRect.x+=AppData.CWrect.x;
        randRect.y+=AppData.CWrect.y;
    }
    if (d->mode == 'l')
    {
        if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
        {

            if ((x >= lineRect.x && x <= lineRect.x + lineRect.w) && (y >= lineRect.y && y <= lineRect.y + lineRect.h))
            {
                printf("Line!\n");
                AppData.moveMode=d->mode;
                settings();
            }
            deleteJob(&AppData.joblist, d->jobnode);
        }
    }
    else if (d->mode == 'r')
    {
        if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
        {

            if ((x >= randRect.x && x <= randRect.x + randRect.w) && (y >= randRect.y && y <= randRect.y + randRect.h))
            {
                printf("Rand!\n");
                AppData.moveMode=d->mode;
                settings();
            }
            deleteJob(&AppData.joblist, d->jobnode);
        }
    }
}

void clickSpeedLv1Callback(Uint32 state)
{
    if (SDL_BUTTON_LMASK&state)
    {
        AppData.speed='1';
        settings();
    }
}

void clickSpeedLv2Callback(Uint32 state)
{
    if (SDL_BUTTON_LMASK&state)
    {
        AppData.speed='2';
        settings();
    }
}

void clickSpeedLv3Callback(Uint32 state)
{
    if (SDL_BUTTON_LMASK&state)
    {
        AppData.speed='3';
        settings();
    }
}

void clickSpeedLv4Callback(Uint32 state)
{
    if (SDL_BUTTON_LMASK&state)
    {
        AppData.speed='4';
        settings();
    }
}

void clickSpeedLv5Callback(Uint32 state)
{
    if (SDL_BUTTON_LMASK&state)
    {
        AppData.speed='5';
        settings();
    }
}

void changeLanguage(void *data)
{
    struct data
    {
        JobNode *jobnode;
        char language;
    } *d = data;

    SDL_Rect languageBaseRect={AppData.controlSurface_temp->w*0.05,AppData.controlSurface_temp->h-AppData.textS_en->h-3};
    SDL_Rect enRect={languageBaseRect.x,languageBaseRect.y,AppData.textS_en->w,AppData.textS_en->h};
    languageBaseRect.x+=(AppData.textS_en->w+AppData.controlSurface_temp->w*0.015);languageBaseRect.y=AppData.controlSurface_temp->h-AppData.textS_cn->h-3;
    SDL_Rect cnRect={languageBaseRect.x,languageBaseRect.y,AppData.textS_cn->w,AppData.textS_cn->h};
    languageBaseRect.x+=(AppData.textS_cn->w+AppData.controlSurface_temp->w*0.015);languageBaseRect.y=AppData.controlSurface_temp->h-AppData.textS_jp->h-3;
    SDL_Rect jpRect={languageBaseRect.x,languageBaseRect.y,AppData.textS_jp->w,AppData.textS_jp->h};
    int x,y;
    if(AppData.appMode!='c')
    {
        enRect.x+=AppData.CWrect.x;
        enRect.y+=AppData.CWrect.y;
        cnRect.x+=AppData.CWrect.x;
        cnRect.y+=AppData.CWrect.y;
        jpRect.x+=AppData.CWrect.x;
        jpRect.y+=AppData.CWrect.y;
    }
    if (d->language == 'e')
    {
        if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
        {

            if ((x >= enRect.x && x <= enRect.x + enRect.w) && (y >= enRect.y && y <= enRect.y + enRect.h))
            {
                printf("en!\n");
                AppData.language=d->language;
                settings();
                loadTextSurface();
            }
            deleteJob(&AppData.joblist, d->jobnode);
        }
    }
    else if (d->language == 'c')
    {
        if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
        {

            if ((x >= cnRect.x && x <= cnRect.x + cnRect.w) && (y >= cnRect.y && y <= cnRect.y + cnRect.h))
            {
                printf("cn!\n");
                AppData.language=d->language;
                settings();
                loadTextSurface();
            }
            deleteJob(&AppData.joblist, d->jobnode);
        }
    }
    else if (d->language == 'j')
    {
        if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
        {

            if ((x >= jpRect.x && x <= jpRect.x + jpRect.w) && (y >= jpRect.y && y <= jpRect.y + jpRect.h))
            {
                printf("jp!\n");
                AppData.language=d->language;
                settings();
                loadTextSurface();
            }
            deleteJob(&AppData.joblist, d->jobnode);
        }
    }
}

void clickApplyCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        SDL_Rect Brect;
        void (*fun)(Uint8 state);
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        printf("Apply!\n");
        // HKEY hkey;
        // RegOpenKeyEx(HKEY_CURRENT_USER,"Control Panel\\Desktop",0,KEY_ALL_ACCESS,&hkey);
        // // char str[100]={0};str[99]=EOF;long unsigned int a=100;
        // // RegGetValue(hkey,NULL,"SCRNSAVE.EXE",RRF_RT_ANY,NULL,str,&a);
        // // printf("%d:%s\n",a,str);

        // RegSetValueEx(hkey,"SCRNSAVE.EXE",0,REG_SZ,"C:\\Code\\flypig\\window2.scr",sizeof("C:\\Code\\flypig\\window2.scr"));

        // RegCloseKey(hkey);

        JobNode* job=addJob(&AppData.joblist,ButtonJob);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;

        d->Brect.x=AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-AppData.controlSurface_temp->w*0.1-AppData.controlSurface_temp->w*0.25-2;
        d->Brect.y=AppData.controlSurface_temp->h*0.85;
        d->Brect.w=AppData.controlSurface_temp->w*0.25;
        d->Brect.h=AppData.controlSurface_temp->h*0.1;
        d->fun=ButtonApplyHandler;

        job->data=d;

    }
}

void clickSettingCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        SDL_Rect Brect;
        void (*fun)(Uint8 state);
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        printf("Setting!\n");
        // //system("rundll32.exe desk.cpl,InstallScreenSaver");   有阻塞以及控制台窗口问题
        // WinExec("Rundll32.exe shell32.dll,Control_RunDLL desk.cpl,screensaver,@screensaver",SW_NORMAL);//rundll32.exe desk.cpl,InstallScreenSaver//control.exe desk.cpl,,@screensaver//control.exe desk.cpl,screensaver,@screensaver

        JobNode* job=addJob(&AppData.joblist,ButtonJob);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->Brect.x=AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-AppData.controlSurface_temp->w*0.1;
        d->Brect.y=AppData.controlSurface_temp->h*0.85;
        d->Brect.w=AppData.controlSurface_temp->w*0.1;
        d->Brect.h=AppData.controlSurface_temp->h*0.1;
        d->fun=ButtonSettingHandler;


        job->data=d;
    
    }
    
}

void changeAppMode(char mode)
{
    //先判断当前模式
    if(AppData.appMode=='c')
    {
        if (mode=='s') //要切换到的模式
        {
            AppInit('s');
            AppData.appMode='s';
        }
        else if(mode=='m')
        {   
            //坐标互通 from c to m
            int tmp_x,tmp_y;
            SDL_GetWindowPosition(AppData.controlWindow,&tmp_x,&tmp_y);
            
            AppInit('m');

            AppData.CWrect.x=tmp_x;
            AppData.CWrect.y=tmp_y;

            AppData.appMode='m';
        }
    }
    else if(AppData.appMode=='m')
    {
        if (mode=='s')
        {
            AppInit('s');
            AppData.appMode='s';
        }
        else if(mode=='c')
        {
            AppInit('c');

            //坐标互通 from m to c
            SDL_SetWindowPosition(AppData.controlWindow,AppData.CWrect.x,AppData.CWrect.y);

            AppData.appMode='c';
        }
    }

}

void ShowControlPlane(Uint8 toggle) // 0 hide 1 show
{
    if (toggle==0)
    {
        AppData.hide_flag=1;
        //本来打算是通过更改数据(装卸Area、...)来影响行为的,现在是直接通过标志指示不同的行为
    }
    else if (toggle==1)
    {
        AppData.hide_flag=0;
    }
    
}

#define SettingButtonW AppData.controlSurface_temp->w*0.1

void clickStartCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        SDL_Rect Brect;
        void (*fun)(Uint8 state);
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        printf("Start!\n");
        JobNode* job=addJob(&AppData.joblist,ButtonJob);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;

        SDL_Rect iconB={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*3,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        SDL_Rect iconB2={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*2,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        if(AppData.appMode=='c')iconB=iconB2;

        d->Brect=iconB;
        d->fun=ButtonStartHandler;


        job->data=d;
    }
    else drawStartButton(1);
}

void clickEyeCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        SDL_Rect Brect;
        void (*fun)(Uint8 state);
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        printf("Eye!\n");
        JobNode* job=addJob(&AppData.joblist,ButtonJob);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;

        SDL_Rect iconB={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75*2,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        SDL_Rect iconB2={AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75,AppData.controlSurface_temp->h-3-25,SettingButtonW*0.75,25};
        if(AppData.appMode=='c')iconB=iconB2;

        d->Brect=iconB;
        d->fun=ButtonEyeHandler;


        job->data=d;
    }
    else drawEyeButton(1);
}

void clickHideCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        SDL_Rect Brect;
        void (*fun)(Uint8 state);
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        JobNode* job=addJob(&AppData.joblist,ButtonJob);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->Brect.x=AppData.controlSurface_temp->w-AppData.controlSurface_temp->w*0.05-SettingButtonW*0.75;
        d->Brect.y=AppData.controlSurface_temp->h-3-25;
        d->Brect.w=SettingButtonW*0.75;
        d->Brect.h=25;
        d->fun=ButtonHideHandler;


        job->data=d;
    }
    else drawHideButton(1);
}

void clickLogoCallback(Uint32 state)
{
    struct data
    {
        JobNode *jobnode;
        SDL_Rect Brect;
        void (*fun)(Uint8 state);
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        JobNode* job=addJob(&AppData.joblist,ButtonJob);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->Brect.x=AppData.scrn_rect.w-AppData.logo->w;
        d->Brect.y=AppData.scrn_rect.h-AppData.logo->h;
        d->Brect.w=AppData.logo->w;
        d->Brect.h=AppData.logo->h;
        d->fun=ButtonLogoHandler;


        job->data=d;
    }

}

void ButtonSettingHandler(Uint8 state)
{
    if(state == 1)
    {
        drawSettingButton(1);
    }
    else if(state == 2)
    {
        WinExec("Rundll32.exe shell32.dll,Control_RunDLL desk.cpl,screensaver,@screensaver",SW_NORMAL);//rundll32.exe desk.cpl,InstallScreenSaver//control.exe desk.cpl,,@screensaver//control.exe desk.cpl,screensaver,@screensaver
    }
}

void ButtonApplyHandler(Uint8 state)
{
    if(state == 1)
    {
        drawApplyButton(1);
    }
    else if(state == 2)
    {
        HKEY hkey;
        RegOpenKeyEx(HKEY_CURRENT_USER,"Control Panel\\Desktop",0,KEY_ALL_ACCESS,&hkey);
        // char str[100]={0};str[99]=EOF;long unsigned int a=100;
        // RegGetValue(hkey,NULL,"SCRNSAVE.EXE",RRF_RT_ANY,NULL,str,&a);
        // printf("%d:%s\n",a,str);

        if (AppData.apply_flag==0)
        {
            char path[MAX_PATH]={0};
            GetModuleFileName(NULL,path,MAX_PATH);
            RegSetValueEx(hkey,"SCRNSAVE.EXE",0,REG_SZ,path,strnlen(path,MAX_PATH)+1);
            printf("Apply:%s\n",path);

            RegSetValueEx(hkey,"ScreenSaveActive",0,REG_SZ,"1",sizeof("1"));
        }
        else if (AppData.apply_flag==1)
        {
            int return_value=RegDeleteValue(hkey,"SCRNSAVE.EXE");
            printf("DELETE KEY!\n");
            if (return_value!=ERROR_SUCCESS)
            {
                printf("Failed!%d\n",return_value);
            }
            
        }
        
        
        

        RegCloseKey(hkey);
        printf("BBBBBBBBBBBBBBBBB~\n");
    }
}

Uint32 cancelBufferTimeCallback(Uint32 interval, void *param)
{
    AppData.bufferTime_flag=0;
    return 0;
}

void ButtonStartHandler(Uint8 state)
{
    if(state == 1)
    {
        drawStartButton(2);
    }
    else if(state == 2)
    {
        changeAppMode('s');
        AppData.bufferTime_flag=1;
        SDL_AddTimer(3000,cancelBufferTimeCallback,NULL);
    }
}

void ButtonEyeHandler(Uint8 state)
{
    if(state == 1)
    {
        drawEyeButton(2);
    }
    else if(state == 2)
    {
        if (AppData.appMode=='c')
        {
            changeAppMode('m');
        }
        else if (AppData.appMode=='m')
        {
            changeAppMode('c');
        }
    }
}

void ButtonHideHandler(Uint8 state)
{
    if(state == 1)
    {
        drawHideButton(2);
    }
    else if(state == 2)
    {
        ShowControlPlane(0);
    }
}

void ButtonLogoHandler(Uint8 state)
{
    if(state == 2)
    {
        ShowControlPlane(1);
    }
}

void ButtonJob(void *data)
{
    struct data
    {
        JobNode *jobnode;
        SDL_Rect Brect;
        void (*fun)(Uint8 state);
    } *d = data;

    SDL_Rect Brect=d->Brect;
    if(AppData.appMode!='c' && AppData.hide_flag!=1)
    {
        Brect.x+=AppData.CWrect.x;
        Brect.y+=AppData.CWrect.y;
    }
    int x,y;
    if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
    {
        if ((x >= Brect.x && x <= Brect.x + Brect.w)&&(y >= Brect.y && y <= Brect.y + Brect.h))
        {
            d->fun(2);
        }
        deleteJob(&AppData.joblist, d->jobnode);
    }
    else d->fun(1);
}



// 在链表头部插入一个节点
void insertAreaNode(AreaNode** head, AreaNode* newNode)
{
    AreaNode *tmp = *head;
    *head = newNode;
    newNode->next = tmp;
}

// 在链表末尾添加一个节点
void appendAreaNode(AreaNode** head, AreaNode* newNode) 
{
    AreaNode* p = *head;
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
void deleteAreaNode(AreaNode** headP, AreaNode* nodeToDel) 
{
    AreaNode* p = *headP;
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
    AreaNode* q=p->next;
    p->next=q->next;
    free(q->data);
    free(q);
    return;
}

// 通过名称删除链表中指定位置的节点
void deleteAreaNodeByName(AreaNode** headP, char* name) 
{
    AreaNode* p = *headP;
    if (p==NULL)return;
    if (!strcmp(p->name,name))
    {
        *headP=p->next;
        free(p->data);
        free(p);
        return;
    }
    while (p->next != NULL && strcmp(p->next->name,name)) {
        p = p->next;
    }
    if (p->next == NULL) {
        return;
    }
    AreaNode* q=p->next;
    p->next=q->next;
    free(q->data);
    free(q);
    return;
}

// 添加区域
AreaNode* addArea(AreaNode** list,char* name,SDL_Rect area,void (*callback)())
{
   AreaNode* newNode=malloc(sizeof(AreaNode));
   memset(newNode,0,sizeof(AreaNode));
   newNode->name=name;
   newNode->area=area;
   newNode->callback=callback;
   newNode->next=NULL;
   insertAreaNode(list,newNode);
   return newNode;
}

//删除区域
void deleteArea(AreaNode** list,AreaNode* nodeToDel)
{
    free(nodeToDel->data);//释放关联的数据
    deleteAreaNode(list,nodeToDel);//删除Job
}

//清空区域列表
void clearArea(AreaNode* list)
{
    while (list!=NULL)
    {   
        AreaNode* tmp;
        tmp=list;
        list=list->next;//先保存好下一节点指针，以防节点自删后找不到下一节点（free后内存被格式化）
        free(tmp->data);
        free(tmp);
        
    }

}










// 在链表末尾添加一个节点
void appendJobNode(JobNode** head, JobNode* newNode) {
    JobNode* p = *head;
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
void deleteJobNode(JobNode** headP, JobNode* nodeToDel) {
    JobNode* p = *headP;
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

    JobNode* q=p->next;
    p->next=q->next;
    free(q);
    return;
}

// 添加任务
JobNode* addJob(JobNode** list,void (*function)())
{
   JobNode* newNode=malloc(sizeof(JobNode));
   newNode->fun=function;
   newNode->next=NULL;
   appendJobNode(list,newNode);
   return newNode;
}

//删除任务
void deleteJob(JobNode** list,JobNode* nodeToDel)
{
    free(nodeToDel->data);//释放Job关联的数据
    deleteJobNode(list,nodeToDel);//删除Job
}

//执行任务列表
void RunJob(JobNode* list)
{
    while (list!=NULL)
    {   
        JobNode* tmp;
        tmp=list;
        list=list->next;//先保存好下一节点指针，以防节点自删后找不到下一节点（free后内存被格式化）
        tmp->fun(tmp->data);
        
    }
    

}

//清空任务列表
void clearJob(JobNode* list)
{
    while (list!=NULL)
    {   
        JobNode* tmp;
        tmp=list;
        list=list->next;//先保存好下一节点指针，以防节点自删后找不到下一节点（free后内存被格式化）
        free(tmp->data);
        free(tmp);
        
    }

}