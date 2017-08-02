// (c) dzmat@yandex.ru 2015-2017 --------------------------------------------

#include <list>
#pragma hdrstop

#include "tasks.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void port_result::init(TWinControl* parent,int i,
            TNotifyEvent OnClick_check,TNotifyEvent OnClick_select)
{
    int STEP_X=240;
    int STEP_Y=180;
    int OFFS_X=10;
    int OFFS_Y=10+8*25+10;
    int cx=i%4;int cy=i/4;
    int Left=OFFS_X+STEP_X*cx;
    int Top=OFFS_Y+STEP_Y*cy;

//    m=new TMemo(parent);
    m=new TRichEdit(parent);
    m->Parent=parent;
    m->Left=175;
    m->Top=120;
    m->Width=710;
    m->Height=500;
    m->Anchors<<akBottom;
    m->Visible=true;
    m->ScrollBars=ssBoth;
    m->Font->Name="Courier New";
    m->Font->Size=8;
    m->Font->Pitch=fpFixed;

    l=new TLabel(parent);
    l->Parent=parent;
    l->Left=20;
    l->Top=235;
    l->Width=100;
    l->Height=20;
    l->Visible=true;
    l->Caption=AnsiString("Порт ")+AnsiString((i+1));

    b=new TButton(parent);
    b->Parent=parent;
    b->Left=70;
    b->Top=230;
    b->Width=50;
    b->Height=20;
    b->Visible=true;
    b->Caption=AnsiString("Check");
    b->Tag=i+1;
    b->OnClick=OnClick_check;

    //init hadle buttons
    STEP_X=55;
    STEP_Y=25;
    OFFS_X=10;
    OFFS_Y=10;
    cx=i%16;cy=i/16;
    Left=OFFS_X+STEP_X*cx;
    Top=OFFS_Y+STEP_Y*cy;

    sel=new TSpeedButton(parent);
    sel->Parent=parent;
    sel->Left=Left;
    sel->Top=Top;
    sel->Width=50;
    sel->Height=23;
    sel->Visible=true;
    sel->Caption=AnsiString(i+1);
    //sel->Font->Height=sel->Font->Height5;
    sel->Font->Size=sel->Font->Size+4;
    TFontStyles fs;fs<<fsBold;
    sel->Font->Style=fs;
    sel->Tag=i+1;
    sel->GroupIndex=1;
    sel->OnClick=OnClick_select;
    set_res2(RES_NONE);
}

void port_result::hide()
{
    m->Enabled=false;
    m->Visible=false;
    l->Enabled=false;
    l->Visible=false;
    b->Enabled=false;
    b->Visible=false;
    sel->Down=false;
}
void port_result::show()
{
    m->Enabled=true;
    m->Visible=true;
    l->Enabled=true;
    l->Visible=true;
    b->Enabled=true;
    b->Visible=true;
    sel->Down=true;
}


bool task_test::run_tick(){
#define INFO1(a) debug_log(DB_INFO,"test_tes::run_tick",a)
    switch (state){
        case 0:
            set_port(port);
            state=1;
            cnt=0;
            return false;
        case 1:
            cnt++;
            if (cnt>150){//after 150 sec fix results anyway
                return fix_result();
            }else{//maybe trap indicate that link already up
                AnsiString s;
                com->read_ansi(s);
                if (s.Pos("Upstream Data Rate") ||
                    s.Pos("-> DATA"))
                {
                    return fix_result();
                }
            }
            return false;
        case 2:
            return true;
    };
    return true;
}
#undef INFO1
bool task_test::fix_result(){
    AnsiString s;
    Sleep(300);
    com->read_ansi(s);//clear input buffer just for case
    s.sprintf("adsl show port state p%d\n",port);
    com->write(s);Sleep(800);
    com->read_ansi(s);
    port_res->clear();
    port_res->add_string(s);
    port_res->analize();
    state=2;
    return true;
}

#define INFO(a) debug_log(DB_INFO,"task_sethearbeat::run_tick",a)
bool task_setheartbeat::run_tick(){

    timer->Interval=timeout;
    AnsiString msg;msg.sprintf(" hearbeat set to %d",timeout);
    INFO(msg.c_str());
    return true;
}
#undef INFO(a)

class RELine{
    public:
    RELine(TRichEdit *_re,int _begin=0,int _len=0){re=_re;begin=_begin;len=_len;}
    RELine(const RELine& rel)
        :re(rel.re)
        ,begin(rel.begin)
        ,len(rel.len)
    {}
    ~RELine(){}
    size_t Length() const {return len;};
    AnsiString make_string()const{
        return re->Text.SubString(begin+1,len);// AnsiString Substring() uses 1-based indicies
    };
    void set_color(TColor cl){
        re->SelStart=begin;
        re->SelLength=len;
        re->SelAttributes->Color=cl;
    };
    private:
    int begin,len;
    TRichEdit *re;
};

bool skip_head_extract_value(const RELine& re,const char* h,AnsiString& res)
{
    AnsiString s(re.make_string());
    int h_len=strlen(h);
    int s_len=s.Length();
    if (strncmp(s.c_str(),h,h_len)!=0)return false;
    //string found, start exctracting value
    res="";
    int j=h_len+1;
    while (j<=s_len){
        char ch=s[j];
        if( isdigit(ch) || ch=='.'){
            res+=ch;
            ++j;
        }else break;
    }
    return true;
}

typedef std::list<RELine> Chops;

int chops_from_RichEdit(TRichEdit *re, Chops &res)
{
    res.clear();
    AnsiString txt=re->Text;
    char* p=txt.c_str();
    int beg=0;
    int pos=0;
    while(p[pos]!=0){
        if ( p[pos]=='\n' ){
            int len=pos-beg;
            res.push_back(RELine(re,beg,len));
            ++pos;
            beg=pos;
        }
        else {
            ++pos;
        }
    }
    return 0;
}


/*int check_parametr(TRichEdit* m,char* prefix,char cmp_type,double control_val,int points)
{
    AnsiString val_str;
    for (int i=0;i<m->Lines->Count;++i){
        AnsiString s=(*(m->Lines))[i];//->operator[](i);
        if (skip_head_extract_value(s,prefix,val_str)){
            char old_sep=DecimalSeparator;
            DecimalSeparator='.';
            double val=val_str.ToDouble();
            DecimalSeparator=old_sep;
            switch (cmp_type){
                case '>':
                    if (val>control_val)return 0;//ok
                    set_line_color_red();
                    return points;//not passed
                case '<':
                    if (val<control_val)return 0;//ok
                    set_line_color_red();
                    return points;//not passed
                default:
                //should never get here, just precaution for a case of bad refactoring
                    throw "Invalid comparator type";
            };
        }
    }
    return 5;//if we get here so we got missing string,treat it as half error
}*/

/*int check_line_for_parametr(const AnsiString& line,const char* param,char cmp_type,double control_val,int points)
{
    AnsiString val_str;
    if (skip_head_extract_value(line,param,val_str)){
        char old_sep=DecimalSeparator;
        DecimalSeparator='.';
        double val=val_str.ToDouble();
        DecimalSeparator=old_sep;
        switch (cmp_type){
            case '>':
                if (val>control_val)return 0;//ok
                return points;//not passed
            case '<':
                if (val<control_val)return 0;//ok
                return points;//not passed
            default:
            //should never get here, just precaution for a case of bad refactoring
                throw "Invalid comparator type";
        };
    }
    return 0;
}

 */

namespace tasks{

struct st_cmp_token{
    st_cmp_token(
        const char* _key=0,
        char  _cmp=0,
        double _val=0,
        int _points=0
    ){
        key=_key;
        cmp=_cmp;
        val=_val;
        points=_points;
    }
    const char* key;
    char  cmp;
    double val;
    int points;
};

const int N_TOKENS=6;
st_cmp_token cmp_arr[N_TOKENS];
void init()
{
    cmp_arr[0]=st_cmp_token("	Attainable Rate Ds    : ",'>',24000,4);
    cmp_arr[1]=st_cmp_token("	Ds Line Rate          : ",'>',15000,4);
    cmp_arr[2]=st_cmp_token("	Attainable Rate Us    : ",'>',1100,4);
    cmp_arr[3]=st_cmp_token("	Us Line Rate          : ",'>',1000,4);
    cmp_arr[4]=st_cmp_token("	DS Line Attenuation   : ",'<',6.0,4);
    cmp_arr[5]=st_cmp_token("	US Line Attenuation   : ",'<',10.0,4);
}

int get_success_points(RELine &line,const st_cmp_token& tok)
{
    AnsiString val_str;
    if (skip_head_extract_value(line,tok.key,val_str)){
        double val=val_str.ToDouble();
        bool success=false;
        switch (tok.cmp){
            case '>':
                if (val > tok.val)success=true;
                break;
            case '<':
                if (val < tok.val)success=true;
                break;
            default:
            //should never get here, just precaution for a case of bad refactoring
                throw "Invalid comparator type";
        };
        if(success){
            line.set_color(clGreen);
            return tok.points;//ok
        }else{
            line.set_color(clRed);
            return 0;
        }
    }
    //color unchanged
    return 0;
}


} //end of namespace tasks


void port_result::analize()
{
    if (m->Lines->Count==0){
        set_res2(RES_NONE);
        return;
    }
    Chops strs;
    chops_from_RichEdit(m, strs);
    char old_sep=DecimalSeparator;
    DecimalSeparator='.';
    //get_success_points(*i)
    int points=0;
    for (Chops::iterator it=strs.begin();it!=strs.end();++it){
        for (int j=0;j<tasks::N_TOKENS;++j){
            points+=get_success_points( *it, tasks::cmp_arr[j] );
        }
    }
    DecimalSeparator=old_sep;
    if (points < 14){// dead port
        set_res2(RES_DEAD);
        return;
    }
    if (points < 19){// half dead
        set_res2(RES_HALFDEAD);
        return;
    }
    set_res2(RES_OK);
}
