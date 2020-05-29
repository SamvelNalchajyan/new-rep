#pragma once

#include <string>

#define LinkSize 80
#define MemSize 100

class TText;
class TTextLink;

typedef char TStr[LinkSize];

struct TTextMem
{
	TTextLink* pFirst;
	TTextLink* pLast;
	TTextLink* pFree;
	friend class TTextLink;
};


class TTextLink {

protected:
	TTextLink* pNext, * pDown;
	static TTextMem MemHead;
	friend class TText;
public:

	TStr str;
	int recD;
	TTextLink(const TStr c = NULL, TTextLink* _pNext = NULL, TTextLink* _pDown = NULL)
	{
		recD = 0;
		pNext = _pNext;
		pDown = _pDown;
		if (c == NULL)
		{
			str[0] = '\0';
		}
		else
		{
			strcpy_s(str, c);
		}
	}
	~TTextLink() {}

	static void InitMem(int size = MemSize);
	static void PrintFreeLinks(void);
	void* operator new (size_t size);
	void operator delete (void* pM);
	static void MemClean(TText& txt);
};