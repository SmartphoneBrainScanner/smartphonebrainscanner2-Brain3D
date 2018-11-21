#include "model.h"
#include <colordata.h>



Model::Model(QString objectFile)
{
    readGreyBrain=true;
    QGLFormat fmt;
    QGLFormat::setDefaultFormat(fmt);
    context = new QGLContext(fmt);
    program = new QGLShaderProgram(QGLContext::currentContext());

    load(objectFile);
}

void Model::updateColorForVertex(int vertex, qreal r, qreal g, qreal b, qreal a)
{
    ++vertex;
    int size =  trianglesMap[vertex].size();
    for (int i=0; i < size; ++i)
    {
	groups.last().triangles[(trianglesMap[vertex])[i][0]]->colors4[(trianglesMap[vertex])[i][1]] = QVector4D((qreal)r , (qreal)g , (qreal)b, (qreal)a);
    }
}

void Model::resetColors()
{
    for (int i=0; i<trianglesMap.size(); ++i )
    {
	updateColorForVertex(i,1,0,0,0);
    }
}


void Model::load(QString filename)
{
    if (filename.startsWith(":"))
    {
        QTemporaryDir d;
        QString newFile = d.filePath(QLatin1String("model"));
        QFile::copy(filename, newFile);
        model = glmReadOBJ(newFile.toLatin1());
    }
    else
    {
        model = glmReadOBJ(filename.toLatin1());
    }
    if(model->numtexcoords < 1)
    {
    qWarning() << "WARNING Missing UV map in file:" << filename.toLatin1();
    }

    GLMgroup* group;
    group = model->groups;
    while (group)
    {
	ModelGroup grp;
	for(int i = 0; i < group->numtriangles; i++)
	{
	    ModelTriangle* triangle = new ModelTriangle();
	    QVector<QVector3D> verts;
	    QVector<QVector4D> colors;
	    for(int j = 0; j < 3; j++)
	    {
		QVector3D vector(model->vertices[3 * model->triangles[group->triangles[i]].vindices[j] + 0],
				 model->vertices[3 * model->triangles[group->triangles[i]].vindices[j] + 1],
				 model->vertices[3 * model->triangles[group->triangles[i]].vindices[j] + 2]);
		verts.append(vector);


		if (readGreyBrain)
		{
		    QVector4D vectorColor(1.0,
					  1.0,
					  1.0,
					  1.0);
		    colors.append(vectorColor);

		}
		else
		{
		    QVector3D vectorColor(colorDataLowRes[3 * (model->triangles[group->triangles[i]].vindices[j]-1) + 0],
					  colorDataLowRes[3 * (model->triangles[group->triangles[i]].vindices[j]-1) + 1],
					  colorDataLowRes[3 * (model->triangles[group->triangles[i]].vindices[j]-1) + 2]);
		    colors.append(vectorColor);
		}

	    }

	    triangle->vertex1=(model->triangles[group->triangles[i]].vindices[0]);
	    triangle->vertex2=(model->triangles[group->triangles[i]].vindices[1]);
	    triangle->vertex3=(model->triangles[group->triangles[i]].vindices[2]);

	    QVector<int> triangle0;
	    triangle0.append(i);
	    triangle0.append(0);

	    (trianglesMap[model->triangles[group->triangles[i]].vindices[0]]).append(triangle0);

	    QVector<int> triangle1;
	    triangle1.append(i);
	    triangle1.append(1);

	    (trianglesMap[model->triangles[group->triangles[i]].vindices[1]]).append(triangle1);

	    QVector<int> triangle2;
	    triangle2.append(i);
	    triangle2.append(2);

	    (trianglesMap[model->triangles[group->triangles[i]].vindices[2]]).append(triangle2);

	    QVector<QVector3D> norms;
	    for(int j = 0; j < 3; j++)
	    {



		//                QVector3D vector(normalData[3 * (model->triangles[group->triangles[i]].vindices[j]-1) + 0]/30.0,
		//                                 normalData[3 * (model->triangles[group->triangles[i]].vindices[j]-1) + 1]/30.0,
		//                                 normalData[3 * (model->triangles[group->triangles[i]].vindices[j]-1) + 2]/30.0);
		QVector3D vector(model->normals[3 * model->triangles[group->triangles[i]].nindices[j] + 0],
				 model->normals[3 * model->triangles[group->triangles[i]].nindices[j] + 1],
				 model->normals[3 * model->triangles[group->triangles[i]].nindices[j] + 2]);


		norms.append(vector);



	    }

	    if(model->numtexcoords > 0)
	    {
		QVector<QVector3D> texs;
		for(int j = 0; j < 3; j++)
		{
		    QVector3D vector(model->texcoords[2 * model->triangles[group->triangles[i]].tindices[j] + 0],
				     model->texcoords[2 * model->triangles[group->triangles[i]].tindices[j] + 1],
				     model->texcoords[2 * model->triangles[group->triangles[i]].tindices[j] + 2]);
		    texs.append(vector);
		}
		triangle->texcoords = texs;
	    }
	    triangle->vertices = verts;
	    triangle->normals = norms;
	    triangle->colors4 = colors;



	    grp.triangles.append(triangle);
	}
	groups.append(grp);
	group = group->next;
    }
    qDebug() << "loading file";
}

bool Model::setFragmentShaderFile(QString filename)
{



    qDebug() << "bool Model::setFragmentShaderFile(QString filename)";
    QGLShader* shaderF = new QGLShader(QGLShader::Fragment, QGLContext::currentContext());
    qDebug() << "bool Model::setFragmentShaderFile(QString filename) 1";
    if(!shaderF->compileSourceFile(filename))
    {
	qDebug() << "Could not load shader file " + filename + ": " << program->log();
	return false;
    }
    else {
	qDebug() << "Loaded " + filename + " successfully";
	program->addShader(shaderF);
	return true;
    }
}

bool Model::setVertexShaderFile(QString filename)
{
    QGLShader* shaderV = new QGLShader(QGLShader::Vertex, QGLContext::currentContext());

    if(!shaderV->compileSourceFile(filename)) {
	qDebug() << "Could not load shader file " + filename + ": " << program->log();
	return false;
    } else {
	qDebug() << "Loaded " + filename + " successfully";
	program->addShader(shaderV);
	return true;

    }
}

bool Model::linkShaderProgram()
{
    if(program->link())
    {
	qDebug() << "Program linked";
        return true;
    }
    else
    {
	qDebug() << "Failed to link program:" << program->log();
        return false;
    }
}

void Model::initShaderProgram()
{
    vertexAttr = program->attributeLocation("vertex");
    normalAttr = program->attributeLocation("normal");
    texCoordAttr = program->attributeLocation("texCoord");
    matrixUniform = program->uniformLocation("matrix");
    textureUniform = program->uniformLocation("tex");
    colorAttr = program->attributeLocation("a_color");
    lightAttr = program->attributeLocation("u_LightPos");


}

void Model::draw(QMatrix4x4 modelview) {
    program->bind();

    //  glBindTexture(GL_TEXTURE_2D, texture);
    foreach(ModelGroup grp, groups)
    {



	foreach(ModelTriangle* triangle, grp.triangles)
	{


	    program->setUniformValue(textureUniform, 0);    // use texture unit 0

	    QVector3D zeroVector = QVector3D(0.0,0.0,0.0);

	    program->setAttributeArray(vertexAttr, triangle->vertices.constData());
	    program->setAttributeArray(normalAttr, triangle->normals.constData());
	    program->setAttributeArray(lightAttr,&zeroVector);

	    //program.setAttributeArray(texCoordAttr, triangle.texcoords.constData());

	    program->setAttributeArray(colorAttr, triangle->colors4.constData());

	    program->enableAttributeArray(colorAttr);
	    program->enableAttributeArray(normalAttr);
	    program->enableAttributeArray(vertexAttr);
	    program->enableAttributeArray(lightAttr);




	    glDrawArrays(GL_TRIANGLES, 0, triangle->vertices.size());
	    program->disableAttributeArray(normalAttr);
	    program->disableAttributeArray(vertexAttr);
	    program->disableAttributeArray(lightAttr);
	    program->disableAttributeArray(colorAttr);

	}

    }
    program->setUniformValue(matrixUniform, modelview);
    program->release();
    program->bind();
}

void Model::setTexture(GLuint texture)
{
    this->texture = texture;
}

