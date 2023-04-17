#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class InstituteEmployee {
private:
    string last_name, first_name, middle_name, department_name, position;
    int birth_year, work_experience, salary, tbl_nomer;
    static int count;
public:
    InstituteEmployee() {
        tbl_nomer = ++count;
    }
    InstituteEmployee(string l_name, string f_name, string m_name, string dep_name, int b_year, int w_exp, string pos, int salary) :
        last_name(l_name), first_name(f_name), middle_name(m_name), department_name(dep_name),
        birth_year(b_year), work_experience(w_exp), position(pos), salary(salary), tbl_nomer(++count) {}

    string getLast_name() const {
        return last_name;
    }
    void setLast_name(string last_name) {
        this->last_name = last_name;
    }
    string getFirst_name() const {
        return first_name;
    }
    void setFirst_name(string first_name) {
        this->first_name = first_name;
    }
    string getMiddle_name() const {
        return middle_name;
    }
    void setMiddle_name(string middle_name) {
        this->middle_name = middle_name;
    }
    string getDepartment_name() const {
        return department_name;
    }
    void setDepartment_name(string department_name) {
        this->department_name = department_name;
    }
    int getBirth_year() const {
        return birth_year;
    }
    void setBirth_year(int birth_year) {
        this->birth_year = birth_year;
    }
    int getWork_experience() const {
        return work_experience;
    }
    void setWork_experience(int work_experience) {
        this->work_experience = work_experience;
    }
    string getPosition() const {
        return position;
    }
    void setPosition(string position) {
        this->position = position;
    }
    int getSalary() const {
        return salary;
    }
    void setSalary(int salary) {
        this->salary = salary;
    }
    int getTbl_nomer() const {
        return tbl_nomer;
    }
};

int InstituteEmployee::count = 0;

void showEmployees(vector<InstituteEmployee>& employees) {
    cout << "Список сотрудников института:\n";
    for (InstituteEmployee employee : employees) {
        cout << employee.getTbl_nomer() << " " << employee.getLast_name() << " " << employee.getFirst_name() << " " << employee.getMiddle_name();
        cout << " " << employee.getDepartment_name() << " " << employee.getBirth_year() << " " << employee.getWork_experience();
        cout << " " << employee.getPosition() << " " << employee.getSalary() << endl;
    }
}

void showRetiredEmployees(vector<InstituteEmployee>& employees) {
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int currentYear = 1900 + timePtr->tm_year;
    cout << "Список сотрудников пенсионного возраста на " << currentYear << " год:\n";
    for (InstituteEmployee employee : employees) {
        if ((currentYear - employee.getBirth_year() >= 55) && (currentYear - employee.getBirth_year() <= 120)) {
            cout << employee.getLast_name() << " " << employee.getFirst_name() << " " << employee.getMiddle_name() << " ";
            cout << employee.getDepartment_name() << " " << employee.getWork_experience() << endl;
        }
    }
}

void showDepartmentExperience(vector<InstituteEmployee>& employees) {
    string department;
    cout << "Введите название отдела: ";
    cin >> department;
    cout << endl << "Средний стаж сотрудников отдела " << department << ": ";
    int sum = 0, count = 0;
    for (InstituteEmployee employee : employees) {
        if (employee.getDepartment_name() == department) {
            sum += employee.getWork_experience();
            count++;
        }
    }
    if (count == 0) {
        cout << "Отдел не найден.";
    }
    else {
        cout << (double)sum / count << " лет. \n";
    }
}

void addEmployee(vector<InstituteEmployee>& employees) {
    string l_name, f_name, m_name, dep_name, pos;
    int b_year, w_exp, salary;
    cout << "Введите данные сотрудника:\n";
    cout << "Фамилия: \n";
    cin >> l_name;
    cout << "\nИмя: ";
    cin >> f_name;
    cout << "\nОтчество: ";
    cin >> m_name;
    cout << "\nНазвание отдела: ";
    cin >> dep_name;
    cout << "\nГод рождения: ";
    cin >> b_year;
    cout << "\nСтаж работы: ";
    cin >> w_exp;
    cout << "\nДолжность: ";
    cin >> pos;
    cout << "\nОклад: ";
    cin >> salary;
    InstituteEmployee employee(l_name, f_name, m_name, dep_name, b_year, w_exp, pos, salary);
    employees.push_back(employee);
    cout << endl << "Новый сотрудник успешно добавлен!" << endl;
}

void deleteEmployee(vector<InstituteEmployee>& employees) {
    int tbl_nomer;
    bool found = false;
    cout << "Введите табельный номер удаляемого сотрудника: ";
    cin >> tbl_nomer;

    for (vector<InstituteEmployee>::iterator it = employees.begin(); it != employees.end(); ) {
        if (it->getTbl_nomer() == tbl_nomer) {
            it = employees.erase(it);
            found = true;
        }
        else {
            ++it;
        }
    }
    if (found) {
        cout << endl << "Сотрудник успешно удален!" << endl;
    }
    else {
        cout << endl << "Сотрудник не найден." << endl;
    }
}

void sortEmployees(vector<InstituteEmployee>& employees) {
    cout << "Выберите поле для сортировки:\n";
    cout << "\n1 - Фамилия";
    cout << "\n2 - Год рождения";
    cout << "\n3 - Стаж работы";
    cout << "\n4 - Оклад";
    cout << "\nПоле: ";
    int field;
    cin >> field;
    switch (field) {
    case 1:
        sort(employees.begin(), employees.end(), [](InstituteEmployee& e1, InstituteEmployee& e2) {return e1.getLast_name() < e2.getLast_name(); });
        cout << "\nСортировка по фамилии выполнена!\n";
        break;
    case 2:
        sort(employees.begin(), employees.end(), [](InstituteEmployee& e1, InstituteEmployee& e2) {return e1.getBirth_year() < e2.getBirth_year(); });
        cout << "\nСортировка по году рождения выполнена!\n";
        break;
    case 3:
        sort(employees.begin(), employees.end(), [](InstituteEmployee& e1, InstituteEmployee& e2) {return e1.getWork_experience() < e2.getWork_experience(); });
        cout << "\nСортировка по стажу работы выполнена!\n";
        break;
    case 4:
        sort(employees.begin(), employees.end(), [](InstituteEmployee& e1, InstituteEmployee& e2) {return e1.getSalary() < e2.getSalary(); });
        cout << "\nСортировка по окладу выполнена!\n";
        break;
    default:
        cout << "\nНекорректный ввод.\n";
        break;
    }
}

void saveToFile(vector<InstituteEmployee>& employees) {
    ofstream fout("employees.txt");
    for (InstituteEmployee employee : employees) {
        fout << employee.getLast_name() << ";" << employee.getFirst_name() << ";" << employee.getMiddle_name() << ";" << employee.getDepartment_name() << ";"
            << employee.getBirth_year() << ";" << employee.getWork_experience() << ";" << employee.getPosition() << ";" << employee.getSalary() << endl;
    }
    fout.close();
    cout << endl << "Список сотрудников успешно сохранен в файл!\n";
}

void readFromFile(vector<InstituteEmployee>& employees) {
    employees.clear();
    ifstream fin("employees.txt");
    if (!fin.is_open()) {
        cout << "Файл не найден.\n";
        return;
    }
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string l_name, f_name, m_name, dep_name, pos;
        int b_year, w_exp, salary;
        getline(ss, l_name, ';');
        getline(ss, f_name, ';');
        getline(ss, m_name, ';');
        getline(ss, dep_name, ';');
        ss >> b_year;
        ss.ignore();
        ss >> w_exp;
        ss.ignore();
        getline(ss, pos, ';');
        ss >> salary;
        InstituteEmployee employee(l_name, f_name, m_name, dep_name, b_year, w_exp, pos, salary);
        employees.push_back(employee);
    }
    fin.close();
    cout << endl << "Список сотрудников успешно загружен из файла!\n";
}

void showMenu() {
    cout << "1. Показать список сотрудников\n";
    cout << "2. Добавить нового сотрудника\n";
    cout << "3. Удалить сотрудника\n";
    cout << "4. Отобразить список сотрудников пенсионного возраста\n";
    cout << "5. Отобразить средний стаж работы сотрудников в заданном отделе\n";
    cout << "6. Отсортировать список сотрудников\n";
    cout << "7. Сохранить список сотрудников в файл\n";
    cout << "8. Загрузить список сотрудников из файла\n";
    cout << "0. Выйти\n";
    cout << "\nВыберите действие: ";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    vector<InstituteEmployee> employees;
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
        case 0:
            break;
        case 1:
            showEmployees(employees);
            break;
        case 2:
            addEmployee(employees);
            break;
        case 3:
            deleteEmployee(employees);
            break;
        case 4:
            showRetiredEmployees(employees);
            break;
        case 5:
            showDepartmentExperience(employees);
            break;
        case 6:
            sortEmployees(employees);
            break;
        case 7:
            saveToFile(employees);
            break;
        case 8:
            readFromFile(employees);
            break;
        default:
            cout << "Некорректный ввод.\n";
            break;
        }
        cout << endl;
    } while (choice != 0);
    return 0;
}