/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "LevelCrObj.h"
#include "SFile.h"
#include "ShapeLib.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include "TDB.h"
#include "TRitem.h"
#include "Game.h"
#include "TrackItemObj.h"
#include "TS.h"
#include <QDebug>

LevelCrObj::LevelCrObj() {
    this->shape = -1;
    this->loaded = false;
    this->levelCrParameters[0] = 30; 
    this->levelCrParameters[1] = 20; 
    this->crashProbability = 0;
    this->levelCrData[0] = 0;
    this->levelCrTiming[0] = 60;
    this->levelCrTiming[1] = 60;
    this->levelCrTiming[2] = 4;
}

LevelCrObj::LevelCrObj(const LevelCrObj& orig) {
}

LevelCrObj::~LevelCrObj() {
}

bool LevelCrObj::allowNew(){
    return true;
}

bool LevelCrObj::isTrackItem(){
    return true;
}

void LevelCrObj::load(int x, int y) {
    this->shape = Game::currentShapeLib->addShape(resPath +"/"+ fileName);
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->qDirection[2] = -this->qDirection[2];
    this->loaded = true;
    this->size = -1;
    this->skipLevel = 1;
    this->modified = false;
    setMartix();
}

void LevelCrObj::deleteTrItems(){
    TDB* tdb = Game::trackDB;
    TDB* rdb = Game::roadDB;
    for(int i = 0; i<this->trItemIdCount/2; i++){
        if(this->trItemId[i*2] == 0)
            tdb->deleteTrItem(this->trItemId[i*2+1]);
        else if(this->trItemId[i*2] == 1)
            rdb->deleteTrItem(this->trItemId[i*2+1]);
        this->trItemId[i*2+1] = -1;
    }
}

void LevelCrObj::initTrItems(float* tpos){
    if(tpos == NULL)
        return;
    int trNodeId = tpos[0];
    float metry = tpos[1];
    
    TDB* tdb = Game::trackDB;
    TDB* rdb = Game::roadDB;
    qDebug() <<"new levelcr  "<<this->fileName;

    //trItemIdCount = 4;
    //levelCrData[1] = 1;
    //trItemId = new int[4];
    int* tid;
    //tdb->newLevelCrObject(tid, trNodeId, metry, this->typeID);
    //trItemId[0] = 0;
    //trItemId[1] = tid[1];
    float* playerT = Vec2::fromValues(this->x, this->y);
    float pos[3];
    Vec3::set(pos, position[0], position[1], -position[2]);
    float quat[4];
    float* buffer;
    int len;
    qDebug() << "find nearest road ";
    rdb->findNearestPositionOnTDB(playerT, (float*)&pos, (float*)&quat, tpos);
    qDebug() << "road pos "<<tpos[0]<<" "<<tpos[1];
    rdb->getVectorSectionLine(buffer, len, playerT[0], playerT[1], tpos[0], 0, 0);
    qDebug() << "and find intersections ";
    std::vector<TDB::IntersectionPoint*> ipoints;
    tdb->getSegmentIntersectionPositionOnTDB(ipoints, rdb, playerT, buffer, len, (float*)&pos);
    qDebug() << "intersection count: "<<ipoints.size();
    //trNodeId = tpos[0];
    //metry = tpos[1];
    //rdb->newLevelCrObject(tid, trNodeId, metry, this->typeID);
    //trItemId[2] = 1;
    //trItemId[3] = tid[1];

    trItemIdCount = ipoints.size()*4;
    levelCrData[1] = ipoints.size();
    trItemId = new int[ipoints.size()*4];    
    for(int i = 0; i < ipoints.size(); i++){
        tdb->newLevelCrObject(tid, ipoints[i]->idx, ipoints[i]->m, this->typeID);
        trItemId[i*2+0] = 0;
        trItemId[i*2+1] = tid[1];
        rdb->newLevelCrObject(tid, ipoints[i]->sidx, ipoints[i]->sm, this->typeID);
        trItemId[ipoints.size()*2+i*2+0] = 1;
        trItemId[ipoints.size()*2+i*2+1] = tid[1];
    }
    //trNodeId = tpos[0];
    //metry = tpos[1];
    //rdb->newLevelCrObject(tid, trNodeId, metry, this->typeID);
    //trItemId[2] = 1;
    //trItemId[3] = tid[1];

    this->drawPosition = NULL;
}

void LevelCrObj::set(QString sh, QString val){
    if (sh == ("filename")) {
        fileName = val;
        return;
    }
    if (sh == ("ref_filename")) {
        fileName = val;
        return;
    }
    WorldObj::set(sh, val);
    return;
}

void LevelCrObj::set(int sh, FileBuffer* data) {
    if (sh == TS::LevelCrParameters) {
        data->off++;
        levelCrParameters[0] = data->getFloat();
        levelCrParameters[1] = data->getFloat();
        return;
    }
    if (sh == TS::CrashProbability) {
        data->off++;
        crashProbability = data->getFloat();
        return;
    }
    if (sh == TS::LevelCrData) {
        data->off++;
        levelCrData[0] = data->getUint();
        levelCrData[1] = data->getUint();
        trItemId = new int[levelCrData[1]*4];
        return;
    }
    if (sh == TS::LevelCrTiming) {
        data->off++;
        levelCrTiming[0] = data->getFloat();
        levelCrTiming[1] = data->getFloat();
        levelCrTiming[2] = data->getFloat();
        return;
    }
    if (sh == TS::TrItemId) {
        data->off++;
        trItemId[trItemIdCount++] = data->getUint();
        trItemId[trItemIdCount++] = data->getUint();
        return;
    }
    if (sh == TS::FileName) {
        data->off++;
        int slen = data->getShort()*2;
        fileName = *data->getString(data->off, data->off + slen);
        data->off += slen;
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void LevelCrObj::set(QString sh, FileBuffer* data) {
    if (sh == ("levelcrparameters")) {
        levelCrParameters[0] = ParserX::GetNumber(data);
        levelCrParameters[1] = ParserX::GetNumber(data);
        return;
    }
    if (sh == ("crashprobability")) {
        crashProbability = ParserX::GetNumber(data);
        return;
    }
    if (sh == ("levelcrdata")) {
        levelCrData[0] = ParserX::GetHex(data);
        levelCrData[1] = ParserX::GetNumber(data);
        trItemId = new int[levelCrData[1]*4];
        return;
    }
    if (sh == ("levelcrtiming")) {
        levelCrTiming[0] = ParserX::GetNumber(data);
        levelCrTiming[1] = ParserX::GetNumber(data);
        levelCrTiming[2] = ParserX::GetNumber(data);
        return;
    }
    if (sh == ("tritemid")) {
        trItemId[trItemIdCount++] = ParserX::GetNumber(data);
        trItemId[trItemIdCount++] = ParserX::GetNumber(data);
        qDebug() <<"levelcr "<<trItemId[trItemIdCount-2] <<" "<<trItemId[trItemIdCount-1];
        return;
    }
    if (sh == ("filename")) {
        fileName = ParserX::GetString(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void LevelCrObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov, int selectionColor) {
    if (!loaded) return;
    if (shape < 0) return;
    if (jestPQ < 2) return;
    //GLUU* gluu = GLUU::get();
    //if((this.position===undefined)||this.qDirection===undefined) return;
    //
    if (size > 0) {
        if ((lod > size + 150)) {
            float v1[2];
            v1[0] = pos[0] - (target[0]);
            v1[1] = pos[2] - (target[2]);
            float v2[2];
            v2[0] = posx;
            v2[1] = posz;
            float iloczyn = v1[0] * v2[0] + v1[1] * v2[1];
            float d1 = sqrt(v1[0] * v1[0] + v1[1] * v1[1]);
            float d2 = sqrt(v2[0] * v2[0] + v2[1] * v2[1]);
            float zz = iloczyn / (d1 * d2);
            if (zz > 0) return;

            float ccos = cos(fov) + zz;
            float xxx = sqrt(2 * d2 * d2 * (1 - ccos));
            //if((ccos > 0) && (xxx > 200+50)) return;
            if ((ccos > 0) && (xxx > size) && (skipLevel == 1)) return;
        }
    } else {
        if (Game::currentShapeLib->shape[shape]->loaded)
            size = Game::currentShapeLib->shape[shape]->size;
    }
    
    gluu->mvPushMatrix();
    Mat4::multiply(gluu->mvMatrix, gluu->mvMatrix, matrix);
    gluu->m_program->setUniformValue(gluu->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    
    if(selectionColor != 0){
        int wColor = (int)(selectionColor/65536);
        int sColor = (int)(selectionColor - wColor*65536)/256;
        int bColor = (int)(selectionColor - wColor*65536 - sColor*256);
        gluu->disableTextures((float)wColor/255.0f, (float)sColor/255.0f, (float)bColor/255.0f, 1);
    } else {
        gluu->enableTextures();
    }
        
    Game::currentShapeLib->shape[shape]->render();
    
    if(selected){
        drawBox();
    }
    gluu->mvPopMatrix();
    
    if(Game::viewInteractives) 
        this->renderTritems(gluu, selectionColor);
};

void LevelCrObj::renderTritems(GLUU* gluu, int selectionColor){

    ///////////////////////////////
    TDB* tdb = Game::trackDB;
    if(drawPositions.size() == 0){
        if(this->trItemId == NULL){
            qDebug() << "LevelCrObj: fail trItemId";
            loaded = false;
            return;
        }
        for(int i = 0; i < trItemIdCount/2; i++){
            if(this->trItemId[i*2] != 0)
                continue;

            int id = tdb->findTrItemNodeId(this->trItemId[i*2+1]);
            if (id < 0) {
                qDebug() << "LevelCrObj: fail id";
                loaded = false;
                return;
            }
            //qDebug() << "id: "<< this->trItemId[i*2+1] << " "<< id;
            drawPosition = new float[7];
            bool ok = tdb->getDrawPositionOnTrNode(drawPosition, id, tdb->trackItems[this->trItemId[i*2+1]]->trItemSData1);
            if(!ok){
                this->loaded = false;
                return;
            }
            drawPosition[0] += 2048 * (drawPosition[5] - this->x);
            drawPosition[2] -= 2048 * (-drawPosition[6] - this->y);
            if(pointer3d == NULL){
                pointer3d = new TrackItemObj(1);
                pointer3d->setMaterial(0.9,0.5,0.0);
            }
            drawPositions.push_back(drawPosition);
        }
    }

    //if(pos == NULL) return;
    Mat4::identity(gluu->objStrMatrix);
    gluu->setMatrixUniforms();
    int useSC;

    for(int i = 0; i < drawPositions.size(); i++){
        drawPosition = drawPositions[i];
        gluu->mvPushMatrix();
        Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, drawPosition[0] + 0 * (drawPosition[4] - this->x), drawPosition[1] + 1, -drawPosition[2] + 0 * (-drawPosition[5] - this->y));
        Mat4::rotateY(gluu->mvMatrix, gluu->mvMatrix, drawPosition[3]);
        //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 2048*(this->trItemRData[3] - playerT[0] ), this->trItemRData[1]+2, -this->trItemRData[2] + 2048*(-this->trItemRData[4] - playerT[1]));
        //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 0, this->trItemRData[1]+0, -this->trItemRData[2] + 0);
        gluu->m_program->setUniformValue(gluu->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
        useSC = (float)selectionColor/(float)(selectionColor+0.000001);
        pointer3d->render(selectionColor + (1)*131072*8*useSC);
        gluu->mvPopMatrix();
    }

};

bool LevelCrObj::getBorder(float* border){
    if (shape < 0) return false;
    if (!Game::currentShapeLib->shape[shape]->loaded)
        return false;
    float* bound = Game::currentShapeLib->shape[shape]->bound;
    border[0] = bound[0];
    border[1] = bound[1];
    border[2] = bound[2];
    border[3] = bound[3];
    border[4] = bound[4];
    border[5] = bound[5];
    return true;
}

void LevelCrObj::save(QTextStream* out){
    if (!loaded) return;

*(out) << "	LevelCr (\n";
    
*(out) << "		UiD ( "<<this->UiD<<" )\n";
*(out) << "		LevelCrParameters ( "<<this->levelCrParameters[0]<<" "<<this->levelCrParameters[1]<<" )\n";
*(out) << "		CrashProbability ( "<<this->crashProbability<<" )\n";
*(out) << "		LevelCrData ( "<< ParserX::MakeFlagsString(this->levelCrData[0]) <<" "<<this->levelCrData[1]<<" )\n";
*(out) << "		LevelCrTiming ( "<<this->levelCrTiming[0]<<" "<<this->levelCrTiming[1]<<" "<<this->levelCrTiming[2]<<" )\n";
for(int i = 0; i < trItemIdCount; i+=2){
*(out) << "		TrItemId ( "<<this->trItemId[i]<<" "<<this->trItemId[i+1]<<" )\n";
}
*(out) << "		FileName ( "<<this->fileName<<" )\n";
*(out) << "		Position ( "<<this->position[0]<<" "<<this->position[1]<<" "<<-this->position[2]<<" )\n";
*(out) << "		QDirection ( "<<this->qDirection[0]<<" "<<this->qDirection[1]<<" "<<-this->qDirection[2]<<" "<<this->qDirection[3]<<" )\n";
*(out) << "		VDbId ( "<<this->vDbId<<" )\n";
if(this->staticDetailLevel > -1)
*(out) << "		StaticDetailLevel ( "<<this->staticDetailLevel<<" )\n";
*(out) << "	)\n";
}