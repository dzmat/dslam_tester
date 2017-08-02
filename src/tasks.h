// (c) dzmat@yandex.ru 2015-2017 --------------------------------------------

#ifndef tasksH
#define tasksH
#include "common.h"
#include "ports.h"
#include <buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class port_result{
public:
    port_result(){
    };
    ~port_result(){
        destroy();
    };
    enum E_RESULTS{RES_OK,RES_WAIT,RES_DEAD,RES_HALFDEAD,RES_NONE};
    void set_res2(E_RESULTS r);
    void init(TWinControl* parent,int i,TNotifyEvent OnClick_check,TNotifyEvent OnClick_select);
    void hide();
    void show();
    void analize();
    void clear(){
        set_res2(RES_NONE);
        m->Lines->Clear();
    };
    TStrings* lines(){return m->Lines;};
    void add_string(const AnsiString& s){
        m->Lines->Add(s);
    };
    void destroy();
private:
    //TMemo* m;
    TRichEdit* m;
    TLabel* l;
    TButton* b;     //rechecker button
    TSpeedButton* sel;   //selector button
};


//---------------------------------------------------------------------------


class Task{
    public:
    bool virtual run_tick()=0;
};

void set_port(unsigned char p);//defined in Unit1.cpp

class task_test : public Task

{
    public:
    task_test(int n,port_result* res,COMPort* com_){
        port_res=res;
        com=com_;
        port=n;
        state=0;
        port_res->clear();
        port_res->set_res2(port_result::RES_WAIT);
    };
    bool virtual run_tick();
    bool fix_result();
    private:
    int port,state,cnt;
    port_result* port_res;
    COMPort* com;
    ~task_test(){
        //no result in case of premature destruction
        if (state!=2)port_res->set_res2(port_result::RES_NONE);
    }
#undef INFO(a)
};

class task_setheartbeat : public Task
{
    public:
    task_setheartbeat(TTimer* timer_,int n){timer=timer_;timeout=n;};
    bool virtual run_tick();
    private:
    int timeout;
    TTimer* timer;
};
//---------------------------------------------------------------------------

namespace tasks{
void init();
}

#endif
