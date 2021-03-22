#include "lib.h"

LRESULT CALLBACK WindowHandler(HWND Window, UINT Message, WPARAM w, LPARAM l);
void DrawImg(HWND Window, HDC DC, RECT CR);


HDC DC; RECT CR; 
int x = 0;
HPEN GraphPen = CreatePen(PS_SOLID, 50, Blue); 
HPEN AxisPen = CreatePen(PS_SOLID, 1, Grey); 
HPEN Marker = CreatePen(PS_SOLID, 50, Red);
POINT PixelValue[2088];

BOOL ENTERPRESSED = FALSE;

int WinMain(HINSTANCE i, HINSTANCE p, LPSTR s, int cmd)
{
	WINDOW* COM_TRY = new WINDOW("COM_TRY", i, cmd, WindowHandler);
	COM_TRY -> Show();
	MSG message;
	MessageHandler(&message);	
	return message.wParam;
}

//============================================================================
void NullPixelArray()
{
	for(int i = 0; i < DataSize; i++)
		{PixelValue[i].x = 0;PixelValue[i].y = 0;}
	return;
}

LRESULT CALLBACK WindowHandler(HWND Window, UINT Message, WPARAM w, LPARAM l)
{
	GetClientRect(Window, &CR);	
	DC = GetDC(Window);	
		
	switch(Message)
	{	
		case WM_CREATE: 
		{			
			NullDataBuff();	//PortName = DefineComPort();		
		}break;
		
		case WM_RBUTTONDOWN:
		{
			if(ENTERPRESSED)
			{
				DC = GetDC(Window);
				GetClientRect(Window, &CR);
				DrawImg(Window, DC, CR);
				ReleaseDC(Window, DC);
			}
		}break;
		
		case WM_KEYDOWN:
		{
			switch(w)
			{
				case VK_RETURN:
				{
					PrintMessage(PortName);
					ENTERPRESSED = TRUE;
					NullDataBuff();
					NullPixelArray();
					FillRect(DC, &CR, CreateSolidBrush(PaleTurquoise));
							/* Opening ComPort */					
					if(!OpenComPort())
					{
						MessageBox(NULL, "Can't find com port", "ERROR", MB_OK);CloseHandle(Port);
							MessageBox(Window, "NOTHING TO DO HERE!", "Message", MB_OK);
							CloseHandle(Port);
							ExitProcess(1); 
					}
					/* End of opening ComPort */
					
					
					/* Initialize and configure port */  //-------- Think about COMMPROP struct
					InitDCBStruct();
					InitCOMMCONFIGStruct();
					InitTimeOuts();
					if(!SetCommConfig(Port, &ComPort, ComPort.dwSize))
						{MessageBox(Window, "SetCommCofig error!", "ERROR!!!", MB_OK);}
					if(!SetCommState(Port, &PortDCBConfig))
						{MessageBox(Window, "SetCommState error!", "ERROR!!!", MB_OK);}
					if(!SetCommTimeouts(Port,&ComPortTO))
						{MessageBox(Window, "SetCommState error!", "ERROR!!!", MB_OK);}		
					if(!SetupComm(Port, 4096, 512))
						{MessageBox(Window, "SetupComm error!", "ERROR!!!", MB_OK);}			
					/* End of init and configure port */
					
										
						/* Read data && clear up && write in file */
					MessageBox(Window, "Pull down the trigger", "Message", MB_OK);
					FillRect(DC, &CR, CreateSolidBrush(Red)); // allert light :)
					
					
					/* Clearing up buffer */
					PurgeComm(Port, PURGE_RXABORT|PURGE_RXCLEAR);
					/* End of clearing buffer */
					
					// checking time of accepting
					ElapsedTime = clock();
					PurgeComm(Port, PURGE_RXABORT|PURGE_RXCLEAR);
					ReadFile(Port, data, DataSize, &SizeofIncom, NULL);
					ElapsedTime = clock() - ElapsedTime;		
					
					PurgeComm(Port, PURGE_RXABORT|PURGE_RXCLEAR);
					*DataPath = MakeFileName();
					WriteInFile(DataPath->value, Window);			
						/* End of read data && clear up && write in file */	
						
					MessageBox(Window, DataPath->value, "Data Saved!!!", MB_OK);	
					FillRect(DC, &CR, CreateSolidBrush(White));
					CloseHandle(Port);
					DrawImg(Window, DC, CR);
					ReleaseDC(Window, DC);					
									
				}break;
				
				case VK_ESCAPE:
				{
					DC = GetDC(Window);
					GetClientRect(Window, &CR);
					FillRect(DC, &CR, CreateSolidBrush(White));
					ReleaseDC(Window,DC);
				}break;
				
				case VK_BACK:
				{
					
				}break;
				default:break;
			}
		}break;
		
		case WM_CLOSE: 
		{
			ReleaseDC(Window, DC);
			delete PortName;
			delete DataPath;
			
			DeleteObject(GraphPen);
			DeleteObject(AxisPen);
			DeleteObject(Marker);
			DestroyWindow(Window);			
		}
			break;
		case WM_DESTROY: PostQuitMessage(0); break;
		default: return DefWindowProc(Window, Message, w, l);
	}
		
	return 0;
}
//=============================================================================

void DrawImg(HWND Window, HDC DC, RECT CR)
{
	DC = GetDC(Window);
	GetClientRect(Window, &CR);
	
		// настройка графики
	SelectObject(DC, GraphPen);
					
	SetMapMode(DC, MM_HIMETRIC);
	SetWindowExtEx(DC, CR.right, CR.bottom, NULL); // window size
	SetViewportExtEx(DC, CR.right, -CR.bottom, NULL); // viewport size
	SetViewportOrgEx(DC, CR.left, CR.bottom, NULL); // viewport start point
		// конец настройки графики
	
		// прорисовка данных на экране
	x = 0;                  
	for(int i = 0; i < DataSize; i++)
	{
		PixelValue[i].x = x;
		PixelValue[i].y = data[i] * 50;
		x += 11;
	}
	MoveToEx(DC, 0, 0, NULL);					
	Polyline(DC, PixelValue, DataSize);
		// конец прорисовки данных 
	                                                                                                                                                                                                                                                                                     
		// прорисовка прицела на максимальное значение
	int* MaxValue = new int(data[334]);
	int* MaxValuePixel = new int(data[334]);
	POINT* PixelPosition = new POINT;
	
	// нахождение максимально возможного значения
	// for(int i = 0; i < 34; i++)
	// {
		// if(*MaxValue < data[i])*MaxValue = data[i];
	// }                                                  
	// конец нахождения максимально возможного значения
	
	// поиск максимального значения в 2048-ми байтах	
	x = 334;
	for(int i = 334; i < 2080;i++)
	{
		if(data[i] > 80 && data[i] < 180)					
		{
			*MaxValuePixel = data[i];			
			x = i;	
		}		
	}	
	// конец поиска
	
	
	PrintMessage(x);	
	
	// собственно прорисовка прицела
	SelectObject(DC, Marker);
	MoveToEx(DC, PixelValue[x].x, CR.top, NULL);
	LineTo(DC, PixelValue[x].x, CR.bottom * 50);
	MoveToEx(DC, CR.left*50,PixelValue[x].y , NULL);
	LineTo(DC, CR.right*50, PixelValue[x].y);
	// ---/----
		// конец прорисовки прицела
		
	char* TimeElapsed = new char[10];
	sprintf(TimeElapsed, "%lf", (float)ElapsedTime/CLOCKS_PER_SEC);
	TextOut(DC, CR.left, CR.bottom + 500, TimeElapsed, getlen(TimeElapsed));
	
	
	ReleaseDC(Window, DC);	
	
	delete [] TimeElapsed;
	
	delete MaxValue;
	delete MaxValuePixel;
	delete PixelPosition;
	return;
}
//=============================================================================



