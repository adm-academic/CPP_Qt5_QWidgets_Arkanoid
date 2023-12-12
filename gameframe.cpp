#include "gameframe.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPushButton>
#include <QMessageBox>
#include "prize_catch.h"
#include "prize_expand.h"
#include "prize_life.h"
#include "prize_score50.h"
#include "prize_score100.h"
#include "prize_score250.h"
#include "prize_score500.h"
#include "prize_slow.h"
#include "prize_fast.h"
#include "global_forms.h"
#include "global_widgets.h"


GameFrame::GameFrame(QWidget *parent): QFrame{parent}
{
    this->setMouseTracking(true); // включим отслеживание мышки виджетом
    this->game_timer.setInterval( 100 ); // установим интервал игрового таймера

    this->set_neutral_background(); // устаноим нейтральный фон

    connect( &this->game_timer, SIGNAL(timeout()), \
             this,SLOT(process_prizes_on_timer()) ); // назначим таймер на обработчик падающих призов
}



QVector <QVector <Block*> > GameFrame::get_blocks_vector(){
    return this->blocks_pointers;
}

int  GameFrame::get_blocks_vector_max_width(){
    int max_width = 0;
    for (int row=0; row<this->blocks_pointers.count(); row++ ){
        if ( this->blocks_pointers[row].count() > max_width )
            max_width = this->blocks_pointers[row].count();
    }
    return max_width;
}

void  GameFrame::reinitialize_blocks_vector_size(int cols_x, int rows_y){
    // очистим двумерный вектор от данных и установим ему нулевой размер
    for (int row=0; row<this->blocks_pointers.count(); row++ ){
        for (int col=0; col<this->blocks_pointers[row].count(); col++ ){
            if ( this->blocks_pointers[row][col] != nullptr  ) // если ячейка вектора не пуста
                delete this->blocks_pointers[row][col]; // то удалим объект блока из ячейки вектора
            this->blocks_pointers[row][col] = nullptr; // занулим ячейку вектора!
        };
        // в первой размености массива мы храним не указатели, а объекты, поэтому удалять ничего не надо
        // а вот размер сбросим
        this->blocks_pointers[row].resize(0);
    };
    // здесь тоже сбросим размер до ноля
    this->blocks_pointers.resize(0);


    // инициализируем двумерный вектор с блоками
    this->blocks_pointers.resize( rows_y ); // зададим размер вектора по строкам
    for (int row_y=0; row_y < rows_y; row_y++ ){ // цикл по строкам
        this->blocks_pointers[row_y].resize( cols_x ); // инициализируем размер вектора-строки
                                                       // указав количество столбцов
        for ( int col_x=0; col_x < cols_x ; col_x++ ){ // заполняем столбцы нулевыми указателями
            this->blocks_pointers[ row_y ][ col_x ] = nullptr; // помещаем в ячейку вектора нулевой указатель
        };                                                  // вектора вектор из столбцов
    };
}

void GameFrame::delete_block(int y_row, int x_col){
    this->create_random_prize_at(this->blocks_pointers[y_row][x_col]->x(), \
                                 this->blocks_pointers[y_row][x_col]->y()   );
    this->blocks_pointers[y_row][x_col]->hide();
    delete this->blocks_pointers[y_row][x_col];
    this->blocks_pointers[y_row][x_col]=nullptr;
}

void GameFrame::append_block(int y_row, int x_col){
    Block* blk = new Block(this); // создаём новый блок

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int blocks_col_count = this->get_blocks_vector_max_width();

    // инициализируем блок
    blk->initialize_block( this->width(), blocks_col_count,
                           this->blocks_begin_x, this->blocks_begin_y  );

    // по порядковым координатам блока найдём его экранные координаты на фрейме
    int x_coorinate = this->blocks_begin_x +
            (( blk->get_width()  + blk->get_spacing() ) * x_col);
    int y_coorinate = this->blocks_begin_y +
            (( blk->get_height() + blk->get_spacing() ) * y_row);
    blk->move( x_coorinate, y_coorinate );// позиционируем новый блок
    blk->show();

    blocks_pointers[y_row][x_col] = blk;// поместим указатель на блок в вектор указателей на блоки
}


Platform* GameFrame::get_platform(){
    return this->platform;
}

Ball*     GameFrame::get_ball(){
    return this->ball;
}

void GameFrame::initialize_platform(){
    if (this->platform != nullptr ){ // если объект платформы уже есть - то удалить его
                                     // для предотвращения утечек памяти
        delete this->platform;
        this->platform = nullptr;
    };
    this->platform = new Platform(this); // создадим объект платформы
    this->platform->show(); // покажем виджет платформы
}

void GameFrame::initialize_ball(){
    if (this->ball != nullptr ){ // если объект шарика уже есть - то удалить его.
                                 // для предотвращения утечек памяти
        delete this->ball;
        this->ball = nullptr;
    };
    this->ball = new Ball(this); // создадим объект шарика
    this->ball->ball_landing(); // поместим шарик на платформу
    this->ball->show(); // покажем виджет шарика
    connect(&this->game_timer,SIGNAL(timeout()), \
            this->ball,SLOT(fly_to_next_position()) \
           ); //присоединим слот, который обеспечивает движение шарика по игровому таймеру

}

void GameFrame::clear_blocks(){
    for (int i=0;i<this->blocks_pointers.count();i++){
        for (int j=0;j<this->blocks_pointers[i].count();j++){
           if (this->blocks_pointers[i][j] != nullptr){
               delete this->blocks_pointers[i][j];
               this->blocks_pointers[i][j] = nullptr;
           };
        };
        this->blocks_pointers[i].clear();
    };
    this->blocks_pointers.clear();
}


void GameFrame::deinitialize_platform(){
    if (this->platform != nullptr ){ // проверяем на ненулл и удаляем объект
        delete this->platform;
        this->platform = nullptr;
    };
}
void GameFrame::deinitialize_ball(){
    if (this->ball != nullptr ){ // проверяем на ненулл у удаляем объект
        delete this->ball;
        this->ball = nullptr;
    };
}

void GameFrame::regenerate_stars(){
    stars.clear();
    for (int i=0;i<100;i++){
        stars.append( QPoint( \
                          QRandomGenerator::global()->bounded(0, this->width()  ), \
                          QRandomGenerator::global()->bounded(0, this->height() )  \
                            ) \
                          );
    }
}

void GameFrame::unload_game_scene(){ // выгружает игровую сцену из фрейма
    if ( this->scene_loaded ){//  выполняем действия только если сцена загружена
        this->scene_loaded = false;
        this->delete_all_flying_prizes();
        this->clear_blocks();
        this->deinitialize_ball();
        this->deinitialize_platform();
        this->set_neutral_background();

        LevelInfo li; li.LevelNameEn=""; li.LevelNameRu="";
        wmain->show_level_info(li);

    };
}

void GameFrame::load_game_scene(){ // загружает игровую сцену во фрейм
    if (! this->scene_loaded ){ // выполняем действия только если сцена не загружена
        this->regenerate_stars();
        this->initialize_platform();
        this->initialize_ball();
        this->scene_loaded = true;
    };
}

int  GameFrame::get_blocks_count(){
    int block_left = 0; // здесь храним количество оставшихся блоков
    for (int i=0;i<this->blocks_pointers.count();i++){
            for (int j=0;j<this->blocks_pointers[i].count();j++){
               if (this->blocks_pointers[i][j] != nullptr){
                    block_left++;
               };
            };
    };
    return block_left;
}


void GameFrame::process_level_finished(){
    // подсчитать количество оставшихся на экране блоков
    int block_left = this->get_blocks_count();
    if (block_left <= 0 ){ // все блоки выбиты - уровень закончился
        gamestate->sound_play_level_win(); // проиграем звук конца уровня
        this->delete_all_flying_prizes(); // удалим с поля все падающие призы

        // для всех уровней кроме последнего отобразим окошко с информацией о завершении уровня!
        if ( gamestate->get_level() < gamestate->get_level_loader()->get_last_level_index() ){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr("Level Completed!"),
                                          tr("You have completed the level !"),
                                        QMessageBox::Yes | QMessageBox::No );
        };
    };
}




void GameFrame::resizeEvent( QResizeEvent *event ){// при изменении размера окна подстраиваем размер содержимого
    Q_UNUSED(event);
    ///!!!!!!!!! НЕ РАБОТАЕТ АВТОПОДГОНКА СЦЕН ПРИ РЕСАЙЗЕ ОКНА ...
    ///!!!!!!!!! сцена генерируется заново, хотя должна просто растягиваться под новый размер окна ...
}

void GameFrame::keyPressEvent(QKeyEvent *event){
    if ( !this->scene_loaded ) return; // если сцена не загружена то выходим из метода
    switch( event->key() ) // свитч по нажатой клавише
        {
            case Qt::Key_Left: // переместить платформу влево
                this->platform->platform_go_left();
                break;
            case Qt::Key_Right: // переместить платформу вправо
                this->platform->platform_go_right();
                break;
            case Qt::Key_Space:  // запустить шарик в полёт
                this->ball->ball_flying_start(); // переключить шарик в режим полёта
                this->game_timer.start(); // включить игровой таймер
                break;
            default: // нажата клавиша для которой не назначен обработчик
                break;
        }
}

void GameFrame::mouseMoveEvent(QMouseEvent *event)
{
    if ( !this->scene_loaded ) return;// если сцена не загружена то выходим из метода
    this->platform->set_platform_pos( event->x() - (this->platform->width() / 2) );
}

void GameFrame::mousePressEvent(QMouseEvent *event)
{
    if ( !this->scene_loaded ) return; // если сцена не загружена то выходим из метода
    if ( event->button()==Qt::LeftButton ){
        this->ball->ball_flying_start(); // переключить шарик в режим полёта
        this->game_timer.start(); // включить игровой таймер
    }
}

void GameFrame::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ), \
                       this->background_image, \
                       QRect(0,0,this->background_image.width(),
                       this->background_image.height()) \
                       );


    this->paint_frame();
//    // рисуем фон игрового виджета
//    QBrush brush;
//    QColor bk_color = QColor(10,10,50,255);
//    brush.setColor(bk_color);
//    brush.setStyle(Qt::SolidPattern);
//    painter.setBrush(brush);
//    painter.drawRect( 0,0, this->width(), this->height()  );

//    // рисуем звёзды на игровом виджете
//    QPen pen;
//    QColor stars_color = QColor(255,255,255,255);
//    pen.setColor(stars_color);
//    pen.setStyle(Qt::SolidLine);
//    pen.setWidth(1);
//    painter.setPen(pen);
//    for (int i=0; i<this->stars.count(); i++ ){
//        painter.drawEllipse( this->stars[i], 3, 3 );
//        painter.drawEllipse( this->stars[i], 2, 2 );
//        painter.drawEllipse( this->stars[i], 1, 1 );

//        int x = this->stars[i].x();
//        int y = this->stars[i].y();
//        painter.drawLine( x-5,y,  x+5,y   );
//        painter.drawLine( x,  y-5,x,  y+5 ) ;
//    }
}

void GameFrame::paint_frame() {
    const int pen_width = 2;
    const int frame_width = 5;
    QPainter painter(this);
    QBrush brush;
    QColor brush_color = QColor(200,200,200);
    brush.setColor(brush_color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    QPen pen;
    QColor pen_color = QColor(100,100,100);
    pen.setColor(pen_color);
    pen.setWidth(pen_width);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRect(0,0,this->width(),frame_width);
    painter.drawRect(0,0,frame_width,this->height());
    painter.drawRect(this->width()-frame_width,0,this->width(),this->height());
}

void GameFrame::create_random_prize_at(int x, int y){
    int random_prize_creation = 1; // QRandomGenerator::global()->bounded( 1, 3+1 );
    if ( random_prize_creation !=1 ) return; // обеспечиваем редкое выпадение призов

    int prizes_classes_count = 9;
    int random_prize_selector = QRandomGenerator::global()->bounded( 1,
                                                prizes_classes_count + 1  ); // значение
                                               // селектора для выбора рандомного приза
    Prize* prz = nullptr;
    if     ( random_prize_selector==1 ){
        prz = new Prize_Catch(this);
        game_frame_prizes.append( prz );
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==2 ){
        prz = new Prize_Expand(this);
        game_frame_prizes.append( prz );
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==3 ){
        prz = new Prize_Life(this);
        game_frame_prizes.append(prz);
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==4 ){
        prz = new Prize_Score50(this);
        game_frame_prizes.append(prz);
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==5 ){
        prz = new Prize_Score100(this);
        game_frame_prizes.append(prz);
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==6 ){
        prz = new Prize_Score250(this);
        game_frame_prizes.append(prz);
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==7 ){
        prz = new Prize_Score500(this);
        game_frame_prizes.append(prz);
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==8 ){
        prz = new Prize_Slow(this);
        game_frame_prizes.append(prz);
        prz->move(x,y);
        prz->show();
    }
    else if ( random_prize_selector==9 ){
        prz = new Prize_Fast(this);
        game_frame_prizes.append(prz);
        prz->move(x,y);
        prz->show();
    };


}

void GameFrame::delete_all_flying_prizes(){
    foreach( Prize* prz, this->game_frame_prizes )
    {
        this->game_frame_prizes.removeAt(
        this->game_frame_prizes.indexOf( prz ) ); // удалим ссылку на
                             // объект приза из списка где он хранился
        prz->hide(); // скроем приз
        delete prz; // удалим приз
    };
}

void GameFrame::process_prizes_on_timer(){
    foreach( Prize* prz, this->game_frame_prizes )
    {
        bool prize_catched = false;
        prz->increment_gravity(); // сдвинем очередной приз немного вниз

        // проверяем пойман ли очередной приз платформой
        int bottom_coordinate_value = prz->y() + prz->height(); // нижняя координата приза
        int platform_left_x =  this->get_platform()->x(); // левая координата платформы
        int platform_right_x = this->get_platform()->x() + \
                               this->get_platform()->width(); // правая координата платформы
        int prz_left_x =  prz->x();
        int prz_right_x = prz->x() + prz->width();
        if ( bottom_coordinate_value >=  \
             this->get_platform()->get_platform_top() )
           {// если приз достиг верхнего края платфомы
            if ( ( prz_left_x>platform_left_x and prz_left_x<platform_right_x  ) or \
                 ( prz_right_x>platform_left_x and prz_right_x<platform_right_x ) ){
                // Этот приз пойман!
                gamestate->sound_play_prize_caught();
                this->game_frame_prizes.removeAt(
                this->game_frame_prizes.indexOf( prz ) );// теперь удалим ссылку на
                                       // объект приза из списка где он хранился
                prz->reset_timeout(); // сбросим таймаут приза
                prz->set_drawing_progress(true); // включим прогессбар на виджете приза
                prize_catched = true;// выставим флаг о том что приз был пойман платформой
                gamestate->add_prize(prz); // добавим приз в прибор отображения призов
            }
        };
        //если приз не был пойман и достиг нижнего края игрового экрана
        if ( (!prize_catched) and \
             ( bottom_coordinate_value > this->height() )  ){
            // приз пролетел мимо!
            this->game_frame_prizes.removeAt(
            this->game_frame_prizes.indexOf( prz ) );// теперь удалим ссылку на
                                   // объект приза из списка где он хранился
            prz->hide();
            delete prz; // удалим объект приза чтобы не убегала память
        };
    };
}

void GameFrame::set_backround_image_file(QString image_filename){
    this->background_image.load( image_filename );
}

void GameFrame::set_neutral_background(){
    this->background_image.load( "images/backround.jpg" );
    this->repaint();
}
