#include "VTPLabel.h"

VTPLabel::VTPLabel(QWidget * parent, Qt::WindowFlags f)
    : QLabel(parent, f)
    , m_imageSource("")
{

}


QString VTPLabel::imageSource() const
{
    return m_imageSource;
}


void VTPLabel::setImageSource(QString const & imageSource)
{
    m_imageSource = imageSource;

    // Reset the background image
    QPixmap image(m_imageSource);
    setPixmap(image);

    // Resize the UI
    resize(image.size());
}


void VTPLabel::showEvent(QShowEvent * event)
{
    // set background image
    QPixmap image(m_imageSource);
    setPixmap(image);

    // Resize the UI
    resize(image.size());

    // no need for text
    setText("");

    // Call parent's showEvent
    QLabel::showEvent(event);
}

