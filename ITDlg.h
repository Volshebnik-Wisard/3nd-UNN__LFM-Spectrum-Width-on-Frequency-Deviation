
// ITDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"

// Диалоговое окно CITDlg
class CITDlg : public CDialogEx
{
	// Создание
public:
	CITDlg(CWnd* pParent = nullptr);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double T; //Период
	double F; //Максимальная частота

	double f0; //Начальная частота
	double phi0; //Начальная фаза
	double th; //Порог
	double fd; //Частота дискретизации
	int N; //Кол-во отчётов
	double f; //Ширина спектра (nn2 - nn1)
	double nn1;
	double nn2;
	double B = 0.00001; //Граница 3-го графика по y
	double C = 0.00001; //Граница 3-го графика по x
	double q = 0; //Отчёты 3-го графика

	double A = 0.00001;
	double alpha;

	//Для авто-эксперимента
	double Fmax; //Максимальная F
	double Fmin; //Минимальная F
	double Fstep; //Шаг по F
	int time; //Задержка (в миллисекундах)

	void FirstPlot();//Построение первого графика
	double signal(double T, double f0, double phi0, double F, int N, int i); //Сигнал
	void SecondPlot();//Построение второго графика
	void AddNoise();
	vector<double> X;//сигнал с шумом
	vector<double> Dot;//вектор точек
	vector<double> AA;//вектор модулей частот
	vector<double> A_Re;//действительная
	vector<double> A_Im;//и мнимая части частоты
	vector<double> t_vec; //Порог
	std::vector<double> f_;
	std::vector<double> F_;
	Drawer DisSin;//рисовалка для первого графика
	Drawer AK;//рисовалка для второго графика
	Drawer Signals;//рисовалка третьего графика
	void Find_borders();//нахождение n1*, n2*

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();

};
