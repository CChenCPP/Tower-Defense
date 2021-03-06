#pragma once
#include <random>
#include <QString>
#include <QPointF>
#include <QPixmap>
#include <chrono>

typedef unsigned char uint8_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

namespace Math
{
    static constexpr qreal e = 2.71828182845904523536;
    bool isEven(int i);
    bool isOdd(int i);
    bool isOddAndEven(int i, int j);
}

namespace Geometry
{
    static constexpr qreal radToDegRatio = 3.141592653589793238463 / 180.0;
    qreal distance2D(QPointF src, QPointF dst);
    QVector<QPointF> generateCircle(int edges, int radius);
    QPointF midPoint(const QPointF p1, const QPointF p2);
    QPixmap scaleToWidth(QPixmap pixmap, qreal width);
}

namespace Parse
{
    template<typename stringable>
    QString toQString(stringable& str){
        return QString::fromUtf8(std::to_string(str));
    }

    int ctoi(char c);
    std::string ctos(char c);
    std::vector<std::string> split(std::string& s, const std::string delimiter);
    std::vector<std::string> split(std::string& s, char delim = ' ');
    std::vector<int> stringToInt(const std::vector<std::string>& v);
    QString intToQString(int num);
    QString qrealToQString(qreal num);
}

namespace RNG
{
     static thread_local std::random_device rd;
     static thread_local std::mt19937 generator32(rd());
     static thread_local std::mt19937_64 generator64(rd());

     template<typename numType>
     numType randomNum(numType num){
         if (num >= 0) {
             std::uniform_int_distribution<numType> range(0, num);
             return range(generator32);
         }
         else {
             std::uniform_int_distribution<numType> range(num, 0);
             return range(generator32);
         }
     }

     template<typename numType>
     numType randomNum(numType min, numType max){
         if (max < min) { return 0; };
         std::uniform_int_distribution<numType> range(min, max);
         return range(generator32);
     }

     template<typename numType, typename numType2>
     int64_t randomNum(numType min, numType2 max){
         if (max < min) { return 0; };
         std::uniform_int_distribution<long long int> range(min, max);
         return range(generator32);
     }
}

namespace Time{
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
    time_point now();
    qreal timeSinceSec(time_point startTime);
    qreal timeSinceMilli(time_point startTime);
    qreal timeSinceMicro(time_point startTime);
    qreal timeSinceNano(time_point startTime);
    qreal timeDiffSec(time_point startTime, time_point endTime);
    qreal timeDiffMilli(time_point startTime, time_point endTime);
    qreal timeDiffMicro(time_point startTime, time_point endTime);
    qreal timeDiffNano(time_point startTime, time_point endTime);
}