#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#define MY_CHILD "Мой ребёнок - "

using namespace std;

// всевозможные эмоции
enum EMOTIONS {
    BAD,
    GOOD,
    NONE
};

// в этом классе собраны все базовые вещи, которые могут быть использованы или уже используются людьми
class Base {

protected:
    string name; //коодрдинаты
    int emotion;
    bool there;

    void setEmotion () {
        emotion = rand() % 2;
    }

public:
    void setThere (bool there) {
        this->there = there;
    }
};

class Student : public Base {
    vector <int> marks;
    float rating;
    bool starStudent; // отличник ли он

    void isStarStudent () {
        rating = 0;
        // если рейтинг студента больше или равен 4.7, то он отличник
        for (int mark : marks) {
            this->rating += (float)mark;
        }
        this->rating /= (float)marks.size();

        if (this->rating >= 4.7)
            starStudent = true;
        else starStudent = false;
    }

    friend class Teacher;
    friend class Parent;
    friend class Meeting;
public:

    Student (string name, vector <int> marks) :
            marks(std::move(marks)) {Base::name = name; rating = 0; starStudent = false; isStarStudent ();}

    string toStrStarStudent () const {
        if (starStudent)
            return "является отличником";
        else
            return "не является отличником";
    }

    friend ostream &operator<<(std::ostream &out, Student &s) {
        out << "Студент " << s.name << ' ' << s.toStrStarStudent() << endl;
    }

};

// всевозможные опекуны
enum GUARDIAN {
    PARENT,
    GRANDMOM,
    ELSE
};

// опекуны
class Parent : public Base {
    int guardian;   // кем является опекун(см. enum сверху)
    vector <Student> children;

    // выявление того, принадлежит ли ребёнок родителю
    bool myChild (Student s) {
        for (const auto& i: children) {
            if (s.name == i.name)
                return true;
        }
    }

    friend class Lesson;
    friend class Meeting;

protected:

    // реакция на конкретного ребёнка
    void reaction (const Student& s) {
        // если бабушка, то она регариует немного подругому
        if ((guardian == 1) && (myChild(s)))
            emotion = NONE;
        switch (emotion) {
            case EMOTIONS::BAD:
                if (s.starStudent) { // если отличник
                    cout << MY_CHILD << s.name << ", такой молодец, хорошо учится!" << endl;
                } else { // если не отличник
                    cout << MY_CHILD << s.name << ", ужасно учится!" << endl;
                }
                break;
            case EMOTIONS::GOOD:
                if (s.starStudent) {
                    cout << MY_CHILD << s.name << ", самый лучший люблю его! А ещё он отличник!" << endl;
                } else {
                    cout << MY_CHILD << s.name << ", самый лучший люблю его! Жаль только, что не отличник :(" << endl;
                }
                break;

            default:
                cout << MY_CHILD << s.name << ", просто самый лучший. Жду от него детишек!!!" << endl;
                break;
        }
    }

    // реакция на всех детей
    void reactionAll (bool check) {
        if (guardian == 1)
            emotion = NONE;
        switch (emotion) {
            case EMOTIONS::BAD:
                if (check) { // если отличник
                    cout << "Все мои дети такие молодцы, люблю их!" << endl;
                } else { // если не отличник
                    cout << "Все мои дети ужасно учатся, не люблю их!" << endl;
                }
                break;
            case EMOTIONS::GOOD:
                if (check) {
                    cout << "Все мои дети самые лучшие, люблю их!" << endl;
                } else {
                    cout << "Все мои дети такие хорошие, жаль не отличники!" << endl;
                }
                break;

            default:
                cout << "Все мои дети самые лучшие! Жду от них детишек!" << endl;
                break;
        }
    }
public:
    Parent (string name, vector<Student> children, GUARDIAN guardian1): children(children) {
        setEmotion();
        Base::name = name;
        guardian = guardian1;
    }

    // сказать о рандомном ребёнке
    [[maybe_unused]] void sayAlone () {
        // выбираем рандомного ребёнка о котором рассказать
        int child = rand() % children.size();
        reaction(children[child]);
    }

    // сказать о конкретном ребёнке
    [[maybe_unused]] void sayAlone (const Student& s) {
        reaction(s);
    }

    // сказать о каждом ребёнке по отдельности
    [[maybe_unused]] void sayAllAnithing () {
        for (auto & i : children) {
            reaction(i);
        }
    }

    // рассказать обо всех детях
    [[maybe_unused]] void sayAll () {
        // если средняя отличность больше или равна 0,75, то говорим
        float middle_star = 0;
        bool check;

        // выявляем среднюю отличность
        for (auto & i : children) {
            if (i.starStudent)
                middle_star += 1;
        }
        middle_star /= (float)children.size();
        if (middle_star >= 0.75)
            check = true;
        else check = false;

        // с учётом средней отличности говорим
        reactionAll (check);

    }
};

class Teacher : public Base {
    int howTeacher;  // 3 состояния - зависящий от настроения, плохой(всегда ставит 2),
    // хороший(всегда ставит 5) препод
    int count_marks; // как часто меняется настроение у преподавателя
    int count;

    friend class Meeting;
public:
    explicit Teacher(string name) {
        Base::name = name;
        howTeacher = (unsigned int)(1 + name[5]) % 3;
        count_marks = (unsigned int)name[5] % 5 + 2; // не чаще, чем раз в 2 студента
        count = 0;
    }

    // функция выставления рандомных оценок от 2 до 5 в зависимости от условий
    void assessing (Student s) {
        srand(time(nullptr));
        float min = 2;
        float max = 5;
        // выявление эмоции у преподавателя
        if ((count % count_marks) == 0) {// смена настроения
            srand(count_marks);
            setEmotion(); // спроси норм ли, что эмоции меняются,
            // но рандом в основном меняет на то же значение
            cout << "change emotions" << endl;
        }
        count += 1;

        cout << "emotions" << emotion << endl;
        cout << "howTeacher" << howTeacher << endl;
        if (howTeacher == 1) { // всегда ставит 2
            s.marks.push_back(2);
        } else if (howTeacher == 2) { // всегда ставит 5
            s.marks.push_back(5);
        } else { // зависит от эмоций
            static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

            // выявление возможных оценок студента
            // в зависимости от настроения преподавателя и того,
            // является ли студент отличником
            switch (emotion) {
                case EMOTIONS::BAD:
                    if (s.starStudent) {
                        min = 4;
                        max = 5;
                    } else {
                        min = 2;
                        max = 3;
                    }
                    break;
                case EMOTIONS::GOOD:
                    if (s.starStudent) {
                        min = 5;
                        max = 5;
                    } else {
                        min = 4;
                        max = 4;
                    }
                    break;

                default:
                    break;
            }
            // выставление окончательной оценки
            s.marks.push_back(static_cast<int>(rand() * fraction * (max - min + 1) + min));
        }
    }

    friend ostream &operator<<(std::ostream &out, Teacher &t) {
        out << "Преподаватель " << t.name << endl;
    }
};

class Lesson {
    string name;    // название предмета
    Teacher teacher;
    vector<Student> students;

    // храним студентов со значениями получили ли они оценки или нет
    vector<bool> getMark;

    friend class Teacher;
    friend class Meeting;
public:
    Lesson (string name, Teacher teacher, vector<Student> students):
            name(name), teacher(teacher), students(students) {}

    // выставление произвольным пришедшим на пару студентам оценок
    void lessonAssessing () {
        bool isMark;
        for (auto & student : students) {
            if (rand() % 2 == 0)
                isMark = true;
            else isMark = false;

            if (isMark) {
                teacher.assessing(student);
                getMark.push_back(true);
            } else
                getMark.push_back(false);
        }
    }

    friend ostream &operator<<(std::ostream &out, Lesson l) {
        out << "Предмет: " << l.name << ", " << l.teacher << endl;
    }
};

class Meeting {
    vector<Parent> parents;
    vector<Lesson> lessons;
    vector<Student>isMissing;

    // смотрим получал ли студент оценку
    bool tookMark (Lesson l, const Student& s) {
        // ищем такого студента на занятии
        int i = 0;
        while((i != l.students.size()) && (l.students[i].name != s.name))
            i++;
        // возвращаем то, получил ли он оценку
        if (i != l.students.size())
            return l.getMark[i];
        else return false; // если ребёнка не было на паре
    }

    friend class Lesson;
public:
    Meeting (vector<Parent> parents, vector<Lesson> lessons) : parents(std::move(parents)),
    lessons(std::move(lessons)) {} // в будущем можно there задавать в этом конструкторе, но чтобы было видно, что
    // класс адекватно работает на всех ситуациях, этого я не делал

    // обсуждение занятий
    void say () {
        // смотрим кто из родителей отсутствует
        for(const auto& j: parents) {
            if (!j.there) {
                for (const auto& k: j.children) {
                    isMissing.push_back(k);
                }
            }
        }

        // по всем прошедшим занятиям высказываются родители о своих детях

        for (auto & lesson : lessons) { // смотрим все занятия
            if(lesson.teacher.there) {
                for(auto j: parents) {
                    if(j.there){
                        for(const auto& k: j.children){ // смотрим получил ли ребёнок оценку и если да, то говорим о нём
                            if(tookMark (lesson, k)) {
                                j.sayAlone(k);
                            }
                        }
                    }
                }
            }
        }
            // все дети, чьи родители не пришли
        for(const auto& i: isMissing) {
            cout << i.name << " - опекуны не пришли" << endl;
        }
    }

};
