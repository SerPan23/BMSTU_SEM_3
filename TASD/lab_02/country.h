#ifndef COUNTRY_H
#define COUNTRY_H

#include "useful_funcs.h"

typedef struct
{
    int hours;
    int minute;
} flight_time_t;

typedef enum
{
    EXCURSION = 1,
    BEACH,
    SPORTS
} tourism_enum;

// экскурсионный – количество объектов,
// их основной вид(природа, история, искусство);
typedef enum
{
    NATURE = 1,
    HISTORY,
    ART
} obj_main_type_enum;

typedef struct
{
    int obj_count;
    obj_main_type_enum obj_main_type;
} excursion_t;

// пляжный – основной сезон,
// температура воздуха и воды;
typedef enum
{
    WINTER = 1,
    SPRING,
    SUMMER,
    AUTUMN
} main_season_enum;

typedef struct
{
    main_season_enum main_season;
    double air_temp;
    double water_temp;
} beach_t;

// спортивный – вид спорта(горные лыжи,
//  серфинг, восхождения, сплав))
typedef enum
{
    DOWNHILL_SKIING = 1,
    SURFING,
    CLIMBING,
    RAFTING
} sports_enum;

typedef union
{
    excursion_t excursion;
    beach_t beach;
    sports_enum sport_type;
} tourism_union;

typedef enum
{
    EURASIA = 1,
    AFRICA,
    NORTH_AMERICA,
    SOUTH_AMERICA,
    AUSTRALIA,
    ANTARCTICA
} continent_enum;

typedef struct
{
    char name[MAX_STR_LEN + 1];
    size_t name_len;
    char capital[MAX_STR_LEN + 1];
    size_t capital_len;
    continent_enum continent;
    size_t continent_len;
    int is_need_visa;
    flight_time_t flight_time;
    int min_rest_cost;
    tourism_enum tourism_type;
    tourism_union tourism;
} country_t;

int read_country(country_t *country, FILE *input);
void print_country(country_t *country, FILE *output);

char *get_obj_main_type_str(obj_main_type_enum type);
char *get_season_str(main_season_enum type);
char *get_sports_str(sports_enum type);
char *get_str_continent(int continent);

int read_continent(continent_enum *continent, FILE *input);
int read_sports(sports_enum *sport_type, FILE *input);

int cmp_country_cost(const void *p, const void *q);

#endif
