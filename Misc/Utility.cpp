#include "Utility.h"
#include <QVector>
#include <sstream>

bool Math::isEven(int i){ return i % 2 == 0; }
bool Math::isOdd(int i){ return i % 2 != 0; }
bool Math::isOddAndEven(int i, int j){ return ((isEven(i) && isOdd(j)) || (isEven(j) && isOdd(i))); }

qreal Geometry::distance2D(QPointF src, QPointF dst)
{
    int dx = src.x() - dst.x();
    int dy = src.y() - dst.y();
    return sqrt(pow(dx,2) + pow(dy,2));
}

QVector<QPointF> Geometry::generateCircle(int edges, int radius)
{
    QVector<QPointF> points;
    int radians = 0;
    for (int i = 0; i < edges; ++i, radians = i * (360 / edges)){
        points << QPointF(cos(radians * Geometry::radToDegRatio), sin(radians * Geometry::radToDegRatio));
    }
    for (size_t i = 0; i < points.size(); ++i){
        points[i] *= radius;
    }
    return points;
}

QPointF Geometry::midPoint(const QPointF p1, const QPointF p2)
{
    return QPointF(p1.x() + (p2.x() - p1.x()) / 2, p1.y() + (p2.y() - p1.y()) / 2);
}

QPixmap Geometry::scaleToWidth(QPixmap pixmap, qreal width)
{
    QPixmap scaled = pixmap.scaled(width, pixmap.height() / (pixmap.width() / width));
    return scaled;
}


int Parse::ctoi(char c)
{
    return c - '0';
}

std::string Parse::ctos(char c)
{
    return std::string(1,c);
}

std::vector<std::string> Parse::split(std::string& s, const std::string delimiter)
{
    std::vector<std::string> v;
    int delLen = delimiter.length();;
    int index = 0;
    std::string nextSubstr;
    while (s.length() > 0) {
        index = s.find(delimiter);
        if (index == std::string::npos) { v.push_back(s); break; };
        nextSubstr = s.substr(0, index);
        if (nextSubstr.length() > 0) { v.push_back(nextSubstr); };
        s = s.substr(index + delLen, s.length() - 1);
    }
    return v;
}

std::vector<std::string> Parse::split(std::string& s, char delim) {
    std::vector<std::string> v;
    std::stringstream line(s);
    std::string token;
    while (std::getline(line, token, delim)) {
        v.push_back(token);
    };
    return v;
}

std::vector<int> Parse::stringToInt(const std::vector<std::string>& v)
{
    std::vector<int> ints;
    ints.reserve(v.size());
    for (auto& string : v) {
        ints.push_back(std::atoi(string.c_str()));
    }
    return ints;
}

QString Parse::intToQString(int num)
{
    return QString::number(num);
}

QString Parse::qrealToQString(qreal num)
{
    return QString::number(num);

}

typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
time_point Time::now(){
    return std::chrono::high_resolution_clock::now();
}

qreal Time::timeSinceSec(time_point startTime){
    time_point now = Time::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime).count() / 1000000000.0;
}

qreal Time::timeSinceMilli(time_point startTime){
    time_point now = Time::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime).count() / 1000000.0;
}

qreal Time::timeSinceMicro(time_point startTime){
    time_point now = Time::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime).count() / 1000.0;
}

qreal Time::timeSinceNano(time_point startTime){
    time_point now = Time::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime).count() / 1.0;
}

qreal Time::timeDiffSec(time_point startTime, time_point endTime){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1000000000.0;
}

qreal Time::timeDiffMilli(time_point startTime, time_point endTime){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1000000.0;
}

qreal Time::timeDiffMicro(time_point startTime, time_point endTime){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1000.0;
}

qreal Time::timeDiffNano(time_point startTime, time_point endTime){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1.0;
}
