#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QPixmap>
#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMediaPlayer>

class ImageButton : public QPushButton
{
    Q_OBJECT
public:
    ImageButton() = default;
    ImageButton(QWidget* parent);
    void paintEvent(QPaintEvent* e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent* e) override;
public slots:
    void setDown();
    void setUp();
private:
    QMediaPlayer* clickSound;
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    bool isDown = false;
};

ImageButton::ImageButton(QWidget* parent)
{
    clickSound = new QMediaPlayer(parent);
    clickSound->setMedia(QUrl::fromLocalFile(".\\click.mp3"));
    clickSound->setVolume(100);
    setParent(parent);
    setToolTip("Stop");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap("C:\\buttons\\up.png");
    mButtonDownPixmap = QPixmap("C:\\buttons\\down.png");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
}

void ImageButton::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const
{
    return QSize(100, 100);
}

QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent* e)
{
    setDown();
}

void ImageButton::setDown()
{
    clickSound->play();
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100, this, &ImageButton::setUp);
}

void ImageButton::setUp()
{
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    ImageButton redButton(nullptr);
    redButton.setFixedSize(100, 100);
    redButton.move(1000, 400);
    QObject::connect(&redButton, &QPushButton::clicked, []() {std::cout << "clicked\n"; });
    redButton.show();
    app.exec();
}

#include <main.moc>
