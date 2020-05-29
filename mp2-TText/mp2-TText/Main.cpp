#include <conio.h>
#include <iostream>
#include <string>
#include <clocale>
#include "TText.h"

using namespace std;

TTextMem TTextLink::MemHead;

void TextMenu(TText& txt)
{
	string st;
	string command;
	setlocale(LC_CTYPE, "Russian");
	do
	{
		cout << "введите 'help' чтобы увидить список команд" << endl;
		cin >> command;
		if (command == "exit"){
		}
		if (command == "print")
		{
			txt.Print();
		}
		if (command == "printit")
		{
			for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
			{
				cout << txt.GetLine() << endl;
			}
		}
		if (command == "first")
		{
			txt.GoFirstLink();
			cout << "Now in " << txt.GetLine() << endl;
		}
		if (command == "down")
		{
			txt.GoDownLink();
			cout << "Now in " << txt.GetLine() << endl;
		}
		if (command == "next")
		{
			txt.GoNextLink();
			cout << "Now in " << txt.GetLine() << endl;
		}
		if (command == "prev")
		{
			txt.GoPrevLink();
			cout << "Now in " << txt.GetLine() << endl;
		}
		if (command == "delete_down")
		{
			txt.DelDown();
			cout << "Now in " << txt.GetLine() << endl;
		}
		if (command == "delete_next")
		{
			txt.DelNext();
			cout << "Now in " << txt.GetLine() << endl;
		}
		if (command == "insert_down_line")
		{
			cout << "enter string..." << endl;
			cin >> st;
			txt.InsDownLine(st);
		}
		if (command == "insert_down_section")
		{
			cout << "enter string..." << endl;
			cin >> st;
			txt.InsDownSection(st);
		}
		if (command == "insert_next_line")
		{
			cout << "enter string..." << endl;
			cin >> st;
			txt.InsNextLine(st);
		}
		if (command == "insert_next_section")
		{
			cout << "enter string..." << endl;
			cin >> st;
			txt.InsNextSection(st);
		}
		if (command == "free")
		{
			TTextLink::PrintFreeLinks();
		}

		if (command == "help")
		{
			cout << "print - печать текста с отступами" << endl;
			cout << "printit - печать текста без отстутпов по итератору" << endl;
			cout << "first -перейти в начало текста" << endl;
			cout << "next - перейти на следующую строку" << endl;
			cout << "down - перейти на строку в глубь" << endl;
			cout << "prev - перейти на предыдущую" << endl;
			cout << "delete_down - удалить строку на уровень ниже" << endl;
			cout << "delete_next - удалить следующую строку" << endl;
			cout << "insert_down_line - добавить строку на уровень ниже" << endl;
			cout << "insert_down_section - добавить секцию на уровень ниже" << endl;
			cout << "insert_next_line - добавить строку на место следующей" << endl;
			cout << "insert_next_section - добавить секцию на место следующей" << endl;
			cout << "free -показать свободную память" << endl;
			cout << "exit - закрыть программу" << endl;
		}
	} while (command != "exit");
}

int main()
{
	TTextLink::InitMem(100);
	TText t;
	t.Read("../FILE_in.txt");
	TextMenu(t);
	t.Write("../FILE_out.txt");
	TTextLink::MemClean(t);
	TTextLink::PrintFreeLinks();
}