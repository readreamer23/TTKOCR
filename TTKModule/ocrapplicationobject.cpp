#include "ocrapplicationobject.h"
#include "ocrapplication.h"
#include "ocrbackgroundmanager.h"
#include "ocrcoreutils.h"

#include <QTimer>
#include <QPropertyAnimation>

OCRApplicationObject *OCRApplicationObject::m_instance = nullptr;

OCRApplicationObject::OCRApplicationObject(QObject *parent)
    : QObject(parent)
{
    Q_INIT_RESOURCE(TTKOCR);
    m_instance = this;

    M_BACKGROUND_PTR->setMBackground(":/image/lb_background");

    m_animation = new QPropertyAnimation(OCRApplication::instance(), "windowOpacity", this);
}

OCRApplicationObject::~OCRApplicationObject()
{
    cleanUp();
    Q_CLEANUP_RESOURCE(TTKOCR);
    delete m_animation;
}

QString OCRApplicationObject::getClassName()
{
    return staticMetaObject.className();
}

OCRApplicationObject *OCRApplicationObject::instance()
{
    return m_instance;
}

void OCRApplicationObject::windowCloseAnimation()
{
    m_animation->stop();
    m_animation->setDuration(500);
    m_animation->setStartValue(1.0f);
    m_animation->setEndValue(0.0f);
    m_animation->start();
    QTimer::singleShot(1000, qApp, SLOT(quit()));
}

void OCRApplicationObject::appAboutUs()
{

}

void OCRApplicationObject::cleanUp()
{
    QFile::remove(TEMPORARY_DIR);
    OCRUtils::Core::removeRecursively("dir");
    OCRUtils::Core::removeRecursively(SHOTS_DIR_FULL);
}
