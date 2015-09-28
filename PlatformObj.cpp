#include "PlatformObj.h"
#include "SFile.h"
#include "ShapeLib.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include <QDebug>
#include "Game.h"
#include "TDB.h"
#include "TrackItemObj.h"
#include "OglObj.h"
#include <Math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

PlatformObj::PlatformObj() {
    this->shape = -1;
    this->loaded = false;
    pointer3d = new TrackItemObj();
}

PlatformObj::PlatformObj(const PlatformObj& orig) {
}

PlatformObj::~PlatformObj() {
}

void PlatformObj::load(int x, int y) {
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->qDirection[2] = -this->qDirection[2];
    this->loaded = true;
    this->skipLevel = 1;
    this->modified = false;

    setMartix();
}

void PlatformObj::set(QString sh, FileBuffer* data) {
    if (sh == ("sidingdata") || sh == ("platformdata")) {
        platformData = ParserX::parsuj16(data);
        return;
    }
    if (sh == ("carfrequency")) {
        carFrequency = ParserX::parsujr(data);
        return;
    }
    if (sh == ("caravspeed")) {
        carAvSpeed = ParserX::parsujr(data);
        return;
    }
    if (sh == ("tritemid")) {
        trItemId[trItemIdCount++] = ParserX::parsujr(data);
        trItemId[trItemIdCount++] = ParserX::parsujr(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void PlatformObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov, int selectionColor) {
    //Vector3f *pos = tdb->getDrawPositionOnTrNode(playerT, id, this->trItemSData1);
    
    this->renderTritems(gluu);
};

void PlatformObj::renderTritems(GLUU* gluu){
    
    if (drawPositionB == NULL) {
        TDB* tdb = Game::trackDB;
        if(this->typeID == this->carspawner)
            tdb = Game::roadDB;
        int id = tdb->findTrItemNodeId(this->trItemId[1]);
        if (id < 0) {
            qDebug() << "fail id";
            return;
        }
        //qDebug() << "id: "<< this->trItemId[1] << " "<< id;
        drawPositionB = new float[6];
        tdb->getDrawPositionOnTrNode(drawPositionB, id, tdb->trackItems[this->trItemId[1]]->trItemSData1);
        drawPositionB[0] += 2048 * (drawPositionB[4] - this->x);
        drawPositionB[2] -= 2048 * (-drawPositionB[5] - this->y);
    }
    if (drawPositionE == NULL) {
        TDB* tdb = Game::trackDB;
        if(this->typeID == this->carspawner)
            tdb = Game::roadDB;
        int id = tdb->findTrItemNodeId(this->trItemId[3]);
        if (id < 0) {
            qDebug() << "fail id";
            return;
        }
        drawPositionE = new float[6];
        tdb->getDrawPositionOnTrNode(drawPositionE, id, tdb->trackItems[this->trItemId[3]]->trItemSData1);
        
        drawPositionE[0] += 2048 * (drawPositionE[4] - this->x);
        drawPositionE[2] -= 2048 * (-drawPositionE[5] - this->y);
        
    }
    if(line == NULL){
        line = new OglObj();
        float *punkty = new float[6];
        int ptr = 0;
        int i = 0;

        punkty[ptr++] = 0;
        punkty[ptr++] = 0;
        punkty[ptr++] = 0;
        punkty[ptr++] = drawPositionE[0]-drawPositionB[0];
        punkty[ptr++] = drawPositionE[1]-drawPositionB[1];
        punkty[ptr++] = -drawPositionE[2]+drawPositionB[2];
        
        if(this->typeID == this->platform){
            line->setMaterial(0.0, 1.0, 0.0);
            pointer3d->setMaterial(0.0, 1.0, 0.0);
        }
        if(this->typeID == this->siding){
            line->setMaterial(1.0, 0.7, 0.0);
            pointer3d->setMaterial(1.0, 0.7, 0.0);
        }
        if(this->typeID == this->carspawner){
            line->setMaterial(0.4, 0.0, 1.0);
            pointer3d->setMaterial(0.4, 0.0, 1.0);
        }
        
        line->init(punkty, ptr, line->V, GL_LINES);
        delete punkty;
    }
    //if(pos == NULL) return;
    Mat4::identity(gluu->objStrMatrix);
    gluu->setMatrixUniforms();
    
    //float dlugosc = (float) sqrt(pow(drawPositionB[2]-drawPositionE[2], 2) + pow(drawPositionB[0]-drawPositionE[0], 2));
    float aa = (drawPositionE[2]-drawPositionB[2]);
    if(aa != 0) aa = (aa/fabs(aa));
    float rot = (aa+1)*M_PI/2 + (float)(atan((drawPositionB[0]-drawPositionE[0])/(drawPositionB[2]-drawPositionE[2]))); 
    
    //(-(float)(atan((drawPositionB[1]-drawPositionE[1])/(dlugosc))
    
    gluu->mvPushMatrix();
    Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, drawPositionB[0] + 0 * (drawPositionB[4] - this->x), drawPositionB[1] + 1, -drawPositionB[2] + 0 * (-drawPositionB[5] - this->y));
    Mat4::rotateY(gluu->mvMatrix, gluu->mvMatrix, -rot);
    //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 2048*(this->trItemRData[3] - playerT[0] ), this->trItemRData[1]+2, -this->trItemRData[2] + 2048*(-this->trItemRData[4] - playerT[1]));
    //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 0, this->trItemRData[1]+0, -this->trItemRData[2] + 0);
    gluu->m_program->setUniformValue(gluu->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    pointer3d->render();
    gluu->mvPopMatrix();
    
    gluu->mvPushMatrix();
    Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, drawPositionE[0] + 0 * (drawPositionE[4] - this->x), drawPositionE[1] + 1, -drawPositionE[2] + 0 * (-drawPositionE[5] - this->y));
    Mat4::rotateY(gluu->mvMatrix, gluu->mvMatrix, -rot + M_PI);
    //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 2048*(this->trItemRData[3] - playerT[0] ), this->trItemRData[1]+2, -this->trItemRData[2] + 2048*(-this->trItemRData[4] - playerT[1]));
    //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 0, this->trItemRData[1]+0, -this->trItemRData[2] + 0);
    gluu->m_program->setUniformValue(gluu->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    pointer3d->render();
    gluu->mvPopMatrix();
    
    gluu->mvPushMatrix();
    Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, drawPositionB[0] + 0 * (drawPositionB[4] - this->x), drawPositionB[1] + 1, -drawPositionB[2] + 0 * (-drawPositionB[5] - this->y));
    gluu->m_program->setUniformValue(gluu->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    line->render();
    gluu->mvPopMatrix();
};

void PlatformObj::save(QTextStream* out) {
    if (!loaded) return;
    int l;
    QString flags;
    flags = QString::number(this->staticFlags, 16);
    l = flags.length();
    for (int i = 0; i < 8 - l; i++)
        flags = "0" + flags;

    QString flags2;
    flags2 = QString::number(this->platformData, 16);
    l = flags2.length();
    for (int i = 0; i < 8 - l; i++)
        flags2 = "0" + flags2;

    if (type == "siding")
        *(out) << "	Siding (\n";
    if (type == "platform")
        *(out) << "	Platform (\n";
    if (type == "carspawner")
        *(out) << "	CarSpawner (\n";

    *(out) << "		UiD ( " << this->UiD << " )\n";
    if (type == "siding")
        *(out) << "		SidingData ( " << flags2 << " )\n";
    if (type == "platform")
        *(out) << "		PlatformData ( " << flags2 << " )\n";
    if (type == "carspawner") {
        *(out) << "		CarFrequency ( " << this->carFrequency << " )\n";
        *(out) << "		CarAvSpeed ( " << this->carAvSpeed << " )\n";
    }
    *(out) << "		TrItemId ( " << this->trItemId[0] << " " << this->trItemId[1] << " )\n";
    *(out) << "		TrItemId ( " << this->trItemId[2] << " " << this->trItemId[3] << " )\n";
    *(out) << "		StaticFlags ( " << flags << " )\n";
    *(out) << "		Position ( " << this->position[0] << " " << this->position[1] << " " << -this->position[2] << " )\n";
    *(out) << "		QDirection ( " << this->qDirection[0] << " " << this->qDirection[1] << " " << -this->qDirection[2] << " " << this->qDirection[3] << " )\n";
    *(out) << "		VDbId ( " << this->vDbId << " )\n";
    if (this->staticDetailLevel > -1)
        *(out) << "		StaticDetailLevel ( " << this->staticDetailLevel << " )\n";
    *(out) << "	)\n";
}