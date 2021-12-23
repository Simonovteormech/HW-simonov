#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
const float g = 9.81;

// Функция для траекторий
int func_traect(float x_0, float h_0, float vx0, float vy0,
    int StartIndex,
    const vector<float>& coordX,
    const vector<float>& coordY) {
    if (vx0 > 0) {
        int NewIndex = StartIndex + 1;
        float xi = coordX[NewIndex];
        float ti = (xi - x_0) / vx0;
        float hi = -0.5 * g * ti * ti + vy0 * ti + h_0;

        if (hi <= 0) { // Ничего не произойдет, если высота точки в данный момент на уровне земли или ниже
            return StartIndex;
        }
        else if (coordY[NewIndex] >= hi) { // Если произошло столкновение со столбом (отскок)
            float vxi = -vx0;
            float vyi = -g * ti + vy0;
            return func_traect(xi, hi, vxi, vyi, NewIndex, coordX, coordY);
        }
        else {
            if (NewIndex >= coordX.size() - 1) { // Если всё нормльно, летим дальше
                return NewIndex;
            }
            float vxi = vx0;
            float vyi = -g * ti + vy0;
            return func_traect(xi, hi, vxi, vyi, NewIndex, coordX, coordY); //Рекурсия
        }
    }

    if (vx0 <= 0) { // Если произошёл отскок:
        int NewIndex = StartIndex - 1; // Летим назад
        float xi = coordX[NewIndex];
        float ti = (xi - x_0) / vx0;
        float hi = -0.5 * g * ti * ti + vy0 * ti + h_0;
        // По подобию с первой функцией:
        if (hi <= 0) {
            return NewIndex;
        }
        else if (coordY[NewIndex] > hi) {
            float vxi = -vx0;
            float vyi = -g * ti + vy0;
            return func_traect(xi, hi, vxi, vyi, NewIndex, coordX, coordY);
        }
        else {
            float vxi = vx0;
            float vyi = -g * ti + vy0;
            return func_traect(xi, hi, vxi, vyi, NewIndex, coordX, coordY);
        }
    }
    return StartIndex;
}

// По условию задачи:
int main(int argc, char** argv) {
    if (argc == 2) {
        string line;
        fstream inputFile(argv[1]);
        if (inputFile.is_open()) { //проверка открытия файла
            float h0, dy, dx; // Задание переменных в основной программе
            inputFile >> h0;  // считываем начальные данные
            inputFile >> dx;
            inputFile >> dy;
            int i = 0;
            float CCoord;
            vector<float> coordX; // координаты перегородок
            vector<float> coordY;
            coordX.push_back(0);
            coordY.push_back(h0);
            while (inputFile >> CCoord) { // Вытаскиваем координаты
                if (i % 2 == 0) {
                    coordX.push_back(CCoord);
                }
                else {
                    coordY.push_back(CCoord);
                }
                ++i;
            }
            inputFile.close();

            if (coordX.size() <= 1) {
                cout << 0;
            }
            else {
                int Index = func_traect(0, h0, dx, dy, 0, coordX, coordY); // Подсчёт ответа
                cout << Index; // Вывод номера промежутка
            }
        }
        else {
            cout << "Unable to open file" << endl; // Если невозможно открыть файл
        }
    }
    else {
        cout << "there are no arguments or there are more of them than we expect" << endl; // Если некорректное кол-во аргументов
    }
    return 0;
}