#ifndef CHECK_STATS_H
#define CHECK_STATS_H

#define MAX_CATEGORIES 16 // To be updated whenever needed

typedef struct {
    char name[64];
    int total;
    int passed;
    int failed;
} category_stats_t;

extern int total_checks, passed_checks, failed_checks;
extern category_stats_t categories[MAX_CATEGORIES];
extern int num_categories, current_category;

#define EXEC_CHECK_AND_COUNT(desc, result_ptr, log_msg, hi_msg) \
    do { \
        int result = exec_check(desc, result_ptr, log_msg, hi_msg); \
        total_checks++; \
        categories[current_category].total++; \
        if (result) { \
            failed_checks++; \
            categories[current_category].failed++; \
        } else { \
            passed_checks++; \
            categories[current_category].passed++; \
        } \
    } while (0)

#define ENTER_CATEGORY(cat_name) \
    do { \
        if (num_categories < MAX_CATEGORIES) { \
            strncpy(categories[num_categories].name, cat_name, sizeof(categories[num_categories].name)-1); \
            categories[num_categories].name[sizeof(categories[num_categories].name)-1] = '\0'; \
            categories[num_categories].total = 0; \
            categories[num_categories].passed = 0; \
            categories[num_categories].failed = 0; \
            current_category = num_categories++; \
        } \
        print_check_group(cat_name); \
    } while (0)

#endif // CHECK_STATS_H