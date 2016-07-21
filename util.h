#ifndef UTIL_H
#define UTIL_H
#include <QSettings>
#include <QString>
#include <QVariant>

QVariant loadFromSettings(const QString& fieldName, const QVariant& defValue =  QVariant());
void saveInSettings(const QString &fieldName, const QVariant& defValue);

#endif // UTIL_H
