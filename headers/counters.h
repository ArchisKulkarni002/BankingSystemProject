
#ifndef COUNTERS_H
#define COUNTERS_H

#define C_CUSTOMER 1
#define C_EMPLOYEE 2
#define C_MANAGER 3
#define C_ADMIN 4
#define C_LOAN 5
#define C_FEEDBACK 6

void get_counter_file(int id, char* filepath, int size);
int get_new_count(int id);

#endif // COUNTERS_H