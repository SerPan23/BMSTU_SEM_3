#include "menu.h"

int main(void)
{
    table_t table;
    table.rows_count = 0;
    menu(&table);
    // while (1)
    // {
    //     // int num;
    //     // int rc = read_int(&num, MAX_STR_LEN, stdin);
    //     // printf("num = %d (code: %d)\n", num, rc);
    //     // char tmp[MAX_STR_LEN + 1];
    //     // size_t tmp_l;
    //     // int rc_s = read_string(tmp, &tmp_l, MAX_STR_LEN, stdin) == EXIT_SUCCESS;
    //     // int rc_int = is_int(tmp, tmp_l);
    //     // int read_count = sscanf(tmp, "%d", &num);
    //     // printf("(rc_s = %d | rc_int = %d | read_count = %d)\tnum = %d\n", rc_s, rc_int, read_count, num);
    // }
    return 0;
}
