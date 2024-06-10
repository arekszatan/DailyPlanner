#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql>

class DB : public QObject {
    Q_OBJECT

public:
    explicit DB(QObject *parent = nullptr);
    ~DB();

    bool connect(const QString &dbName);
    void disconnect();

    bool createTable(const QString &tableName, const QStringList &fields);
    bool insertData(const QString &tableName, const QStringList &values);
    bool updateData(const QString &tableName, const QStringList &fields, const QStringList &values, const QString &condition);
    bool deleteData(const QString &tableName, const QString &condition);

    QList<QList<QString>> fetchData(const QString &tableName, const QStringList &fields = QStringList(), const QString &condition = QString());

private:
    QSqlDatabase m_db;
};

#endif // DB_H
