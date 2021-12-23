#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

//Первый вариант

float vectorLength(float x, float y) {
    return sqrt(x * x + y * y);
};

int main(int argc, char** argv) {
    fstream inputFile("in.txt");
    if (inputFile.is_open()) { //проверка открытия файла
        float xn, yx;

        inputFile >> xn; //Приём координат
        inputFile >> yx;

        float ccoord; // временная координата
        vector<float> coordX; // координаты точек
        vector<float> coordY;
        // Пока в файле есть данные, выполнять:
        while (inputFile >> ccoord) {
            coordX.push_back(ccoord); // Вставка в массив данных о координатах
            inputFile >> ccoord;
            coordY.push_back(ccoord);
        }
        inputFile.close(); // Закрытие файла

    //Задание переменных левого минимального угла, правого и их подсчёт
        int left = -1, right = -1;
        float LeftMinCos = 1, RightMinCos = 1;
        float len_v = sqrt(xn * xn + yx * yx);
        float cos_a = xn / len_v;
        float sin_a = yx / len_v;

        //Цикл, считающий по каждой координате:
        for (int i = 0; i < coordX.size(); ++i) {
            // Промежуточные переменные для подсчёта внутри цикла
            float new_x = cos_a * coordX[i] + sin_a * coordY[i];
            float new_y = -sin_a * coordX[i] + cos_a * coordY[i];

            float prod_dot = new_x * 1 + new_y * 0;
            float len_p = sqrt(new_x * new_x + new_y * new_y);
            float cos = prod_dot / 1 / len_p;

            if (new_y > 0) { //слева
                if (cos <= LeftMinCos) {
                    LeftMinCos = cos;
                    left = i;
                }
            }

            if (new_y <= 0) { // справа
                if (cos <= RightMinCos) {
                    RightMinCos = cos;
                    right = i;
                }
            }
        }
        // Вывод результатов
        if (left != -1) {
            cout << "Leftmost: " << coordX[left] << " " << coordY[left] << endl;
        }
        else {
            cout << "Leftmost: " << 0 << " " << 0 << endl;
        }
        if (right != -1) {
            cout << "Rightmost: " << coordX[right] << " " << coordY[right] <<
                endl;
        }
        else {
            cout << "Rightmost: " << 0 << " " << 0 << endl;
        }
    }
    else {
        cout << "Unknown file" << endl; //Выводится, если не открывается файл
    }
    return 0;
}