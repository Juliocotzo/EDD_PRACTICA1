#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listacategorias.h"
#include "listacontactos.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QBitmap>
#include <QString>

//Lamada de Listas
listaCategorias *listCategoria = new listaCategorias();
listaContactos *listContacto = new listaContactos();
string nombre_editar;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(3);
    this->setFixedSize(600,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdministrar_Categoria_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->setFixedSize(450,450);
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<ui->lineEdit->text();
    listCategoria->insertarCategoria(ui->lineEdit->text().toStdString());
    ui->listWidget->addItem(ui->lineEdit->text());
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmacion de Eliminacion", "Esta seguro que desea elininar \n "
                                                                       "1. Actividad que posee esta categoria \n "
                                                                       "2. Contactos que posee esta categoria",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      qDebug() << "Se eliminaron Actividades y Contactos";
      qDebug()<< ui->listWidget->currentItem()->text();
      listCategoria->eliminarCategoria(ui->listWidget->currentItem()->text().toStdString());
      removeItem();
      //QApplication::quit();
    } else {
      qDebug() << "Ningun Movimiento";
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    listCategoria->graficarCategoria();
}

void MainWindow::removeItem()
{
    ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->currentItem()));
}

void MainWindow::on_actionCrear_Contacto_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->setFixedSize(500,500);
    insertarComboBoxCrearContacto();

}

void MainWindow::on_pushButton_4_clicked()
{
    QString usersfilename = QFileDialog::getOpenFileName(this,"Seleccionar archivo",".","Image files (*.jpg);;All files (*.*)");
    ui->lineEdit_Path->setText(usersfilename);
    ui->lineEdit_Path->setEnabled(false);
    QPixmap pixmap(ui->lineEdit_Path->text());
    ui->label_ImagenCrearContacto->setPixmap(pixmap);
    ui->label_ImagenCrearContacto->setMask(pixmap.mask());
    ui->label_ImagenCrearContacto->setScaledContents(true);
}

void MainWindow::insertarComboBoxCrearContacto(){
    listaCategorias* aux = new listaCategorias();
    aux = listCategoria->primero;
    if(listCategoria->primero!=NULL){
        while (aux!=NULL) {
            //cout<<aux->categoria<<endl;
            ui->comboBox_CategoriaCrearContacto->addItem(QString::fromStdString(aux->categoria));
            ui->comboBox_Categoria_Editar->addItem(QString::fromStdString(aux->categoria));
            aux=aux->siguiente;
        }
    }else{
        cout<<"Lista Vacia"<<endl;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug()<<ui->lineEdit_Nombre->text();
    qDebug()<<ui->lineEdit_Direccion->text();
    qDebug()<<ui->lineEdit_Telefono->text();
    qDebug()<<ui->comboBox_CategoriaCrearContacto->currentText();
    qDebug()<<ui->lineEdit_Path->text();
    listContacto->insertarContacto(ui->lineEdit_Nombre->text().toStdString(),ui->lineEdit_Direccion->text().toStdString(),ui->lineEdit_Telefono->text().toStdString(),ui->comboBox_CategoriaCrearContacto->currentText().toStdString(),ui->lineEdit_Path->text().toStdString());
    //Limpiar casillas
    ui->stackedWidget->setCurrentIndex(3);
    ui->lineEdit_Nombre->setText("");
    ui->lineEdit_Direccion->setText("");
    ui->lineEdit_Telefono->setText("");
    ui->comboBox_CategoriaCrearContacto->clear();
    ui->lineEdit_Path->setText("");
    ui->label_ImagenCrearContacto->clear();
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_actionGraficar_Lista_triggered()
{
    listContacto->graficarListaContacto();
}

void MainWindow::InsertarListWidgetContactoEditar(){
    listaContactos* actual = new listaContactos();
    actual = listContacto->Primero;
    if(listContacto->Primero!=NULL){
        do{
            ui->listWidget_Contacto_Editar->addItem(QString::fromStdString(actual->nombre));
           //cout<<"\n"<<actual->nombre<<","<<actual->direccion<<","<<actual->telefono<<","<<actual->categoria<<","<<actual->path<<"\n";
           actual = actual->siguiente;

        }while (actual!=listContacto->Primero);

    }else{
        cout<<"\n La lista es vacia\n";
    }
}

void MainWindow::on_actionModificar_Contacto_triggered()
{
    ui->comboBox_Categoria_Editar->clear();
    ui->stackedWidget->setCurrentIndex(2);
    this->setFixedSize(800,500);
    insertarComboBoxCrearContacto();
    InsertarListWidgetContactoEditar();
}

void MainWindow::on_listWidget_Contacto_Editar_itemDoubleClicked(QListWidgetItem *item)
{
    ui->lineEdit_Nombre_Editar->setText("");
    ui->lineEdit_Direccion_Editar->setText("");
    ui->lineEdit_Telefono_Editar->setText("");
    ui->lineEdit_Categoria_Editar->setText("");
    ui->lineEdit_Path_Editar->setText("");
    ui->label_ImagenCrearContacto_2->clear();

    qDebug()<<ui->listWidget_Contacto_Editar->currentItem()->text();
    nombre_editar = ui->listWidget_Contacto_Editar->currentItem()->text().toStdString();
    qDebug()<<QString::fromStdString(nombre_editar);
    buscarContacto_Editar(nombre_editar);


}

void MainWindow::modificarContacto_Editar(string nombre, string nuevoNombre, string nuevaDireccion, string nuevoTelefono, string nuevaCategoria, string nuevoPath){
    listaContactos* actual = new listaContactos();
    actual = listContacto->Primero;

    bool encontrado = false;

    if(listContacto->Primero!=NULL){
        do{
            if(actual->nombre==nombre){
                cout<<"\nNodo con el dato ( "<<nombre<<" )encontrado";
                cout<<"ingrese el nuevo dato";
                actual->nombre = nuevoNombre;
                actual->direccion = nuevaDireccion;
                actual->telefono = nuevoTelefono;
                actual->categoria = nuevaCategoria;
                actual->path = nuevoPath;
                cout<<"Nodo modificado";

                encontrado = true;
            }

            actual = actual->siguiente;
        }while (actual!=listContacto->Primero && encontrado !=true);

        if(!encontrado){
            cout<<"Palabra no encotrada";
        }
    }else{
        cout<<"Lista se encuentra vacia";
    }
}

void MainWindow::buscarContacto_Editar(string nombre){
    listaContactos* actual = new listaContactos();
    actual = listContacto->Primero;

    bool encontrado = false;
    //string nodoBuscado;
    //cout<< "Ingrese el dato del nodo a Eliminar: ";
    //cin >> nodoBuscado;
    if(listContacto->Primero!=NULL){
        do{
            if(actual->nombre==nombre){
                //cout<<"\nNodo con el dato ( "<<nodoBuscado<<" )encontrado";
                //cout<<"Nombre: "<<actual->nombre<<"\\nDireccion: "<<actual->direccion<<"\\nTelefono: "<<actual->telefono<<"\\nCategoria: "<<actual->categoria<<"\\nImagen: "<<actual->path<<endl;
                ui->lineEdit_Nombre_Editar->setText(QString::fromStdString(actual->nombre));
                ui->lineEdit_Direccion_Editar->setText(QString::fromStdString(actual->direccion));
                ui->lineEdit_Telefono_Editar->setText(QString::fromStdString(actual->telefono));
                ui->lineEdit_Categoria_Editar->setText(QString::fromStdString(actual->categoria));
                ui->lineEdit_Path_Editar->setText(QString::fromStdString(actual->path));
                QPixmap pixmap(QString::fromStdString(actual->path));
                ui->label_ImagenCrearContacto_2->setPixmap(pixmap);
                ui->label_ImagenCrearContacto_2->setMask(pixmap.mask());
                ui->label_ImagenCrearContacto_2->setScaledContents(true);
                encontrado = true;
            }

            actual = actual->siguiente;
        }while (actual!=listContacto->Primero && encontrado !=true);

        if(!encontrado){
            cout<<"Palabra no encotrada";
        }
    }else{
        cout<<"Lista se encuentra vacia";
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->label_ImagenCrearContacto_2->clear();
    QString usersfilename = QFileDialog::getOpenFileName(this,"Seleccionar archivo",".","Image files (*.jpg);;All files (*.*)");
    ui->lineEdit_Path->setText(usersfilename);
    ui->lineEdit_Path->setEnabled(false);
    QPixmap pixmap(ui->lineEdit_Path->text());
    ui->label_ImagenCrearContacto_2->setPixmap(pixmap);
    ui->label_ImagenCrearContacto_2->setMask(pixmap.mask());
    ui->label_ImagenCrearContacto_2->setScaledContents(true);
}

void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmacion de Editar", "Esta seguro que dese editar este contacto",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      //qDebug() << "Se eliminaron Actividades y Contactos";
      //qDebug()<< ui->listWidget_Contacto_Editar->currentItem()->text();
      listContacto->modificarContacto(nombre_editar,ui->lineEdit_Nombre_Editar->text().toStdString(),ui->lineEdit_Direccion_Editar->text().toStdString(),ui->lineEdit_Telefono_Editar->text().toStdString(),ui->comboBox_Categoria_Editar->currentText().toStdString(),ui->lineEdit_Path_Editar->text().toStdString());
      //listCategoria->eliminarCategoria(ui->listWidget->currentItem()->text().toStdString());
      //removeItem();
      //QApplication::quit();
    } else {
      qDebug() << "Ningun Movimiento";
    }

}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_10_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmacion de Eliminacion", "Esta seguro que desea elininar \n "
                                                                       "1. Actividad que posee esta contacto \n ",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      qDebug() << "Se eliminaron Actividades y Contactos";
      qDebug()<< ui->listWidget_Contacto_Editar->currentItem()->text();
      //listCategoria->eliminarCategoria(ui->listWidget_Contacto_Editar->currentItem()->text().toStdString());
      listContacto->eliminarContacto(ui->listWidget_Contacto_Editar->currentItem()->text().toStdString());
      removeItem_ListaContacto();
      //QApplication::quit();
    } else {
      qDebug() << "Ningun Movimiento";
    }
}

void MainWindow::removeItem_ListaContacto()
{
    ui->listWidget_Contacto_Editar->takeItem(ui->listWidget_Contacto_Editar->row(ui->listWidget_Contacto_Editar->currentItem()));
}
