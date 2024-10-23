#include "mainframe.hpp"

mainFrame::mainFrame(const wxString& title):wxFrame(nullptr,wxID_ANY,title,wxPoint(500,200),wxSize(800,800))
{
    wxPanel* pan = new wxPanel(this);
    lab1 = new wxStaticText(pan,wxID_ANY,"1",wxPoint(350,300),wxSize(200,40),5);
    lab2 = new wxStaticText(pan,wxID_ANY,"2",wxPoint(350,500),wxSize(100,20),5);
    lab3 = new wxStaticText(pan,wxID_ANY,"3",wxPoint(350,700),wxSize(100,20),5);
    wxFont font = wxFont(20, wxFONTFAMILY_ROMAN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false);
    wxColour col(000,50,50,200);
    lab1->SetForegroundColour(wxColour(*wxRED));
    lab1->SetBackgroundColour(col);
    lab1->SetFont(font);
    but = new wxButton(pan,wxID_EXIT,"exit",wxPoint(20,20),wxSize(100,100),5);
    butConnect = new wxButton(pan,5001,"connect",wxPoint(20,250),wxSize(100,100),5);
    but2 = new wxButton(pan,5002,"read",wxPoint(20,450),wxSize(100,100),5);
    but3 = new wxButton(pan,5003,"write",wxPoint(20,650),wxSize(100,100),5);
    Connect(5001,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(mainFrame::onButConnect));
    Connect(5002,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(mainFrame::onButRead));
    Connect(5003,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(mainFrame::onButWrite));
    but->SetLabel("opa");butConnect->SetSize(90,90);but2->SetSize(90,90);but3->SetSize(90,90);
	Centre();
	/// [Str]
    ctx = modbus_new_rtu("\\\\.\\COM11", 9600, 'N', 8, 1); //none parity 8-bits 1-stop bits
	/// [Str]
    modbus_init();

    timer1 = new wxTimer(this, 5000);
    Connect(5000,wxEVT_TIMER,wxTimerEventHandler(mainFrame::onTimer1));    
}

void mainFrame::onButExit(wxCommandEvent& event)
{
    if(d==nullptr)
    {
        d = new Dial("qqq");
        //d->ShowModal();
        d->Show();
    }
    else {Close();}
}

void mainFrame::onButConnect(wxCommandEvent& event) 
{
    if(!modbusConnectionFlag)
    {
        modbusConnect();    
        modbusConnectionFlag=true;   
    }
    else
    {
        timer1->Stop();
        modbusDisconnect();
        modbusConnectionFlag=false;
    }            
}

void mainFrame::onButRead(wxCommandEvent& event) 
{
    timer1->Start(500);   
}

void mainFrame::onTimer1(wxTimerEvent& timEvent)
{
    modbusRead();
}

int mainFrame::modbusRead()
{
    rc = modbus_read_registers(ctx, 1, 2, holdRegs); // rc number of holding registers
    if (rc == -1) 
    {
        wxMessageBox("Unable to read modbus registers\n",modbus_strerror(errno));
        //fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
    }   
    uint32_t x=0;
    float y=0;
    x = (holdRegs[0]<<16|holdRegs[1]);
    y = *(reinterpret_cast<float*>(&x));
    //for (uint8_t i=0; i < rc; i++) 
    lab1->SetLabel(wxString::Format(wxT("%f"),y));
    return rc;
}

void mainFrame::onButWrite(wxCommandEvent& event) 
{
    Close();
}

int mainFrame::modbus_init() 
{    
    if (ctx == nullptr) 
    {
        wxMessageBox("Unable to create the libmodbus context\n",modbus_strerror(errno));
        //fprintf(stderr, "Unable to create the libmodbus context\n");
        return -1;
    }
    rc = modbus_set_slave(ctx, 0x01);
    if (rc == -1) 
    {
        wxMessageBox("Unable to create the libmodbus context\n",modbus_strerror(errno));
        //fprintf(stderr, "Invalid slave ID\n");
        modbus_free(ctx);
        return -1;
    }    
    modbus_set_response_timeout(ctx, 0, 200000);
    return 0;
    //modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485); //only on linux
}

int mainFrame::modbusConnect() 
{
    
    if (modbus_connect(ctx) == -1) 
    {
        wxMessageBox("Connection failed:",modbus_strerror(errno));
        //fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }else 
    {
        timer1->Stop();
        butConnect->SetLabel("Disconnect1");        
        return 0;
    }
}
int mainFrame::modbusDisconnect() 
{    
    modbus_close(ctx);
    //modbus_free(ctx);
    butConnect->SetLabel("Connect1");
    return 1;
}
BEGIN_EVENT_TABLE(mainFrame,wxFrame)
    EVT_BUTTON(wxID_EXIT,mainFrame::onButExit)
END_EVENT_TABLE()
