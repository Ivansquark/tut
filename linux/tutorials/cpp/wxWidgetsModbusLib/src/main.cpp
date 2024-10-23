/*!
	\file
	\brief Главная файл с которого стартует код
	\mainpage Приложение
	Состоит из:
	- Цикл главного приложения
	\ref MyApp	
*/
#include <wx/wx.h>
#include "mainframe.hpp"
/*!
	\brief класс приложения ждущего события в бесконечном цикле
	- Главное окно
	\ref MainFrame
*/
class MyApp : public wxApp
{
public:
	virtual bool OnInit()
	{	
		//! Создание главного окна
		mainFrame *frame = new mainFrame(wxT("opa"));
		//! Вызов главного окна
		frame->Show(true);
		return true;
	}
};
//void (*InterruptManager::IsrVi[10])()={nullptr};
//!  Макрос реализующий вызов main и реализацию бесконечного цикла
IMPLEMENT_APP(MyApp)

