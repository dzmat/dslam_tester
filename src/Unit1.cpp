// (c) dzmat@yandex.ru 2015-2017 --------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <list>
#include <stdio.h>
#include "Unit1.h"
#include "ports.h"
#include "common.h"
#include "tasks.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

const unsigned int line_to_byte[16]={
0,8,4,12,2,10,6,14,
1,9,5,13,3,11,7,15
};

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------


//volatile bool flag_break=false;
/*const BUF_SIZE=1024;
unsigned char buff[BUF_SIZE];
  */

LPT lpt("LPT1");
COMPort com("COM3");

const DEBUG_LEVEL CURRENT_DEBUG_LEVEL=DB_INFO;
void debug_log(DEBUG_LEVEL lvl,char* func,char* message)
{
    if (lvl>CURRENT_DEBUG_LEVEL)return;
    AnsiString msg;
    msg.sprintf("%s : %s",func,message);
    Form1->Memo1->Lines->Add(msg);
}
void console_write(char* prefix,char* message)
{
    AnsiString msg;
    msg.sprintf("%s %s",prefix,message);
    Form1->Memo2->Lines->Add(msg);
    debug_log(DB_INFO,"console_log()",msg.c_str());
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btOpenLPTClick(TObject *Sender)
{
    lpt.open();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btCloseLPTClick(TObject *Sender)
{
    lpt.close();
}
//---------------------------------------------------------------------------
void commutate_line(unsigned char b)
{
    int wr=lpt.write(line_to_byte[b&0xf]);
    debug_log(DB_INFO,"commutate_line",AnsiString().sprintf("writed %d bytes",wr).c_str());
    if (wr==0)
        Application->MessageBox("Error writing to commutator","commutate_line");
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btWriteLPTClick(TObject *Sender)
{
    int a=Edit1->Text.ToInt();
    set_port((unsigned char) a);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btLEDtestClick(TObject *Sender)
{
    for(int j=0;j<5;j++){
        for (int i=0;i<16;i++)
        {
            commutate_line(i);
            Sleep(100);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btNextPortClick(TObject *Sender)
{
    set_port(current_port+1);
}
//---------------------------------------------------------------------------
int timeout=0;

void set_port(unsigned char p)
{
    Form1->set_port(p);
}
void TForm1::set_port(unsigned char p)
{
    //port counts from 1
    current_port=p;
    Edit1->Text=AnsiString(p);

    p=(p-1)&0x0f;
    commutate_line(p);

    //set up notification
    Beep(1000,100);
    Timer1->Enabled=true;
    timeout=120;         //120 seconds
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    if (timeout==0){
        Timer1->Enabled=false;
        Beep(800,200);
    }else{
        timeout--;
    }
}
//---------------------------------------------------------------------------
void create_test_task(int port);
port_result result_arr[64];
void __fastcall TForm1::PortCheckClick(TObject *Sender)
{
    int port=((TButton *)Sender)->Tag;
    create_test_task(port);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PortSelectClick(TObject *Sender)
{
    for (int i=0;i<64;++i){
        result_arr[i].hide();
    }
    int port=((TSpeedButton *)Sender)->Tag;
    result_arr[port-1].show();  //ports count starts from 1, but index from 0
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
    for(int i=0;i<64;++i){
        result_arr[i].init(ScrollBox1,i,PortCheckClick,PortSelectClick);
        result_arr[i].hide();
   }
   result_arr[0].show();
   tasks::init();
   #ifndef NO_HARDWARE
   com.open();
   lpt.open();
   #else
   debug_log(DB_INFO,"Form1.OnCreate","NO_HARDWARE defined - skipping opening ports");
   #endif
   debug_log(DB_INFO,"Form1.OnCreate","done");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    for(int i=0;i<64;++i){
        result_arr[i].destroy();
    }
}
//---------------------------------------------------------------------------

std::list<Task*> tasks_list;
//---------------------------------------------------------------------------

class task_setprofile : public Task
{
    public:
    task_setprofile(int n){port=n;};
    bool virtual run_tick(){
        do_cmd("adsl set port admin status p%d dis\n",50);
        do_cmd("adsl apply profile p%d 8\n",50);
        do_cmd("adsl set port admin status p%d ena\n",50);
        return true;
    };
    private:
    void do_cmd(char* s,int time){
        AnsiString c;
        c.sprintf(s,port);
        com.write(c);
        Sleep(time);
        com.read_ansi(c);
    }
    int port;
};

class task_send_string : public Task
{
    public:
    task_send_string(AnsiString _s,int _delay){s=_s;delay=_delay;};
    bool virtual run_tick(){
        com.write(s);
        Sleep(delay);
        AnsiString tmp;
        com.read_ansi(tmp);
        return true;
    };
    private:
    AnsiString s;
    int delay;
};



void create_test_task(int port)
{
    Task* p=new task_test(port,&(result_arr[port-1]),&com);
    tasks_list.push_back(p);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::btGenerateTasksClick(TObject *Sender)
{
    int start,end;
    if (get_input_port_range(start,end)){
        for (int i=start;i<=end;++i)
            create_test_task(i);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer_heartbeatTimer(TObject *Sender)
{
    LTaskCount->Caption=AnsiString(tasks_list.size());
    if (!com.isOpened()){// refresh color indication according to port open status
        //debug_log(DB_ERR,"heartbeat","COM port is closed!");
        LTaskCount->Color=TColor(0x000000FF);
        return; //nothing to do when port is closed
    }else {
        LTaskCount->Color=TColor(0x0088ff88);
    }
    if (tasks_list.empty()){// here we can do some idle processing
        AnsiString input;
        if(com.read_ansi(input) )
            Memo1->Lines->Add(input);
    } else {
        Task* p=tasks_list.front();
        if(p->run_tick()){
            tasks_list.pop_front();
            delete p;
            if (tasks_list.empty()){
                Timer_heartbeat->Interval=1000;
                // Play notification
                for(int i=0;i<5;++i){
                    Beep(1200,200);
                    Sleep(800);
                }
            }
        }

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btOpenCOMClick(TObject *Sender)
{
    com.open();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btCloseCOMClick(TObject *Sender)
{
    com.close();
}

void __fastcall TForm1::bt_SendCommandClick(TObject *Sender)
{
//    ComboBox1->Text
    com.write(ComboBox1->Text+"\n");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_Profile8Click(TObject *Sender)
{
    int start,end;
    if (get_input_port_range(start,end)){
        Task* p;
        p=new task_setheartbeat(Timer_heartbeat,250);
        tasks_list.push_back(p);
        for (int i=start;i<=end;++i){
            p=new task_setprofile(i);
            tasks_list.push_back(p);
        }
        p=new task_setheartbeat(Timer_heartbeat,1000);
        tasks_list.push_back(p);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btExportClick(TObject *Sender)
{
    FILE* f;
    if(SaveDialog1->Execute()){
        AnsiString fname=OpenDialog1->FileName;
        f=fopen(fname.c_str(),"wt");
        if (!f){
            Application->MessageBox("не могу открыть выходной файл","Ошибка",MB_OK);
            return;
        }
        for(int i=0;i<64;i++){
            fprintf(f,"\n------ port %d ------------------------\n",i+1);
            TStrings* l= result_arr[i].lines();
            int c=l->Count;
            for(int j=0;j<c;++j){
                AnsiString s=l->Strings[j];
                fprintf(f,"%s\n",s.c_str());
            }
        }
        fclose(f);
    }
}
//---------------------------------------------------------------------------

bool TForm1::get_input_port_range(int& start, int& end)
{
    try{
        start=Estart->Text.ToInt();
        end  =Eend  ->Text.ToInt();
    }catch(EConvertError& e){
        Application->MessageBox("Введено нечисловое значение",
            "Ошибка диапазона",MB_OK);
        return false;
    };
    if (start>=1 && end <=64 && start<=end){
        return true;
    }
    Application->MessageBox("Введен неверный диапазон портов\n"
    "Должно быть 1 <= \"начальный порт\" <= \"конечный порт\" <= 64",
        "Ошибка диапазона",MB_OK);
    return false;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBox1MouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
//Application->MessageBox("wheel down","msg",MB_OK);
TControlScrollBar* sb= ScrollBox1->VertScrollBar;
    sb->Position = sb->Position + sb->Increment;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBox1MouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{

TControlScrollBar* sb= ScrollBox1->VertScrollBar;
    sb->Position = sb->Position - sb->Increment;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{

Application->MessageBox("wheel ","Form1",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btImportClick(TObject *Sender)
{

    FILE* f;
    AnsiString fname;
    if(OpenDialog1->Execute()){
        fname=OpenDialog1->FileName;
    } else {
        return;
    }
    TStringList *ls=new TStringList();
    try{
        ls->LoadFromFile(fname.c_str());
    }
    catch(const EFOpenError &oe){
        Application->MessageBox("Ошибка открытия файла","Ощибка");
        return;
    }
    const char* prefix="------ port ";
    for(int i=0;i<64;++i){
        result_arr[i].hide();
        result_arr[i].clear();
    }
    int cur_port=-1;
    TStrings* lines=NULL;
    AnsiString port_str;
    for (int i=0;i<ls->Count;++i){
        AnsiString s=ls->Strings[i];
        if (skip_head_extract_value(s,prefix,port_str)){
            cur_port=port_str.ToIntDef(-1);
            //port number obtained
            if (cur_port>=1 && cur_port<=64){
                lines=result_arr[cur_port-1].lines();
            }else{
                lines=NULL;
            }
        }else if (lines!=NULL){
            lines->Add(s);
        }
    }
    delete ls;
    for(int i=0;i<64;++i){
        result_arr[i].analize();
    }
    result_arr[0].show();
}
//---------------------------------------------------------------------------

void __fastcall  TForm1::Button1_64Click(TObject *Sender){Estart->Text= "1";Eend->Text="64";}
void __fastcall  TForm1::Button1_16Click(TObject *Sender){Estart->Text= "1";Eend->Text="16";}
void __fastcall TForm1::Button17_32Click(TObject *Sender){Estart->Text="17";Eend->Text="32";}
void __fastcall TForm1::Button33_48Click(TObject *Sender){Estart->Text="33";Eend->Text="48";}
void __fastcall TForm1::Button49_64Click(TObject *Sender){Estart->Text="49";Eend->Text="64";}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_SendCommandsClick(TObject *Sender)
{
    int cnt= Memo_Commands->Lines->Count;
    Task* p;
    p=new task_setheartbeat(Timer_heartbeat,200);
    tasks_list.push_back(p);
    for(int i=0;i<cnt;++i){
        AnsiString cmd=Memo_Commands->Lines->Strings[i];
        p=new task_send_string(cmd+"\n",100);
        tasks_list.push_back(p);
    }
    p=new task_setheartbeat(Timer_heartbeat,1000);
    tasks_list.push_back(p);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btClearQueueClick(TObject *Sender)
{
    while (!tasks_list.empty()){
        Task* p=tasks_list.front();
        delete p;
        tasks_list.pop_front();
    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::LabeledEditParamChange(TObject *Sender)
{
    TLabeledEdit* S=(TLabeledEdit*)Sender;
    int tag=S->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btApplyLimitsClick(TObject *Sender)
{
    // do something
}

//---------------------------------------------------------------------------

