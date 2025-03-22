/*Вариант 17
Объект - автомобиль
(поля: название модели, массив, расходов топлива из 3 - х элементов(на трассе, в городе, смешанный),
максимальная скорость, мощность)
    Сортировка по названию модели*/
/*Для класса, разработанного в ЛР4, обеспечить возможность добавления объектов в контейнер set
(сортировка как указано в задании на ЛР4) и в контейнер unordered_set.
Исходные данные как в ЛР4 читать из файла, вывести на печать для контроля объекты контейнеров.*/
#include <iostream>
#include <fstream>


#include <string>
#include <set>
#include <unordered_set>

#include <deque>
#include <algorithm>

using namespace std;


class Car {
private:
    string model;
    double* consumption;
    int velocity;
    int power;
public:
    Car() {
        model = "";
        consumption = nullptr;
        velocity = 0;
        power = 0;
    }
    Car(const Car& copy_car) {
        model = copy_car.model;
        consumption = new double[3];
        for (int i = 0; i < 3; i++) consumption[i] = copy_car.consumption[i];
        velocity = copy_car.velocity;
        power = copy_car.power;
    }
    Car& operator=(const Car& copy_car) {
        model = copy_car.model;
        if (consumption != nullptr) delete[] consumption;
        consumption = new double[3];
        for (int i = 0; i < 3; i++) consumption[i] = copy_car.consumption[i];
        velocity = copy_car.velocity;
        power = copy_car.power;
        return *this;
    }
    bool operator<(Car& car) {
        return model < car.model;
    }
    friend ostream& operator<<(ostream& out, Car& car);
    friend istream& operator>>(istream& in, Car& car);
    friend class Auto;

};

ostream& operator<<(ostream& out, Car& car) {
    out << "Model: " << car.model << "\nConsumption: ";
    for (int i = 0; i < 3; i++) out << car.consumption[i] << " ";
    out << "\nVelocity: " << car.velocity << "\nPower: " << car.power << "\n\n";
    return out;
}

istream& operator>>(istream& in, Car& car) {
    in >> car.model;
    if (car.consumption != nullptr) delete[] car.consumption;
    car.consumption = new double[3];
    for (int i = 0; i < 3; i++) in >> car.consumption[i];
    in >> car.velocity;
    in >> car.power;
    return in;
}
class Auto{
private:
    hash<string> shash;
    hash<double*> dhash;
    hash<int> ihash;
    const size_t coef = 2'946'901;
public:
    size_t operator()(Car const& car) const {
        return (coef * coef * coef * shash(car.model)
            + coef * coef * dhash(car.consumption)
            + coef * ihash(car.velocity)
            + ihash(car.power));
    }
};


int main() {
    ifstream file("input.txt");
    if (!file) return 1;
    int s;
    file >> s;
    set<Car> car_set;
    unordered_set<Car, Auto> car_un_set;
    for (int i = 0; i < s; i++) {
        Car car;
        file >> car;
        car_set.insert(car);
        car_un_set.insert(car);
    }
    file.close();

    cout << "in set:\n";
    for (auto car : car_set) cout << car;
    cout << "\n\nin unordered set:\n";
    for (auto car : car_un_set) cout << car;

    return 0;
}

