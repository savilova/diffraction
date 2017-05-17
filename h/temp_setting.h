#ifndef temp_setting_H
#define temp_setting_H

#include <QDialog>

namespace Ui {
class temp_setting;
}

class temp_setting : public QDialog
{
    Q_OBJECT

public:
    explicit temp_setting(QWidget *parent = 0);
    ~temp_setting();

private:
    Ui::temp_setting *ui;
};

#endif // temp_setting_H
