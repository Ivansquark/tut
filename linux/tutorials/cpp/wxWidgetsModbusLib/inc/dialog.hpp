#ifndef DIALOG_HPP_
#define DIALOG_HPP_

#include "classes.hpp"

#include <wx/wx.h>
class Dial : public wxDialog
{
public: 
    Dial(const wxString &title);
    ~Dial();
    void onBut1Click(wxCommandEvent& event);
    void onBut2Click(wxCommandEvent& event);
    static constexpr uint8_t TIMER_ID=1;
    static constexpr uint8_t TIMER_ID1=2;
private:
    void init();
    void onTimer1(wxTimerEvent& event);
    void onTimer2(wxTimerEvent& event);
    wxPanel* pan{nullptr};
    wxButton* but1{nullptr};
    wxButton* but2{nullptr};
    wxStaticText* txt{nullptr};
    wxStaticText* txt1{nullptr};
    wxStaticText* txt2{nullptr};
    wxTimer* timer1{nullptr};
    wxTimer* timer2{nullptr};
    int count{0};
    int count1{0};
    int count2{0};
    InterruptableClasses<1>* cl1;
    InterruptableClasses<2>* cl2;
    Adder* add;
    Subber* sub;
    DECLARE_EVENT_TABLE()
};

#endif //DIALOG_HPP_