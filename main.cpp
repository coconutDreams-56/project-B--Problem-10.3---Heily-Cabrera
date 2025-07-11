/****Project-B--Problem-10.3---Heily-Cabrera ****/

/** Implement a base class Appointment and derived classes Onetime, Daily, Weekly, and Monthly. 
An appointment has a description (for example, “see the dentist”) and a date and time. 
Write a virtual function occurs_on(int year, int month, int day) that checks whether the appointment occurs on that date. 
For example, for a monthly appointment, you must check whether the day of the month matches. 
Then fill a vector of Appointment* with a mixture of appointments. 
Have the user enter a date and print out all appointments that happen on that date. **/

//Programmer: Heily Cabrera
//Tester: Audrey Tapia

// Group Project B //
/***** Members *****/
/***** Ashley Jacobson *****/
/***** Giannfranco Brance *****/
/***** Audrey Tapia *****/
/***** Heily Cabrera Guerrero *****/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Appointment 
{
protected:
    string description;
    int year;
    int month;
    int day;

public:
    Appointment(string desc, int y, int m, int d)
        : description(desc), year(y), month(m), day(d) {}

    virtual ~Appointment() {} 

    virtual bool occurs_on(int y, int m, int d) const = 0;

    virtual void print() const 
    {
        cout << description << " on " << year << "-" << month << "-" << day << endl;
    }
};

class Onetime : public Appointment 
{
public:
    Onetime(string desc, int y, int m, int d)
        : Appointment(desc, y, m, d) {}

    bool occurs_on(int y, int m, int d) const override 
    {
        return (year == y && month == m && day == d);
    }

    void print() const override 
    {
        cout << "[One-time] ";
        Appointment::print();
    }
};

class Daily : public Appointment 
{
public:
    Daily(string desc, int y, int m, int d)
        : Appointment(desc, y, m, d) {}

    bool occurs_on(int y, int m, int d) const override 
    {
        return (y > year || (y == year && (m > month || (m == month && d >= day))));
    }

    void print() const override 
    {
        cout << "[Daily] ";
        Appointment::print();
    }
};

class Weekly : public Appointment {
public:
    Weekly(string desc, int y, int m, int d)
        : Appointment(desc, y, m, d) {}

    bool occurs_on(int y, int m, int d) const override 
    {
        if (y < year || (y == year && m < month)) return false;
        if (y == year && m == month && d < day) return false;

        int days_since = (y - year) * 365 + (m - month) * 30 + (d - day);
        return days_since % 7 == 0;
    }

    void print() const override 
    {
        cout << "[Weekly] ";
        Appointment::print();
    }
};

class Monthly : public Appointment 
{
public:
    Monthly(string desc, int y, int m, int d)
        : Appointment(desc, y, m, d) {}

    bool occurs_on(int y, int m, int d) const override 
    {
        return (day == d && (y > year || (y == year && m >= month)));
    }

    void print() const override 
    {
        cout << "[Monthly] ";
        Appointment::print();
    }
};

int main() {
    vector<Appointment*> calendar;

    calendar.push_back(new Onetime("Doctor appointmenr", 2025, 7, 15));
    calendar.push_back(new Daily("Get vaccine", 2025, 7, 1));
    calendar.push_back(new Weekly("Conference", 2025, 7, 3));
    calendar.push_back(new Monthly("Pay landlord", 2025, 1, 1));

    int y, m, d;
    cout << "Enter a date to check appointments (YYYY MM DD): ";
    cin >> y >> m >> d;

    cout << "\nAppointments on " << y << "-" << m << "-" << d << ":\n";
    bool found = false;

    for (Appointment* appt : calendar) 
    {
        if (appt->occurs_on(y, m, d)) 
        {
            appt->print();
            found = true;
        }
    }

    if (!found) 
    {
        cout << "No appointments on this date.\n";
    }

    for (Appointment* appt : calendar) {
        delete appt;
    }

    return 0;
}
