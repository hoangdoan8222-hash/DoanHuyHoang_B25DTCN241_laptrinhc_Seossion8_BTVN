#include <stdio.h>
#include <string.h>

struct Subscription {
    int user_id;
    char account_name[31];
    int plan_type;
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;
};

int main() {
    struct Subscription subscriptions[50];

    int n;
    int i;
    int downgraded_count = 0;
    int violation_count = 0;
    int violation;

    do {
        printf("Nhap so luong tai khoan (1-50): ");
        scanf("%d", &n);

        if (n < 1 || n > 50) {
            printf("Loi: So luong tai khoan phai tu 1 den 50.\n");
        }
    } while (n < 1 || n > 50);

    for (i = 0; i < n; i++) {
        printf("\n========== TAI KHOAN %d ==========\n", i + 1);

        printf("User ID: ");
        scanf("%d", &subscriptions[i].user_id);

        printf("Account name: ");
        scanf("%30s", subscriptions[i].account_name);

        do {
            printf("Plan type (1-Free, 2-Individual, 3-Family): ");
            scanf("%d", &subscriptions[i].plan_type);

            if (subscriptions[i].plan_type < 1 ||
                subscriptions[i].plan_type > 3) {
                printf("Loi: Plan type phai tu 1 den 3.\n");
            }
        } while (subscriptions[i].plan_type < 1 ||
                 subscriptions[i].plan_type > 3);

        do {
            printf("Active devices: ");
            scanf("%d", &subscriptions[i].active_devices);

            if (subscriptions[i].active_devices < 0) {
                printf("Loi: So thiet bi khong duoc am.\n");
            }
        } while (subscriptions[i].active_devices < 0);

        do {
            printf("Days overdue: ");
            scanf("%d", &subscriptions[i].days_overdue);

            if (subscriptions[i].days_overdue < 0) {
                printf("Loi: So ngay no khong duoc am.\n");
            }
        } while (subscriptions[i].days_overdue < 0);

        subscriptions[i].account_status = 1;

        if (subscriptions[i].plan_type == 1) {
            subscriptions[i].max_devices = 1;
        } else if (subscriptions[i].plan_type == 2) {
            subscriptions[i].max_devices = 1;
        } else {
            subscriptions[i].max_devices = 5;
        }
    }

    for (i = 0; i < n; i++) {
        violation = 0;

        if (subscriptions[i].days_overdue > 3) {
            subscriptions[i].plan_type = 1;
            subscriptions[i].max_devices = 1;
            subscriptions[i].account_status = 0;
            downgraded_count++;
        }

        if (subscriptions[i].active_devices >
            subscriptions[i].max_devices) {
            violation = 1;
            violation_count++;
        }
    }

    printf("\n");
    printf("================================================================================\n");
    printf("                    SAAS SUBSCRIPTION AUDIT REPORT\n");
    printf("================================================================================\n");

    printf("%-8s %-20s %-12s %-15s %-12s %-15s\n",
           "User ID",
           "Account Name",
           "Plan",
           "Devices",
           "Overdue",
           "Status");

    printf("--------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        if (subscriptions[i].plan_type == 1) {
            if (subscriptions[i].account_status == 0) {
                printf("%-8d %-20s %-12s %d/%d           %-12d %-15s\n",
                       subscriptions[i].user_id,
                       subscriptions[i].account_name,
                       "Free",
                       subscriptions[i].active_devices,
                       subscriptions[i].max_devices,
                       subscriptions[i].days_overdue,
                       "Downgraded");
            } else {
                printf("%-8d %-20s %-12s %d/%d           %-12d %-15s\n",
                       subscriptions[i].user_id,
                       subscriptions[i].account_name,
                       "Free",
                       subscriptions[i].active_devices,
                       subscriptions[i].max_devices,
                       subscriptions[i].days_overdue,
                       "Active");
            }
        } else if (subscriptions[i].plan_type == 2) {
            if (subscriptions[i].active_devices >
                subscriptions[i].max_devices) {
                printf("%-8d %-20s %-12s %d/%d           %-12d %-15s\n",
                       subscriptions[i].user_id,
                       subscriptions[i].account_name,
                       "Individual",
                       subscriptions[i].active_devices,
                       subscriptions[i].max_devices,
                       subscriptions[i].days_overdue,
                       "Device Violation");
            } else {
                printf("%-8d %-20s %-12s %d/%d           %-12d %-15s\n",
                       subscriptions[i].user_id,
                       subscriptions[i].account_name,
                       "Individual",
                       subscriptions[i].active_devices,
                       subscriptions[i].max_devices,
                       subscriptions[i].days_overdue,
                       "Active");
            }
        } else {
            if (subscriptions[i].active_devices >
                subscriptions[i].max_devices) {
                printf("%-8d %-20s %-12s %d/%d           %-12d %-15s\n",
                       subscriptions[i].user_id,
                       subscriptions[i].account_name,
                       "Family",
                       subscriptions[i].active_devices,
                       subscriptions[i].max_devices,
                       subscriptions[i].days_overdue,
                       "Device Violation");
            } else {
                printf("%-8d %-20s %-12s %d/%d           %-12d %-15s\n",
                       subscriptions[i].user_id,
                       subscriptions[i].account_name,
                       "Family",
                       subscriptions[i].active_devices,
                       subscriptions[i].max_devices,
                       subscriptions[i].days_overdue,
                       "Active");
            }
        }
    }

    printf("================================================================================\n");
    printf("                  BAO CAO THONG KE VAN HANH\n");
    printf("================================================================================\n");
    printf("Tong so tai khoan da ra soat: %d\n", n);
    printf("So tai khoan bi ha cap ve Free: %d\n", downgraded_count);
    printf("So tai khoan vi pham gioi han thiet bi: %d\n", violation_count);
    printf("================================================================================\n");

    return 0;
}
