#ifndef __SDL__SIMPLE__LIBARY__H__
#define __SDL__SIMPLE__LIBARY__H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <Windows.h>

/*
ͷ�ļ����ƣ�SDLFR.h
���ܣ�����SDL�г��ú������������
���ߣ�HelloClyde
*/

/*
���ܣ���WINDOWS���ص��ַ���ת����UTF8����
���룺SRC �ַ���ָ��
�����ת������Ժ���ַ���ָ��
*/
char *SDL_localeToUTF8(char *src);

/*
���ܣ����ַ�����TTF����ת��Ϊ��ͼ
���룺TTF_Font TTF����ָ�룬SDL_Renderer ��Ⱦ��ָ�룬Text ������ַ���ָ�룬Color_R ��ɫRֵ��Color_G ��ɫGֵ��Color_B ��ɫBֵ
�����SDL_Texture ��ͼָ��
*/
SDL_Texture *SDL_CreateTTFTexture(TTF_Font *Font, SDL_Renderer *Renderer, char *Text, int Color_R, int Color_G, int Color_B);

/*
���ܣ�����ͼ��ʾ����Ⱦ������
���룺Renderer Ŀ����Ⱦ����Texture ��ͼ��Mode ��ʾģʽ��1����ԭʼ�����ʾ��0��ʹ��֮���Զ���Ŀ����ʾ����Src_X ԴX��Src_Y ԴY��Src_Width Դ��Src_Height Դ�ߣ�Dst_X Ŀ��X��Dst_Y Ŀ��Y��Dst_Width Ŀ���Dst_Height Ŀ���
��������֣�0���ɹ���-1��ʧ�ܣ�
*/
int SDL_CopyTextureToRenderer(SDL_Renderer *Renderer, SDL_Texture *Texture,int Mode, int Src_X, int Src_Y, int Src_Width, int Src_Height, int Dst_X, int Dst_Y, int Dst_Width, int Dst_Height);

/*
���ܣ���ⰴ���Ƿ񱻰���
���룺������ScanCodeֵ��ע�����Ҫ�Ǹ�ֵ��������ܷ����������
���������������1���ð��������� 0���ð���δ�����£�
*/
int SDL_KeyBoardKeyPressed(int Key);

/*
���ܣ����ַ�����TTF������ʾ����Ⱦ����
���룺���壬Ŀ����Ⱦ��������ʾ���ı��ַ�������ʾ����Ⱦ����λ��X����ʾ����Ⱦ����λ��Y��������ɫRֵ��������ɫGֵ��������ɫBֵ
�����0���ɹ�
*/
int SDL_ShowTTFtoRenderer(TTF_Font *Font, SDL_Renderer *Renderer, char *text,int x, int y, int Color_R, int Color_G, int Color_B);

/*
���ܣ���ȡ��ǰ��Ļ�ֱ���
���룺�����ȵĵ�ַ������߶ȵĵ�ַ
���أ���
*/
void SDL_GetScreenWH(int *Wid,int *Hgt);

/*
����Ƿ����رհ�ť,����͹رճ���
*/
void SDL_WindowsQuitThreadRun();

#endif