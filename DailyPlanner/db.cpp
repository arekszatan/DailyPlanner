#include "db.h"

DB::DB(QObject *parent) : QObject(parent) {
    // Set up database connection
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

DB::~DB() {
    // Close database connection
    disconnect();
}

bool DB::connect(const QString &dbName) {
    m_db.setDatabaseName(dbName);
    if (!m_db.open()) {
        qDebug() << "Error: Failed to connect to database.";
        return false;
    }
    qDebug() << "Database connected.";
    return true;
}

void DB::disconnect() {
    if (m_db.isOpen()) {
        m_db.close();
        qDebug() << "Database disconnected.";
    }
}

bool DB::createTable(const QString &tableName, const QStringList &fields) {
    QSqlQuery query(m_db);
    QString queryString = "CREATE TABLE IF NOT EXISTS " + tableName + "(" + fields.join(", ") + ")";
    return query.exec(queryString);
}

bool DB::insertData(const QString &tableName, const QStringList &values) {
    QSqlQuery query(m_db);
    QString queryString = "INSERT INTO " + tableName + " VALUES (" + values.join(", ") + ")";
    qInfo()<< queryString;
    return query.exec(queryString);
}

bool DB::updateData(const QString &tableName, const QStringList &fields, const QStringList &values, const QString &condition) {
    QSqlQuery query(m_db);
    QString queryString = "UPDATE " + tableName + " SET " + fields.join(", ") + " WHERE " + condition;
    return query.exec(queryString);
}

bool DB::deleteData(const QString &tableName, const QString &condition) {
    QSqlQuery query(m_db);
    QString queryString = "DELETE FROM " + tableName + " WHERE " + condition;
    qInfo() << queryString;
    return query.exec(queryString);
}

QList<QList<QString>> DB::fetchData(const QString &tableName, const QStringList &fields, const QString &condition) {
    QList<QList<QString>> result;
    QSqlQuery query(m_db);
    QString fieldList = fields.isEmpty() ? "*" : fields.join(", ");
    QString queryString = "SELECT " + fieldList + " FROM " + tableName;
    if (!condition.isEmpty()) {
        queryString += " WHERE " + condition;
    }
    if (query.exec(queryString)) {
        while (query.next()) {
            QList<QString> row;
            for (int i = 0; i < query.record().count(); ++i) {
                row.append(query.value(i).toString());
            }
            result.append(row);
        }
    }
    return result;
}
