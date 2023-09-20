#ifndef COUNTRY_H
#define COUNTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <math.h>

#define MAX_NAME_LEN 100
#define MAX_CAPITAL_LEN 100
#define MAX_CONTINENT_LEN 30

#define ERROR_EMPTY_INPUT 1
#define ERROR_STR_LEN 2
#define ERROR_WRONG_VISA_FLAG 3
#define ERROR_WRONG_HOURS 4
#define ERROR_WRONG_MINUTES 5
#define ERROR_WRONG_COST 6
#define ERROR_WRONG_TOURISM_TYPE 7
#define ERROR_WRONG_OBJ_COUNT 8
#define ERROR_WRONG_OBJ_TYPE 9
#define ERROR_WRONG_SEASON 10
#define ERROR_WRONG_AIR_TEMP 11
#define ERROR_WRONG_WATER_TEMP 12
#define ERROR_WRONG_SPORTS_TYPE 13

typedef struct
{
    int hours;
    int minute;
} time_t;

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

typedef struct
{
    sports_enum sport_type;
} sports_t;

typedef union
{
    excursion_t excursion;
    beach_t beach;
    sports_t sports;
} tourism_union;

typedef struct
{
    char name[MAX_NAME_LEN];
    size_t name_len;
    char capital[MAX_CAPITAL_LEN];
    size_t capital_len;
    char continent[MAX_CAPITAL_LEN];
    size_t continent_len;
    int is_need_visa;
    time_t flight_time;
    int min_rest_cost;
    tourism_enum tourism_type;
    tourism_union tourism;
} country_t;

int read_country(country_t *country);
void print_country(country_t *country);

#endif
