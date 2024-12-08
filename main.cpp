#include "Polyline.h"


void create_a_polyline(Polyline<double>& Polygon, int N) {
    double angleStep = 2 * 3.14 / N; //угол между соседними вершинами
    for (int i = 0; i < N; ++i) {
        double angle = i * angleStep;
        Polygon[i] = { cos(angle), sin(angle) };
    }
    cout << Polygon << endl;
}


int main()
{
    size_t numPoints;
    int m1 = 0, m2 = 0;
    cout << "Enter the number of points for the first polyline(int): ";
    cin >> numPoints;
    cout << "Enter the left border: ";
    cin >> m1;
    cout << "Enter the right border: ";
    cin >> m2;

    Polyline<int> line1(numPoints, m1, m2);
    cout << line1;
    cout << "\nThe length of the first polyline(int): " << line1.length() << std::endl;
    cout << std::endl;

    cout << "Enter the number of points for the first polyline(int): ";
    cin >> numPoints;
    cout << "Enter the left border: ";
    cin >> m1;
    cout << "Enter the right border: ";
    cin >> m2;

    Polyline<int> line2(numPoints, m1, m2);
    cout << line2;
    cout << "\nThe length of the second polyline(int): " << line2.length() << std::endl;
    cout << std::endl;

    Polyline<int> line(line1.size() + line2.size(),m1,m2);
    line = line1 + line2;
    cout << line;
    cout << "\nThe sum of the length of the polyline(int): " << line.length() << std::endl;
    cout << std::endl;

    Point<int> vertex(11, 11);

    // ƒобавление вершины в конец ломаной
    Polyline<int> extendedLine = line + vertex;
    cout << "The vertex is added to the end:" << endl;
    cout << extendedLine << endl;

    // ¬ставка вершины в начало другой ломаной линии
    Polyline<int> insertedLine = vertex + line;
    cout << "The vertex at the beginning:" << endl;
    cout << insertedLine << endl;

    //дл€ комплексных
    std::complex<double> x1(1.0f, 2.0f);
    std::complex<double> y1(3.0f, 4.0f);
    std::complex<double> x2(7.0f, 6.0f);
    std::complex<double> y2(3.0f, 4.0f);
    cout << "-----------------------------------" << endl;
    Polyline<std::complex<double>> complex;
    Point<std::complex<double>>xy1(x1, y1);
    Point<std::complex<double>>xy2(x2, y2);
    complex = complex + xy1;
    complex = complex + xy2;
    cout << complex << endl;
    cout << "\nThe length of the second polyline(int): " << complex.length() << std::endl;
    cout << "-----------------------------------" << endl;

    // —оздание правильного N-угольника 
    int N = 5;
    Polyline<double> Polygon(N);
    create_a_polyline(Polygon, N);
    cout << "The length of the correct " << N << "-square: " << Polygon.length() << endl;

    return 0;
}
