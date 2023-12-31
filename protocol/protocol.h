#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "stdint.h"
#include <QDebug>
#include <QtGlobal>

#pragma pack(push,1)

/*!
 * \brief Mode_select - структура, используемая для обозначения
 * выбора режима работы ГА модемов.
 */
enum class Mode_select : quint8
{
    IDLE = 0,                     //! Стартовый режим работы
    DIRECT,                       //! Режим персонального общения
    ROUND                         //! Режим обмена нескольких модемов
};

/*!
 * \brief Coordinate - структура, используемая для обозначения
 * информации о координат буёв
 */
struct Coordinate
{
    quint8          id;           //! id буя, чьи координаты записаны
    quint8          fi;           //! Широта
    quint8          lambda;       //! Долгота
};

/*!
 * \brief BeaconData - структура, используемая для общения гидроакустических
 * модемов
 */
struct BeaconData
{
    qint8           id;             //! id буя
    quint8          nbr_rd;         //! Число полученных ответ
    quint8          nbr_td;         //! Число отправленных сообщений
    quint8          tFlight;        //! Время от отправки до получения
};

/*!
 * \brief Direct_agent - структура, используемая в аппарате для
 * формирования данных об гидроакустических модемов в режиме round.
 */
struct Direct_agent
{
    float           dt;           //! Период запросов
    BeaconData      receiver;     //! Информация о получателе сообщений
};

/*!
 * \brief Round_agent - структура, используемая в аппарате для
 * формирования данных об гидроакустических модемов в режиме round.
 */
struct Round_agent
{
    float           dt;             //! Период запросов
    quint8          countBeacon;    //! Число опрашиваемых буёв
    BeaconData      receiver1;      //! Информация о получателе сообщений 1
    BeaconData      receiver2;      //! Информация о получателе сообщений 2
    BeaconData      receiver3;      //! Информация о получателе сообщений 3
    BeaconData      receiver4;      //! Информация о получателе сообщений 4
};

/*!
 * \brief Mode_data_agent - структура, используемая для формирования
 * посылок в агенте. Несет информацию о режиме работы ГА модема.
 */
struct Mode_data_agent
{
    Direct_agent    direct;
    Round_agent     round;
};


/*!
 * \brief Round_gui - структура, используемая в пульте для задания общения
 * гидроакустических модемов в режиме round.
 */
struct Round_gui
{
    float           dt;             //! Период запросов
    quint8          countBeacon;    //! Число опрашиваемых буёв
    Coordinate      receiver1;      //! Информация о получателе сообщений 1
    Coordinate      receiver2;      //! Информация о получателе сообщений 2
    Coordinate      receiver3;      //! Информация о получателе сообщений 3
    Coordinate      receiver4;      //! Информация о получателе сообщений 4
};

/*!
 * \brief Direct_gui - структура, используемая в пульте для задания общения
 * гидроакустических модемов в режиме direct.
 */
struct Direct_gui
{
    float           dt;             //! Период запросов
    Coordinate      receiver;       //! Информация о получателе сообщений
};

/*!
 * \brief Mode_data_gui - структура, используемая для формирования
 * посылок в пульте. Несет информацию о режиме работы ГА модема.
 */
struct Mode_data_gui
{
    Direct_gui      direct;
    Round_gui       round;
};





/*!
 * \brief BeaconSetup - структура, формируемая в пульте и передаваемая
 * на агента.
 */
struct FromPult
{
    Mode_select     mode_select;    //! Выбранный режим работы ГА модема
    Mode_data_gui   mode_data;      //! Информация о режиме работы

    quint8          salinity;       //! Информация о солености воды
    quint8          salinityFlag;   //! Флаг обновления солености воды
    uint checksum;
};

/*!
 * \brief NavigationData_beacon - структура, формируемая на агенте и передаваемая
 * на пульт
 */
struct ToPult
{
    Mode_select     mode_select;    //! Текущий режим работы ГА модема
    Mode_data_agent mode_data;      //! Информация о режиме работы

    quint8          depth;          //! Текущий глубина ГА модема
    qint8           temperature;    //! Текущий температура ГА модема
    qint8           voltage;        //! Текущий потребляемый вольтаж ГА модема
    uint checksum;
};


#pragma pack (pop)


#endif // PROTOCOL_H
