#include "TextEditor.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TextEditor w;
	w.show();
	return a.exec();
}
