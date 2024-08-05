#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <cstring>
#include <map>
#include<fstream>
using namespace std;

/*
 *          ********
 * author:  M.NASSER
 *          ********
 */

 ///////////////////////////////////////   START   //////////////////////////////////////////

class user;
class System;
class visacard;
class Mustercard;
class Icard;
vector<user>vec_user;
vector<Icard*>vec;

class user
{
public:
    string user_name;
    string password;
    string phone;
public:
    friend class System;
    friend class Icard;
    friend class visacard;
    friend class Mustercard;
    user() {};
    user(string name, string pass, string ph)
    {
        user_name = name;
        password = pass;
        phone = ph;
    }

};

class Icard
{
public:
    string username;
    string phone;
    string password;
    int type;
    long long balance = 0;
public:
    virtual void sendmoney(string s, long long n) = 0;
    virtual void sendmoney(long long n, string s) = 0;
    virtual void showbalance() = 0;
    virtual void addbalance() = 0;

};

class visacard : public Icard
{
public:
    friend class user;
    void sendmoney(string name, long long money)
    {
        if (money > balance) {
            cout << "There is not enough value\n";
        }
        else {
            bool found = false;
            for (int i = 0; i < vec_user.size(); ++i) {
                if (name == vec_user[i].user_name) {
                    found = true;
                }
            }
            if (found) {
                balance -= money;
                for (int i = 0; i < vec.size(); ++i) {
                    if (name == vec[i]->username) {
                        vec[i]->balance += (money - (money / 100) * 1);
                        cout << "operation accomplished successfully\n";
                        break;
                    }
                }
            }
            else {
                cout << "Invalid user\n";
            }
        }
    }
    void sendmoney(long long money, string ph)
    {
        if (money > balance) {
            cout << "There is not enough value\n";
        }
        else {
            bool found = false;
            for (int i = 0; i < vec_user.size(); ++i) {
                if (ph == vec_user[i].phone) {
                    found = true;
                }
            }
            if (found) {
                balance -= money;
                for (int i = 0; i < vec.size(); ++i) {
                    if (ph == vec[i]->phone) {
                        vec[i]->balance += (money - (money / 100) * 1);
                        cout << "operation accomplished successfully\n";
                        break;
                    }
                }
            }
            else {
                cout << "Invalid user\n";
            }
        }
    }

    void addbalance()
    {
        cout << "Balance [limit 10000$]: ";
        long long bal;
        cin >> bal;
        if (bal > 10000) {
            cout << "Exceeded the maximum\n";
            addbalance();
        }
        balance += bal - (bal / 100) * 1;
        cout << "operation accomplished successfully\n";
    }

    void showbalance()
    {
        cout << "\tBalance: " << balance << '$' << '\n';
    }
};
class Mustercard : public Icard
{
public:
    friend class user;
    void sendmoney(string name, long long money)
    {
        if (money > balance) {
            cout << "There is not enough value\n";
        }
        else {
            bool found = false;
            for (int i = 0; i < vec_user.size(); ++i) {
                if (name == vec_user[i].user_name) {
                    found = true;
                }
            }
            if (found) {
                balance -= money;
                for (int i = 0; i < vec.size(); ++i) {
                    if (name == vec[i]->username) {
                        vec[i]->balance += (money - (money / 100) * 2);
                        cout << "operation accomplished successfully\n";
                        break;
                    }
                }
            }
            else {
                cout << "Invalid user\n";
            }
        }
    }
    void sendmoney(long long money, string ph)
    {
        if (money > balance) {
            cout << "There is not enough value\n";
        }
        else {
            bool found = false;
            for (int i = 0; i < vec_user.size(); ++i) {
                if (ph == vec_user[i].phone) {
                    found = true;
                }
            }
            if (found) {
                balance -= money;
                for (int i = 0; i < vec.size(); ++i) {
                    if (ph == vec[i]->phone) {
                        vec[i]->balance += (money - (money / 100) * 2);
                        cout << "operation accomplished successfully\n";
                        break;
                    }
                }
            }
            else {
                cout << "Invalid user\n";
            }
        }
    }

    void addbalance()
    {
        cout << "Balance [limit 10000$]: ";
        long long bal;
        cin >> bal;
        if (bal > 10000) {
            cout << "Exceeded the maximum\n";
            addbalance();
        }
        balance += bal - (bal / 100) * 3;
        cout << "operation accomplished successfully\n";
    }
    void showbalance()
    {
        cout << "\tBalance: " << balance << '$' << '\n';
    }
};
class System
{
public:
    friend class user;
    user sign_up()
    {
        string name, pass, ph;
        cout << "Enter user name .(No space) : ";
        cin >> name;
        cout << "Enter password : ";
        cin >> pass;
        cout << "Enter your phone number : ";
        cin >> ph;
        bool found = 0;
        for (int i = 0; i < vec_user.size(); ++i) {
            if (vec_user[i].user_name == name) {
                found = 1;
            }
        }
        if (found) {
            cout << "This user_name is already used...!\n";
            sign_up();
        }
        // 1 - visa
        // 2 - muster
        cout << '\t' << "1- visacard\n";
        cout << '\t' << "2- mustercard\n";
        int p;
        cin >> p;
        Icard* ptr;
        if (p == 1) {
            ptr = new visacard;
        }
        else {
            ptr = new Mustercard;
        }
        ptr->username = name;
        ptr->password = pass;
        ptr->phone = ph;
        ptr->type = p;
        ptr->balance = 0;
        vec.push_back(ptr);
        user US = { name, pass, ph };
        vec_user.push_back(US);
        return US;
    }
    user login()
    {
        string name, pass, ph;
        cout << "Enter user name .(No space) : ";
        cin >> name;
        cout << "Enter password : ";
        cin >> pass;
        bool found = 0;
        for (int i = 0; i < vec_user.size(); ++i) {
            if (vec_user[i].user_name == name && vec_user[i].password == pass) {
                user us = { name,pass,ph };
                return us;
            }
        }
        cout << "Invalid user name, Please try again...\n";
        cout << "Enter 1 to login or any button to logout!\n";
        int n;
        cin >> n;
        if (n == 1) {
            return login();
        }
        else {
            user invalid = { "-1","-1","-1" };
            return invalid;
        }
    }
    int menu()
    {
        cout << "Menu:" << endl;
        cout << '\t' << "1: Sign up" << endl;
        cout << '\t' << "2: login" << endl;
        cout << "Enter number in range 1 - 2:";
        int n;
        cin >> n;
        cout << endl;
        switch (n) {
        case 1:
            return n;
            break;
        case 2:
            return n;
            break;
        default:
            cout << "Selection not found, Try again..." << endl << endl;
            return menu();
        }
    }
    int options_menu()
    {
        cout << "Menu:" << endl;
        cout << '\t' << "1: send money" << endl;
        cout << '\t' << "2: show money" << endl;
        cout << "\t" << "3: add visa" << endl;
        cout << "\t" << "4: add money" << endl;
        cout << '\t' << "5: logout" << endl;
        cout << "Enter number in range 1 - 5:";

        int option;
        cin >> option;

        if (option < 1 || option > 5) {
            cout << "Invalid option...!" << endl;
            return options_menu();
        }
        else {
            return option;
        }
    }
    void addvisa(user USER)
    {
        cout << '\t' << "1- visacard\n";
        cout << '\t' << "2- mustercard\n";
        int p;
        cin >> p;
        bool found = false;
        for (int i = 0; i < vec.size(); ++i) {
            if (USER.user_name == vec[i]->username && vec[i]->type == p) {
                cout << "Already used!\n";
                found = true;
                break;
            }
        }
        if (found) {
            int n;
            cout << "\t1- Try again\n";
            cout << "\t2- Exit\n";
            cin >> n;
            if (n == 1) {
                addvisa(USER);
            }
        }
        else {
            //1-visa
            //2-muster
            Icard* ptr{};
            if (p == 1) {
                ptr = new visacard;
            }
            else {
                ptr = new Mustercard;
            }
            ptr->username = USER.user_name;
            ptr->password = USER.password;
            ptr->phone = USER.phone;
            ptr->type = p;
            ptr->balance = 0;
            vec.push_back(ptr);
            cout << "Visa is created successfully\n";
        }
    }
    System()
    {
        ifstream file("USERS.txt", ios::in);
        if (file.fail()) {
            cout << "fail download users data" << endl;
            return;
        }
        vec_user.clear();
        if (!file.fail()) {
            user us;
            while (file >> us.user_name >> us.password >> us.phone) {
                vec_user.push_back(us);
            }
            file.close();
        }


        ifstream file2("Icard.txt", ios::in);
        if (file2.fail()) {
            cout << "fail download  data" << endl;
            return;
        }
        vec.clear();
        if (!file2.fail()) {
            Icard* ptr{};
            string username, password, phone; long long  balance; int type;
            while (file2 >> username >> password >> phone >> balance >> type) {
                if (type == 1) {
                    visacard v;
                    v.username = username;
                    v.password = password;
                    v.phone = phone;
                    v.balance = balance;
                    v.type = type;
                    ptr = new visacard(v);
                    vec.push_back(ptr);
                }
                else {
                    Mustercard v;
                    v.username = username;
                    v.password = password;
                    v.phone = phone;
                    v.balance = balance;
                    v.type = type;
                    ptr = new Mustercard(v);
                    vec.push_back(ptr);
                }
            }
            file2.close();
        }

    }
    ~System()
    {
        ofstream file("USERS.txt", ios::out);
        if (file.fail()) {
            cout << "faild download users data" << endl;
            return;
        }
        for (int i = 0; i < vec_user.size(); ++i) {
            user us = vec_user[i];
            file << us.user_name + '\n' << us.password + '\n' << us.phone + '\n';
        }
        file.close();

        ofstream file2("Icard.txt", ios::out);
        if (file2.fail()) {
            cout << "faild download users data" << endl;
            return;
        }
        for (int i = 0; i < vec.size(); ++i) {
            Icard* ptr{};
            ptr = vec[i];
            file2 << ptr->username << endl << ptr->password << endl << ptr->phone << endl << ptr->balance << endl << ptr->type  << endl ;
        }
        file2.close();
    }
};
int main()
{
    user USER;
    System sys;
    /*for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i]->username << '\n' << vec[i]->password << vec[i]->phone << vec[i]->balance << vec[i]->type << '\n';
    }*/
    
start:
    int n = sys.menu();
    switch (n) {
    case 1:
        USER = sys.sign_up();
        break;
    case 2:
        USER = sys.login();
        if (USER.phone == "-1") {
            return 0;
        }
        break;
    }
    cout << "Hello, " << USER.user_name << '\n';
restart:
    n = sys.options_menu();
    string name;
    string phone_num;
    int cnt;
    int op;
    switch (n) {
    case 1:
        cout << '\t' << "1- Send by username\n";
        cout << '\t' << "2- send by phone number\n\n";
        cout << "Enter option: ";
        int op;
        cin >> op;
        cout << "Enter the value: ";
        long long val;
        cin >> val;
        if (op == 1) {
            cout << "Enter username: ";
            cin >> name;
        }
        else if (op == 2) {
            cout << "Enter phone number: ";
            cin >> phone_num;
        }
        else {
            goto restart;
        }
        cnt = 0;
        for (int i = 0; i < vec.size(); ++i) {
            if (USER.user_name == vec[i]->username) {
                ++cnt;
            }
        }
        if (cnt == 1) {
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i]->username == USER.user_name && op == 1) {
                    vec[i]->sendmoney(name, val);
                }
                else if (vec[i]->username == USER.user_name && op == 2) {
                    vec[i]->sendmoney(val, phone_num);
                }
            }
        }
        else {
            cout << '\t' << "1- visacard\n";
            cout << '\t' << "2- mustercard\n";
            int p;
            cin >> p;

            for (int i = 0; i < vec.size(); ++i) {
                if (USER.user_name == vec[i]->username && p == vec[i]->type == p) {
                    if (op == 1) {
                        vec[i]->sendmoney(name, val);
                    }
                    else {
                        vec[i]->sendmoney(val, phone_num);
                    }
                }
            }
        }
        goto restart;
        break;
    case 2:
        cnt = 0;
        for (int i = 0; i < vec.size(); ++i) {
            if (USER.user_name == vec[i]->username) {
                ++cnt;
            }
        }
        if (cnt == 1) {
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i]->username == USER.user_name) {
                    vec[i]->showbalance();
                }
            }
        }
        else {
            cout << '\t' << "1- visacard\n";
            cout << '\t' << "2- mustercard\n";
            int p;
            cin >> p;

            for (int i = 0; i < vec.size(); ++i) {
                if (USER.user_name == vec[i]->username && vec[i]->type == p) {
                    if (p == 1) {
                        vec[i]->showbalance();
                    }
                    else {
                        vec[i]->showbalance();
                    }
                }
            }
        }
        goto restart;
        break;
    case 3:
        // 1 - visa
        // 2 - muster
        sys.addvisa(USER);
        goto restart;
        break;
    case 4:

        cnt = 0;
        for (int i = 0; i < vec.size(); ++i) {
            if (USER.user_name == vec[i]->username) {
                ++cnt;
            }
        }
        if (cnt == 1) {
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i]->username == USER.user_name) {
                    vec[i]->addbalance();
                }
            }
        }
        else {
            cout << '\t' << "1- visacard\n";
            cout << '\t' << "2- mustercard\n";
            int p;
            cin >> p;
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i]->username == USER.user_name && vec[i]->type == p) {
                    vec[i]->addbalance();
                }
            }
        }
        goto restart;
        break;

    case 5:
        cout << "\t1- Menu\n";
        cout << "\t2- Exit\n";
        cin >> op;
        if (op == 1) {
            goto start;
        }
        else {
            return 0;
        }
        break;
    }
}