#include "country.h"

int read_string(char *str, size_t *len, size_t max_len)
{
    char tmp[max_len + 2];

    if (fgets(tmp, max_len + 2, stdin) == NULL)
        return ERROR_EMPTY_INPUT;

    tmp[strcspn(tmp, "\n")] = '\0';

    if (strlen(tmp) && strlen(tmp) > max_len)
        return ERROR_STR_LEN;

    *len = strlen(tmp);

    strncpy(str, tmp, *len + 1);

    return EXIT_SUCCESS;
}

// READ

int read_excursion(excursion_t *excursion)
{
    if (scanf("%d", &excursion->obj_count) != 1 && excursion->obj_count < 0)
        return ERROR_WRONG_OBJ_COUNT;

    if (scanf("%d", &excursion->obj_main_type) != 1 && (excursion->obj_main_type < 1 || excursion->obj_main_type > 3))
        return ERROR_WRONG_OBJ_TYPE;

    return EXIT_SUCCESS;
}

int read_beach(beach_t *beach)
{
    if (scanf("%d", &beach->main_season) != 1 && (beach->main_season < 1 || beach->main_season > 4))
        return ERROR_WRONG_SEASON;

    if (scanf("%lf", &beach->air_temp) != 1)
        return ERROR_WRONG_AIR_TEMP;

    if (scanf("%lf", &beach->water_temp) != 1)
        return ERROR_WRONG_WATER_TEMP;
    return EXIT_SUCCESS;
}

int read_sports(sports_t *sports)
{
    if (scanf("%d", &sports->sport_type) != 1 && (sports->sport_type < 1 || sports->sport_type > 4))
        return ERROR_WRONG_SPORTS_TYPE;
    return EXIT_SUCCESS;
}

int read_tourism(country_t *country)
{
    int rc = EXIT_SUCCESS;
    switch (country->tourism_type)
    {
    case EXCURSION:
        rc = read_excursion(&country->tourism.excursion);
        break;
    case BEACH:
        rc = read_beach(&country->tourism.beach);
        break;
    case SPORTS:
        rc = read_sports(&country->tourism.sports);
        break;
    }
    return rc;
}

int read_visa(country_t *country)
{
    if (scanf("%d", &country->is_need_visa) != 1 
        && (country->is_need_visa < 0 || country->is_need_visa > 1))
        return ERROR_WRONG_VISA_FLAG;
    return EXIT_SUCCESS;
}

int read_flight_time(country_t *country)
{
    if (scanf("%d", &country->flight_time.hours) != 1 && country->flight_time.hours < 0)
        return ERROR_WRONG_HOURS;
    if (scanf("%d", &country->flight_time.minute) != 1 
        && (country->flight_time.minute < 0 || country->flight_time.minute > 59))
        return ERROR_WRONG_MINUTES;
    return EXIT_SUCCESS;
}

int read_min_rest_cost(country_t *country)
{
    if (scanf("%d", &country->min_rest_cost) != 1 && country->min_rest_cost < 0)
        return ERROR_WRONG_COST;
    return EXIT_SUCCESS;
}

int read_tourism_type(country_t *country)
{
    if (scanf("%d", &country->tourism_type) != 1 
        && (country->tourism_type < 1 || country->tourism_type > 3))
        return ERROR_WRONG_TOURISM_TYPE;
    return EXIT_SUCCESS;
}

int read_country(country_t *country)
{
    int rc = EXIT_SUCCESS;
    do
    {
        rc = read_string(country->name, &country->name_len, MAX_NAME_LEN);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while(rc != EXIT_SUCCESS);

    do
    {
        rc = read_string(country->capital, &country->capital_len, MAX_CAPITAL_LEN);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_string(country->continent, &country->continent_len, MAX_CONTINENT_LEN);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_visa(country);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_flight_time(country);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_min_rest_cost(country);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_tourism_type(country);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_tourism(country);
        if (rc != EXIT_SUCCESS)
            printf("ERROR NUMBER: %d", rc);
    } while (rc != EXIT_SUCCESS);

    return EXIT_SUCCESS;
}

//PRINT
void print_excursion(excursion_t *excursion)
{
    printf("Objects count: %d\n", excursion->obj_count);

    printf("Objects main type: ");
    switch (excursion->obj_main_type)
    {
    case NATURE:
        printf("nature\n");
        break;
    case HISTORY:
        printf("history\n");
        break;
    case ART:
        printf("art\n");
        break;
    }
}

void print_beach(beach_t *beach)
{
    printf("Main season: ");
    switch (beach->main_season)
    {
    case WINTER:
        printf("winter\n");
        break;
    case SPRING:
        printf("spring\n");
        break;
    case SUMMER:
        printf("summer\n");
        break;
    case AUTUMN:
        printf("autumn\n");
        break;
    }

    printf("Air temp: %.6lf\n", beach->air_temp);
    printf("Water temp: %.6lf\n", beach->water_temp);
}

void print_sports(sports_t *sports)
{
    printf("Sport type: ");
    switch (sports->sport_type)
    {
    case DOWNHILL_SKIING:
        printf("downhill skiing\n");
        break;
    case SURFING:
        printf("surfing\n");
        break;
    case CLIMBING:
        printf("climbing\n");
        break;
    case RAFTING:
        printf("rafting\n");
        break;
    }
}

void print_country(country_t *country)
{
    printf("Name: %s\n", country->name);
    printf("Capital: %s\n", country->capital);
    printf("Continent: %s\n", country->continent);
    printf("Need visa: %s\n", country->is_need_visa? "Yes": "No");
    printf("Flight time: %d:%d\n", country->flight_time.hours, country->flight_time.minute);
    printf("Min cost: %d\n", country->min_rest_cost);
    printf("Tourism type: ");
    switch (country->tourism_type)
    {
        case EXCURSION:
            printf("excursion\n");
            print_excursion(&country->tourism.excursion);
            break;
        case BEACH:
            printf("beach\n");
            print_beach(&country->tourism.beach);
            break;
        case SPORTS:
            printf("sports\n");
            print_sports(&country->tourism.sports);
            break;
    }
}
