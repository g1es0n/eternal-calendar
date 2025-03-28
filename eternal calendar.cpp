#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cassert>

using namespace std;

bool leap_year(int);
bool correctness(int, int, int, int);
bool mix(int, int, int, int);
int first_day (int, int);
bool correct_k (int, int);
void calendar(int, int);
void counter(int, int, int, int);
vector<int> this_year(int);
int amount(int, int, int, int);
void run_tests();
void test_leap_year();
void test_first_year();
void test_position();
void test_correct_k();
void test_correctness();

const string month[] = {"ЯНВАРЬ", "ФЕВРАЛЬ", "МАРТ", "АПРЕЛЬ", "МАЙ", "ИЮНЬ", "ИЮЛЬ", "АВГУСТ", "СЕНТЯБРЬ", "ОКТЯБРЬ", "НОЯБРЬ", "ДЕКАБРЬ"};
const int year_start = 1919;
const int pos_start = 2;
const int month_start = 1;

int main(){
    cout << "Для календаря введите:\ncalendar\nX XXXX\nДля счётчика дней введите:\ncounter\nX XXXX X XXXX\n";
    string variant;
    cin >> variant;
    if (variant == "calendar"){
        int mon, year;
        cin >> mon >> year;
        calendar(mon, year);
    }
    else if (variant == "counter"){
        int month_1, year_1, month_2, year_2;
        cin >> month_1 >> year_1 >> month_2 >> year_2;
        counter(month_1, year_1, month_2, year_2);
    }
    else cout << "Функция не поддерживается";
    run_tests();
}

bool leap_year(int year){
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

bool correctness(int month_1, int year_1, int month_2, int year_2){
    return month_1 >= 1 && month_1 <= 12 && year_1 >= 1919 && year_1 <= 2169 && month_2 >= 1 && month_2 <= 12 && year_2 >= 1919 && year_2 <= 2169;
}

bool mix(int month_1, int year_1, int month_2, int year_2){
    return !((month_1 < year_1 && year_1 < year_2 && month_2 < year_2) || (year_1 == year_2 && month_1 <= month_2));
}

int first_day(int year_end, int mon_end){
    int new_position = pos_start;
    int new_year = year_start;
    int new_mon = month_start;
    while (new_year != year_end){
        new_position++;
        if (leap_year(new_year)) 
            new_position++;
        new_year ++;
        new_position %= 7;
        }
    vector <int> months = this_year(new_year);
    while (new_mon != mon_end){
            new_position += months[new_mon-1];
            new_position %= 7;
            new_mon++;
        }
    return new_position;
}

bool correct_k (int month_k, int year_k){
    return month_k <= 12 && month_k >= 1 && year_k >= 1919 && year_k <= 2169;
}

int amount(int month_1, int year_1, int month_2, int year_2){
    int ans = 0;
        while (month_1 != month_2 || year_1 != year_2){
            vector<int> year = this_year(year_1);
            ans += year[month_1-1];
            if (month_1 % 12 == 0){
                month_1 = 1;
                year_1 += 1;
            }
            else 
                month_1 += 1;
    }
    return ans;
}

void counter(int month_1, int year_1, int month_2, int year_2){
        if (mix(month_1, year_1, month_2, year_2))  
            cout << "Неверная последовательность данных. Последовательность ввода: месяц, от которого считать; год, от которого считать; месяц, до которого считать; год, до которого считать";
        else if (correctness(month_1, year_1, month_2, year_2)){
            int ans = amount(month_1, year_1, month_2, year_2);
            cout << ans;
        }
        else cout << "Неверно введены данные";
}

void calendar(int mon, int year){
    if (mon > year){
            cout << "Неверная последовательность данных. Сначала введите месяц, потом год";
        }
    else if (correct_k(mon, year)){
        vector <int> days = this_year(year);
        int position_first = first_day(year, mon);
        cout << position_first << endl;
        cout << month[mon-1] << " " << year << "\n";
        cout << " ПН ВТ СР ЧТ ПТ СБ ВС" << "\n";
        int k;
        for (k = 0; k < position_first; k++) 
            cout << "   ";
        for (int j = 1; j <= days[mon-1]; j++) {
            k++;
            cout << setw(3) <<j;
            if (k > 6) {
                k = 0; 
                cout << "\n"; 
            }
        }
    }
    else cout << "Невернно введены данные";
}

vector<int> this_year(int year){
    vector<int> months = {31, 28 + leap_year(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return months;
}

void test_leap_year(){
    assert(leap_year(2020) == true);
    assert(leap_year(2019) == false);
    assert(leap_year(2000) == true);
    assert(leap_year(2100) == false);
}

void test_first_day(){
    assert(first_day(2024, 1) == 0);
    assert(first_day(1919, 1) == 2);
    assert(first_day(2020, 3) == 6);
    assert(first_day(1986, 3) == 5);
}

void test_amount(){
    assert(amount(1, 1919, 1, 1919) == 0);
    assert(amount(1, 2000, 3, 2000) == 60);
    assert(amount(2, 1999, 10, 2004) == 2069);
    assert(amount(12, 2025, 1, 2026) == 31);
}

void test_correct_k (){
    assert(correct_k(12, 1987) == 1);
    assert(correct_k(13, 1968) == 0);
    assert(correct_k(11, 1856) == 0);
    assert(correct_k(13, 2172) == 0);
}

void test_mix(){
    assert(mix(10, 1987, 9, 1989) == 0);
    assert(mix(9, 1989, 10, 1987) == 1);
    assert(mix(10, 1987, 9, 1987) == 1);
}

void test_correctness(){
    assert(correctness(13, 1989, 1, 2000) == 0);
    assert(correctness(1, 1917, 2, 2200) == 0);
    assert(correctness(6, 1967, 16, 2020) == 0);
    assert(correctness(1, 1989, 12, 2004) == 1);
}

void run_tests(){
    test_first_day();
    test_leap_year();
    test_amount();
    test_correct_k();
    test_mix();
    test_correctness();
    cout << "\nТесты пройдены успешно";
}