#include "xmlhandler.h"

#include <QDebug>
#include <QStyle>
#include <QTreeWidgetItem>

XmlHandler::XmlHandler(QTreeWidget *_treeWidget)
{

    treeWidget = _treeWidget;
    QStyle *style = treeWidget->style();

    cdicon.addPixmap(style->standardPixmap(QStyle::SP_FileDialogDetailedView));

    treeWidget->clear();
}


bool XmlHandler::startElement(const QString & /* namespaceURI */,
                               const QString & /* localName */,
                               const QString &qName,
                               const QXmlAttributes &attributes)
{
    if (qName == "outline") {

        if (attributes.value("xmlUrl") == "" ) { // elimate sections

            return true;

        } else {

            item = new QTreeWidgetItem(treeWidget);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            item->setIcon(0, cdicon);
            item->setText(0, attributes.value("text"));

            root = item;

       //   item = new QTreeWidgetItem(root);
       //   item->setText(0, "Title:: "+attributes.value("title"));

        //  item = new QTreeWidgetItem(root);
        //  item->setText(0, "Type:: "+attributes.value("type"));

            item = new QTreeWidgetItem(root);
            item->setText(0, "xmlURL: "+attributes.value("xmlUrl"));

            item = new QTreeWidgetItem(root);
            item->setText(0, "htmlURL: "+attributes.value("htmlUrl"));
       }

    }

    return true;
}
