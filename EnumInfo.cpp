#include "EnumInfo.h"
#include <QDebug>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

EnumInfo::EnumInfo(QObject* parent) :
    QObject(parent)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

EnumInfo::EnumInfo(const QString& name, const QVariant& context, QObject* parent) :
    QObject(parent)
{
    setContext(context);
    setName(name);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString EnumInfo::stringify(int value) const
{
    return metaEnum().valueToKey(value);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant EnumInfo::parse(const QString& key) const
{
    return metaEnum().keyToValue(key.toUtf8().data());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList EnumInfo::availableNames() const
{
    if (!m_Context.isValid() || m_Context.isNull())
    {
        return QStringList();
    }

    QObject* context = qvariant_cast<QObject*>(m_Context);
    if (!context)
    {
        return QStringList();
    }

    const QMetaObject* metaObject = context->metaObject();
    if (!metaObject)
    {
        return QStringList();
    }

    QStringList list;
    for (int index = 0; index < metaObject->enumeratorCount(); index++)
    {
        QMetaEnum metaEnum = metaObject->enumerator(index);
        list.append(metaEnum.name());
    }
    return list;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void EnumInfo::setContext(const QVariant& context)
{
    if (context == m_Context)
    {
        return;
    }

    m_Context = context;

    emit enumInfoChanged();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void EnumInfo::setName(const QString& name)
{
    if (name == m_Name)
    {
        return;
    }

    m_Name = name;

    emit enumInfoChanged();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QMetaEnum EnumInfo::metaEnum() const
{
    if (!m_Context.isValid() || m_Context.isNull())
    {
        return QMetaEnum();
    }

    QObject* context = qvariant_cast<QObject*>(m_Context);
    if (!context)
    {
        return QMetaEnum();
    }

    const QMetaObject* metaObject = context->metaObject();
    if (!metaObject)
    {
        return QMetaEnum();
    }

    int index = metaObject->indexOfEnumerator(m_Name.toUtf8().data());
    return metaObject->enumerator(index);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
