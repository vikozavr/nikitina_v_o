#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "structures.h"

#ifndef OBJECT_TRACKER_H
#define OBJECT_TRACKER_H

/*!
    \brief Класс, реализующий работу по расчету видеопотока
    \author Никитина Виктория Олеговна
    \date 18.01.23
*/
class ObjectTracker {

    public:
        /*!
            \brief Конструктор класса
            \param path, start, stop путь к файлу в формате std::string, зона старта в формате cv::Rect, зона конца в формате cv::Rect
        */
        ObjectTracker(std::string path, cv::Rect start, cv::Rect stop);
        ~ObjectTracker() = default;

        /*!
            \brief Метод для старта основных расчетов
            \param useGui использование GUI в формате bool
            \return Данные о расчетах в формате ResultParams
        */
        ResultParameters compute(bool useGui);

    private:
        std::string path; ///< Путь к видеофайлу
        cv::Rect startZone, stopZone; ///< Зона начала, зона конца

        

};

#endif //OBJECT_TRACKER_H