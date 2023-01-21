#pragma once

#ifndef OBJECT_TRACKER_STRUCTURES_H
#define OBJECT_TRACKER_STRUCTURES_H

/*!
    \brief Структура для вывода результатов расчетов
    \author Никитина Виктория Олеговна
    \date 18.01.23
*/
struct ResultParameters{

    public:

        /*!
            \brief Конструктор
            \param t, d секунды в формате double, расстояние в пикселях в формате int
        */
        ResultParameters(double t, int d) {
            time = t;
            pixelDistance = d;
        }

        ~ResultParameters() = default;

        /*!
            \brief Метод для получения секунд
            \param -
            \return Секунды в формате double
        */
        double getTime() {return time;}

        /*!
            \brief Метод для получения расстояния в пикселях
            \param -
            \return Пиксели в формате int
        */
        int getPixelDistance() {return pixelDistance;};

        /*!
            \brief Метод для получения скорости в пиксель/секунда
            \param -
            \return Скорость в формате double
        */
        double getPixelSpeed() { return pixelDistance/time;};

        /*!
            \brief Метод для получения скорости в см/секунда
            \param rt коэффициент для перевода пикселей в сантиметры в формате double
            \return Скорость в формате double
        */
        double getRealSpeed(double rt) {return rt*pixelDistance/time;};

    private:
        double time; ///< Время в секундах
        int pixelDistance; ///< Расстояние в пикселях
};

#endif //OBJECT_TRACKER_STRUCTURES_H