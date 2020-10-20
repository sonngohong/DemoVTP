#ifndef VTPLABEL_H
#define VTPLABEL_H

#include <QLabel>

class VTPLabel : public QLabel
{
    Q_OBJECT
signals:

public slots:

public:
    explicit VTPLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);

    QString imageSource() const;
    void setImageSource(QString const & imageSource);

protected:
    virtual void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

private:
    QString m_imageSource;
};

#endif // VTPLABEL_H
