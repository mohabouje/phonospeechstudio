#include "util.h"


QVariant loadFromSettings(const QString &fieldName, const QVariant& defValue)
{
    QSettings settings;
    return settings.value(fieldName, defValue);
}

void saveInSettings(const QString &fieldName, const QVariant& defValue) {
    QSettings settings;
    settings.setValue(fieldName, defValue);
}
