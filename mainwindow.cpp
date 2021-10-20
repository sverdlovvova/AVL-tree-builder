#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"

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

int MainWindow::getHeight(tree *root) {
    if (!root) {
        return 0;
    }
    return root->height;
}

int MainWindow::diff(tree *root) {
    return getHeight(root->rig) - getHeight(root->lef);
}

void MainWindow::updHeight(tree *root) {
    if (!root) {
        return;
    }
    int h1 = getHeight(root->lef), h2 = getHeight(root->rig);
    if (h1 > h2) {
        root->height = h1 + 1;
    } else {
        root->height = h2 + 1;
    }
}

tree* MainWindow::leftRotate(tree *root) {
    tree *q = root;
    tree *p = q->rig;
    q->rig = p->lef;
    updHeight(q);
    p->lef = q;
    updHeight(p);
    return p;
}

tree* MainWindow::rightRotate(tree *root) {
    tree *p = root;
    tree *q = root->lef;
    p->lef = q->rig;
    updHeight(p);
    q->rig = p;
    updHeight(q);
    return q;
}

tree* MainWindow::balance(tree *root){
    updHeight(root);
    int dif = diff(root);
    if (dif == 2) {
        if (diff(root->rig) < 0) {
            root->rig = rightRotate(root->rig);
        }
        return leftRotate(root);
    } else if (dif == -2) {
        if (diff(root->lef) > 0) {
            root->lef = leftRotate(root->lef);
        }
        return rightRotate(root);
    }
    return root;
}

tree* MainWindow::insert(tree *root, int x){
    if (!root) {
        return new tree(x);
    }
    if (x < root->key) {
        root->lef = insert(root->lef, x);
        updHeight(root);
        return balance(root);
    } else if (x > root->key) {
        root->rig = insert(root->rig, x);
        updHeight(root);
        return balance(root);
    }
    return root;
}

tree* MainWindow::findMin(tree *root) {
    if (!root->lef) {
        return root;
    }
    return findMin(root->lef);
}

tree* MainWindow::eraseMin(tree *root) {
    if (!root->lef) {
        return root->rig;
    } else {
        root->lef = eraseMin(root->lef);
        updHeight(root);
        return balance(root);
    }
}

tree* MainWindow::erase(tree *root, int x) {
    if (x < root->key) {
        root->lef = erase(root->lef, x);
        updHeight(root);
        return balance(root);
    } else if (x > root->key) {
        root->rig = erase(root->rig, x);
        updHeight(root);
        return balance(root);
    } else {
        tree *p = root->lef;
        tree *q = root->rig;
        delete root;
        if (!q) {
            return p;
        } else {
            tree *new_ = findMin(q);
            q = eraseMin(q);
            new_->rig = q;
            new_->lef = p;
            updHeight(new_);
            return balance(new_);
        }
    }
}

const int inf = 1000000000, xmin = 240, ymin = 30, X = 1700, Y = 1000, scale = 30;


void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    QFont font = p.font();
    font.setPixelSize(12);
    p.setFont(font);
    const QRect bckgrnd = QRect(xmin - ymin, 0, X, Y);
    p.fillRect(bckgrnd, QColor(255, 247, 206));
    QPen pen = p.pen();
    printTree(root, this, scale, 210, width(), scale);
}

void MainWindow::on_add_clicked()
{
    QString str = ui->num_but->toPlainText();
    ui->num_but->clear();
    int num = str.toInt();
    if (num < 1 || num > inf) {
        return;
    }
    else {
        root = insert(root, num);
        repaint();
    }
}

void MainWindow::printTree(tree *root, QPaintDevice *pd, int scale, int li, int ri, int j) {
    if (root == nullptr) {
        return;
    }
    QPainter p(pd);
    int x1 = (li + ri) / 2;
    int y1 = j;
    p.drawText(x1, y1, QString::number(root->key));
    p.drawEllipse(QPoint((li + ri) / 2, j), scale, scale);
    printTree(root->lef, pd, scale, li, (li + ri) / 2, j + 2 * scale);
    printTree(root->rig, pd, scale, (li + ri) / 2, ri, j + 2 * scale);
}

int MainWindow::search(tree* root, int num){
    if (!root) {
        return 0;
    }
    if (root->key > num){
        root = root->lef;
        return search(root, num);
    } else if (root->key < num) {
        root = root->rig;
        return search(root, num);
    }
    return 1;
}

void MainWindow::on_delite_clicked()
{
    QString str = ui->num_but->toPlainText();
    ui->num_but->clear();
    int num = str.toInt();
    if (num < 1 || num > inf) {
        return;
    }
    else if (search(root, num)) {
        root = erase(root, num);
    }
    repaint();
}
