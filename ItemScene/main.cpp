#include "itemscene.h"
#include <QApplication>

#include <QProxyStyle>
#include <QAbstractItemView>
#include <QComboBox>

class PGE_ProxyStyle : public QProxyStyle
{
public:
    PGE_ProxyStyle(QStyle *style = Q_NULLPTR) : QProxyStyle(style) {}
    PGE_ProxyStyle(const QString &key) : QProxyStyle(key) {}
    ~PGE_ProxyStyle() {}
    int styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
    {
        if(hint==QStyle::SH_MenuBar_AltKeyNavigation)
            return 0;
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle( new PGE_ProxyStyle(a.style()) );
    ItemScene w;
    w.show();

    return a.exec();
}
