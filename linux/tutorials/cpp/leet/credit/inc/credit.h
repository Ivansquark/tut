#ifndef CREDIT_H
#define CREDIT_H

class Credit {
  public:
    static double cash_final(int m, int cash_month_plus,
                             double percent) {
        double sum = 0;
        for (int i = 0; i < m; ++i) {
            sum += sum * percent / (12 * 100);
            sum += cash_month_plus;
        }
        return sum;
    }

    static double sum_month_minus_pay(int m, int cash, double percent,
                                      double month_pay) {
        double sum = cash;
        for (int i = 0; i < m; ++i) {
            sum += cash * percent / (100 * 12);
        }
        sum -= month_pay * m;
        return sum;
    }

    static double sum_month(int m, int cash, double percent) {
        double sum = cash;
        for (int i = 0; i < m; ++i) {
            sum += cash * percent / (100 * 12);
        }
        return sum;
    }
};

#endif // CREDIT_H
