// (c) dzmat@yandex.ru 2015-2017 --------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ports.h"
#include "common.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



void LPT::open(){
    if(opened)return;
    h=CreateFile(name,GENERIC_WRITE,0,NULL,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if( h==INVALID_HANDLE_VALUE){
        debug_log(DB_ERR,"LPT::open","CreateFile returnet invalid handle");
        Application->MessageBox("LPT port open: invalide handle","Error",MB_OK);
        return;
    }
    opened=true;
};
void LPT::close(){
    if(opened){
        CloseHandle(h);
        h==INVALID_HANDLE_VALUE;
        opened=false;
    }
};
int LPT::write(unsigned char b){
    if(!opened)open();
    DWORD wr=0;
    WriteFile(h,&b,1,&wr,NULL);
    return wr;
};


//---------------------------------------------------------------------------
//******************** COMPort implementation *******************************
//---------------------------------------------------------------------------


bool COMPort::open(){
    if (opened)return true;
    DCB dcb;
    hPort = CreateFile(name,GENERIC_WRITE | GENERIC_READ,
        0,NULL,OPEN_EXISTING,0,NULL);
    //if (h==
    if (!GetCommState(hPort,&dcb)){
        err_msg="GetCommState() failed";
        debug_log(DB_ERR,"comport::open",err_msg.c_str());
        return false;
    }
    dcb.BaudRate = CBR_57600; //57600 Baud
    dcb.ByteSize = 8; //8 data bits
    dcb.Parity = NOPARITY; //no parity
    dcb.StopBits = ONESTOPBIT; //1 stop
    if (!SetCommState(hPort,&dcb)){
        err_msg="SetCommState() failed";
        debug_log(DB_ERR,"comport::open",err_msg.c_str());
        return false;
    }


    COMMTIMEOUTS timeouts;
    GetCommTimeouts(hPort,&timeouts);
    timeouts.ReadIntervalTimeout=10;
    timeouts.ReadTotalTimeoutMultiplier=0;
    timeouts.ReadTotalTimeoutConstant=100;
    SetCommTimeouts(hPort,&timeouts);
    opened=true;
    return true;
};
bool COMPort::write(char* data,DWORD n){
    debug_log(DB_INFO,"comport::write",
        (AnsiString("writing ")+n+" bytes").c_str()
    );
    DWORD byteswritten;
    bool retVal;
    while (n){
        retVal = WriteFile(hPort,data,n,&byteswritten,NULL);
        if (!retVal){
            int err=GetLastError();
            AnsiString msg;
            msg.sprintf("GetLastError=%d",err);
            debug_log(DB_ERR,"comport::write", msg.c_str());
            return false;
        }
        n-=byteswritten;
        data+=byteswritten;
        if (n)debug_log(DB_WARN,"comport::write", "write loop iteration");
    }
    return retVal;
}

  /*
int COMPort::read(int n)
{
    DCB dcb;
    int retVal;
    BYTE Byte;
    DWORD dwBytesTransferred;
    DWORD dwCommModemStatus;
    SetCommMask (hPort, EV_RXCHAR | EV_ERR); //receive character event
    WaitCommEvent (hPort, &dwCommModemStatus, 0); //wait for character
    if (dwCommModemStatus & EV_RXCHAR)
        ReadFile (hPort, &Byte, 1, &dwBytesTransferred, 0); //read 1
    else if (dwCommModemStatus & EV_ERR)
        retVal = 0x101;
    retVal = Byte;
    CloseHandle(hPort);
    return retVal;
}   */

void COMPort::close(){
        if (opened) {
            CloseHandle(hPort);
            opened=false;
        }
    };

int COMPort::read_ansi(AnsiString& s)
{
    const int BUF_SIZE=4096;
    if (!opened){
        debug_log(DB_ERR,"comport::read_ansi()","reading on closed port");
        return 0;
    }
    int retVal;
    char buf[BUF_SIZE+16];
    DWORD dwBytesRead;
    //DWORD dwCommModemStatus;
    if (!ReadFile (hPort, &buf, 4092, &dwBytesRead, 0)){
        int err=GetLastError();
        AnsiString s("ReadFile failed -");
        s += err+" "+ getwin32_errmsg(err);
        debug_log(DB_INFO,"comport::read_ansi", s.c_str() );
        s="";
        return 0;
    }
    buf[4092]=0;
    buf[dwBytesRead]=0;
    s=AnsiString(buf);
    if (dwBytesRead>0){
        debug_log(DB_INFO,"comport::read_ansi",
            (AnsiString("read ")+dwBytesRead+" bytes").c_str()
        );
        console_write(">>",s.c_str());
    }
    return dwBytesRead;
}


bool COMPort::write(AnsiString s)
{
    bool r=write(s.c_str(),s.Length());
    console_write("<<",s.c_str());
    return r;
}

bool COMPort::isOpened()
{
    return opened;
}
