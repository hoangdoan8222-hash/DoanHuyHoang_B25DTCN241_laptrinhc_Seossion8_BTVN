#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    struct UserAccount user_list[100];
    struct UserAccount active_list[100];
    struct UserAccount free_list[100];

    int n;
    int i;
    int j;
    int active_count = 0;
    int free_count = 0;
    int position = 0;
    int max_devices;
    int temp_fee;

    int mrr_before = 0;
    int mrr_after = 0;
    int mrr_difference;

    do {
        printf("Nhap so luong tai khoan (1-100): ");
        scanf("%d", &n);

        if (n < 1 || n > 100) {
            printf("Loi: N phai nam trong khoang 1 den 100.\n");
        }
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\n=== TAI KHOAN %d ===\n", i + 1);

        printf("Account ID: ");
        scanf("%d", &user_list[i].account_id);

        do {
            printf("Plan type (0-Free, 1-Standard, 2-Premium): ");
            scanf("%d", &user_list[i].plan_type);

            if (user_list[i].plan_type < 0 ||
                user_list[i].plan_type > 2) {
                printf("Loi: Plan type phai tu 0 den 2.\n");
            }
        } while (user_list[i].plan_type < 0 ||
                 user_list[i].plan_type > 2);

        printf("Monthly fee: ");
        scanf("%d", &user_list[i].monthly_fee);

        printf("Remaining days: ");
        scanf("%d", &user_list[i].remaining_days);

        printf("Active devices: ");
        scanf("%d", &user_list[i].active_devices);

        mrr_before += user_list[i].monthly_fee;
    }

    for (i = 0; i < n; i++) {

        if (user_list[i].active_devices <= 0) {
            user_list[i].active_devices = 1;
        }

        if (user_list[i].remaining_days <= 0) {
            user_list[i].plan_type = 0;
            user_list[i].monthly_fee = 0;
        } else {
       
            if (user_list[i].plan_type == 0) {
                user_list[i].monthly_fee = 0;
                max_devices = 1;
            } else if (user_list[i].plan_type == 1) {
                user_list[i].monthly_fee = 120000;
                max_devices = 2;
            } else {
                user_list[i].monthly_fee = 300000;
                max_devices = 5;
            }

            if (user_list[i].active_devices > max_devices) {
                user_list[i].active_devices = max_devices;
            }
        }

        if (user_list[i].plan_type > 0) {
            active_list[active_count] = user_list[i];
            active_count++;
        } else {
            free_list[free_count] = user_list[i];
            free_count++;
        }
    }

    for (i = 0; i < active_count - 1; i++) {
        for (j = i + 1; j < active_count; j++) {
            if (active_list[i].monthly_fee < active_list[j].monthly_fee) {
                struct UserAccount temp;

                temp = active_list[i];
                active_list[i] = active_list[j];
                active_list[j] = temp;
            }
        }
    }

    position = 0;

    for (i = 0; i < active_count; i++) {
        user_list[position] = active_list[i];
        position++;
    }

    for (i = 0; i < free_count; i++) {
        user_list[position] = free_list[i];
        position++;
    }

    for (i = 0; i < n; i++) {
        mrr_after += user_list[i].monthly_fee;
    }

    mrr_difference = mrr_before - mrr_after;

    printf("\n");
    printf("=======================================================================\n");
    printf("                 BAO CAO KIEM TOAN SAAS\n");
    printf("=======================================================================\n");

    printf("%-10s %-10s %-15s %-15s %-15s\n",
           "Account ID",
           "Plan",
           "Monthly Fee",
           "Remain Days",
           "Devices");

    printf("-----------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-10d %-15d %-15d %-15d\n",
               user_list[i].account_id,
               user_list[i].plan_type,
               user_list[i].monthly_fee,
               user_list[i].remaining_days,
               user_list[i].active_devices);
    }

    printf("=======================================================================\n");
    printf("MRR truoc kiem toan : %d VND\n", mrr_before);
    printf("MRR sau kiem toan   : %d VND\n", mrr_after);
    printf("Chenh lech MRR      : %d VND\n", mrr_difference);
    printf("So tai khoan Active : %d\n", active_count);
    printf("So tai khoan Free   : %d\n", free_count);
    printf("=======================================================================\n");

    return 0;
}


