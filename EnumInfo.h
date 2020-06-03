//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __EnumInfo__
#define __EnumInfo__
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QMetaEnum>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class EnumInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool valid READ isValid NOTIFY enumInfoChanged)
    Q_PROPERTY(QVariant context READ context WRITE setContext NOTIFY enumInfoChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY enumInfoChanged)
    Q_PROPERTY(QStringList availableNames READ availableNames NOTIFY enumInfoChanged)

signals:
    void enumInfoChanged();

public:
    EnumInfo(QObject* parent = nullptr);
    EnumInfo(const QString& name, const QVariant& context = QVariant(), QObject* parent = nullptr);

    Q_INVOKABLE QString stringify(int value) const;
    Q_INVOKABLE QVariant parse(const QString& key) const;

protected:
    QVariant m_Context;
    QString m_Name;

    bool isValid() const { return metaEnum().isValid(); }

    QVariant context() const { return m_Context; }
    void setContext(const QVariant& value);

    QString name() const { return metaEnum().name(); }
    void setName(const QString& name);

    QMetaEnum metaEnum() const;

    QStringList availableNames() const;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
