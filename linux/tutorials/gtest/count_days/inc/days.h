#ifndef DAYS
#define DAYS

#include <stdint.h>

struct Xray_Time {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};
struct Xray_Date {
    uint8_t day;
    uint8_t month;
    uint8_t year; // since 2000 = 00
};

//int time(const Xray_Time time);
int days(const Xray_Date& date);
int time_diff_secs(int days, const Xray_Time& last, const Xray_Time& cur);
#endif // DAYS1
