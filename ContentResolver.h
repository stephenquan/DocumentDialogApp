#ifndef __ContentResolver__
#define __ContentResolver__

#include <QObject>
#include <QVariant>

class ContentResolver : public QObject
{
    Q_OBJECT

public:
    ContentResolver(QObject* parent = nullptr);

    static bool isContentUri(const QString& uri);
    static QVariant queryContentUri(const QString& uri, const QString& columnName);

};

#endif
