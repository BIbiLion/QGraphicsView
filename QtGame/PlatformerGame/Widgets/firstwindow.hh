#ifndef FIRSTWINDOW_HH
#define FIRSTWINDOW_HH

#include <QMainWindow>

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();

private:
    Ui::FirstWindow *ui;
};

#endif // FIRSTWINDOW_HH
