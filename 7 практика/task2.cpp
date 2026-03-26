#include <iostream>

class Shape
{
public:
    virtual ~Shape() {}
    virtual double area() const = 0;
    virtual void print() const { std::cout << "Фигура"; }
};

class Circle : public Shape
{
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14 * radius * radius; }
    double getRadius() const { return radius; }
};

class Rectangle : public Shape
{
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
};

int main()
{
    Shape* shape = new Circle(5.0);

    //безопасный static_cast
    Circle* circle = static_cast<Circle*>(shape);
    std::cout << "Radius: " << circle->getRadius() << std::endl;

    //неправильное приведение
    //компилируется, но вызов методов Rectangle для объекта Circle — неопределенное поведение
    Rectangle* rect = static_cast<Rectangle*>(shape);

    delete shape;
    return 0;
}
