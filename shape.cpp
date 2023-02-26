#include <iostream>

using namespace std;
// Пополнение и использование библиотеки фигур
#include "screen.h"
#include "shape.h"

// дополнительная функция присоединения снизу
void down(shape &p, const shape &q) {
    point n = q.south();
    point s = p.north();
    p.move(n.x - s.x, n.y - s.y - 1);
}

// дополнительная функция размещения в центре
void center(shape &p, const shape &q) {
    point cq;
    point cp;
    cq.x = q.north().x;
    cq.y = q.west().y;
    cp = p.south();
    p.move(cq.x - cp.x, cq.y - cp.y - 1);
}

//Дополнительный фрагмент - прямоугольный треугольник
class r_triangle : public rectangle, public reflectable {
    /*
    nw ------ n ------ ne
    |  *            *   |
    |     *      *      |
    w        * *        e
    |       *   *       |
    |    *         *    |
    sw------- s ------ se
    */
    bool reflected;
    int rotated = 1; // переменная для определения положения наклона треугольника
public:
    r_triangle(point a, point b, bool r = true) : rectangle(a, b), reflected(r) {}

    void draw();

    void flip_horisontally(); // Отразить горизонтально (пустая функция)
    void flip_vertically(); //{ reflected = !reflected; };	// Отразить вертикально
    void rotate_right();

    void rotate_left();
};

// переопределение функции-члена для рисования фигуры
void r_triangle::draw() {
    if (rotated == 1) {
        put_line(seast(), sw);
        put_line(sw, nwest());
        put_line(nwest(), seast());
    } else if (rotated == 2) {
        put_line(nwest(), ne);
        put_line(sw, ne);
        put_line(nwest(), sw);
    } else if (rotated == 3) {
        put_line(nwest(), ne);
        put_line(seast(), ne);
        put_line(seast(), nwest());
    } else if (rotated == 4) {
        put_line(sw, ne);
        put_line(seast(), ne);
        put_line(seast(), sw);
    }
    if (ne.y < 0 || ne.x > XMAX || sw.y > YMAX || sw.x < 0) { throw out_of_bounds_Error(); }
}

// переопределение функции-члена для поворота направо
void r_triangle::rotate_right() {
    int w = ne.x - sw.x, h = ne.y - sw.y; //(учитывается масштаб по осям)
    sw.x = ne.x - h * 2;
    ne.y = sw.y + w / 2;

    rotated += 1;
    if (rotated == 5) {
        rotated = 1;
    }
}

// переопределение функции-члена для поворота налево
void r_triangle::rotate_left() {
    int w = ne.x - sw.x, h = ne.y - sw.y;
    ne.x = sw.x + h * 2;
    ne.y = sw.y + w / 2;

    rotated -= 1;
    if (rotated == 0) {
        rotated = 4;
    }
}

// переопределение функции-члена для отражения по-горизонтали
void r_triangle::flip_horisontally() {
    point new_sw;
    point new_ne;
    new_sw.y = sw.y + (sw.y - nwest().y);
    new_sw.x = sw.x;
    new_ne = seast();

    this->ne = new_ne;
    this->sw = new_sw;

    if (rotated == 1) {
        this->rotated = 2;
    } else if (rotated == 2) {
        this->rotated = 1;
    } else if (rotated == 3) {
        this->rotated = 4;
    } else if (rotated == 4) {
        this->rotated = 3;
    }
}

// переопределение функции-члена для отражения по-вертикали
void r_triangle::flip_vertically() {
    point new_sw;
    point new_ne;
    new_ne.x = ne.x + (ne.x - nwest().x);
    new_ne.y = ne.y;
    new_sw = seast();

    this->ne = new_ne;
    this->sw = new_sw;


    if (rotated == 1) {
        this->rotated = 4;
    } else if (rotated == 2) {
        this->rotated = 3;
    } else if (rotated == 3) {
        this->rotated = 2;
    } else if (rotated == 4) {
        this->rotated = 1;
    }
}

// Cборная пользовательская фигура - физиономия
class myshape : public rectangle { // Моя фигура ЯВЛЯЕТСЯ
    int w, h;                         //        прямоугольником

    line mouth; // рот
public:
    //глаза перемещены в public для поворота и отражения треугольников
    r_triangle l_eye; // левый глаз
    r_triangle r_eye; // правый глаз
    myshape(point, point);

    void draw();

    void move(int, int);

    void resize(int) {}
};

myshape::myshape(point a, point b)
        : rectangle(a, b),    //Инициализация базового класса
          w(neast().x - swest().x + 1), // Инициализация данных
          h(neast().y - swest().y + 1), // - строго в порядке объявления!
          l_eye(point(swest().x + w / 8 + 1, swest().y + h * 3 / 4),
                point(swest().x + w / 8 + 1 + w / 4, swest().y + h * 3 / 4 + h / 6)),
          r_eye(point(swest().x + w - w / 8 - 1 - 1 - w / 4, swest().y + h * 3 / 4),
                point(swest().x + w - w / 8 - 1 - 1, swest().y + h * 3 / 4 + h / 6)),
          mouth(point(swest().x + 2, swest().y + h / 4), w - 4) {}

void myshape::draw() {
    rectangle::draw(); //Контур лица (глаза и нос рисуются сами!)
    int a = (swest().x + neast().x) / 2;
    int b = (swest().y + neast().y) / 2;
    put_point(point(a, b)); // Нос – существует только на рисунке!
    if (a < 0 || b < 0 || a > XMAX || b > YMAX) {
        throw out_of_bounds_Error();
    }
}

void myshape::move(int a, int b) {
    rectangle::move(a, b);
    l_eye.move(a, b);
    r_eye.move(a, b);
    mouth.move(a, b);
}

int main() {
    setlocale(LC_ALL, "Rus");
    screen_init();
//== 1.Объявление набора фигур ==
    rectangle hat(point(0, 0), point(14, 5));  // прямоугольная шляпа
    line brim(point(0, 15), 17);                 // линия-край шляпы
    myshape face(point(15, 10), point(27, 18));     // класс-лицо
    r_triangle beard(point(40, 10), point(50, 20));  // прямоугольный треугольник - борода
    r_triangle pizza(point(60, 20), point(65, 23));  // прямоугольный треугольник - эмблема на шляпе
    try {
        shape_refresh();
        std::cout << "=== Generated... ===\n";
        std::cin.get(); //Смотреть исходный набор
    } catch (out_of_bounds_Error) {
        std::cout << "Out of bounds!\n";
    }
//== 2.Подготовка к сборке ==
    hat.rotate_right();
    brim.resize(2);
    face.resize(2);
    beard.flip_horisontally();   // бородп отражается по горизонтали
    face.l_eye.rotate_left();    // левый глаз поворачивается налево
    face.r_eye.rotate_right();   // правый глаз поворачивается направо
    try {
        shape_refresh();
        std::cout << "=== Prepared... ===\n";
        std::cin.get(); //Смотреть результат поворотов/отражений
    } catch (out_of_bounds_Error) {
        std::cout << "Out of bounds!\n";
    }
//== 3.Сборка изображения ==
	//face.move(0, -10); // Лицо - в исходное положение (Если убрать комментарий, сработает ошибка out_of_bounds_Error)
    up(brim, face);
    up(hat, brim);
    down(beard, face);    // борода присоединяется к лицу снизу
    center(pizza, hat);   // эмблема присоединяется в центр шляпы
    try {
        shape_refresh();
        std::cout << "=== Ready! ===\n";
        std::cin.get(); //Смотреть результат
    } catch (out_of_bounds_Error) {
        std::cout << "Out of bounds!\n";
    }
    screen_destroy();
    return 0;
}
