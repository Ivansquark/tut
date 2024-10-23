#include "dialog.hpp"

Dial::Dial(const wxString &title):wxDialog(nullptr,wxID_ANY,title,wxPoint(100,100),wxSize(300,300)) 
{
    init();
    //but->Centre();    
}
Dial::~Dial()
{
    delete but1;
    delete but2;
    delete txt;delete txt1;delete txt2;
    delete pan;
    delete timer1;delete timer2;
    //delete this;   
}
void Dial::init()
{
    pan = new wxPanel(this);
    but1 = new wxButton(pan,wxID_CLOSE,"Close",wxPoint(50,50),wxSize(50,50),5);
    but2 = new wxButton(pan,wxID_UP,"-",wxPoint(50,150),wxSize(50,50),5);
    Connect(wxID_UP,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Dial::onBut2Click));
    txt = new wxStaticText(pan,wxID_ANY,wxString("0"),wxPoint(150,50),wxSize(50,20),5);
    txt1 = new wxStaticText(pan,wxID_ANY,wxString("0"),wxPoint(150,80),wxSize(50,20),5);
    txt2 = new wxStaticText(pan,wxID_ANY,wxString("0"),wxPoint(150,100),wxSize(50,20),5);
    timer1 = new wxTimer(this,TIMER_ID);
    timer2 = new wxTimer(this,TIMER_ID1);
    timer1->Start(1000);
    timer2->Start(500);
    cl1 = new InterruptableClasses<1>;
    cl2 = new InterruptableClasses<2>;
    add = new Adder;
    add->x = &count;
    sub = new Subber;
    sub->x = &count1;
    cl1->addClass(add);
    cl2->addClass(sub);
    cl1->setVector();
    cl2->setVector();
}

void Dial::onTimer1(wxTimerEvent& event) 
{
    InterruptManager::call(1);
    txt1->SetLabel(wxString::Format(wxT("%d"),count1++));
}

void Dial::onTimer2(wxTimerEvent& event) 
{
    InterruptManager::call(2);
    txt2->SetLabel(wxString::Format(wxT("%d"),count2--));
}

void Dial::onBut1Click(wxCommandEvent& event) 
{
    //Destroy();
    delete this;
}
void Dial::onBut2Click(wxCommandEvent& event)
{
    count++;
    txt->SetLabel(wxString::Format(wxT("%d"),count));
}

BEGIN_EVENT_TABLE(Dial,wxDialog)
    EVT_BUTTON(wxID_CLOSE,Dial::onBut1Click)
    //EVT_BUTTON(wxID_UP,Dial::onBut2Click)
    EVT_TIMER(TIMER_ID,Dial::onTimer1)
    EVT_TIMER(TIMER_ID1,Dial::onTimer2)
END_EVENT_TABLE()
