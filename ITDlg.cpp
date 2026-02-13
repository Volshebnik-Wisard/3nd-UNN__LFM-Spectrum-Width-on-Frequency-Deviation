
// ITDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT.h"
#include "ITDlg.h"
#include "afxdialogex.h"
#include <windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define M_PI 3.14159265358979323846



// Диалоговое окно CITDlg
CITDlg::CITDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT_DIALOG, pParent)
	, T(8)
	, F()
	, th(20)
	, fd(100)
	, N(501)
	, f(0)
	, f0(0)
	, phi0(0.785)
	, Fmax(50)
	, Fmin(1)
	, Fstep(1)
	, time(0)
	, alpha(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CITDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, T);
	DDX_Text(pDX, IDC_EDIT2, F);
	DDX_Text(pDX, IDC_EDIT6, th);
	DDX_Text(pDX, IDC_EDIT8, alpha);
	DDX_Text(pDX, IDC_EDIT4, fd);
	DDX_Text(pDX, IDC_EDIT5, N);
	DDX_Text(pDX, IDC_EDIT7, f);
	DDX_Text(pDX, IDC_EDIT10, f0);
	DDX_Text(pDX, IDC_EDIT3, phi0);
	DDX_Text(pDX, IDC_EDIT11, Fmax);
	DDX_Text(pDX, IDC_EDIT12, Fmin);
	DDX_Text(pDX, IDC_EDIT13, Fstep);
	DDX_Text(pDX, IDC_EDIT14, time);
}

BEGIN_MESSAGE_MAP(CITDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CITDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CITDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CITDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Обработчики сообщений CITDlg

BOOL CITDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	DisSin.Create(GetDlgItem(IDC_PIC1)->GetSafeHwnd());
	AK.Create(GetDlgItem(IDC_PIC2)->GetSafeHwnd());
	Signals.Create(GetDlgItem(IDC_PIC3)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CITDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CITDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CITDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double CITDlg::signal(double T, double f0, double phi0, double F, int N, int i)
//Сигнал
{
	return cos(phi0 + (2 * M_PI * ((f0 * (i / fd)) + (((F - f0) / (T)) * pow(i / fd, 2) / 2))));
}

void CITDlg::FirstPlot()
//Первый график (Сигнал)
{
	UpdateData(TRUE);

	for (int i = 0; i < N; i++) {
		double temp = signal(T, f0, phi0, F, N, i);
		X.push_back(temp);
		Dot.push_back(i);
	}
	AddNoise();
	DisSin.DrawGrid(X, 1, Dot, N, 1, Dot[N - 1]);
	DisSin.DrawAnimation(X, 1, Dot, N, 1, Dot[N - 1], 1);
}

double random()
//Генератор рандома
{
	return rand() - RAND_MAX / 2;
}

void CITDlg::AddNoise()
//Шум
{
	double* g = new double[N]; //параметр шума
	for (int i = 0; i < N; i++) {
		g[i] = 0;
		for (int k = 0; k < 12; k++) {
			g[i] += random();
		}
	}
	double beta(0);  //параметр шума
	double chisl(0), znam(0); //временные переменные
	for (int i = 0; i < N; i++) {
		chisl += X[i] * X[i];
		znam += g[i] * g[i];
	}
	beta = sqrt((alpha / 500) * chisl / znam);
	for (int i = 0; i < N; i++) {
		X[i] += beta * g[i];
		if (X[i] > 1) A = X[i];
	}
}

void CITDlg::SecondPlot()
//Второй график (Спектр)
{
	Dot.clear();
	for (int k = 0; k < N; k++)
	{
		double Re(0), Im(0);
		for (int n = 0; n < N; n++)
		{
			Re += X[n] * cos(2 * M_PI * k * n / N);
			Im -= X[n] * sin(2 * M_PI * k * n / N);
		}
		A_Re.push_back(Re);
		A_Im.push_back(Im);
		AA.push_back(sqrt(Re * Re + Im * Im));
		Dot.push_back(k * fd / N);
		if (AA[k] > A) A = AA[k];
	}
	th = A / 5;
	th = round(th * 1000) / 1000;
	for (int k = 0; k < N; k++)
	{
		t_vec.push_back(th);
	}
	AK.DrawGrid(AA, 2, Dot, N, A, Dot[N - 1]);
	AK.DrawAnimation(AA, 2, Dot, N, A, Dot[N - 1], 3);
	AK.DrawAnimation(t_vec, 2, Dot, N, A, Dot[N - 1], 1);

}

void CITDlg::Find_borders()
//Ширина спектра
{
	for (int i = 0; i < N / 2; i++)
	{
		if (AA[i] >= th) {
			nn1 = i * fd / N;
			break;
		}
	}
	for (int i = N / 2; i > 0; i--)
	{
		if (AA[i] >= th) {
			nn2 = i * fd / N;
			break;
		}
	}
	f = nn2 - nn1;
	f_.push_back(f);
	F_.push_back(F);
	if (f_.back() > B) B = 10 * f_.back() / 9;
	if (F_.back() > C) C = 10 * F_.back() / 9.5;
	f = round(f * 1000) / 1000;
}

void CITDlg::OnBnClickedButton4()
//Сбросить всё
{
	f_.clear();
	F_.clear();
	q = 0;
	B = 0.00001;
	C = 0.00001;
}

void CITDlg::OnBnClickedOk()
//Задаваемый эксперимент
{
	UpdateData(TRUE);
	X.clear();
	Dot.clear();
	AA.clear();
	A_Re.clear();
	A_Im.clear();
	t_vec.clear();
	//построить графики
	FirstPlot();
	SecondPlot();
	Find_borders();
	q++;
	Signals.DrawGrid(f_, 2, F_, q, B, C);
	Signals.DrawAnimation(f_, 2, F_, q, B, C, 3);
	A = 0.00001;
	//почистить память
	UpdateData(FALSE);
}

//Для авто-эксперимента
void CITDlg::OnBnClickedButton2()
//Автоматизированный эксперимент
{
	UpdateData(TRUE);
	f_.clear();
	F_.clear();
	q = 0;

	for (F = Fmin; Fmax >= F; F += Fstep)
	{
		UpdateData(FALSE);
		OnBnClickedOk();
		Sleep(time);
	}

	UpdateData(FALSE);
}

/*
CEdit* pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
if (pEdit->IsWindowEnabled()) pEdit->EnableWindow(FALSE);
pEdit->EnableWindow(FALSE);
*/