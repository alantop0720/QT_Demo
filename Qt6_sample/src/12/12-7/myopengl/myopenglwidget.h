#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class QOpenGLShaderProgram;
class QOpenGLTexture;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);
    ~ MyOpenGLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    QOpenGLTexture *textures[2];
    GLfloat translate, xRot, yRot, zRot;
};

#endif // MYOPENGLWIDGET_H
