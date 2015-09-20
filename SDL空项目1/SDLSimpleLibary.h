#ifndef __SDL__SIMPLE__LIBARY__H__
#define __SDL__SIMPLE__LIBARY__H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <Windows.h>

/*
头文件名称：SDLFR.h
功能：整合SDL中常用函数，方便调用
作者：HelloClyde
*/

/*
功能：把WINDOWS当地的字符串转换成UTF8编码
输入：SRC 字符串指针
输出：转换完成以后的字符串指针
*/
char *SDL_localeToUTF8(char *src);

/*
功能：把字符串用TTF字体转化为贴图
输入：TTF_Font TTF字体指针，SDL_Renderer 渲染器指针，Text 输入的字符串指针，Color_R 颜色R值，Color_G 颜色G值，Color_B 颜色B值
输出：SDL_Texture 贴图指针
*/
SDL_Texture *SDL_CreateTTFTexture(TTF_Font *Font, SDL_Renderer *Renderer, char *Text, int Color_R, int Color_G, int Color_B);

/*
功能：将贴图显示到渲染器上面
输入：Renderer 目标渲染器，Texture 贴图，Mode 显示模式（1：以原始宽高显示，0：使用之后自定义的宽高显示），Src_X 源X，Src_Y 源Y，Src_Width 源宽，Src_Height 源高，Dst_X 目标X，Dst_Y 目标Y，Dst_Width 目标宽，Dst_Height 目标高
输出：数字（0：成功，-1：失败）
*/
int SDL_CopyTextureToRenderer(SDL_Renderer *Renderer, SDL_Texture *Texture,int Mode, int Src_X, int Src_Y, int Src_Width, int Src_Height, int Dst_X, int Dst_Y, int Dst_Width, int Dst_Height);

/*
功能：检测按键是否被按下
输入：按键的ScanCode值，注意必须要是该值，否则可能发生溢出错误
输出：返回整数（1：该按键被按下 0：该按键未被按下）
*/
int SDL_KeyBoardKeyPressed(int Key);

/*
功能：把字符串用TTF字体显示到渲染器上
输入：字体，目标渲染器，欲显示的文本字符串，显示到渲染器的位置X，显示到渲染器的位置Y，字体颜色R值，字体颜色G值，字体颜色B值
输出：0：成功
*/
int SDL_ShowTTFtoRenderer(TTF_Font *Font, SDL_Renderer *Renderer, char *text,int x, int y, int Color_R, int Color_G, int Color_B);

/*
功能：获取当前屏幕分辨率
输入：所需宽度的地址，所需高度的地址
返回：无
*/
void SDL_GetScreenWH(int *Wid,int *Hgt);

/*
检测是否点击关闭按钮,点击就关闭程序
*/
void SDL_WindowsQuitThreadRun();

#endif