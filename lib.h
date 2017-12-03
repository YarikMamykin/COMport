#include "E:\\OneDrive\\Document\\Coding\\C\\Windows\\LIBS\\win.h"
#include "stdio.h"
#include "fcntl.h"
#include "stdint.h"
#include "sclass.h"
#include "time.h"




BOOL OpenComPort(void);
void InitCOMMCONFIGStruct(void);
char ItoC(int num);
BOOL WriteInFile(const char* path, HWND Window); 
void ReadCOMData(HWND Window);
void InitDCBStruct(void);
void InitTimeOuts(void);
void WriteMST(int code);
STRING GetTime();
STRING MakeFileName();
char* DefineComPort();
//----------------------------------------------------------------------------
// STRING* PortName = new STRING("com");
char* PortName = DefineComPort();
STRING* DataPath = new STRING("data.csv");
const int DataSize = 2088;
HANDLE Port;
COMMCONFIG ComPort;
COMMTIMEOUTS ComPortTO;
COMMPROP ComProps;
DCB PortDCBConfig;
uint8_t data[DataSize];
DWORD SizeofIncom;
clock_t ElapsedTime;

/*static const char day_name[][4] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };*/
static const char mon_name[][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

static time_t rawtime;
static struct tm * timeinfo;
//----------------------------------------------------------------------------
BOOL OpenComPort()
{
	// Example of opening and closing COM_Port
	//Port = CreateFile(PortName->value, GENERIC_READ , 0, NULL, OPEN_EXISTING, 0, NULL);
	Port = CreateFile(PortName, GENERIC_READ , 0, NULL, OPEN_EXISTING, FILE_SHARE_READ, NULL); // <<--- for asynchronic transmit\read  use FILE_FLAG_OVERLAPPED after OPEN_EXISTING
	if(Port == INVALID_HANDLE_VALUE)
	{return FALSE;}
	else {MessageBox(NULL, "COM port is OPENED", "Message", MB_OK);}	
	return TRUE;
}
//=============================================================================
void InitCOMMCONFIGStruct()
{
	ComPort.dwSize = sizeof(COMMCONFIG);
	ComPort.wVersion = 1;
	ComPort.dcb = PortDCBConfig;	
	ComPort.dwProviderSubType = PST_RS232;		
}
//=============================================================================
BOOL WriteInFile(const char* path, HWND Window)
{
	FILE *descriptor = fopen(path, "w");
	if(descriptor == NULL)
	{
		int check = creat(path, O_RDWR);
		if(check < 0){MessageBox(Window, "ERROR CREATING FILE", "ERROR", MB_OK); 
		fclose(descriptor);close(check);return FALSE;}
		else {close(check); descriptor = fopen(path, "w");}		
	}	
	for(int i = 0; i < DataSize; i++)
		{fprintf(descriptor, "%hu\n", data[i]);}	
			//{fputc(data[i], descriptor);} // write in file only bites
	fprintf(descriptor, "\n\n\nNumber of bytes received = %d\n\nElapsedTime = %.3f", SizeofIncom, ((float)ElapsedTime)/CLOCKS_PER_SEC);
	fclose(descriptor);
	return TRUE;
}
//=============================================================================
void InitDCBStruct()
{
	PortDCBConfig.DCBlength = sizeof(DCB);
	if(!GetCommState(Port, &PortDCBConfig))
	WriteMST(GetLastError());
	
	PortDCBConfig.BaudRate = CBR_19200;
 	PortDCBConfig.ByteSize = 8;
 	PortDCBConfig.Parity = NOPARITY;
 	PortDCBConfig.StopBits = ONESTOPBIT;
 	PortDCBConfig.fAbortOnError = FALSE;
 	PortDCBConfig.fDtrControl = DTR_CONTROL_DISABLE;
 	PortDCBConfig.fRtsControl = RTS_CONTROL_DISABLE;
 	PortDCBConfig.fBinary = TRUE;
 	PortDCBConfig.fParity = FALSE;
 	PortDCBConfig.fInX = FALSE;
    PortDCBConfig.fOutX = FALSE;
 	PortDCBConfig.XonChar = 0;
 	PortDCBConfig.XoffChar = (unsigned char)0xFF;
 	PortDCBConfig.fErrorChar = FALSE;
 	PortDCBConfig.fNull = FALSE;
 	PortDCBConfig.fOutxCtsFlow = FALSE;
 	PortDCBConfig.fOutxDsrFlow = FALSE;
 	PortDCBConfig.XonLim = 0;
 	PortDCBConfig.XoffLim = DataSize;
}
//=============================================================================
void InitTimeOuts()
{
	ComPortTO.ReadIntervalTimeout = 10000;
	ComPortTO.ReadTotalTimeoutMultiplier = 0;	
	ComPortTO.ReadTotalTimeoutConstant = 5000;
	ComPortTO.WriteTotalTimeoutMultiplier = 0;
	ComPortTO.WriteTotalTimeoutConstant = 0;
}
//=============================================================================
void WriteMST(int code)
{
	FILE *f = fopen("watcher.txt", "w");
	if(f != NULL)
	{fprintf(f, "Last error code = %d", code);}
	fclose(f);
	return;	
}

void NullDataBuff()
{
	for(int i = 0; i < DataSize; i++)
	{data[i] = (uint8_t)0;}
}

STRING GetTime()
{
	STRING result("\0");	
	static char ReceivedTime[30];
	time (&rawtime);
	timeinfo = localtime (&rawtime);
		
	sprintf(ReceivedTime, "%d-%.3s-%.2d;%.2d;%.2d-%d",timeinfo->tm_mday,mon_name[timeinfo->tm_mon],  timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_year+1900);
	
	result.value = ReceivedTime;
	
	result.ValueChanged();
	
	printf("\n\t%s", result.value);
	return result;
}

STRING MakeFileName()
{
	STRING time = GetTime();
	time.ValueChanged();	
	STRING FileName = time;	
	
	STRING Extention(".csv");
	Extention.ValueChanged();
	printf("\nExtension = %s", Extention.value);
	
	FileName = FileName + Extention; 	
	printf("\nFileName = %s",FileName.value);
	return FileName;
	
}

char* DefineComPort()
{
	FILE *f = fopen("ComPortAddress.txt", "r");
	if(f == NULL)return "\0";
	char* ComPortName = new char[10];
	fgets(ComPortName, 10, f);
	fclose(f);	
	delete f;
	return ComPortName;
}
