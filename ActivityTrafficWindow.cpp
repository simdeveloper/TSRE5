/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "ActivityTrafficWindow.h"
#include "ActivityTrafficProperties.h"
#include "Route.h"
#include "Traffic.h"

ActivityTrafficWindow::ActivityTrafficWindow(QWidget* parent) : QWidget(parent) {
    setWindowFlags(Qt::WindowType::Tool);
    setWindowTitle(tr("Traffic"));
    
    trafficProperties = new ActivityTrafficProperties(this);
    
    QVBoxLayout *actionListLayout = new QVBoxLayout;
    actionListLayout->setContentsMargins(0,0,0,0);
    actionListLayout->setSpacing(0);
    QPushButton *bNew = new QPushButton("New Traffic");
    QObject::connect(bNew, SIGNAL(released()),
                      this, SLOT(bNewSelected()));
    QPushButton *bDelete = new QPushButton("Delete");
    QObject::connect(bDelete, SIGNAL(released()),
                      this, SLOT(bDeleteSelected()));
    QStringList list;
    list.append("Name:");
    list.append("This:");
    list.append("Any:");
    lTraffic.setFixedWidth(250);
    lTraffic.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lTraffic.setColumnCount(3);
    lTraffic.setHeaderLabels(list);
    lTraffic.setRootIsDecorated(false);
    lTraffic.header()->resizeSection(0,170);    
    lTraffic.header()->resizeSection(1,30);    
    lTraffic.header()->resizeSection(2,30);    
    actionListLayout->addWidget(&lTraffic);
    actionListLayout->addWidget(bNew);
    actionListLayout->addWidget(bDelete);
    QHBoxLayout *v = new QHBoxLayout;
    v->setSpacing(2);
    v->setContentsMargins(1,1,1,1);
    v->addItem(actionListLayout);
    v->addWidget(trafficProperties);
    this->setLayout(v);
    
    QObject::connect(&lTraffic, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
                      this, SLOT(lTrafficSelected(QTreeWidgetItem*, int)));
}

ActivityTrafficWindow::~ActivityTrafficWindow() {
}

void ActivityTrafficWindow::showTraffic(Route* r){
    if(this->isHidden())
        return;
    route = r;
    //serviceProperties->setPaths(route->path);
    //activity = r->s
    
    lTraffic.clear();
    QList<QTreeWidgetItem *> items;
    QStringList list;
    for(int i = 0; i < route->traffic.size(); i++ ){
        if(route->traffic[i] == NULL)
            continue;
        //new QListWidgetItem ( route->service[i]->displayName, &serviceList, i );
        list.clear();
        list.append(route->traffic[i]->nameId);
        list.append("");
        list.append("");
        QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, list, i );
        if(i == 0){
            item->setCheckState(1, Qt::Checked);
        }else{
            item->setCheckState(1, Qt::Unchecked);
        }
        item->setCheckState(2, Qt::Checked);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        items.append(item);
    }
    lTraffic.insertTopLevelItems(0, items);
}

void ActivityTrafficWindow::lTrafficSelected(QTreeWidgetItem *item, int column){
    if(route == NULL)
        return;
    trafficProperties->showTraffic(route->traffic[item->type()]);
}
