// (c) dzmat@yandex.ru 2015-2017 --------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TButton *btOpenLPT;
    TMemo *Memo1;
    TEdit *Edit1;
    TButton *btWriteLPT;
    TButton *btCloseLPT;
    TButton *btLEDtest;
    TButton *btNextPort;
    TTimer *Timer1;
    TScrollBox *ScrollBox1;
    TEdit *Estart;
    TLabel *Label1;
    TEdit *Eend;
    TLabel *Label2;
    TButton *btGenerateTasks;
    TTimer *Timer_heartbeat;
    TLabel *Label3;
    TLabel *LTaskCount;
    TButton *btOpenCOM;
    TButton *btCloseCOM;
    TButton *bt_SendCommand;
    TButton *bt_Profile8;
    TComboBox *ComboBox1;
    TButton *btExport;
    TButton *btImport;
    TPageControl *PageControl1;
    TTabSheet *PagePorts;
    TTabSheet *PageTasks;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TTabSheet *PageResults;
    TTabSheet *PageLog;
    TMemo *Memo2;
    TButton *Button1_64;
    TButton *Button1_16;
    TButton *Button33_48;
    TButton *Button49_64;
    TButton *Button17_32;
    TButton *bt_SendCommands;
    TMemo *Memo_Commands;
    TButton *btClearQueue;
    TLabeledEdit *LabeledEdit1;
    TLabeledEdit *LabeledEdit2;
    TLabeledEdit *LabeledEdit3;
    TLabeledEdit *LabeledEdit4;
    TLabeledEdit *LabeledEdit5;
    TLabeledEdit *LabeledEdit6;
    TButton *btApplyLimits;
    void __fastcall btOpenLPTClick(TObject *Sender);
    void __fastcall btWriteLPTClick(TObject *Sender);
    void __fastcall btLEDtestClick(TObject *Sender);
    void __fastcall btCloseLPTClick(TObject *Sender);
    void __fastcall btNextPortClick(TObject *Sender);
    void __fastcall PortCheckClick(TObject *Sender);
    void __fastcall PortSelectClick(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btGenerateTasksClick(TObject *Sender);
    void __fastcall Timer_heartbeatTimer(TObject *Sender);
    void __fastcall btCloseCOMClick(TObject *Sender);
    void __fastcall btOpenCOMClick(TObject *Sender);
    void __fastcall bt_SendCommandClick(TObject *Sender);
    void __fastcall bt_Profile8Click(TObject *Sender);
    void __fastcall btExportClick(TObject *Sender);
    void __fastcall ScrollBox1MouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
    void __fastcall ScrollBox1MouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
    void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall btImportClick(TObject *Sender);
    void __fastcall Button1_64Click(TObject *Sender);
    void __fastcall Button1_16Click(TObject *Sender);
    void __fastcall Button17_32Click(TObject *Sender);
    void __fastcall Button33_48Click(TObject *Sender);
    void __fastcall Button49_64Click(TObject *Sender);
    void __fastcall bt_SendCommandsClick(TObject *Sender);
    void __fastcall btClearQueueClick(TObject *Sender);
    void __fastcall LabeledEditParamChange(TObject *Sender);
    void __fastcall btApplyLimitsClick(TObject *Sender);

private:
    unsigned char current_port;
    bool get_input_port_range(int& start, int& end);	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    void set_port(unsigned char p);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
