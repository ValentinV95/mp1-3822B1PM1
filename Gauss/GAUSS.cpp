#include <iostream>

using namespace std;

template<typename T>
class matrix {
private:
    T **arr;
    int n; //размерность
public:
    matrix(int _n) {
        n = _n;
        arr = new T *[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new T[n];
        }
    }

    T &operator()(int ind1, int ind2) {
        return arr[ind1][ind2];
    }

    matrix(const matrix<T> &A) {
        n = A.n;
        arr = new T *[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new T[n];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] = A.arr[i][j];
            }
        }
    }


    void set_matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
            }
        }
    };

    void get_matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j] << " ";
            }
            cout << "\n";
        }
    }
}

template<typename T>
class vec {
private:
    int n;
    T *arr;
public:
    vec(int _n) {
        n = _n;
        arr = new T[n];
        for (int i = 0; i < n; i++) {
            arr[i] = -2;
        }
    }

    T &operator[](int ind) {
        return arr[ind];
    }

    void set_vec(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }

    void get_vec(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            cout << "( " << arr[i] << " )\n";
        }
    }

    ~vec() {
        delete[] arr;
        n = 0;
    }
};


template<typename T>
bool was_using(int k, int n, vec<T> &U) {
    for (int i = 0; i < n; i++) {
        if (U[i] == k) {
            return true;
        }
    }
    return false;
}


template<typename T>
int search_max(int n, int ind, matrix<T> &A, vec<T> &U) {
    T max;
    int max_ind;
    for (int i = 0; i < n; i++) {
        if (!was_using(i, n, U)) {
            max = A(i, ind);
            max_ind = i;
        }
    }


    for (int i = 0; i < n; i++) {
        if (abs(max) <= abs(A(i, ind)) && !was_using(i, n, U)) {
            max = A(i, ind);
            max_ind = i;
        }
    }
    return max_ind;
}


template<typename T>
int search_max_for_result(int n, int ind, matrix<T> &A) {
    T max = A(0, ind);
    int max_ind = 0;
    for (int i = 0; i < n; i++) {
        if (abs(max) <= abs(A(i, ind))) {
            max = A(i, ind);
            max_ind = i;
        }
    }
    return max_ind;
}


template<typename T>
bool is_null(int n, int ind, matrix<T> &A) {
    T eps = 10e-16;
    for (int j = 0; j < n; j++) {
        if (abs(A(ind, j)) - T(eps) < 0)
            return false;
    }
    return true;
}


template<typename T>
void solver(int n) {
    T eps = 10e-16;
    matrix<T> A(n);
    vec<T> B(n);
    vec<T> used(n); //массив строк, которые уже использовались в i-ых столбцах
    cout << "Enter A:\n";
    A.set_matrix(n);
    cout << "Enter B:\n";
    B.set_vec(n);
    int ind_max; //индекс максимального
    T divid;

    for (int column = 0; column < n; column++) {
        ind_max = search_max(n, column, A, used);
        if (abs(A(ind_max, column)) - eps < 0) {
            used[column] = -1; //то есть все строки в этом столбце равны нулю (лин.зависимые есть)
            continue;
        }
        used[column] = ind_max;
        for (int i = 0; i < n; i++) {
            if (i == ind_max) {
                continue;
            }
            divid = A(i, column) / A(ind_max, column);
            for (int j = column; j < n; j++) {
                if (A(i, j) != 0) {
                    A(i, j) -= A(ind_max, j) * divid;
                }
            }
            B[i] -= B[ind_max] * divid;
        }

        cout << "\n";
        for (int i = 0; i < n; i++) {
            cout << "\n";
            for (int j = 0; j < n; j++) {
                cout << A(i, j) << " ";
            }
        }
    }

    cout << "\n\n\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A(i, j) << "\t";
        }
        cout << "\t" << " | " << B[i] << "\n";
    }


    if (!was_using(-1, n, used)) {  //если не было зависимых строк
        cout << "\n\n\n Result:\n";
        for (int column = 0; column < n; column++) {
            ind_max = search_max_for_result(n, column, A);
            B[ind_max] /= A(ind_max, column);
            cout << "x" << column + 1 << " = " << B[ind_max] << ";\n";
        }
    } else {                               //если есть зависимые строки
        cout << "\n\n\n Result:\n";
        for (int column = 0; column < n; column++) {
            if (used[column] != -1) {
                ind_max = search_max_for_result(n, column, A);
                divid = A(ind_max, column);
                B[ind_max] /= divid;
                for (int j = 0; j < n; j++) { //привожу к единичной левую часть
                    A(ind_max, j) /= divid;
                }
            }
        }
        int c = 0;
        for (int i = 0;
             i < n; i++) { //счетчик линейно зависимых (впоследствии нулевых) строк (количество параметров)
            if (used[i] == -1) {
                c++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (is_null(n, i, A)) { // проверка на нулевую строку
                continue;
            }
            for (int j = 0; j < n - c; j++) {
                if (A(i, j) == 1) {
                    cout << "x" << j + 1 << " = " << B[i];
                    for (int k = 0; k < c; k++) {
                        cout << " - (" << A(i, n - k - 1) << ")t" << k + 1 << "\n";
                    }
                }
            }
        }
    }
}


int main() {
    int choice;
    int n;
    cout << "Enter typename:\n 1. double;\n 2. float;\n 3. int\n";
    cin >> choice;
    cout << "Enter size: ";
    cin >> n;
    switch (choice) {
        case 1:
            solver<double>(n);
            break;
        case 2:
            solver<float>(n);
            break;
        case 3:
            solver<int>(n);
            break;
        default:
            solver<double>(n);
            break;
    }
    return 0;
}
