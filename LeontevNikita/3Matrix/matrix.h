#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void sgndprint(size_t first, size_t sgn, ostream& output = cout);

template<typename T>
class Vector {
public:
	Vector(size_t n) {
		if (n != 0) {
			main = new T[n];
			coords = n;
		}
		else {
			main = nullptr;
			coords = 0;
		}
	}
	~Vector() {
		delete[] main;
	}
	Vector(const Vector &c) {
		if (c.coords != 0) {
			main = new T[c.coords];
			for (size_t i = 0; i < c.coords; i++) {
				main[i] = c.main[i];
			}
			coords = c.coords;
		}
	}
	T &operator[](size_t i) {
		if (i < coords) {
			return main[i];
		}
	}
	void show(ostream& output = cout) {
		output << '(';
		for (size_t i = 0; i < coords-1; i++) {
			output << main[i] << ' ';
		}
		output << main[coords - 1] << ")\n";
		output.flush();
	}
private:
	T *main;
	size_t coords;
};

template<typename T>
class Matrix {
public:
	Matrix(size_t w, size_t h, size_t right_part = 0, bool one = 0); // w includes right_part
	Matrix(const T& num);
	Matrix(const Matrix &c);
	~Matrix() {
		delete[] isready;
		delete[] main;
		delete[] solved;
	}
	bool swap(size_t l1, size_t l2); // Swap lines, starts from 1
	void addline(T *arr); // Adds [width] array
	void show(ostream& output = cout);
	void startsolve(bool jord = 1, bool quiet = 0, ostream& output = cout);
	bool checkzeroerror(size_t rpart); // Is there (0 0 ... 0 |	1)?
	bool summarize(size_t from, size_t to, T coef); // Summarize lines, starts from 1
	bool division(size_t to, T coef); // Divide line by coef, line starts from 1
	Matrix<T> transposed();
	Vector<T> getvec(size_t num); // starts from 1
	void killholds() {
		holds = 1;
	}
	T Determinator();
	bool is_solved() {
		return issolved;
	}
	size_t get_width() {
		return width - right_part;
	}
	size_t get_height() {
		return lines;
	}
	size_t get_rightpart() {
		return right_part;
	}
	//ops
	Matrix<T> operator+(const Matrix &sec);
	Matrix<T>& operator=(const Matrix<T> &sec);
	Matrix<T> operator*(const T& coef);
	Matrix<T> operator*(Matrix<T> &sec); // n^3
	Matrix<T> operator/(Matrix<T> &sec); // m1 * (m2)^-1 actually
	vector<T>& operator[](size_t index);
private:
	void showfx(size_t rpart, ostream& output);
	int searchforusableline(size_t num);
	size_t funcline(size_t w);
	bool full;
	bool *solved;
	bool *isready;
	bool issolved;
	bool autozero;
	vector<T> *main;
	size_t lines;
	size_t width;
	size_t height;
	size_t right_part;
	T holds;
};

template<typename T>
ostream& operator<<(ostream &output, Matrix<T> &m) {
	m.show(output);
	return output;
}

template<typename T>
inline Matrix<T> operator/(T frst, Matrix<T> sec) {
	return (Matrix<T>)frst / sec;
}

template<typename T>
size_t Matrix<T>::funcline(size_t w) {
	size_t maxline = height;
	for (size_t i = 0; i < height; i++) {
		if (isready[i] == 0) {
			maxline = i;
			break;
		}
	}
	for (size_t i = maxline; i < height; i++) {
		if (main[i][w] > main[maxline][w] && isready[i] == 0) {
			maxline = i;
		}
	}
	return maxline;
}

template<typename T>
Matrix<T>::Matrix(size_t w, size_t h, size_t right_part, bool one) {
	full = 0;
	lines = 0;
	autozero = 0;
	holds = 1;
	issolved = 0;
	if (w == 0 || h == 0) {
		w = 1; h = 1;
	}
	width = w;
	height = h;
	if (right_part < width) {
		this->right_part = right_part;
	}
	else {
		right_part = 0;
	}
	if (right_part == 0) {
		width++;
		this->right_part = 1;
		autozero = 1;
	}
	solved = new bool[this->right_part];
	main = new vector<T>[height];
	isready = new bool[height];
	if (one) {
		T *line = new T[width];
		for (size_t j = 0; j < width; j++) {
			line[j] = 0;
		}
		for (size_t i = 0; i < height; i++) {
			if (i > 0) {
				line[i - 1] = 0;
			}
			if (i < width - right_part) {
				line[i] = 1;
			}
			addline(line);
		}
		delete[] line;
	}
}

template<typename T>
Matrix<T>::Matrix(const T& num) {
	Matrix<T> tocopy(1, 1, 0, 1);
	solved = nullptr;
	main = nullptr;
	isready = nullptr;
	*this = tocopy * num;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &c) {
	full = 0;
	lines = 0;
	holds = 1;
	width = c.width;
	height = c.lines;
	right_part = c.right_part;
	autozero = c.autozero;
	//holds = c.holds;
	issolved = c.issolved;
	solved = new bool[right_part];
	main = new vector<T>[height];
	isready = new bool[height];
	for (size_t i = 0; i < right_part; i++) {
		solved[i] = c.solved[i];
	}
	for (size_t i = 0; i < height; i++) {
		addline(&c.main[i][0]);
		isready[i] = c.isready[i];
	}
}

template<typename T>
bool Matrix<T>::swap(size_t l1, size_t l2) {
	T buf;
	if (l1 == l2) {
		return 0;
	}
	if (l1 >= lines || l2 >= lines) {
		return 1;
	}
	for (size_t j = 0; j < width; j++) {
		buf = main[l1][j];
		main[l1][j] = main[l2][j];
		main[l2][j] = buf;
	}
	holds *= -1;
	return 0;
}

template<typename T>
T Matrix<T>::Determinator() {
	if (width - right_part != height || !issolved) {
		return 0;
	}
	for (size_t i = 0; i < width - right_part; i++) {
		if (searchforusableline(i) == -1) {
			return 0;
		}
	}
	return holds;
}

template<typename T>
void Matrix<T>::addline(T *arr) {
	if (full) {
		return;
	}
	size_t newwidth = autozero ? width - 1 : width;
	for (size_t i = 0; i < newwidth; i++) {
		main[lines].push_back(arr[i]);
	}
	if (autozero) {
		main[lines].push_back(0);
	}
	lines++;
	if (lines == height) {
		full = 1;
	}
}

template<typename T>
void Matrix<T>::show(ostream& output) {
	size_t i;
	for (i = 0; i < lines; i++) {
		output << "(";
		for (size_t j = 0; j < width; j++) {
			T elem = main[i][j];
			if (elem == 0) {
				output << "0";
			}
			else {
				output << elem;
			}
			if (j == width - right_part - 1) {
				output << " |";
			}
			if (j < width - 1) {
				output << " ";
			}
		}
		output << ")\n";
	}
	while (i < height) {
		output << "(...)\n";
		i++;
	}
	output.flush();
}

template<typename T>
int Matrix<T>::searchforusableline(size_t col) {
	size_t i;
	bool bad;
	if (col > width - right_part) {
		return -1;
	}
	for (i = 0; i < height; i++) {
		bad = 0;
		if (main[i][col] != 0) {
			for (size_t j = 0; j < col; j++) {
				if (main[i][j] != 0) {
					bad = 1;
					break;
				}
			}
			if (!bad) {
				return i;
			}
		}
	}
	return -1;
}

template<typename T>
void Matrix<T>::startsolve(bool jord, bool quiet, ostream& output) {
	bool errcheck;
	if (!full) {
		return;
	}
	for (size_t i = 0; i < height; i++) {
		isready[i] = 0;
	}
	size_t check;
	for (size_t p = 0; p < width - right_part; p++) {
		check = funcline(p);
		for (size_t q = 0; q < height; q++) {
			T elem = main[q][p];
			if (!isready[q] && (elem != 0) && (q == check)) {
				errcheck = division(q + 1, elem);
				holds *= elem;
				for (size_t t = q*(!jord); t < height; t++) {
					if (t != q && main[t][p] != 0) {
						T coef1 = -main[t][p];
						errcheck = errcheck || summarize(q + 1, t + 1, coef1);
					}
				}
				//show(output); // debug
				isready[q] = 1;
				if (errcheck) {
					output << "Bad error!\n";
					return;
				}
			}
		}
	}
	int tline;
	for (size_t i = 0; i < width - right_part; i++) {
		tline = searchforusableline(i);
		if (tline >= 0) {
			swap(tline, i);
		}
	}
	if (!quiet) {
		show(output);
	}
	issolved = 1;
	for (size_t i = 0; i < right_part; i++) {
		solved[i] = !checkzeroerror(i + 1);
		if (solved[i] == 0) {
			issolved = 0;
		}
		if (!quiet) {
			showfx(i + 1, output);
		}
	}
}

template<typename T>
bool Matrix<T>::checkzeroerror(size_t rpart) {
	bool good; // is line 0 0 0...
	if (rpart > right_part) {
		return 1;
	}
	for (size_t i = 0; i < height; i++) {
		good = 1;
		for (size_t j = 0; j < width - right_part; j++) {
			if (main[i][j] != 0) {
				good = 0;
				break;
			}
		}
		if (good && (main[i][width - right_part + rpart - 1] != 0)) {
			return 1;
		}
	}
	return 0;
}

template<typename T>
bool Matrix<T>::division(size_t to, T coef) {
	to = to - 1;
	if (to >= lines) {
		return 1;
	}
	if (coef == 1) {
		return 0;
	}
	if (coef != 0) {
		for (size_t i = 0; i < width; i++) {
			main[to][i] /= coef;
		}
	}
	else {
		return 1;
	}
	return 0;
}

template<typename T>
bool Matrix<T>::summarize(size_t from, size_t to, T coef) {
	from = from - 1;
	to = to - 1;
	if (coef == 0) {
		return 0;
	}
	if (from >= lines || to >= lines) {
		return 1;
	}
	for (size_t i = 0; i < width; i++) {
		main[to][i] += main[from][i] * coef;
	}
	return 0;
}

template<typename T>
void Matrix<T>::showfx(size_t rpart, ostream& output) {
	//return;
	bool first;
	bool empty;
	size_t xl;
	output << "--- #" << rpart << " ---\n";
	if (!solved[rpart - 1]) {
		output << "Not solved.\n";
		return;
	}
	for (size_t i = 0; i < width - right_part; i++) {
		empty = 1;
		first = 1;
		xl = searchforusableline(i);
		output << "x" << i + 1 << " = ";
		if (xl != -1) {
			for (size_t j = i + 1; j < width; j++) {
				bool sgn;
				if (main[xl][j] == 0 || ((j >= width - right_part) && j != width - right_part + rpart - 1)) {
					continue;
				}
				if (empty) {
					empty = 0;
				}
				sgn = main[xl][j] > 0 ? 1 : 0;
				if (j == width - right_part + rpart - 1) { // our rpart
					sgndprint(first, sgn, output);
					output << (main[xl][j] * (2 * sgn - 1));
				}
				else {
					sgndprint(first, !sgn, output);
					output << (main[xl][j] * (2 * sgn - 1)) << "x" << j + 1;
				}
				first = 0;
			}
		}
		else {
			output << "const";
			empty = 0;
		}
		if (empty) {
			output << '0';
		}
		output << '\n';
	}
	output << "Determinator: " << Determinator() << '\n';
	output.flush();
}

void sgndprint(size_t first, size_t sgn, ostream& output) {
	if (first && !sgn) {
		output << "-";
	}
	else if (!first && sgn) {
		output << " + ";
	}
	else if (!first && !sgn) {
		output << " - ";
	}
}

template<typename T>
Matrix<T> Matrix<T>::transposed() {
	Matrix<T> res(lines, width-right_part);
	T *line = new T[res.width];
	for (size_t i = 0; i < res.height; i++) {
		for (size_t j = 0; j < res.width-1; j++) {
			line[j] = main[j][i];
		}
		res.addline(line);
	}
	delete[] line;
	return res;
}

template<typename T>
Vector<T> Matrix<T>::getvec(size_t num) {
	size_t count = 0;
	for (size_t i = 0; i < height; i++) {
		count += isready[i];
	}
	if (count != width - right_part || num == 0 || num > right_part) {
		return Vector<T>(1);
	}
	Vector<T> res(count);
	for (size_t i = 0; i < count; i++) {
		res[i] = main[i][count + num - 1];
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &sec) {
	if (width - right_part != sec.width - sec.right_part || lines != sec.lines) {
		return *this;
	}
	Matrix<T> res = right_part >= sec.right_part ? *this : sec;
	const Matrix<T> &anoth = right_part >= sec.right_part ? sec : *this;
	for (size_t i = 0; i < res.right_part; i++) {
		res.solved[i] = 0;
	}
	for (size_t i = 0; i < res.height; i++) {
		res.isready[i] = 0;
		for (size_t j = 0; j < anoth.width; j++) {
			res.main[i][j] += anoth.main[i][j];
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& coef) {
	Matrix<T> res(0, 0);
	res = *this;
	for (size_t i = 0; i < res.height; i++) {
		for (size_t j = 0; j < res.width; j++) {
			res.main[i][j] *= coef;
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &sec) {
	Matrix<T> *anoth; // this
	Matrix<T> thr(sec.width - sec.right_part, sec.width - sec.right_part, 0, 1); // special case E matrix
	anoth = this;
	if ((width - right_part) == 1 && height == 1) { // special case if 1x1 matrix
		thr = thr * main[0][0];
		anoth = &thr;
	}
	if (anoth->width-anoth->right_part != sec.lines) {
		return *this;
	}
	size_t cols = sec.width - sec.right_part;
	Matrix<T> res(cols, anoth->height);
	res.holds = anoth->holds * sec.holds;
	T *line = new T[cols];
	T sum;
	for (size_t i = 0; i < anoth->height; i++) {
		for (size_t j = 0; j < cols; j++) {
			sum = 0;
			for (size_t k = 0; k < sec.lines; k++) {
				sum += anoth->main[i][k] * sec.main[k][j];
			}
			line[j] = sum;
		}
		res.addline(line);
	}
	delete[] line;
	return res;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &sec) {
	if (solved != nullptr) {
		delete[] solved;
	}
	if (main != nullptr) {
		delete[] main;
	}
	if (isready != nullptr) {
		delete[] isready;
	}
	width = sec.width;
	height = sec.lines;
	right_part = sec.right_part;
	autozero = sec.autozero;
	holds = sec.holds;
	full = 0;
	lines = 0;
	issolved = sec.issolved;
	solved = new bool[right_part];
	main = new vector<T>[height];
	isready = new bool[height];
	for (size_t i = 0; i < right_part; i++) {
		solved[i] = sec.solved[i];
	}
	for (size_t i = 0; i < height; i++) {
		addline(&sec.main[i][0]);
	}
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(Matrix<T> &sec) {
	if (sec.width - sec.right_part != sec.lines) {
		return *this;
	}
	Matrix<T> resolv(2*sec.lines, sec.lines, sec.lines);
	Matrix<T> res(sec.lines, sec.lines, 0);
	T *line = new T[resolv.width];
	for (size_t i = 0; i < resolv.height; i++) {
		for (size_t j = 0; j < sec.lines; j++) {
			line[j] = sec.main[i][j];
		}
		for (size_t j = sec.lines; j < resolv.width; j++) {
			line[j] = j == (i + sec.lines) ? 1 : 0;
		}
		resolv.addline(line);
	}
	resolv.startsolve(1, 1);
	if (resolv.Determinator() != 0) {
		for (size_t i = 0; i < sec.lines; i++) {
			for (size_t j = 0; j < sec.lines; j++) {
				line[j] = resolv.main[i][j + sec.lines];
			}
			res.addline(line);
		}
		delete[] line;
		return *this * res;
	}
	else {
		delete[] line;
		return *this;
	}
}

template<typename T>
vector<T>& Matrix<T>::operator[](size_t index) {
	if (index > height) {
		return main[height-1];
	}
	return main[index];
}