#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "TTextLink.h"
#include "TText.h"
#include "TStack.h"

void TTextLink::InitMem(int size)
{
	MemHead.pFirst = (TTextLink*) new char[sizeof(TTextLink) * size];
	MemHead.pFree = MemHead.pFirst;
	MemHead.pLast = MemHead.pFirst + (size - 1);
	TTextLink* pLink = MemHead.pFirst;

	for (int i = 0; i < size - 1; i++)
	{
		pLink->str[0] = '\0';
		pLink->pNext = pLink + 1;
		pLink++;
	}
	pLink->pNext = NULL;
}

void TTextLink::PrintFreeLinks()
{
	std::cout << "Free links" << std::endl;
	int count = 0;
	for (TTextLink* pLink = MemHead.pFree; pLink != NULL; pLink = pLink->pNext)
	{
		std::cout << pLink->str << std::endl;
		count++;
	}
	std::cout << count << std::endl;
}

void* TTextLink::operator new(size_t size)
{
	TTextLink* pLink = MemHead.pFree;
	if (MemHead.pFree) {
		MemHead.pFree = pLink->pNext;
	}
	return pLink;
}

void TTextLink::operator delete(void* pM)
{
	TTextLink* pLink = (TTextLink*)pM;
	pLink->pNext = MemHead.pFree;
	MemHead.pFree = pLink;
}

void TTextLink::MemClean(TText& txt)
{

	for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
	{
		std::string tmp = "&&&";
		tmp += txt.GetLine();
		txt.SetLine(tmp);
	}
	TTextLink* pLink;
	for (pLink = MemHead.pFree; pLink != NULL; pLink = pLink->pNext)
	{
		strcpy(pLink->str, "&&&");
	}
	for (pLink = MemHead.pFirst; pLink <= MemHead.pLast; pLink++)
	{
		if (std::strstr(pLink->str, "&&&") != NULL)
		{
			std::strcpy(pLink->str, pLink->str + 3);
		}
		else
		{
			delete pLink;
		}
	}
}