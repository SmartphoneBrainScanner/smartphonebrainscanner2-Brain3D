#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QPainter>
#include <QPaintEngine>
#include <QMap>
#include <QVector>



#include "glm.h"

class QOpenGLContext;
class QOpenGLShaderProgram;

class ModelTriangle
{
public:
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<QVector3D> texcoords;
    QVector<QVector4D> colors4;
    int vertex1;
    int vertex2;
    int vertex3;
signals:

public slots:

};

class ModelGroup
{
public:
    QVector<ModelTriangle*> triangles;
signals:

public slots:

};

class Model
{
public:
    Model(QString filename);

    // functions
    void load(QString filename);
    void draw(QMatrix4x4 modelview);
    void setTexture(GLuint texture);
    bool setVertexShaderFile(QString filename);
    bool setFragmentShaderFile(QString filename);
    void setProgram(QOpenGLShaderProgram *program);
    bool linkShaderProgram();
    void initShaderProgram();
    void updateColorForVertex(int vertex, qreal r, qreal g, qreal b, qreal a);
    QMap<int, QVector<QVector<int> > > trianglesMap;
    void resetColors();
    // variables
    GLMmodel *model;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<ModelGroup> groups;
    GLuint texture;
    QOpenGLShaderProgram* program;
    int vertexAttr;
    int normalAttr;
    int matrixUniform;
    int texCoordAttr;
    int textureUniform;
    int colorAttr;
    int readGreyBrain;
    int lightAttr;
    QOpenGLContext* context;
};

#endif // MODEL_H
