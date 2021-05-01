#include <iostream>
#include <vector>
#include "School.h"

using namespace std;

void fill_students(vector<int> &st_marks, const vector<string> &name_students, vector<Student> &students, int n);

int main() {
    vector<int> marks = {3, 4, 5, 5};
    vector<int> st_marks = {0, 0, 0, 0};
    vector<string> name_students = {"Семён", "Егор", "Роман", "Олеся"};
    vector<string> name_teachers = {"Роман Лось", "Юрий Клевчихин", "Евгений Ефремов",
                                    "Светлана Остроухова"};
    vector<string> name_lessons = {"ООП-шиза", "мат анализ", "мат логика",
                                   "структуры и алгоритмы данных"};
    vector<Student> students = {};
    vector<Teacher> teachers = {};
    vector<Parent> parents = {};
    fill_students(st_marks, name_students, students, 4);

    // добавляем 4 преподавателей
    for (int i = 0; i < 4; ++i) {
        Teacher t(name_teachers[i]);
        teachers.push_back(t);
    }

    // добавляем родителя
    Parent p("Ваша мама", students, PARENT);
    p.sayAll();
    p.setThere(false);
    parents.push_back(p);

    vector<string> name_students2 = {"Леонид", "Анастасия", "Вика", "Данил"};
    vector<Student> students2 = {};
    fill_students(st_marks, name_students2, students2, 4);

    // добавляем родителя
    Parent p2("Ваша мама2", students2, PARENT);
    p2.setThere(true);

    p2.sayAllAnithing();
    p2.sayAlone();
    p2.sayAlone(students2[0]);
    parents.push_back(p2);

    teachers[0].setThere(true);
    teachers[1].setThere(true);
    Lesson l(name_lessons[0], teachers[0], students);
    cout << l;
    l.lessonAssessing();

    Lesson l2(name_lessons[1], teachers[1], students2);
    cout << l2;
    l2.lessonAssessing();

    vector<Lesson> lessons;
    lessons.push_back(l);
    lessons.push_back(l2);
    Meeting m(parents, lessons);
    m.say();

    Parent p3("Бабуля", students2, GRANDMOM);
    p3.setThere(true);
    parents.push_back(p3);

    Meeting m2(parents, lessons);
    m2.say();
    return 0;
}

// заполняем вектор студентов
void fill_students(vector<int> &st_marks, const vector<string> &name_students,
                   vector<Student> &students, int n) {// добавляем 10 студентов для тестов
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            st_marks[j] = (static_cast<int>(rand() * (1.0 / (static_cast<double>(RAND_MAX) + 1.0)) * (5 - 4 + 1) + 4));
            cout << st_marks[j] << ' ';
        }
        cout << endl;
        Student s(name_students[i], st_marks);
        cout << s;
        students.push_back(s);
    }
}
