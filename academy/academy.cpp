#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<time.h>
#include<fstream>
//#include<typeinfo> // для typeid, если нужно

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, const std::string& birth_date
#define HUMAN_GIVE_PARAMETERS last_name, first_name, birth_date

class Human
{
    static const int LAST_NAME_WIDTH = 12;
    static const int FIRST_NAME_WIDTH = 12;
    static const int AGE_WIDTH = 5;

    const std::string LAST_NAME;
    const std::string FIRST_NAME;
    const tm BIRTH_DATE;
public:
    const std::string& get_last_name()const { return LAST_NAME; }
    const std::string& get_first_name()const { return FIRST_NAME; }
    tm get_birth_date()const { return BIRTH_DATE; }

    int get_age()const
    {
        time_t t_today = time(NULL);
        tm tm_today = *localtime(&t_today);
        tm birth_date = BIRTH_DATE;
        time_t t_birth_date = mktime(&birth_date);
        time_t difference = t_today - t_birth_date;
        tm age_tm = *localtime(&difference);
        age_tm.tm_year -= 70; // исправлено
        return age_tm.tm_year;
    }

    tm parse_date(const std::string& date)
    {
        char sz_date[32] = {};
        strcpy(sz_date, date.c_str());
        int date_parts[3] = {};
        int n = 0;
        const char delimiters[] = "-./";
        for (char* pch = strtok(sz_date, delimiters); pch; pch = strtok(NULL, delimiters))
            date_parts[n++] = atoi(pch);
        date_parts[0] -= 1900;
        date_parts[1]--;
        tm tm_birth_date = {};
        tm_birth_date.tm_year = date_parts[0];
        tm_birth_date.tm_mon = date_parts[1];
        tm_birth_date.tm_mday = date_parts[2];
        return tm_birth_date;
    }

    Human(HUMAN_TAKE_PARAMETERS) :
        LAST_NAME(last_name), FIRST_NAME(first_name), BIRTH_DATE(parse_date(birth_date))
    {
        cout << "HConstructor:\t" << this << endl;
    }
    virtual ~Human()
    {
        cout << "HDestructor:\t" << this << endl;
    }
    virtual std::ostream& info(std::ostream& os)const
    {
        os.width(LAST_NAME_WIDTH);
        os << std::left;
        os << LAST_NAME;
        os.width(FIRST_NAME_WIDTH);
        os << FIRST_NAME;
        os.width(AGE_WIDTH);
        os << get_age();
        return os;
    }
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
    return obj.info(os);
}

// Академический член
#define ACADEMY_MEMBER_TAKE_PARAMETERS const std::string& speciality
#define ACADEMY_MEMBER_GIVE_PARAMETERS speciality

class AcademyMember :public Human
{
    const int SPECIALITY_WIDHT = 40;
    std::string speciality;
public:
    const std::string& get_speciality()const { return speciality; }
    void set_speciality(const std::string& s) { speciality = s; }

    AcademyMember(HUMAN_TAKE_PARAMETERS, ACADEMY_MEMBER_TAKE_PARAMETERS) :
        Human(HUMAN_GIVE_PARAMETERS)
    {
        set_speciality(speciality);
        cout << "AMConstructor:\t" << this << endl;
    }
    virtual ~AcademyMember()
    {
        cout << "AMDestructor:\t" << this << endl;
    }
    std::ostream& info(std::ostream& os)const override
    {
        Human::info(os);
        os.width(SPECIALITY_WIDHT);
        os << speciality;
        return os;
    }
};

// Студент
#define STUDENT_TAKE_PARAMETERS const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS group, rating, attendance

class Student :public AcademyMember
{
    static const int group_widht = 8;
    static const int ratting_width = 8;
    static const int attendance_width = 8;
    std::string group;
    double rating;
    double attendance;
public:
    const std::string& get_group()const { return group; }
    double get_rating()const { return rating; }
    double get_attendance()const { return attendance; }

    void set_group(const std::string& g) { group = g; }
    void set_rating(double r) { rating = r; }
    void set_attendance(double a) { attendance = a; }

    Student(HUMAN_TAKE_PARAMETERS, ACADEMY_MEMBER_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :
        AcademyMember(HUMAN_GIVE_PARAMETERS, ACADEMY_MEMBER_GIVE_PARAMETERS)
    {
        set_group(group);
        set_rating(rating);
        set_attendance(attendance);
        cout << "SConstructor:\t" << this << endl;
    }
    virtual ~Student()
    {
        cout << "SDestructor:\t" << this << endl;
    }
    std::ostream& info(std::ostream& os)const override
    {
        return AcademyMember::info(os) << " " << group << " " << rating << " " << attendance;
    }
};

// Учитель
#define TEACHER_TAKE_PARAMETERS int experience
#define TEACHER_GIVE_PARAMETERS experience

class Teacher :public AcademyMember
{
    int experience;
public:
    int get_experience()const { return experience; }
    void set_experience(int e) { experience = e; }

    Teacher(HUMAN_TAKE_PARAMETERS, ACADEMY_MEMBER_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :
        AcademyMember(HUMAN_GIVE_PARAMETERS, ACADEMY_MEMBER_GIVE_PARAMETERS)
    {
        set_experience(experience);
        cout << "TConstructor:\t" << this << endl;
    }
    virtual ~Teacher()
    {
        cout << "TDestructor:\t" << this << endl;
    }
    std::ostream& info(std::ostream& os)const override
    {
        return AcademyMember::info(os) << " " << experience;
    }
};

// Выпускник
#define GRADUATE_TAKE_PARAMETERS const std::string& subject
#define GRADUATE_GIVE_PARAMETERS subject

class Graduate :public Student
{
    std::string subject;
public:
    const std::string& get_subject()const { return subject; }
    void set_subject(const std::string& s) { subject = s; }

    Graduate(HUMAN_TAKE_PARAMETERS,
        ACADEMY_MEMBER_TAKE_PARAMETERS,
        STUDENT_TAKE_PARAMETERS,
        GRADUATE_TAKE_PARAMETERS) :
        Student(HUMAN_GIVE_PARAMETERS, ACADEMY_MEMBER_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
    {
        set_subject(subject);
        cout << "GConstructor:\t" << this << endl;
    }
    ~Graduate()
    {
        cout << "GDestructor:\t" << this << endl;
    }
    std::ostream& info(std::ostream& os)const override
    {
        return Student::info(os) << " " << subject;
    }
};

// Функции для печати и сохранения
void G_Print(Human* group[], const int n);
void seve(Human* group[], const int size, const std::string& filename);

int main()
{
    setlocale(LC_ALL, "");

#ifdef INHERITANCE
    cout << "Academy" << endl;
    Human human("Тупенко", "Василий", "2009.09.02");
    human.info();

    AcademyMember am("Тупенко", "Василий", "2000.10.24", "Флуктуации пространства в вакууме");
    am.info();

    Student student("Чухарев", "Матвей", "2009.09.02", "Разработка программного обеспечения", "P_421", 100, 100);
    student.info();

    Teacher teacher("Einstein", "Albert", "1979.03.14", "Астрономия", 20);
    teacher.info();
#endif

    Human* group[] =
    {
        new Student("Чухарев", "Матвей", "2009.09.02", "Разработка программного обеспечения", "P_421", 100, 100),
        new Teacher("Einstein", "Albert", "1979.03.14", "Астрономия", 20),
        new Student("Гусев", "Савелий", "2010.08.29", "Разработка программного обеспечения", "P_421", 98, 98),
        new Teacher("Олег", "Анатольевич", "1985.01.16", "Разработка программного обеспечения", 16),
        // Создаем дипломника
        new Graduate("Иванов", "Иван", "1990.05.15",
            "Физика", "P_500", 95, 88,
            "Теория относительности")
    };
    G_Print(group, sizeof(group) / sizeof(group[0]));
    seve(group, sizeof(group) / sizeof(group[0]), "group.txt");

    // Освобождение памяти
    for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
        delete group[i];

    return 0;
}

void G_Print(Human* group[], const int n)
{
    std::cout << delimiter;
    for (int i = 0; i < n; i++)
    {
        std::cout << *group[i] << std::endl;
        std::cout << delimiter;
    }
}

void seve(Human* group[], const int size, const std::string& filename)
{
    std::ofstream fout(filename);
    for (int i = 0; i < size; i++)
    {
        fout << *group[i] << endl;
    }
    fout.close();
    std::string cmd = "notepad ";
    cmd += filename;
    system(cmd.c_str());
}