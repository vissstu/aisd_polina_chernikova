#pragma once
#include <random>
#include <iostream> 
#include <cmath> 
#include <complex> 
#include <typeinfo>


using namespace std;

template<typename T>
struct Point
{
    T x;
    T y;

    Point() : x(), y() {} // ����������� �� ��������� 
    Point(T _x, T _y) : x(_x), y(_y) {} // ����������� � ����� �����������
    // �������� ������������
    Point& operator=(const Point& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

};

template<typename T>
class Polyline
{
private:
    Point<T>* vertexs; // ������ ������ 
    std::size_t number_of_vertexs; // ���������� ������ 
    std::size_t max_number_vertexs; // ������������ ������� ������� ������ 

    // ����� ��� ��������� ������� ������� ������
    void resize()
    {
        max_number_vertexs = (max_number_vertexs == 0) ? 1 : max_number_vertexs * 2;
        Point<T>* temp = new Point<T>[max_number_vertexs];
        for (size_t i = 0; i < number_of_vertexs; ++i) {
            if (number_of_vertexs <= max_number_vertexs)    temp[i] = vertexs[i];
        }
        delete[] vertexs;
        vertexs = temp;
    }

public:
    // ����������� �� ���������
    Polyline() : vertexs(nullptr), number_of_vertexs(0), max_number_vertexs(0) {}

    // ����������� � ����������: ���������� �����
    Polyline(T x, T y) {
        // �������������� ������ �����
        vertexs = new Point<T>[1];
        vertexs[0] = Point<T>(x, y);

        number_of_vertexs = 1;
        max_number_vertexs = 1;
    }

    // ����������� � ����������: ���������� �����
    Polyline(const size_t n, T m1, T m2) : number_of_vertexs(n), max_number_vertexs(n) {
        vertexs = new Point<T>[max_number_vertexs];
        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (is_integral_v<T>)
        {
            uniform_int_distribution<T> dis(m1, m2);
            for (size_t i = 0; i < number_of_vertexs; i++)
            {
                T x = dis(gen);
                T y = dis(gen);
                vertexs[i] = Point<T>(x, y);
            }
        }
        else if constexpr (is_floating_point_v<T>)
        {
            uniform_real_distribution<T> dis(m1, m2);
            for (size_t i = 0; i < number_of_vertexs; i++)
            {
                T x = dis(gen);
                T y = dis(gen);
                vertexs[i] = Point<T>(x, y);
            }
        }
    }

    // ����������� � ����������� (������� ������� �� �����, ���������� ������ �� ������� ����� � ��������� [m1, m2])
    Polyline(size_t n) : number_of_vertexs(n), max_number_vertexs(n) {
        vertexs = new Point<T>[max_number_vertexs];
    }

    // ����������� �����������
    Polyline(const Polyline& other) : vertexs(new Point<T>[other.max_number_vertexs]), number_of_vertexs(other.number_of_vertexs), max_number_vertexs(other.max_number_vertexs) {
        for (std::size_t i = 0; i < number_of_vertexs; ++i)
        {
            if (number_of_vertexs <= max_number_vertexs) {
                vertexs[i] = other.vertexs[i];
            }
        }
    }

    // �������� ������������
    Polyline& operator=(const Polyline& other)
    {
        if (this != &other)
        {
            delete[] vertexs;
            vertexs = new Point<T>[other.max_number_vertexs];
            max_number_vertexs = other.max_number_vertexs;
            number_of_vertexs = other.number_of_vertexs;
            for (std::size_t i = 0; i < number_of_vertexs; ++i)
            {
                if (number_of_vertexs <= max_number_vertexs) {
                    vertexs[i] = other.vertexs[i];
                }
            }
        }
        return *this;
    }

    // ����������
    ~Polyline()
    {
        delete[] vertexs;
    }


    // �������� [] ��� ������/������ ������� ������� �� � �������
    Point<T>& operator[](std::size_t index)
    {
        return vertexs[index];
    }

    const Point<T>& operator[](std::size_t idx) const
    {
        return vertexs[idx];
    }

    // ����� ��� ���������� ����� �������
    void addVertex(const Point<T>& point)
    {
        if (number_of_vertexs == max_number_vertexs)
        {
            resize();
        }
        vertexs[number_of_vertexs++] = point;
    }

    // ����� ��� ��������� �������� ����� ������
    size_t size() const
    {
        return number_of_vertexs;
    }

    size_t Get_max_number_vertexs()
    {
        return max_number_vertexs;
    }

    // �������� �������� ���� ������� (������������)
    Polyline operator+(const Polyline& rhs) const
    {
        Polyline result(size() + rhs.size());
        for (std::size_t i = 0; i < size(); ++i)
        {
            result.vertexs[i] = vertexs[i];
        }
        for (std::size_t i = size(); i < size() + rhs.size(); ++i)
        {
            result.vertexs[i] = rhs.vertexs[i - size()];
        }
        return result;
    }

    // �������� �������� ������� � ������� (���������� ������� � ����� �������)
    friend Polyline operator+(const Polyline& line, const Point<T>& vertex) {
        Polyline result(line);
        result.addVertex(vertex);
        return result;
    }

    // �������� �������� ������� � ������� (������� ������� � ������ �������)
    friend Polyline operator+(const Point<T>& vertex, const Polyline& line) {
        Polyline result(line.size() + 1);
        result[0] = vertex;
        for (std::size_t i = 0; i < line.size(); ++i) {
            result[i + 1] = line[i];
        }
        return result;
    }

    // ���������� ����������
    static double distance(const Point<T>& p1, const Point<T>& p2)
    {
        using std::sqrt;
        return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
    }

    // ���������� ���������� ����� ����� ������������ �������
    static double distance_complex(const std::complex<double>& p1, const std::complex<double>& p2)
    {
        using std::abs;
        return abs(p2 - p1);
    }

    T length() const
    {

        if constexpr (is_integral_v<T>)
        {
            int Length = 0;
            for (size_t i = 1; i < size(); ++i)
            {
                Length += distance(vertexs[i - 1], vertexs[i]);
            }
            return Length;
        }
        else if constexpr (is_floating_point_v<T>)
        {
            double Length = 0;
            for (size_t i = 1; i < size(); ++i)
            {
                Length += distance(vertexs[i - 1], vertexs[i]);
            }
            return Length;
        }
        else if constexpr (std::is_same_v<T, std::complex<double>>) 
        {
            std::complex<double> Length = 0.0;
            for (size_t i = 1; i < size(); ++i)
            {
                Length += distance_complex(vertexs[i - 1].x + vertexs[i - 1].y, vertexs[i].x + vertexs[i].y);
            }
            return Length;
        }
    }
};

template <typename T>
ostream& operator<<(ostream& stream, const Polyline<T>& line)
{
    for (size_t i = 0; i < line.size(); ++i)
    {
        stream << "Point: [" << i + 1 << "] = (" << line[i].x << ", " << line[i].y << ")\n";
    }
    return stream;
};

template <>
ostream& operator<<(ostream& stream, const Polyline<std::complex<double>>& line)
{
    for (size_t i = 0; i < line.size(); ++i)
    {
        stream << "Point: [" << i + 1 << "] = (" << line[i].x << ", " << line[i].y << ")\n";
    }
    return stream;
};