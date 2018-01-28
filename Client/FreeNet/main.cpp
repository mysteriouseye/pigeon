

#include <QApplication>
#include <QWidget>
#include <QLabel>


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QWidget box;
    QLabel line("HelloWorld");
    line.setParent(& box);
    box.show();
    return application.exec();
}
