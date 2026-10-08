#include <stdio.h>

struct Subscription {
    int sub_id;
    char plan_name[31];
    double monthly_fee;
    int user_limit;
};

int main() {
    struct Subscription subscriptions[100];

    int n;
    int i;
    double total_revenue = 0.0;

    scanf("%d", &n);

    if (n <= 0) {
        printf("So luong goi dich vu khong hop le!\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        scanf("%d %30s %lf %d",
              &subscriptions[i].sub_id,
              subscriptions[i].plan_name,
              &subscriptions[i].monthly_fee,
              &subscriptions[i].user_limit);

        total_revenue += subscriptions[i].monthly_fee;
    }

    printf("MA GOI TEN GOI CUOC PHI (USD) GIOI HAN USER\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-15s %-18.2f %-15d\n",
               subscriptions[i].sub_id,
               subscriptions[i].plan_name,
               subscriptions[i].monthly_fee,
               subscriptions[i].user_limit);
    }

    printf("---------------------------------------------------------------\n");
    printf("TONG DOANH THU HANG THANG: %.2f USD\n", total_revenue);

    return 0;
}
