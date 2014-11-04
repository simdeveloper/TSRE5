#ifndef DYNTRACKOBJ_H
#define	DYNTRACKOBJ_H

#include "WorldObj.h"
#include <QString>

class DynTrackObj : WorldObj{
public:
    struct Section{
        float type;
        float val1;
        float a;
        float r;
    };
    struct Shape{
        int iloscv;
        QOpenGLBuffer VBO;
        QOpenGLVertexArrayObject VAO;
    };
    
    float sectionIdx;
    float elevation;
    float collideFlags;
    Section* sections;
    Shape shape[2];
    
    DynTrackObj();
    DynTrackObj(const DynTrackObj& orig);
    virtual ~DynTrackObj();
    void load(int x, int y);
    void set(QString sh, FileBuffer* data);
    void render(GLUU* gluu, float lod, float posx, float posz, float* playerW, float* target, float fov);
private:
    int tex1;
    int tex2;
    bool init;
    void drawShape();
    void genShape();
    void createVBO(Shape* shape, int ptr, float * data);
};

#endif	/* DYNTRACKOBJ_H */

