#include "SignalShape.h"
#include "FileBuffer.h"
#include "ParserX.h"
#include <QDebug>

SignalShape::SignalShape() {
}

SignalShape::~SignalShape() {
}

void SignalShape::set(QString sh, FileBuffer* data) {
    //if (sh == ("tritemid")) {
    //    trItemId = ParserX::parsujUint(data);
    //    return;
    //}
    if (sh == "signalsubobjs") {
        iSubObj = ParserX::parsujr(data);
        //qDebug() << iSubObj;
        subObj = new SubObj[iSubObj];
        int idx;
        for(int i = 0; i < iSubObj; i++){
            idx = ParserX::parsujr(data);
            subObj[idx].iLink = 0;
            subObj[idx].type = ParserX::odczytajtc(data);
            subObj[idx].desc = ParserX::odczytajtc(data);
            //qDebug() <<subObj[idx].type;
            //qDebug() <<subObj[idx].desc;
            while (!((sh = ParserX::nazwasekcji_inside(data).toLower()) == "")) {
                //qDebug() << sh;
                if (sh == "") {
                    break;
                }
                if (sh == "sigsubtype") {
                    subObj[idx].sigSubType = ParserX::odczytajtc(data);
                    ParserX::pominsekcje(data);
                    continue;
                }
                if (sh == "signalflags") {
                    QString sflags;
                    while((sflags = ParserX::odczytajtcInside(data)) != "" ){
                        if(sflags == "JN_LINK"){
                            //qDebug() << "JN_LINK";
                            this->isJnLink = true;
                            subObj[idx].isJnLink = true;
                            continue;
                        }
                        if(sflags == "DEFAULT"){
                            subObj[idx].defaultt = true;
                            continue;
                        }
                        if(sflags == "OPTIONAL"){
                            subObj[idx].optional = true;
                            continue;
                        }
                        if(sflags == "BACK_FACING"){
                            subObj[idx].backFacing = true;
                            continue;
                        }
                        qDebug() << "signalFlags" << sflags;
                        //subObj[idx].signalFlags = sflags;
                    }
                    ParserX::pominsekcje(data);
                    continue;
                }
                if (sh == "sigsubstype") {
                    subObj[idx].sigSubSType = ParserX::odczytajtc(data);
                    ParserX::pominsekcje(data);
                    continue;
                }
                if (sh == "sigsubjnlinkif") {
                    subObj[idx].iLink = ParserX::parsujr(data);
                    subObj[idx].sigSubJnLinkIf = new int[subObj[idx].iLink];
                    for(int j = 0; j < subObj[idx].iLink; j++)
                        subObj[idx].sigSubJnLinkIf[j] = ParserX::parsujr(data);
                    ParserX::pominsekcje(data);
                    continue;
                }
                qDebug() << "--- " << sh;
                ParserX::pominsekcje(data);
                continue;
            }
            ParserX::pominsekcje(data);
        }
        return;
    }
    qDebug() << "-- " << sh;
    return;
}
