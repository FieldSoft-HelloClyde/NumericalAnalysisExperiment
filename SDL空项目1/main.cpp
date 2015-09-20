#include "SDL.h"
#include "SDLSimpleLibary.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int Windows_X,Windows_Y;
int Windows_Width = 960;
int Windows_Height = 640;
char *Windows_Title = "Lagrange Demo";
SDL_Window *Main_Windows = nullptr;
SDL_Renderer *Main_Renderer = nullptr;

double Lagrange_n(double xx);
double Lagrange(int n,double *x,double *y,double xx);
double Newton_n(double xx);
double Newton(int n,double *x,double *y,double xx);
double DiffQuotient(double *x,double *y,int xstart,int xx);
double DiffQuoTable[13][13];
bool DiffQuoExist[13][13];
double Hermite_n(double xx);
double Hermite(int n,double *x,double *y,double *m,double xx);
double TheLeastSquareMethod_n(double xx);
double TheLeastSquareMethod(int m,double *x,double *y,double xx);
void Menu();
int DrawFx(double (*Fx)(double),double *x,double *y,int n);

int DrawFx(double (*Fx)(double),double *x,double *y,int n)
{
    //Start SDL
    SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	//获取屏幕分辨率
	int Screen_Wid;
	int Screen_Hgt;
	SDL_GetScreenWH(&Screen_Wid,&Screen_Hgt);

	//设置窗口居中
	Windows_X = (Screen_Wid - Windows_Width) / 2;
	Windows_Y = (Screen_Hgt - Windows_Height) / 2;

	//创建窗口
	Main_Windows = SDL_CreateWindow(Windows_Title,Windows_X,Windows_Y,Windows_Width,Windows_Height,SDL_WINDOW_SHOWN);

	Main_Renderer = SDL_CreateRenderer(Main_Windows, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	TTF_Font *MainFont = TTF_OpenFont("./cour.ttf", 18);

	SDL_Event event;
	int While_Quit = -1;
	
	int X_pos = Windows_Width / 2;
	int Y_pos = Windows_Height / 2;
	int Mouse_Old_X;
	int Mouse_Old_Y;
	double PixRate = 1.0;
	int MoveState = false;
	while (While_Quit == -1)
	{
		//清屏
		SDL_SetRenderDrawColor(Main_Renderer,0,0,0,255);
		SDL_RenderClear(Main_Renderer);
		SDL_SetRenderDrawColor(Main_Renderer,255,255,255,255);
		//画X轴
		SDL_RenderDrawLine(Main_Renderer,0,Y_pos,Windows_Width,Y_pos);
		//画Y轴
		SDL_RenderDrawLine(Main_Renderer,X_pos,0,X_pos,Windows_Height);
		//画L(n)
		int xx;
		for (xx = 0;xx < Windows_Width;xx ++){
			double x1,y1;
			x1 = ((double)(xx - X_pos)) / PixRate;
			y1 = Fx(x1);
			int yy;
			yy = Y_pos - y1 * PixRate;
			SDL_RenderDrawPoint(Main_Renderer,xx,yy);
		}
		//画fx
		SDL_SetRenderDrawColor(Main_Renderer,255,0,0,255);
		for (int i = 0;i < n;i ++){
			int xx;
			xx = X_pos + x[i] * PixRate;
			int yy;
			yy = Y_pos - y[i] * PixRate;
			SDL_Rect TempRect;
			TempRect.x = xx-3;
			TempRect.y = yy-3;
			TempRect.w = 5;
			TempRect.h = 5;
			SDL_RenderFillRect(Main_Renderer,&TempRect);
			SDL_RenderDrawPoint(Main_Renderer,xx,yy);
		}
		//绘制调试信息
		char str[100] = {0};
		sprintf(str,"%d",X_pos);
		SDL_ShowTTFtoRenderer(MainFont,Main_Renderer,str,20, 20,0,255,0);
		sprintf(str,"%d",Y_pos);
		SDL_ShowTTFtoRenderer(MainFont,Main_Renderer,str,20, 40,0,255,0);
		sprintf(str,"%lf",PixRate);
		SDL_ShowTTFtoRenderer(MainFont,Main_Renderer,str,20, 60,0,255,0);
		//复位按钮
		SDL_ShowTTFtoRenderer(MainFont,Main_Renderer,"Reset",20, 80,0,255,0);
		SDL_RenderPresent(Main_Renderer);

		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT){
				While_Quit = 4;
			}
			else if (event.type == SDL_MOUSEMOTION){
				if (MoveState){
					int dx,dy;
					dx = event.motion.x - Mouse_Old_X;
					dy = event.motion.y - Mouse_Old_Y;
					X_pos += dx;
					Y_pos += dy;
					Mouse_Old_X = event.motion.x;
					Mouse_Old_Y = event.motion.y;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN){
				if (event.button.button == SDL_BUTTON_LEFT){
					if (event.motion.x >= 20 && event.button.x <= 65 && event.button.y >= 80 && event.button.y <= 100){
						X_pos = Windows_Width / 2;
						Y_pos = Windows_Height / 2;
						PixRate = 1.0;
					}
					else{
						MoveState = true;
						Mouse_Old_X = event.motion.x;
						Mouse_Old_Y = event.motion.y;
					}
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP){
				if (event.button.button == SDL_BUTTON_LEFT){
					MoveState = false;
				}
			}
			else if (event.type == SDL_MOUSEWHEEL){
				if (event.wheel.y > 0){
					//放大
					PixRate *= 2;
				}
				else if (event.wheel.y < 0){
					PixRate /= 2;
				}
			}
         }
    }

	//SDL_Delay(1000);
	SDL_DestroyRenderer(Main_Renderer);
	SDL_DestroyWindow(Main_Windows);
    //Quit SDL
    SDL_Quit();
	//关闭TTF
	TTF_Quit();
    return 0;

}

int main(int args,char **argc){
	int While_Quit = false;
	int MenuIndex = -1;
	while (!While_Quit){
		system("cls");
		cout << "选择函数" << endl;
		cout << "1.Lagrange(65)" << endl;
		cout << "2.Newton(65)" << endl;
		cout << "3.Hermite(0.55)" << endl;
		cout << "4.TheLeastSquareMethod(55)" << endl;
		cout << "0:退出" << endl;
		cin >> MenuIndex;
		if (MenuIndex == 1){
			double x[] = {0,10,20,30,40,50,60,70,80,90,100,110,120};
			double y[] = {5,1,7.5,3,4.5,8.8,15.5,6.5,-5,-10,-2,4.5,7};
			system("cls");
			cout << "Lagrange(65):" << Lagrange_n(65) << endl;
			DrawFx(Lagrange_n,x,y,13);
		}
		else if (MenuIndex == 2){
			double x[] = {0,10,20,30,40,50,60,70,80,90,100,110,120};
			double y[] = {5,1,7.5,3,4.5,8.8,15.5,6.5,-5,-10,-2,4.5,7};
			system("cls");
			cout << "Newton_n(65):" << Newton_n(65) << endl;
			DrawFx(Newton_n,x,y,13);
		}
		else if (MenuIndex == 3){
			double x[] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
			double y[] = {0.904837,0.818731,0.740818,0.670320,0.606531,
				0.548812,0.496585,0.449329,0.406570,0.367879};system("cls");
			cout << "Hermite_n(0.55):" << Hermite_n(0.55) << endl;
			DrawFx(Hermite_n,x,y,10);
		}
		else if (MenuIndex == 4){
			double x[] = {0,10,20,30,40,50,60,70,80,90};
			double y[] = {68,67.1,66.4,65.6,64.6,61.8,61.0,60.8,60.4,60};
			cout << "TheLeastSquareMethod(55):" << TheLeastSquareMethod_n(55) << endl;
			DrawFx(TheLeastSquareMethod_n,x,y,10);
		}
		else if (MenuIndex == 0){
			While_Quit = true;
		}
	}
	return 0;
}

double TheLeastSquareMethod_n(double xx){
	double x[] = {0,10,20,30,40,50,60,70,80,90};
	double y[] = {68,67.1,66.4,65.6,64.6,61.8,61.0,60.8,60.4,60};
	return TheLeastSquareMethod(10,x,y,xx);
}

double TheLeastSquareMethod(int m,double *x,double *y,double xx){
	double sxi2 = 0;
	double syi = 0;
	double sxi = 0;
	double sxiyi = 0;
	for (int i = 0;i < m;i ++){
		sxi2 += x[i] * x[i];
		syi += y[i];
		sxi += x[i];
		sxiyi += x[i] * y[i];
	}
	double a = (sxi2 * syi - sxi * sxiyi) / ((m + 1) * sxi2 - sxi * sxi);
	double b = ((m + 1) * sxiyi - sxi * syi) / ((m + 1) * sxi2 - sxi * sxi);
	return a * xx + b;
}

double Hermite_n(double xx){
	double x[] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
	double y[] = {0.904837,0.818731,0.740818,0.670320,0.606531,
				0.548812,0.496585,0.449329,0.406570,0.367879};
	double m[] = {-0.904837,-0.818731,-0.740818,-0.670320,-0.606531,
				-0.548812,-0.496585,-0.449329,-0.406570,-0.367879};
	return Hermite(10,x,y,m,xx);
}

double Hermite(int n,double *x,double *y,double *m,double xx){
	double Result = 0;
	for (int j = 0;j < n;j ++){
		double lj = 1;
		for (int i = 0;i < n;i ++){
			if (i == j) continue;
			lj *= (xx - x[i]) / (x[j] - x[i]);
		}
		double ljs = 0;
		for (int k = 0;k < n;k ++){
			if (k == j) continue;
			ljs += (double)1.0 / (x[j] - x[k]);
		}
		double aj;
		aj = (1 - 2 * (xx - x[j]) * ljs) * lj * lj;
		double bj;
		bj = (xx - x[j]) * lj * lj;
		Result += y[j] * aj + m[j] * bj;
	}
	return Result;
}

double Lagrange_n(double xx){
	double x[] = {0,10,20,30,40,50,60,70,80,90,100,110,120};
	double y[] = {5,1,7.5,3,4.5,8.8,15.5,6.5,-5,-10,-2,4.5,7};
	return Lagrange(13,x,y,xx);
}

double Lagrange(int n,double *x,double *y,double xx){
	double addResult = 0;
	int k = 0;
	for (k = 0;k < n;k ++){
		double mulResult = 1;
		int j = 0;
		for (j = 0;j < n;j ++){
			if (j == k) continue;
			mulResult *= (xx - x[j]) / (x[k] - x[j]);
		}
		addResult += y[k] * mulResult;
	}
	return addResult;
}

double Newton_n(double xx){
	double x[] = {0,10,20,30,40,50,60,70,80,90,100,110,120};
	double y[] = {5,1,7.5,3,4.5,8.8,15.5,6.5,-5,-10,-2,4.5,7};
	for (int i = 0;i < 13;i ++){
		for (int j = 0;j < 13;j ++){
			DiffQuoTable[i][j] = 0;
			DiffQuoExist[i][j] = false;
		}
	}
	return Newton(13,x,y,xx);
}

/*
原本效率较低
优化001：
	数组储存临时内容，减少重复计算
*/
double DiffQuotient(double *x,double *y,int xstart,int xx){
	if (DiffQuoExist[xstart][xx]){
		return DiffQuoTable[xstart][xx];
	}
	else{
		if (xx == 1){
			return (y[xstart] - y[xstart + 1]) / (x[xstart] - x[xstart + 1]);
		}
		else if (xx == 0){
			return y[xstart + xx];
		}
		else{
			DiffQuoTable[xstart][xx] = (DiffQuotient(x,y,xstart,xx - 1) - DiffQuotient(x,y,xstart + 1,xx - 1)) / (x[xstart] - x[xstart + xx]);
			DiffQuoExist[xstart][xx] = true;
			return DiffQuoTable[xstart][xx];
		}
	}
}

double Newton(int n,double *x,double *y,double xx){
	double result = y[0];
	int index = 0;
	for (index = 0;index < n - 1;index ++){
		double anresult;
		anresult = DiffQuotient(x,y,0,index + 1);
		int index2 = 0;
		for (index2 = 0;index2 <= index;index2 ++){
			anresult *= (xx - x[index2]);
		}
		result += anresult;
	}
	return result;
}