#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <sstream>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString file;

void MainWindow::on_pushButton_clicked()
{

        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename1 = file.toStdString();


}


void MainWindow::on_pushButton_2_clicked()
{

        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename2 = file.toStdString();


}
void stringmatching(brute_force& a, vector<char> pattern, int index)
{


    for (int i = 1; i <= a.number_of_phrases_filey(); i++)
    {

        vector<char> temp = a.getsentence_filey(i);


        vector<logs> tempI = a.trial(temp, pattern);

        if (tempI.size() > 0)
        {
            cout << "sentence: " << index << endl;
            for (int j = 0; j < tempI.size(); j++)
            {
                cout << "the phrase : (" << tempI[j].text << ") is similar to a phrase in sentence: " << i << " of the second file"<<" this phrase starts from word number: "<<tempI[j].index_x<<" of the first file sentence and starts from the word: "<<tempI[j].index_y<<" of the second file sentence"<< endl;
            }

        }

    }


}
void plagiarism_check(brute_force& a)
{
    cout << endl;
    cout << "checking every sentence in file 1 " << endl;
    cout << endl;
    for (int j = 1; j <= a.number_of_phrases_filex(); j++)          // every phrase in filex vector
    {

        stringmatching(a, a.getsentence_filex(j), j);
    }

}
#include <sstream>

#include <sstream>

void output()
{
    std::cout << "cherif" << std::endl;
}

void MainWindow::on_pushButton_3_clicked()
{
    brute_force a(filename1,filename2);







    ui->label->setWordWrap(true);

    ui->label->setText("checking every sentence in file 1\n");

    for (int j = 1; j <= a.number_of_phrases_filex(); j++)          // every phrase in filex vector
    {


        for (int i = 1; i <= a.number_of_phrases_filey(); i++)
        {

            vector<char> temp = a.getsentence_filey(i);


            vector<logs> tempI = a.trial(temp, a.getsentence_filex(j));

            if (tempI.size() > 0)
            {
                ui->label->setText(ui->label->text()+QString("sentence: ") + QString::fromStdString(std::to_string(j)) + '\n');

                for (int z = 0; z < tempI.size(); z++)
                {
                    ui->label->setText(ui->label->text()+QString("the phrase : (") + QString::fromStdString(tempI[z].text) +
                                       QString(") is similar to a phrase in sentence: ") + QString::number(i) +
                                       QString(" of the second file") + QString(" this phrase starts from word number: ") +
                                       QString::number(tempI[z].index_x) + QString(" of the first file sentence and starts from the word: ") +
                                       QString::number(tempI[z].index_y) + QString(" of the second file sentence") + QChar('\n'));

                }

            }

        }

    }
}


