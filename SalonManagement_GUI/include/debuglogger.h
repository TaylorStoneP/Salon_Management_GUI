#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H

/*
Author:				Taylor Phillips
Last Updated:		03/03/2021
Description:
			A compilation of tools to add to your debugging needs with
			easy colour modification and quick logging methods for
			debugging, traces, warnings and errors with different
			debugging levels to easily define the scope and depth of console output.
*/
#include <iostream>
#include <string>
#define TP_LINE_AND_FILE std::string("")+"{" + __FILE__ + ":"+ std::to_string(__LINE__)+ "}"
#define LOG_TAB "\t"
#define LOG_QUOTE "\""
#define LOG_POUND "\x9C"

#define TP_FULL_DEBUG 3
#define TP_STRONG_DEBUG 2
#define TP_WEAK_DEBUG 1
#define TP_RELEASE 0

#define TP_NO_CONSOLE 0
#define TP_WIN_CONSOLE 1
#define TP_WX_CONSOLE 2
//Change console type with defines above ^^^
#define TP_DEBUG_CONSOLE_TYPE TP_WX_CONSOLE

#define TP_LOGLVL TP_FULL_DEBUG
//Replace line above ^^^ with below to change scope of console logging
//\
#define TP_LOGLVL TP_FULL_DEBUG
//\
#define TP_LOGLVL TP_STRONG_DEBUG
//\
#define TP_LOGLVL TP_WEAK_DEBUG
//\
#define TP_LOGLVL TP_RELEASE

#if TP_DEBUG_CONSOLE_TYPE==TP_NO_CONSOLE
#define _dbg(x)
#else
#define _dbg(x) x
#endif


#if TP_DEBUG_CONSOLE_TYPE==TP_WIN_CONSOLE||TP_DEBUG_CONSOLE_TYPE==TP_NO_CONSOLE
#include <Windows.h>
#include <chrono>
#include <iostream>
#include <string>
enum class CONSOLE_COLOURS {
	black,
	dark_blue,
	dark_green,
	light_blue,
	red,
	dark_purple,
	orange,
	light_grey,
	grey,
	blue,
	green,
	teal,
	light_red,
	magenta,
	cream,
	white
};



enum class CONSOLE_BACKGROUNDS {
	black = 16 * 0,
	dark_blue = 16 * 1,
	dark_green = 16 * 2,
	light_blue = 16 * 3,
	red = 16 * 4,
	dark_purple = 16 * 5,
	orange = 16 * 6,
	light_grey = 16 * 7,
	grey = 16 * 8,
	blue = 16 * 9,
	green = 16 * 10,
	teal = 16 * 11,
	light_red = 16 * 12,
	magenta = 16 * 13,
	cream = 16 * 14,
	white = 16 * 15
};


class CONSOLE
{
	static CONSOLE* instance;
public:
	HANDLE hConsole;
	static CONSOLE* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CONSOLE();
		}
		return instance;
	}
	void SetColour(CONSOLE_COLOURS colour = CONSOLE_COLOURS::white, CONSOLE_BACKGROUNDS background = CONSOLE_BACKGROUNDS::black)
	{
		SetConsoleTextAttribute(hConsole, (int)colour + (int)background);
		return;
	}
	CONSOLE()
	{
		instance = this;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

};

//Main Logging Functions
#if TP_LOGLVL==TP_FULL_DEBUG
#define LOG_ERROR(x)	_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::light_red,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[ERROR]"<<TP_LINE_AND_FILE<<": "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_WARN(x)		_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::orange,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[WARNING]: "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_TRACE(x)	_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::cream,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[TRACE]:  "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_DEBUG(x)	_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::grey,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[DEBUG]:  "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x)	_dbg(x)
#define DEBUG_TRACE_CODE(x)			_dbg(x)
#define DEBUG_DEBUG_CODE(x)			_dbg(x)

#elif TP_LOGLVL==TP_STRONG_DEBUG
#define LOG_ERROR(x)	_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::light_red,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[ERROR]"<<TP_LINE_AND_FILE<<": "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_WARN(x)		_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::orange,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[WARNING]: "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_TRACE(x)	_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::white,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[TRACE]:  "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_DEBUG(x)

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x)	_dbg(x)
#define DEBUG_TRACE_CODE(x)			_dbg(x)
#define DEBUG_DEBUG_CODE(x)

#elif TP_LOGLVL==TP_WEAK_DEBUG
#define LOG_ERROR(x)	_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::light_red,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[ERROR]"<<TP_LINE_AND_FILE<<": "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_WARN(x)		_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::orange,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[WARNING]: "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_TRACE(x)
#define LOG_DEBUG(x)

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x)	_dbg(x)
#define DEBUG_TRACE_CODE(x) 
#define DEBUG_DEBUG_CODE(x)

#elif TP_LOGLVL==TP_RELEASE
#define LOG_ERROR(x)	_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::light_red,CONSOLE_BACKGROUNDS::black);\
						std::cout<<"[ERROR]"<<TP_LINE_AND_FILE<<": "<<x<<std::endl;\
						CONSOLE::GetInstance()->SetColour())
#define LOG_WARN(x)				
#define LOG_TRACE(x)			
#define LOG_DEBUG(x)

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x) 
#define DEBUG_TRACE_CODE(x) 
#define DEBUG_DEBUG_CODE(x)

#endif

//Sub Logging Functions
#define DEBUG_MEMORY FALSE	//Change to TRUE to enable memory allocation and deallocation

#if DEBUG_MEMORY == TRUE
#define LOG_ALLOCATION(type,m_this)		_dbg(LOG_DEBUG("Allocation    :  " LOG_QUOTE <<type<< LOG_QUOTE LOG_TAB "0x"<<m_this<<"."))
#define LOG_DEALLOCATION(type,m_this)	_dbg(LOG_DEBUG("Deallocation  :  " LOG_QUOTE <<type<< LOG_QUOTE LOG_TAB "0x"<<m_this<<"."))
#else
#define LOG_ALLOCATION(type,m_this)	
#define LOG_DEALLOCATION(type,m_this)
#endif

#define LOG_PRINT(text)					_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::white,CONSOLE_BACKGROUNDS::black);\
										std::cout<<"[OUTPUT]: "<<text;\
										CONSOLE::GetInstance()->SetColour())

#define LOG_PRINT_LINE(text)			_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::white,CONSOLE_BACKGROUNDS::black);\
										std::cout<<"[OUTPUT]: "<<text<<std::endl;\
										CONSOLE::GetInstance()->SetColour())

#define LOG(text)						CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::white,CONSOLE_BACKGROUNDS::black);\
										std::cout<<text;\
										CONSOLE::GetInstance()->SetColour()

#define LOG_LINE(text)					CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::white,CONSOLE_BACKGROUNDS::black);\
										std::cout<<text<<std::endl;\
										CONSOLE::GetInstance()->SetColour()

#define LOG_GET(text, data)				_dbg(CONSOLE::GetInstance()->SetColour(CONSOLE_COLOURS::white,CONSOLE_BACKGROUNDS::black);\
										std::cout<<"[INPUT]:  "<<text;\
										std::cin>>data;\
										CONSOLE::GetInstance()->SetColour())

class tp_Timer
{
public:
	// Record start time
	std::chrono::steady_clock::time_point m_start;// std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point m_finish;// std::chrono::high_resolution_clock::now();
	std::string m_message;
	tp_Timer(std::string message = "")
	{
		m_start = std::chrono::high_resolution_clock::now();
		m_finish = std::chrono::high_resolution_clock::now();
	}
	~tp_Timer()
	{
		m_finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = m_finish - m_start;
		LOG_DEBUG(LOG_QUOTE + m_message + LOG_QUOTE + LOG_TAB + "lasted : " + LOG_TAB + (elapsed.count() > 1 ? (std::to_string(elapsed.count()) + "s") : (std::to_string(elapsed.count() * 1000) + "ms")));
	}
};
#define DEBUG_TIME TRUE	//Change to TRUE to enable memory allocation and deallocation

#if DEBUG_TIME == TRUE
#define FUNC_TIMER(text)				_dbg(tp_Timer timer(text);)
#define CLASS_TIMER(text)				_dbg(tp_Timer timer = tp_Timer(text);)	
#else
#define FUNC_TIMER(text)
#define CLASS_TIMER(text)
#endif	
#elif TP_DEBUG_CONSOLE_TYPE==TP_WX_CONSOLE
#include <Windows.h>
#include <chrono>
#include <iostream>
#include <string>
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/graphics.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "extraColours.h"

class wxTextWindow : public wxFrame
{
public:
	wxTextCtrl* box;
	wxTextWindow(wxWindow* app) : wxFrame(NULL, wxID_ANY, "CONSOLE", wxDefaultPosition, wxSize(640, 360))
	{
		box = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE| wxTE_RICH);
		box->SetWindowStyle(wxBORDER_SUNKEN);
	}
};

class CONSOLE
{
	static CONSOLE* instance;
	wxTextWindow* logWin;
	CONSOLE()
	{
		instance = this;
		logWin = new wxTextWindow(NULL);
		logWin->box->SetBackgroundColour(tp_colour_menus::menu_black);
		logWin->box->SetEditable(false);
		logWin->Show(true);
	}
	void log_priv(std::string string, const tpCOLOURTYPE& fg_colour, const tpCOLOURTYPE& bg_colour)
	{
		instance->logWin->box->SetDefaultStyle(wxTextAttr(fg_colour, bg_colour));
		instance->logWin->box->WriteText(string);
		instance->logWin->box->SetDefaultStyle(wxTextAttr(tp_colour_misc::white, tp_colour_menus::menu_black));
	}
public:

	static CONSOLE* Get()
	{
		if (instance == nullptr)
		{
			instance = new CONSOLE();
		}
		else if (instance->logWin->box == nullptr)
		{
			instance = new CONSOLE();
		}
		return instance;
	}
	static void log(std::string string, const tpCOLOURTYPE& fg_colour = tp_colour_misc::white, const tpCOLOURTYPE& bg_colour = tp_colour_menus::menu_black)
	{
		Get();
		instance->log_priv(string, fg_colour,bg_colour);
	}
};

//Main Logging Functions
#if TP_LOGLVL==TP_FULL_DEBUG
#define LOG_ERROR(x)	_dbg(CONSOLE::log(std::string("\n")+"[ERROR]: "+TP_LINE_AND_FILE+": "+x,tp_colour_log::error);)

#define LOG_WARN(x)		_dbg(CONSOLE::log(std::string("\n")+"[WARNING]: "+x,tp_colour_log::warning);)

#define LOG_TRACE(x)	_dbg(CONSOLE::log(std::string("\n")+"[TRACE]: "+x,tp_colour_log::trace);)
	
#define LOG_DEBUG(x)	_dbg(CONSOLE::log(std::string("\n")+"[DEBUG]: "+x,tp_colour_log::debug);)

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x)	_dbg(x)
#define DEBUG_TRACE_CODE(x)			_dbg(x)
#define DEBUG_DEBUG_CODE(x)			_dbg(x)

#elif TP_LOGLVL==TP_STRONG_DEBUG
#define LOG_ERROR(x)	_dbg(tpLogger::log(std::string("\n")+"[ERROR]: "+TP_LINE_AND_FILE+": "+x,tp_colour_log::error);)

#define LOG_WARN(x)		_dbg(tpLogger::log(std::string("\n")+"[WANRING]: "+x,tp_colour_log::warning);)

#define LOG_TRACE(x)	_dbg(tpLogger::log(std::string("\n")+"[TRACE]: "+x,tp_colour_log::trace);)

#define LOG_DEBUG(x)

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x)	_dbg(x)
#define DEBUG_TRACE_CODE(x)			_dbg(x)
#define DEBUG_DEBUG_CODE(x)

#elif TP_LOGLVL==TP_WEAK_DEBUG
#define LOG_ERROR(x)	_dbg(tpLogger::log(std::string("\n")+"[ERROR]: "+TP_LINE_AND_FILE+": "+x,tp_colour_log::error);)

#define LOG_WARN(x)		_dbg(tpLogger::log(std::string("\n")+"[WANRING]: "+x,tp_colour_log::warning);)

#define LOG_TRACE(x)
#define LOG_DEBUG(x)

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x)	_dbg(x)
#define DEBUG_TRACE_CODE(x) 
#define DEBUG_DEBUG_CODE(x)

#elif TP_LOGLVL==TP_RELEASE
#define LOG_ERROR(x)	_dbg(tpLogger::log(std::string("\n")+"[ERROR]: "+TP_LINE_AND_FILE+": "+x,tp_colour_log::error);)

#define LOG_WARN(x)				
#define LOG_TRACE(x)			
#define LOG_DEBUG(x)

#define DEBUG_ERROR_CHECK_CODE(x)	_dbg(x)
#define DEBUG_WARN_CHECK_CODE(x) 
#define DEBUG_TRACE_CODE(x) 
#define DEBUG_DEBUG_CODE(x)

#endif

//Sub Logging Functions
#define DEBUG_MEMORY FALSE	//Change to TRUE to enable memory allocation and deallocation

#if DEBUG_MEMORY == TRUE
#define LOG_ALLOCATION(type,m_this)		_dbg(LOG_DEBUG("Allocation    :  " LOG_QUOTE <<type<< LOG_QUOTE LOG_TAB "0x"<<m_this<<"."))
#define LOG_DEALLOCATION(type,m_this)	_dbg(LOG_DEBUG("Deallocation  :  " LOG_QUOTE <<type<< LOG_QUOTE LOG_TAB "0x"<<m_this<<"."))
#else
#define LOG_ALLOCATION(type,m_this)	
#define LOG_DEALLOCATION(type,m_this)
#endif

#define LOG_PRINT(text)					_dbg(CONSOLE::log(std::string("")+"[OUTPUT]: "+text,tp_colour_log::light);)

#define LOG_PRINT_LINE(text)			_dbg(CONSOLE::log(std::string("\n")+"[OUTPUT]: "+text,tp_colour_log::light);)

#define LOG(text)						_dbg(CONSOLE::log(text,tp_colour_log::light);)

#define LOG_LINE(text)					_dbg(CONSOLE::log(std::string("\n")+text,tp_colour_log::light);)

#define LOG_GET(text, data)				


class tp_Timer
{
public:
	// Record start time
	std::chrono::steady_clock::time_point m_start;// std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point m_finish;// std::chrono::high_resolution_clock::now();
	std::string m_message;
	tp_Timer(std::string message = ""):m_message(message)
	{
		m_start = std::chrono::high_resolution_clock::now();
		m_finish = std::chrono::high_resolution_clock::now();
	}
	~tp_Timer()
	{
		m_finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = m_finish - m_start;
		LOG_DEBUG(LOG_QUOTE + m_message + LOG_QUOTE + LOG_TAB + " lasted : " + LOG_TAB + (elapsed.count() > 1 ? (std::to_string(elapsed.count()) + "s") : (std::to_string(elapsed.count() * 1000) + "ms")));
	}
};
#define DEBUG_TIME TRUE	//Change to TRUE to enable memory allocation and deallocation

#if DEBUG_TIME == TRUE
#define FUNC_TIMER(text)				_dbg(tp_Timer timer(text);)
#define CLASS_TIMER(text)				_dbg(tp_Timer timer = tp_Timer(text);)	
#else
#define FUNC_TIMER(text)
#define CLASS_TIMER(text)

#endif
#endif
#endif
