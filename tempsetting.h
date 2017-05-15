#ifndef TEMPSETTING_H
#define TEMPSETTING_H

#include <QDialog>

namespace Ui {
class tempSetting;
}

class tempSetting : public QDialog
{
    Q_OBJECT

public:
    explicit tempSetting(QWidget *parent = 0);
    ~tempSetting();

private:
    Ui::tempSetting *ui;
};

#endif // TEMPSETTING_H
