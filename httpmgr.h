#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>// Qt 的 URL 类
// 用来表示网址，比如 http://xxx 或 https://xxx
// 发送网络请求时通常会用 QUrl 来封装请求地址
#include <QObject>// Qt 的基础对象类
// 如果你的类需要使用 Qt 的信号和槽机制，一般要继承 QObject
// 例如：class HttpMgr : public QObject, public Singleton<HttpMgr>
#include <QNetworkAccessManager>// Qt 的网络访问管理器
// 负责发送 HTTP 请求，比如 GET、POST
// 可以理解为 Qt 里专门管网络请求的类
#include <QJsonObject>// Qt 的 JSON 对象类
// 用来构造或解析 JSON 对象
// 比如：{"user":"tom", "password":"123456"}
#include <QJsonDocument>// Qt 的 JSON 文档类
// 用来在 JSON 对象和 QByteArray / 字符串之间转换
// 常用于发送 POST 请求时，把 QJsonObject 转成 JSON数据

class HttpMgr:public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>//CRTP
{
    Q_OBJECT//Q_OBJECT 不能随便放在普通类里，它通常要求这个类直接或间接继承 QObject
public:
    ~HttpMgr();
private:
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
