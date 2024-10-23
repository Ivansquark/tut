#include "credit.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    constexpr int month = 12;
    constexpr int deposit_month_sum = 100000;
    constexpr int cash = 1380000;
    constexpr int month_pay = 19280;
    constexpr int insurence_difference = 5000;
    constexpr double perc = 6.1F;
    double max = Credit::sum_month(month, cash, perc);
    double max1 = Credit::sum_month_minus_pay(month, cash, perc, month_pay);
    double max2 = Credit::sum_month_minus_pay(month, cash, perc,
                                              month_pay + deposit_month_sum);
    print(" Дано: ипотека под 6.1 процент, ежемесячный платеж 19280");
    print("       есть лишние 100000 каждый месяц");
    print("");
    print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    print("Что лучше платить досрочно ипотеку или класть на вклад?");
    print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    print("");
    print("сумма ипотеки начальная =", cash);
    print("----------------------------------------------------------------");
    print("полная сумма ипотеки через год =", (int)max);
    print("----------------------------------------------------------------");
    print("оставшаяся сумма ипотеки через год если не гасить досрочно =",
          (int)max1);
    print("----------------------------------------------------------------");
    print(
        "оставшаяся сумма ипотеки через год при досрочном погашение на 119280 =",
        (int)max2);
    print("----------------------------------------------------------------");
    print("сумма ежемесячного депозита на вклад = ", deposit_month_sum);
    print("----------------------------------------------------------------");
    print("разница в сумме страховок ~ ", "5000");
    print("----------------------------------------------------------------");
    double percent = 0;
    for (int i = 6; i < 20; i += 2) {
        percent = i;
        double fin = Credit::cash_final(month, deposit_month_sum, percent);
        print("процент вклада = ", percent,
              "\tсумма на вкладе в конце года = ", (int)fin);
        //print("Разница = ", (int)(fin - max1));
        print("Разница = ", (int)(fin - max1 - insurence_difference));
        print("-------------------------------------------------------------");
    }

    return 0;
}
