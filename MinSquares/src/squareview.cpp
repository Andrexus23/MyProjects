#include "../inc/squareview.h"
#include "QDebug"


SquareView::SquareView(int x, int y, int size, int coef, QGraphicsScene *scene): x(x*coef), y(y*coef), size(size*coef)
{
       this->scene = scene;
       square =  new QGraphicsRectItem(this->x, this->y, this->size, this->size);
       square->setBrush(QBrush(Qt::white));
       scene->addItem(square);
       std::string s = std::to_string(size);

       this->text = scene->addText(s.c_str());
       if(size*coef < 30) {
           text->setFont(QFont("Arial", 5));
           text->setPos((coef)*(x), (coef)*(y));
       } else{
           text->setFont(QFont("Arial", 10));
           text->setPos((coef)*(x + size/2.5), (coef)*(y + size/2.5));
       };
}

SquareView::~SquareView()
{
    scene->removeItem(square);
    scene->removeItem(text);
    delete square;
    delete text;
}
