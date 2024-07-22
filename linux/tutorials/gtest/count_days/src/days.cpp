#include "days.h"

int days(const Xray_Date& date) {
    int julian_days = 0;
    int a = (14 - date.month) / 12;
    int y = date.year + 2000 + 4800 - a;
    int m = date.month + 12 * a - 3;

    julian_days = date.day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 +
                  y / 400 - 32045;

    return julian_days;
}

int time_diff_secs(int days, const Xray_Time& last, const Xray_Time& cur) {
    int secs = 0;

    int h = cur.hours, m = cur.minutes, s = cur.seconds;
    int h_t = last.hours, m_t = last.minutes, s_t = last.seconds;

    h -= h_t;
    if (h < 0) {
        h += 24;
        secs = (days - 1) * 24 * 3600;
    } else {
        secs = (days) * 24 * 3600;
    }
    m -= m_t;
    if (m < 0) {
        m += 60;
    }
    s -= s_t;
    if(s < 0) {
        s+=60;
    }
    secs += (s + (m * 60) + (h * 3600));
    if(secs < 0) return 0;
    return secs;
}
