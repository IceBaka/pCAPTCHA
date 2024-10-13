#ifndef CONTROL_h_
#define CONTROL_h_

#include <SDL.h>

extern struct appdata AppData;

typedef struct jobnode JobNode;
typedef struct areanode AreaNode;
typedef struct pignode PigNode;
typedef struct itemnode ItemNode;
typedef struct effectnode EffectNode;

//应用数据
struct appdata
{
    Uint32 SceneContext;  //用位标志记录使用的场景（主菜单、功能页、弹窗、战斗画面） 00000000 00000000 00000000 00000000
    JobNode* joblist;  //任务列表
    AreaNode* controlAreaList;
    AreaNode* noplaneAreaList;
    SDL_Window* controlWindow;
    SDL_Window* scrnWindow;
    SDL_Window* preWindow;
    SDL_Rect scrn_rect;
    SDL_Rect pre_rect;
    
    SDL_Surface* logo;

    SDL_Surface* textS_title;
    SDL_Surface* textS_path;
    SDL_Surface* textS_speed;
    SDL_Surface* textS_line;
    SDL_Surface* textS_random;
    SDL_Surface* textS_en;
    SDL_Surface* textS_cn;
    SDL_Surface* textS_jp;
    SDL_Surface* textS_en_w;
    SDL_Surface* textS_cn_w;
    SDL_Surface* textS_jp_w;
    SDL_Surface* textS_1;
    SDL_Surface* textS_2;
    SDL_Surface* textS_3;
    SDL_Surface* textS_4;
    SDL_Surface* textS_5;
    SDL_Surface* textS_apply;
    SDL_Surface* textS_icon_setting;
    SDL_Surface* textS_icon_start;
    SDL_Surface* textS_icon_eye;
    SDL_Surface* textS_icon_hide;

    //=======Renderer=======
    SDL_Window* theWindow;
    SDL_Renderer* theRenderer;
    SDL_Renderer* tmp_cpl_renderer;

    SDL_Renderer* controlRenderer;
    SDL_Renderer* scrnsaverRenderer;
    SDL_Renderer* previewRenderer;


    SDL_Texture* logo_T;

    SDL_Texture* text_T_title;
    SDL_Texture* text_T_path;
    SDL_Texture* text_T_speed;
    SDL_Texture* text_T_line;
    SDL_Texture* text_T_random;
    SDL_Texture* text_T_en;
    SDL_Texture* text_T_cn;
    SDL_Texture* text_T_jp;
    SDL_Texture* text_T_en_w;
    SDL_Texture* text_T_cn_w;
    SDL_Texture* text_T_jp_w;
    SDL_Texture* text_T_1;
    SDL_Texture* text_T_2;
    SDL_Texture* text_T_3;
    SDL_Texture* text_T_4;
    SDL_Texture* text_T_5;
    SDL_Texture* text_T_apply;
    SDL_Texture* text_T_icon_setting;
    SDL_Texture* text_T_icon_start;
    SDL_Texture* text_T_icon_eye;
    SDL_Texture* text_T_icon_hide;

    SDL_Texture* controlTexture_temp;
    //=======================
    SDL_Texture* ui_T;
    SDL_Texture* ui2_T;
    SDL_Texture* L_ani_T;
    SDL_Surface* ui;
    SDL_Surface* ui2;
    SDL_Surface* L_ani;


    SDL_Rect CWrect;
    float zoom;

    PigNode* pigs;
    ItemNode* items;
    EffectNode* effects;
    // SDL_Surface* controlSurface;
    SDL_Surface* controlSurface_temp;
    // // SDL_Surface* RAni_sprite;
    // // SDL_Surface* RAni_tempSurface;
    // SDL_Surface* scrnSurface;
    // SDL_Surface* preSurface;
    float k;

    char appMode;//'s' scrnsave  'c' control 'm' mixed 'p' preview-child window
    char language;// 'e' 'c' 'j'
    char moveMode;// 'l' 直线 'r' 随机
    char speed;// '1' '2' '3' '4' '5'

    Uint8 hide_flag;
    Uint8 apply_status;
    Uint8 bufferTime_flag;
    Uint8 apply_flag;// 0 off 1 on

    SDL_sem* itemCallbackLock;//防止回调的数据访问和主线程释放内存所产生的冲突

    Uint8 ClickLock;
};

// typedef struct actionarea
// {
//     SDL_Rect area;
//     //int level;
//     void (*callback)(Uint32 state);
// }ActionArea;


void loadConfig();

void clickTopBarCallback(Uint32 state);
void clickCloseCallback(Uint32 state);
void clickBtCallback(Uint32 state);
void clickLineModeCallback(Uint32 state);
void clickRandModeCallback(Uint32 state);

void clickSpeedLv1Callback(Uint32 state);
void clickSpeedLv2Callback(Uint32 state);
void clickSpeedLv3Callback(Uint32 state);
void clickSpeedLv4Callback(Uint32 state);
void clickSpeedLv5Callback(Uint32 state);

void dragWindow(void *data);
void dragWindow_m(void *data);
void closeButton(void *data);
void clickBt(void *data);
void changePathMode(void *data);
void ButtonSettingHandler(Uint8 state);
void ButtonApplyHandler(Uint8 state);
void ButtonStartHandler(Uint8 state);
void ButtonEyeHandler(Uint8 state);
void ButtonHideHandler(Uint8 state);
void ButtonLogoHandler(Uint8 state);

void ButtonJob(void *data);

void clickEnCallback(Uint32 state);
void clickCnCallback(Uint32 state);
void clickJpCallback(Uint32 state);
void changeLanguage(void *data);

void clickApplyCallback(Uint32 state);
void clickSettingCallback(Uint32 state);
void clickStartCallback(Uint32 state);
void clickEyeCallback(Uint32 state);
void clickHideCallback(Uint32 state);
void clickLogoCallback(Uint32 state);

void CheckMouse(AreaNode* list);
void insertAreaNode(AreaNode** head, AreaNode* newNode);
void appendAreaNode(AreaNode** head, AreaNode* newNode);
void deleteAreaNode(AreaNode** headP, AreaNode* nodeToDel);
void deleteAreaNodeByName(AreaNode** headP, char* name);
AreaNode* addArea(AreaNode** list,char* name,SDL_Rect area,void (*callback)());
void deleteArea(AreaNode** list,AreaNode* nodeToDel);
void clearArea(AreaNode* list);


void appendJobNode(JobNode** head, JobNode* newNode);
void deleteJobNode(JobNode** headP, JobNode* nodeToDel);
JobNode* addJob(JobNode** list,void (*function)());
void deleteJob(JobNode** list,JobNode* nodeToDel);
void RunJob(JobNode* list);
void clearJob(JobNode* list);



#endif /* CONTROL_h_ */