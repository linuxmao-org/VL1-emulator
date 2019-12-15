#pragma once
#include "Widget.hpp"
#include <list>
#include <memory>


class ImageLabel;


enum
{
	kLcdLine1Size = 10,
	kLcdLine2Size = 9,
	//kLcdMaxLine = 2,
	kLcdMaxChar = 9,
	kLcdMaxSharp = 3,
	kLcdMaxDot = 8,
	kLcdMaxCursor = kLcdLine2Size-1,
};


class CLcd : public Widget
{
public:
	explicit CLcd(Widget *pGroup);
	~CLcd();

	void Initialize();
	void Open(Widget *pGroup);
	void Close();

	void Show(char *pLine1, int lineSize1, char *pLine2, int lineSize2, unsigned char dot, bool bNothing=false);

private:
	void onDisplay() override;

	bool AddChar(int id, int idBmp, int x, int y, int nBmp, ImageLabel **ppControl, Widget *group);
	float MapChar(char ch);
	bool SetControlValue(ImageLabel *pControl, float value);

	int m_mode;
	int m_function;
	int m_cursor;
	unsigned char m_dot;

	ImageLabel *m_pSharp[kLcdMaxSharp];
	ImageLabel *m_pE;
	ImageLabel *m_pM;
	ImageLabel *m_pK;
	ImageLabel *m_pMul;
	ImageLabel *m_pDiv;
	ImageLabel *m_pAdd;
	ImageLabel *m_pSub;
	ImageLabel *m_pChars[kLcdMaxChar];
	ImageLabel *m_pDot[kLcdMaxDot];

	bool m_bOpen;

	std::list<std::unique_ptr<Widget>> m_subWidgets;
};
