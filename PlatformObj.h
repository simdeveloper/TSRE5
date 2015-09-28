#ifndef PLATFORMOBJ_H
#define	PLATFORMOBJ_H

#include "WorldObj.h"
#include <QString>
#include "FileBuffer.h"

class TrackItemObj;
class OglObj;

class PlatformObj : public WorldObj  {
public:
    PlatformObj();
    PlatformObj(const PlatformObj& orig);
    virtual ~PlatformObj();
    void load(int x, int y);
    void set(QString sh, FileBuffer* data);
    void save(QTextStream* out);
    void render(GLUU* gluu, float lod, float posx, float posz, float* playerW, float* target, float fov, int selectionColor);

private:
    unsigned int platformData;
    int trItemId[4];
    int trItemIdCount = 0;
    int carFrequency = 0;
    int	carAvSpeed = 0;
    TrackItemObj* pointer3d = NULL;
    OglObj* line = NULL;
    float* drawPositionB = NULL;
    float* drawPositionE = NULL;
    void renderTritems(GLUU* gluu);
};

#endif	/* PLATFORMOBJ_H */
