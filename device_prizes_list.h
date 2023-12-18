// виджет прибора. отображающего текущие активные призы
#ifndef DEVICE_PRIZES_LIST_H
#define DEVICE_PRIZES_LIST_H

#include <QList>
#include "device_background.h"
#include "prize.h"



class Device_Prizes_List : public Device_Background
{
    Q_OBJECT
public:
    explicit Device_Prizes_List(QWidget *parent = nullptr);
    void     check_and_add_prize(Prize* prize); // добавляет приз в прибор отображения.
    void     clear_prizes(); // очищаем экран с активными призами
    bool     alreay_contains_similar_prize(Prize* prize);// истина если приз уже содержится в приборе
    void prize_states_action_update(); // вызов метода "обновление" всех пойманых призов...
    void prize_states_action_repaint(); // вызов метода "перерисовка" всех пойманых призов...

private:
    QList < Prize* > active_prizes; // список отобажаемых прибором объектов призов
    QTimer prizes_timer; // таймер для управления временем жизни текущих призов
    void arrange_and_show_prizes(); //  перестраивает и выводит на экран текущий список призов
    const int spacing = 5;
    const int prize_width = 80;
    const int prize_height = 30;
protected:

public slots:
    void slot_prizes_timer(); // обрабатывает таймаут текущих призов
};

#endif // DEVICE_PRIZES_LIST_H
