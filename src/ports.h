// (c) dzmat@yandex.ru 2015-2017 --------------------------------------------
#ifndef portsH
#define portsH

#include <vcl.h>
//---------------------------------------------------------------------------

class LPT{
    public:
    LPT(char* s){
        strncpy(name,s,64);
        name[63]=0;
        h==INVALID_HANDLE_VALUE;
        opened=false;
    };
    ~LPT(){
        if (opened)
        close();
    };
    void open();
    void close();
    int write(unsigned char b);
    private:
    HANDLE h;
    char name[64];
    bool opened;
};



class COMPort{
  public:
    COMPort(char* s){
		opened=false;
        strncpy(name,s,64);
        name[63]=0;
        hPort==INVALID_HANDLE_VALUE;
        opened=false;
    };
    bool open();
    void close();
    ~COMPort(){
		close();
    };
//    int read(int n);
    int read_ansi(AnsiString& s);
    bool write(char* data,DWORD n);



    AnsiString get_err_msg(){return err_msg;}
    bool write(AnsiString s);
    bool isOpened();
  private:
    AnsiString err_msg;
    HANDLE hPort;
    bool opened;
    char name[64];
protected:

};


#endif
