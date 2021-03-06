#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double pow(double a);

struct Point
{
	double x;
	double y;

	friend double sqLength(Point& a, Point& b) {
		return (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
	}

	friend double length(Point& a, Point& b) {
		return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
	}
};

class Polygon
{
public:
	Polygon();
	Polygon(vector<Point> points);
	void ShowCoordinates();
	double perimeter();
	virtual const char* typeOfFigure();
	virtual double Square();
	~Polygon();
	Polygon& operator=(const Polygon& old);


protected:
	vector<Point> points;
};

Polygon::Polygon()
{
}

Polygon::Polygon(vector<Point> points) {
	for (size_t i = 0; i < points.size(); ++i) {
		this->points.push_back(points[i]);
	}
}

void Polygon::ShowCoordinates() {
	for (size_t i = 0; i < points.size(); ++i) {
		cout << "x:\t" <<points[i].x << "\ty:\t" << points[i].y << endl;
	}
}

double Polygon::perimeter() {
	int k = 0;
	Point prev = points.back();
	double per = 0;
	for (size_t i = 0; i < this->points.size(); ++i) {
		per += length(prev, points[i]);
		prev = points[i];
	}
	return per;
}

const char* Polygon::typeOfFigure() {
	return "Polygon\0";
}

double Polygon::Square() {
	Point prev = this->points.back();
	double square = 0;
	for (size_t i = 0; i < this->points.size(); ++i) {
		square += (prev.x + this->points[i].x)*(prev.y - this->points[i].y);
		prev = this->points[i];
	}
	return (abs(square) / 2);
}

Polygon::~Polygon()
{
}

Polygon& Polygon::operator=(const Polygon& old) {
	this->points = old.points;
	return *this;
}

class Triangle : public Polygon
{
public:
	Triangle();
	Triangle(vector<Point> points);
	~Triangle();
	double square();
	double lengthMedian(int countPoint);
	Point& crossMedian();
	double lengthBiss(int countPoint);
	Point& crossBiss();
	double lengthHigth(int countPoint);
	const char* typeOfFigure();	

private:
	vector<double> vecDbLength;
};

Triangle::Triangle()
{
}

Triangle::Triangle(vector<Point> points) {
	if (points.size() == 3) {
		this->points = points;
		Point prev = points.back();
		for (size_t i = 0; i < this->points.size(); i++) {
			vecDbLength.push_back(length(prev, points[i]));
			prev = points[i];
		}
	}
}

Triangle::~Triangle()
{
}

double Triangle::square() {
	return 0.5*length(points[0], points[1])*lengthHigth(2);
}

double Triangle::lengthMedian(int countPoint) {
	if (countPoint > 0 && countPoint < this->points.size()) {
		int i1 = countPoint%this->points.size();
		int i2 = (countPoint + 1) % this->points.size();
		int i3 = (countPoint + 2) % this->points.size();

		return 0.5*sqrt(2 * pow(vecDbLength[i1]) + 2 * pow(vecDbLength[i2]) - pow(vecDbLength[i3]));
	}
	else {
		cout << "Wrong number of point!" << endl;
		return -1;
	}
}

Point& Triangle::crossMedian() {
	Point crsMed = { 0,0 };
	for (size_t i = 0; i < points.size(); ++i) {
		crsMed.x += points[i].x;
		crsMed.y += points[i].y;
	}
	crsMed.x /= 3;
	crsMed.y /= 3;
	return crsMed;
}

double Triangle::lengthBiss(int countPoint) {
	if (countPoint > 0 && countPoint < this->points.size()) {
		int i1 = countPoint%this->points.size();
		int i2 = (countPoint + 1) % this->points.size();
		int i3 = (countPoint + 2) % this->points.size();

		return sqrt(vecDbLength[i1] * vecDbLength[i2] * (vecDbLength[i1] + vecDbLength[i2] + vecDbLength[i3])
													  * (vecDbLength[i1] + vecDbLength[i2] - vecDbLength[i3]))
													  / (vecDbLength[i1] + vecDbLength[i2]);
	}
	else {
		cout << "Wrong number of point!" << endl;
		return -1;
	}
}

Point& Triangle::crossBiss() {
	Point crsBiss = { 0,0 };
		
	crsBiss.x = (vecDbLength[0] * points[2].x + vecDbLength[1] * points[1].x + vecDbLength[2] * points[0].x) / (vecDbLength[0] + vecDbLength[1] + vecDbLength[2]);
	crsBiss.y = (vecDbLength[0] * points[2].y + vecDbLength[1] * points[1].y + vecDbLength[2] * points[0].y) / (vecDbLength[0] + vecDbLength[1] + vecDbLength[2]);

	return crsBiss;
}

double Triangle::lengthHigth(int countPoint) {
	if (countPoint > 0 && countPoint < this->points.size()) {
		int i1 = countPoint	% this->points.size();
		int i2 = (countPoint + 1) % this->points.size();
		int i3 = (countPoint + 2) % this->points.size();

		double hPer = this->perimeter() / 2;

		return 2 * sqrt(hPer*(hPer - vecDbLength[i1]) * (hPer - vecDbLength[i2]) * (hPer - vecDbLength[i3])) / vecDbLength[i3];
	}
	else {
		cout << "Wrong number of point!" << endl;
		return -1;
	}
}

const char* typeOfFigure() {
	return "Triangle\0";
}

class Rectangle : public Polygon
{
public:
	Rectangle();
	~Rectangle();
	Rectangle(vector<Point> points);
	double diagSquare();
	double Square();
	const char* typeOfFigure();

private:
	vector<double> vecDbLength;
};

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

Rectangle::Rectangle(vector<Point> points) {
	if (points.size() == 4) {
		Point prev = points.back();
		this->points = points;

		//проверка углов и записывание длин сторон в вектор
		for (size_t i = 0; i < points.size(); i++) {
			if (((prev.x == points[i].x) && (points[i].y == points[i+1].y)) || ((prev.y == points[i].y) && (points[i].x == points[i+1].x))) {
				vecDbLength.push_back(length(prev, points[i]));
				prev = points[i];
				if (i == points.size() - 2) {
					vecDbLength.push_back(length(points[i], points[i + 1]));
					break;
				}
			}

			else {
				vecDbLength.clear();
				cout << "This is not square!\n";
				break;
			}
		}
	}
	else {
		cout << "Wrong points!" << endl;
		//throw
	}
}

double Rectangle::diagSquare() {
	return sqrt(pow(vecDbLength[0]) + pow(vecDbLength[1]));
}

double Rectangle::Square() {
	return vecDbLength[0] * vecDbLength[1];
}

const char* typeOfFigure() {
	return "Rectangle\0";
}

double pow(double num) {
	return num*num;
}

int main() {
	Point a = { 1,2 };
	Point b = { 3,4 };
	Point c = { 5,2 };

	vector<Point> points = { a, b, c };

	Point a1 = { 1,1 };
	Point a2 = { 1,2 };
	Point a3 = { 3,2 };
	Point a4 = { 3,1 };

	vector<Point> squarePoints = { a1,a2,a3,a4 };

	Triangle trg(points);
	Rectangle sqr(squarePoints);

	Polygon* objs[2];

	objs[0] = &trg;
	objs[1] = &sqr;


	cout << "Triangle median: " << trg.lengthMedian(2) << endl;
	cout << "Triangle biss: " << trg.lengthBiss(0) << endl;
	cout << "Triangle hight: " << trg.lengthHigth(1) << endl;
	cout << "Triange crossing med point: " << trg.crossMedian().x << ' ' << trg.crossMedian().y << endl;
	cout << "Triangle cross biss point: " << trg.crossBiss().x << ' ' << trg.crossBiss().y << endl;


	cout << "Square diagonale: " << sqr.diagSquare() << endl;
	cout << "Square of square: " << sqr.Square() << endl;

	char k;
	cin >> k;
	return 0;
}
