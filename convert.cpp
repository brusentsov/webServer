#include "convert.h"
#include "webserver.h"

#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTime>
#include <QVariant>
#include <QDebug>
#include <QFile>

QString getServerInfo() {
    QVariant title("WebServer"), developer("Yury Brusetsov"), time(QTime::currentTime().toString());
    QJsonObject json;
    json.insert("title", title.toString());
    json.insert("developer", developer.toString());
    json.insert("time", time.toString());
    QJsonDocument doc(json);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    return strJson;
}

QString getFavourites() {
    QJsonArray favArray;
    int favSize = 0;

    // use initializer list to construct QJsonObject
    QVariant id("1"), name("Tyler"), surname("Durden");
    QJsonObject json;
    json.insert("id", id.toString());
    json.insert("name", name.toString());
    json.insert("surname", surname.toString());
    favArray.push_back(QJsonValue(json));
    favSize++;

    id = "2";
    name = "Forest";
    surname = "Gump";
    json.insert("id", id.toString());
    json.insert("name", name.toString());
    json.insert("surname", surname.toString());
    favArray.push_back(QJsonValue(json));
    favSize++;

    id = "3";
    name = "Andy";
    surname = "Dufresne";
    json.insert("id", id.toString());
    json.insert("name", name.toString());
    json.insert("surname", surname.toString());
    favArray.push_back(QJsonValue(json));
    favSize++;

    id = "4";
    name = "Harry";
    surname = "Potter";
    json.insert("id", id.toString());
    json.insert("name", name.toString());
    json.insert("surname", surname.toString());
    favArray.push_back(QJsonValue(json));
    favSize++;

    id = "5";
    name = "Harry";
    surname = "Callahan";
    json.insert("id", id.toString());
    json.insert("name", name.toString());
    json.insert("surname", surname.toString());
    favArray.push_back(QJsonValue(json));
    favSize++;

    QJsonObject final_object;
    final_object.insert(QString("favourites"), QJsonValue(favArray));

    QJsonDocument doc(final_object);
    QString strJson(doc.toJson(QJsonDocument::Indented));

    return strJson;
}

QString getIdObject(QString _id) {
    QString returnId;
    QString returnName;
    QString returnSurame;

    QString favs = getFavourites();

    QJsonDocument document = QJsonDocument::fromJson(favs.toUtf8());
    QJsonObject object = document.object();
    QJsonValue jsonValue = object.value("favourites");
    QJsonArray jsonArray = jsonValue.toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString id = obj["id"].toString();
        if (id == _id) {
            returnId = id;
            returnName = obj["name"].toString();
            returnSurame = obj["surname"].toString();
            break;
        }
    }

    QVariant id(returnId), name(returnName), surname(returnSurame);
    QJsonObject json;
    json.insert("id", id.toString());
    json.insert("name", name.toString());
    json.insert("surname", surname.toString());

    QJsonDocument doc(json);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    return strJson;
}

QString getNameObjects(QString _name) {

    QString returnId;
    QString returnName;
    QString returnSurame;
    QJsonArray array;

    QString favs = getFavourites();

    QJsonDocument document = QJsonDocument::fromJson(favs.toUtf8());
    QJsonObject object = document.object();
    QJsonValue jsonValue = object.value("favourites");
    QJsonArray jsonArray = jsonValue.toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        if (name == _name) {
            QJsonObject json;
            returnId = obj["id"].toString();
            returnName = obj["name"].toString();
            returnSurame = obj["surname"].toString();
            json.insert("id", returnId);
            json.insert("name", returnName);
            json.insert("surname", returnSurame);
            array.push_back(QJsonValue(json));
        }
    }

    if(array.size() == 0) {
        return "failure";
    }

    QJsonDocument doc(array);
    QString strJson(doc.toJson(QJsonDocument::Indented));

    return strJson;
}

int getFavouritesSize() {
    QString favs = getFavourites();
    QJsonDocument document = QJsonDocument::fromJson(favs.toUtf8());
    QJsonObject object = document.object();
    QJsonValue jsonValue = object.value("favourites");
    QJsonArray jsonArray = jsonValue.toArray();
    return jsonArray.size();
}

QString _getStringFromFile(QString filename) {
    QString data;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "file read error";
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        data += line + '\n';
    }
    file.close();
    return data;
}

QString createDataJson(QString nameOfFile) {
    QString fileData = _getStringFromFile(nameOfFile);

    QVariant filename(nameOfFile), bytes((int)sizeof(fileData)), data(fileData);
    QJsonObject json;
    json.insert("filename", filename.toString());
    json.insert("bytes", bytes.toString());
    json.insert("data", data.toString());
    QJsonDocument doc(json);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    return strJson;
}

QString createDataNumbersJson(QString nameOfFile) {
    QString fileData = _getStringFromFile(nameOfFile);
    QJsonArray array;
    QList<int> numbers;
    int count = 0;
    QStringList strings = fileData.split(" ");
    for (int i = 0; i < strings.size(); i++) {
        if (strings.at(i).toInt() != 0) {
            count++;
            if (count % 2 == 1) {
                numbers.push_back(strings.at(i).toInt());
            }
        }
    }
    count = 1;
    for (int i = 0; i < numbers.size(); i++) {
        QJsonObject json;
        json.insert("number", numbers.at(i));
        json.insert("position", count);
        array.push_back(QJsonValue(json));
        count += 2;
    }
    QJsonDocument doc(array);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    return strJson;
}
