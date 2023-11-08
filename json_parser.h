#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QIODevice>
#include <QFile>
#include <QDebug>

struct Settings
{
    QString comGPS;
    QString comHydro;
    QString puwv1_channel_settings;
    QString receiver_ip;
    int receiver_port;
    QString sender_ip;
    int sender_port;
    float sender_frequency;
};

class Json_parser
{
public:
    Json_parser();
    Settings set;
    QString val;
    QFile file;
    void parser(QString val);
};

#endif // JSON_PARSER_H
