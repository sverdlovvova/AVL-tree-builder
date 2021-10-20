#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPainter"

struct tree {
    int key;
    tree *lef, *rig;
    int height;
    tree(int key) {
        this->key = key;
        lef = nullptr;
        rig = nullptr;
        height = 1;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getHeight(tree *root);
    int diff(tree *root);
    void updHeight(tree *root);
    tree* leftRotate(tree *root);
    tree* rightRotate(tree *root);
    tree* balance(tree *root);
    tree* insert(tree *root, int x);
    tree* findMin(tree *root);
    tree* eraseMin(tree *root);
    tree* erase(tree *root, int x);
    void paintEvent(QPaintEvent*)override;
    tree* root = nullptr;
    void printTree(tree *root, QPaintDevice *pd, int scale, int li, int ri, int j);
    int search(tree* root, int num);

private slots:
    void on_add_clicked();

    void on_delite_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
