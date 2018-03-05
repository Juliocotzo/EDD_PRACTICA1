#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAdministrar_Categoria_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void removeItem();

    void on_actionCrear_Contacto_triggered();

    void on_pushButton_4_clicked();

    void insertarComboBoxCrearContacto();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_actionGraficar_Lista_triggered();

    void InsertarListWidgetContactoEditar();

    void on_actionModificar_Contacto_triggered();

    void on_listWidget_Contacto_Editar_itemDoubleClicked(QListWidgetItem *item);

    void modificarContacto_Editar(string nombre, string nuevoNombre, string nuevaDireccion, string nuevoTelefono, string nuevaCategoria, string nuevoPath);

    void buscarContacto_Editar(string nombre);

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void removeItem_ListaContacto();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
