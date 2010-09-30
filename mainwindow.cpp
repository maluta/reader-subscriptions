#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "xmlhandler.h"

#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->lineEdit,SIGNAL(textChanged( const QString&)),this,SLOT(search(const QString&)));

       connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enter()));

    ui->treeWidget->header()->setResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidget->clear();

    XmlHandler handler(ui->treeWidget);

    /* XML Parsing and Showing */
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    QFile f("/Users/maluta/Downloads/google-reader-subscriptions.xml");
    f.open(QFile::ReadOnly | QFile::Text);

    qDebug() << "-- entrou" ;

    QXmlInputSource xmlInputSource(&f);

    if (reader.parse(xmlInputSource))
        statusBar()->showMessage(tr("Search Finished"), 3000);

    f.close();

}


void MainWindow::enter() {


    QList<QTreeWidgetItem *> list;

    qDebug() << " enter";
    //QTreeWidget::findItems ( const QString & text, Qt::MatchFlags flags, int column = 0 ) const

    list = ui->treeWidget->findItems(ui->lineEdit->text(),Qt::MatchContains,0);

    ui->textEdit->setText("");
    for(int i=0; i<list.length();i++) {
        //ui->textEdit->setText(list[i]->text(0));
        ui->textEdit->append(list[i]->text(0));
        qDebug() << list[i]->text(0);
    }
}

void MainWindow::search(const QString &s) {

    qDebug() << s;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
