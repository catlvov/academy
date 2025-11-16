#include <iostream>
#include <cmath>
#include <string>
#define M_PI 3.141592653589793

// Базовый класс фигуры
class Shape {
public:
    virtual ~Shape() {}
    virtual void printPrimaryProperties() const = 0;
    virtual void printSecondaryProperties() const = 0;
    virtual void draw() const = 0; // Заглушка, реализуйте по своему
};

// Квадрат
class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}

    void printPrimaryProperties() const override {
        std::cout << "Side length: " << side << std::endl;
    }

    void printSecondaryProperties() const override {
        double area = side * side;
        double perimeter = 4 * side;
        std::cout << "Area: " << area << std::endl;
        std::cout << "Perimeter: " << perimeter << std::endl;
    }

    void draw() const override {
        // Реализация рисования с помощью выбранной графической библиотеки
        std::cout << "[Drawing a square with a side " << side << "]" << std::endl;
        // Можно интегрировать с SFML или другой библиотекой
    }
};

// Прямоугольник
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    void printPrimaryProperties() const override {
        std::cout << "Width: " << width << std::endl;
        std::cout << "Height: " << height << std::endl;
    }

    void printSecondaryProperties() const override {
        double area = width * height;
        double perimeter = 2 * (width + height);
        std::cout << "Area: " << area << std::endl;
        std::cout << "Perimeter: " << perimeter << std::endl;
    }

    void draw() const override {
        std::cout << "[Drawing a rectangle " << width << "x" << height << "]" << std::endl;
    }
};

// Круг
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    void printPrimaryProperties() const override {
        std::cout << "Radius: " << radius << std::endl;
    }

    void printSecondaryProperties() const override {
        double area = M_PI * radius * radius;
        double perimeter = 2 * M_PI * radius;
        std::cout << "Area: " << area << std::endl;
        std::cout << "Perimeter (Circumference): " << perimeter << std::endl;
    }

    void draw() const override {
        std::cout << "[Drawing a circle with a radius " << radius << "]" << std::endl;
    }
};

// Равносторонний треугольник
class Triangle : public Shape {
private:
    double side;
public:
    Triangle(double s) : side(s) {}

    void printPrimaryProperties() const override {
        std::cout << "Side length: " << side << std::endl;
    }

    void printSecondaryProperties() const override {
        double area = (sqrt(3) / 4) * side * side;
        double perimeter = 3 * side;
        std::cout << "Area: " << area << std::endl;
        std::cout << "Perimeter: " << perimeter << std::endl;
    }

    void draw() const override {
        std::cout << "[Drawing an equilateral triangle with a side " << side << "]" << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "");
    Square sq(5);
    std::cout << "Square:" << std::endl;
    sq.printPrimaryProperties();
    sq.printSecondaryProperties();
    sq.draw();

    Rectangle rect(4, 6);
    std::cout << "\nRectangle:" << std::endl;
    rect.printPrimaryProperties();
    rect.printSecondaryProperties();
    rect.draw();

    Circle c(3);
    std::cout << "\nCircle:" << std::endl;
    c.printPrimaryProperties();
    c.printSecondaryProperties();
    c.draw();

    Triangle tri(4);
    std::cout << "\nTriangle:" << std::endl;
    tri.printPrimaryProperties();
    tri.printSecondaryProperties();
    tri.draw();

    return 0;
}