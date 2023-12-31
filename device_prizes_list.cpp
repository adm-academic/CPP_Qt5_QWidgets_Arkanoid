#include "global_forms.h"
#include "device_prizes_list.h"
#include "arkanoid_state.h"


Device_Prizes_List::Device_Prizes_List(QWidget *parent)
    : Device_Background{parent}
{
    // настроим фон прибора
    this->points_count = this->width() * 4;

    // настроим таймер и подключим слот для удаления
    // призов с закончишимся таймауте из списка
    connect(&this->prizes_timer,SIGNAL(timeout()), \
            this,SLOT(slot_prizes_timer()));
    this->prizes_timer.setInterval( 200 );
    this->prizes_timer.start();

}




void Device_Prizes_List::slot_prizes_timer(){
   // для каждого приза нужено проверять истечение времени его действия
   // если время действия истекло - приз из списка нужно удалить
   // и вызвать код уборки действия приза
    foreach (Prize* prize_item, this->active_prizes)
    {
        if ( ! prize_item->actual() ){
            this->active_prizes.removeAt(
            this->active_prizes.indexOf( prize_item ) );// теперь удалим ссылку на
                                   // объект приза из списка где он хранился
            prize_item->get_arkanoid_state()->action_exit();///!!!!!!!!!!!
                                                 // вызовем код уборки действия приза
                                                 // вернём назад игровую механику
            delete prize_item; // удалим объект приза чтобы не убегала память
            this->arrange_and_show_prizes();     // если был удалён хотя-бы
                                       // один приз, то нужно пройтись по всем призам
                                       // в коллекции и пересчитать их коодинаты.
        };
    };
}

void Device_Prizes_List::arrange_and_show_prizes(){ // отображает список
                                                    // призов на приборе
    int current_x = this->spacing;
    int current_y = this->spacing;
    bool width_enough = true;
    // итерируем весь список виджетов
    foreach (Prize* prize_item, this->active_prizes)
    {
        // ресайз виджета с призом под настойки прибора
        prize_item->resize(this->prize_width,this->prize_height);

        // проверяем, закончилось ли место по горизонтали в приборе
        if ( (current_x + this->prize_width + this->spacing) < this->width() )
            width_enough = true;
        else
            width_enough = false;

        // если закончилось - переходим на новую строку
        if ( !width_enough ){
            current_y += this->prize_height + this->spacing;
            current_x =  this->spacing;
        }

        // применяем  move и show для отображения призов на приборе
        prize_item->move(current_x,current_y);
        prize_item->show();

        // прирастим координату вывода по горизонтали
        current_x += prize_item->width() + this->spacing;
    }
}

void Device_Prizes_List::check_and_add_prize(Prize* prize){
    if ( this->active_prizes.contains(prize) ) return; // если прибор уже содержит
                                                       // этот объект приза то просто
                                                       // выходим из метода
    if ( ! prize->with_expiration_time() ){
        // если этот приз не поддерживает истечение срока действия то удалим его объект
        // и выйдем из метода
        prize->get_arkanoid_state()->action_single(); // вызовем единичный обработчик для этого приза
        prize->hide(); // скроем приз
        delete prize; // удалим приз
        return; // выйдем из метода
    };

    // Удалим из прибора всех антагонистов переданного приза используя рефлексию Qt
    foreach (Prize* prize_item_in_device, this->active_prizes)
    {
        foreach ( QString antagonist_name, prize->antagonists_classnames ){
            if ( prize_item_in_device->metaObject()->className() == antagonist_name ){
                this->active_prizes.removeAt(
                this->active_prizes.indexOf( prize_item_in_device ) );// удалим ссылку на объект
                                                        //приза-антагониста из списка где он хранился
                prize_item_in_device->get_arkanoid_state()->action_exit();///!!!!!!!!!!!
                                                              // вызовем код уборки действия приза
                                                              // вернём назад игровую механику
                delete prize_item_in_device; // удалим сам объект приза-антагониста
            };
        };
    };


    // поищем такой-же приз в приборе
    // если прибор уже содержит объект этого класса - то выставляем флаг
    // и сбросим таймер у уже имеющегося приза
    bool found = false;
    foreach (Prize* prize_item, this->active_prizes)
    {
        if ( prize_item->get_class_name() == prize->get_class_name() ){
            found = true;
            prize_item->reset_timeout();
            break;
        }
    };
    if ( found ){ // если такой класс приза уже есть в приборе - просто удалим его объект
        prize->hide(); // скроем приз
        delete prize; // удалим приз
        return;
    }
    else{ // иначе - добавим приз в прибор!
        prize->setParent(this); // добавляем приз в прибор
        this->active_prizes.append(prize); // добавим приз в список призов
        this->arrange_and_show_prizes(); // перестроим и отобразим весь список виджетов
        prize->get_arkanoid_state()->action_enter(); // !!!!! расширим игровую механику с помощью
                                                     // этого приза
    };
}

void Device_Prizes_List::clear_prizes(){
    foreach (Prize* prize_item, this->active_prizes)
    {
        prize_item->hide();
        delete prize_item;
    };
    this->active_prizes.clear();
}

bool Device_Prizes_List::alreay_contains_similar_prize(Prize* prize){
    // поищем такой-же приз в приборе
    // если прибор уже содержит объект этого класса - то выставляем флаг bool found = false;
    bool found = false;
    foreach (Prize* prize_item, this->active_prizes)
    {
        if ( prize_item->get_class_name() == prize->get_class_name() ){
            found = true;
            break;
        }
    };
    // возвращаем флаг. он содержит то, что нужно.
    return found;
}

void Device_Prizes_List::prize_states_action_update()
{
    foreach (Prize* prize_item, this->active_prizes)
    {
        prize_item->get_arkanoid_state()->action_update();
    };
}

void Device_Prizes_List::prize_states_action_repaint()
{
    foreach (Prize* prize_item, this->active_prizes)
    {
        prize_item->get_arkanoid_state()->action_repaint();
    };
}
