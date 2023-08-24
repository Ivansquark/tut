/*!
	\file
	\brief файл
	\page MainFrame
*/
#ifndef MAINFRAME_HPP_
#define MAINFRAME_HPP_

#include "dialog.hpp"
#include "modbus.h"
#include "modbus-rtu.h"
#include "modbus-private.h"
#include "modbus-rtu-private.h"

/*! \brief Класс главного окна
	\date 24.06.2020
	\warning alpha version
*/
class mainFrame: public wxFrame
{
public:
	/*!
	\brief Конструктор главного окна
	*/
	/*!
		\snippet mainframe.cpp Str
	*/	
    mainFrame(const wxString& title);
	//! запрет конструктора копирования 
	mainFrame(const mainFrame&) = delete;	
	//! запрет конструктора перемещения	
	mainFrame& operator=(const mainFrame& )= delete;
	/*!
	Метод срабатывает по событию нажатия на кнопку.
	\param [in]  event 
	\return {void}
	*/
    void onButExit(wxCommandEvent& event);  
	//! Указатель на диалоговое окно
    Dial* d{nullptr};
    uint16_t holdRegs[10]={0};
private:
	//! соединение порта
    void onButConnect(wxCommandEvent& event);
	//! чтение из порта
    void onButRead(wxCommandEvent& event);
	//! запись в порт
    void onButWrite(wxCommandEvent& event); 
    wxStaticText* lab1{nullptr};
    wxStaticText* lab2{nullptr};
    wxStaticText* lab3{nullptr};
    wxButton* but{nullptr};
    wxButton* butConnect{nullptr};
    wxButton* but2{nullptr};
    wxButton* but3{nullptr};
    int modbus_init();
    modbus_t* ctx{nullptr};
    int rc{0};
	//! метод соединения по модбас
    int modbusConnect();
    //! метод закрывающий соединение по модбас
	int modbusDisconnect();
    //! флаг соединения
	bool modbusConnectionFlag{false};
	//! метод чтения информации по модбас
    int modbusRead();
	//! таймер по которому вызывается метод чтения
    wxTimer* timer1{nullptr};
	//! метод по которому срабатывает таймер
    void onTimer1(wxTimerEvent& timEvent);
	//! макрос создающий статическую таблицу по которым связываются события
    DECLARE_EVENT_TABLE()
};
#endif //MAINFRAME_HPP_