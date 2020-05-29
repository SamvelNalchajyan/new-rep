#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include "TText.h"
#include "TTextLink.h"
#include "TStack.h"

using namespace std;
static int rec;

TText::TText()
{
	pFirst = pCurr = NULL;
	TStack<TTextLink*> stack;
}

void TText::GoFirstLink()
{
	pCurr = pFirst;
	stack.Clear();
}

void TText::GoDownLink()
{
	if (!pCurr)
	{
		throw - 1;
	}
	if (!pCurr->pDown)
	{
		return;
	}
	stack.Push(pCurr);
	pCurr = pCurr->pDown;
}

void TText::GoNextLink()
{
	if (!pCurr)
	{
		throw - 1;
	}
	if (!pCurr->pNext)
	{
		return;
	}
	stack.Push(pCurr);
	pCurr = pCurr->pNext;
}

void TText::GoPrevLink()
{
	if (!pCurr)
	{
		throw - 1;
	}
	if (stack.IsEmpty())
	{
		return;
	}
	pCurr = stack.Pop();
}

void TText::SetLine(string astr)
{
	if (!pCurr)
	{
		throw - 1;
	}
	strcpy_s(pCurr->str, astr.c_str());
}

string TText::GetLine()
{
	if (!pCurr)
	{
		throw - 1;
	}
	return std::string(pCurr->str);
}

void TText::InsNextLine(string astr)
{
	if (!pCurr)
	{
		throw - 1;
	}
	TTextLink* p = new TTextLink(astr.c_str());
	p->pNext = pCurr->pNext;
	pCurr->pNext = p;
}

void TText::InsNextSection(string astr)
{
	if (!pCurr)
	{
		throw - 1;
	}
	TTextLink* p = new TTextLink(astr.c_str());
	p->pDown = pCurr->pNext;
	pCurr->pNext = p;
}

void TText::InsDownLine(string astr)
{
	if (!pCurr)
	{
		throw - 1;
	}
	TTextLink* p = new TTextLink(astr.c_str());
	p->pDown = pCurr->pDown;
	pCurr->pDown = p;
}

void TText::InsDownSection(string astr)
{
	if (!pCurr)
	{
		throw - 1;
	}
	TTextLink* p = new TTextLink(astr.c_str());
	p->pDown = pCurr->pDown;
	pCurr->pDown = p;
}

void TText::DelNext()
{
	if (!pCurr)
	{
		throw - 1;
	}
	if (!pCurr->pNext)
	{
		return;
	}
	TTextLink* tmp = pCurr->pNext;
	pCurr->pNext = tmp->pNext;
	delete tmp;
}

void TText::DelDown()
{
	if (!pCurr)
	{
		throw - 1;
	}
	if (!pCurr->pNext)
	{
		return;
	}
	TTextLink* tmp = pCurr->pDown;
	pCurr->pDown = tmp->pNext;
	delete tmp;
}

void TText::Read(std::string fn)
{
	ifstream ifs(fn);
	rec = 0;
	pFirst = ReadRec(ifs);
}

TTextLink* TText::ReadRec(ifstream& ifs)
{
	TTextLink* pHead;
	TTextLink* p;
	TTextLink* tmp;
	pHead = p = NULL;
	char tstr[81];
	while (!ifs.eof())
	{
		ifs.getline(tstr, 80, '\n');
		if (tstr[0] == '}')
		{
			break;
		}
		else
			if (tstr[0] == '{')
			{
				p->pDown = ReadRec(ifs);
			}
			else
			{
				tmp = new TTextLink(tstr);
				if (pHead == NULL)
				{
					pHead = p = tmp;
				}
				else
				{
					p->pNext = tmp;
					p = p->pNext;
				}
			}
		if (!p->pDown){
		}
	}
	return pHead;
}

void TText::Write(std::string fn)
{
	ofstream ofs(fn);
	rec = 0;
	WriteRec(ofs, pFirst);
}

void TText::WriteRec(ofstream& ofs, TTextLink* p)
{
	for (int i = 0; i < rec; i++)
	{
		ofs << " ";
	}
	ofs << p->str << endl;

	if (p->pDown)
	{
		rec++;
		ofs << '{' << endl;
		WriteRec(ofs, p->pDown);
		ofs << '}' << endl;
	}
	if (p->pNext)
	{
		WriteRec(ofs, p->pNext);
		rec++;
	}
	rec--;
}

void TText::Print()
{
	rec = 0;
	PrintRec(pFirst);
}

void TText::PrintRec(TTextLink* p)
{
	for (int i = 0; i < rec; i++)
	{
		cout << "  ";
	}
	cout << p->str << endl;
	if (p->pDown)
	{
		rec++;
		PrintRec(p->pDown);

	}
	if (p->pNext) {
		PrintRec(p->pNext);
		rec++;
	}
	rec--;
}

int TText::Reset()
{
	while (!stack.IsEmpty())
	{
		stack.Pop();
	}
	pCurr = pFirst;
	if (pCurr)
	{
		stack.Push(pCurr);
		if (pCurr->pNext)
		{
			stack.Push(pCurr->pNext);
		}
		if (pCurr->pDown)
		{
			stack.Push(pCurr->pDown);
		}
	}
	return IsEnd();
}

int TText::IsEnd()
{
	return stack.IsEmpty();
}

int TText::GoNext()
{
	if (!IsEnd())
	{
		pCurr = stack.Pop();
		if (pCurr != pFirst)
		{
			if (pCurr->pNext)
			{
				stack.Push(pCurr->pNext);
			}
			if (pCurr->pDown)
			{
				stack.Push(pCurr->pDown);
			}
		}
		return true;
	}
	return false;
}