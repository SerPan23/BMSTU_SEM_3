#include "country.h"

// READ
int read_excursion(excursion_t *excursion, FILE *input)
{
    if (input == stdin)
        printf("Enter obj count:\n");
    if (read_int(&excursion->obj_count, MAX_STR_LEN, input) != EXIT_SUCCESS && excursion->obj_count < 0)
        return ERROR_WRONG_OBJ_COUNT;

    if (input == stdin)
        printf("Enter obj main type:\n1) Nature\n2) History\n3) Art\n");
    int tmp;
    if (read_int(&tmp, MAX_STR_LEN, input) != EXIT_SUCCESS && (tmp < 1 || tmp > 3))
        return ERROR_WRONG_OBJ_TYPE;
    excursion->obj_main_type = tmp;
    return EXIT_SUCCESS;
}

int read_beach(beach_t *beach, FILE *input)
{
    int tmp;
    if (input == stdin)
        printf("Enter main season:\n1) Winter\n2) Spring\n3) Summer\n4) Autumn\n");
    if (read_int(&tmp, MAX_STR_LEN, input) != EXIT_SUCCESS && (tmp < 1 || tmp > 4))
        return ERROR_WRONG_SEASON;

    beach->main_season = tmp;

    if (input == stdin)
        printf("Enter air temp:\n");
    if (read_double(&beach->air_temp, MAX_STR_LEN, input) != EXIT_SUCCESS)
        return ERROR_WRONG_AIR_TEMP;

    if (input == stdin)
        printf("Enter water temp:\n");
    if (read_double(&beach->water_temp, MAX_STR_LEN, input) != EXIT_SUCCESS)
        return ERROR_WRONG_WATER_TEMP;
    return EXIT_SUCCESS;
}

int read_sports(sports_enum *sport_type, FILE *input)
{
    int tmp;
    if (input == stdin)
        printf("Choose sport type:\n1) Downhill skiing\n2) Surfing\n3) Climbing\n4) Rafting\n");
    if (read_int(&tmp, MAX_STR_LEN, input) != EXIT_SUCCESS && (tmp < 1 || tmp > 4))
        return ERROR_WRONG_SPORTS_TYPE;
    *sport_type = tmp;
    return EXIT_SUCCESS;
}

int read_tourism(country_t *country, FILE *input)
{
    int rc = EXIT_SUCCESS;
    switch (country->tourism_type)
    {
    case EXCURSION:
        rc = read_excursion(&country->tourism.excursion, input);
        break;
    case BEACH:
        rc = read_beach(&country->tourism.beach, input);
        break;
    case SPORTS:
        rc = read_sports(&country->tourism.sport_type, input);
        break;
    }
    return rc;
}

int read_continent(continent_enum *continent, FILE *input)
{
    int tmp;
    if (input == stdin)
        printf("Choose continent:\n1) Eurasia\n2) Africa\n3) North America\n"
               "4) South America\n5) Australia\n6) Antarctica\n");
    if (read_int(&tmp, MAX_STR_LEN, input) != EXIT_SUCCESS && (tmp < 0 || tmp > 6))
        return ERROR_WRONG_CONTINENT;

    *continent = tmp;

    return EXIT_SUCCESS;
}

int read_visa(int *is_need_visa, FILE *input)
{
    if (input == stdin)
        printf("Choose:\n0) Do not need visa\n1) Need visa\n");
    if (read_int(is_need_visa, MAX_STR_LEN, input) != EXIT_SUCCESS && (*is_need_visa < 0 || *is_need_visa > 1))
        return ERROR_WRONG_VISA_FLAG;
    return EXIT_SUCCESS;
}

int read_flight_time(flight_time_t *flight_time, FILE *input)
{
    if (input == stdin)
        printf("Enter flight hour:\n");
    if (read_int(&flight_time->hours, MAX_STR_LEN, input) != EXIT_SUCCESS && flight_time->hours < 0)
        return ERROR_WRONG_HOURS;

    if (input == stdin)
        printf("Enter flight minutes:\n");
    if (read_int(&flight_time->minute, MAX_STR_LEN, input) != EXIT_SUCCESS && (flight_time->minute < 0 || flight_time->minute > 59))
        return ERROR_WRONG_MINUTES;
    return EXIT_SUCCESS;
}

int read_min_rest_cost(int *min_rest_cost, FILE *input)
{
    if (input == stdin)
        printf("Enter min cost:\n");
    if (read_int(min_rest_cost, MAX_STR_LEN, input) != EXIT_SUCCESS && *min_rest_cost < 0)
        return ERROR_WRONG_COST;
    return EXIT_SUCCESS;
}

int read_tourism_type(tourism_enum *tourism_type, FILE *input)
{
    int tmp;
    if (input == stdin)
        printf("Choose tourism type:\n1) Excursion\n2) Beach\n3) Sport\n");
    if (read_int(&tmp, MAX_STR_LEN, input) != EXIT_SUCCESS && (tmp < 1 || tmp > 3))
        return ERROR_WRONG_TOURISM_TYPE;

    *tourism_type = tmp;

    return EXIT_SUCCESS;
}

int read_country(country_t *country, FILE *input)
{
    int rc = EXIT_SUCCESS;
    do
    {
        if (input == stdin)
            printf("Enter name:\n");
        rc = read_string(country->name, &country->name_len, MAX_STR_LEN, input);
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read name (code: %d)", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    do
    {
        if (input == stdin)
            printf("Enter capital:\n");
        rc = read_string(country->capital, &country->capital_len, MAX_STR_LEN, input);   
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read capital (code: %d)", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    do
    {
        if (input == stdin)
            printf("Enter continent:\n");
        rc = read_continent(&country->continent, input);
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read continent (code: %d)", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_visa(&country->is_need_visa, input);
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read is need visa (code: %d)", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_flight_time(&country->flight_time, input);
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read flight time (code: %d)", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_min_rest_cost(&country->min_rest_cost, input);
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read min rest cost (code: %d)", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_tourism_type(&country->tourism_type, input);
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read tourism type (code: %d)\n", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    do
    {
        rc = read_tourism(country, input);
        if (rc != EXIT_SUCCESS)
        {
            if (input == stdin)
                printf("ERROR: read tourism (code: %d)", rc);
            else
                return rc;
        }
    } while (rc != EXIT_SUCCESS);

    return EXIT_SUCCESS;
}

//PRINT
void print_excursion(excursion_t *excursion, FILE *output)
{
    fprintf(output, "Objects count: %d\n", excursion->obj_count);

    fprintf(output, "Objects main type: ");
    switch (excursion->obj_main_type)
    {
    case NATURE:
        fprintf(output, "nature\n");
        break;
    case HISTORY:
        fprintf(output, "history\n");
        break;
    case ART:
        fprintf(output, "art\n");
        break;
    }
}

void print_beach(beach_t *beach, FILE *output)
{
    fprintf(output, "Main season: ");
    switch (beach->main_season)
    {
    case WINTER:
        fprintf(output, "winter\n");
        break;
    case SPRING:
        fprintf(output, "spring\n");
        break;
    case SUMMER:
        fprintf(output, "summer\n");
        break;
    case AUTUMN:
        fprintf(output, "autumn\n");
        break;
    }

    fprintf(output, "Air temp: %.6lf\n", beach->air_temp);
    fprintf(output, "Water temp: %.6lf\n", beach->water_temp);
}

void print_sports(sports_enum *sport_type, FILE *output)
{
    fprintf(output, "Sport type: ");
    switch (*sport_type)
    {
    case DOWNHILL_SKIING:
        fprintf(output, "downhill skiing\n");
        break;
    case SURFING:
        fprintf(output, "surfing\n");
        break;
    case CLIMBING:
        fprintf(output, "climbing\n");
        break;
    case RAFTING:
        fprintf(output, "rafting\n");
        break;
    }
}

char *get_str_continent(int continent)
{
    switch (continent)
    {
    case EURASIA:
        return "Eurasia";
        break;
    case AFRICA:
        return "Africa";
        break;
    case NORTH_AMERICA:
        return "North America";
        break;
    case SOUTH_AMERICA:
        return "South America";
        break;
    case AUSTRALIA:
        return "Australia";
        break;
    case ANTARCTICA:
        return "Antarctica";
        break;
    }
    return "";
}

void print_country(country_t *country, FILE *output)
{
    fprintf(output, "Name: %s\n", country->name);
    fprintf(output, "Capital: %s\n", country->capital);
    fprintf(output, "Continent: %s\n", get_str_continent(country->continent));
    fprintf(output, "Need visa: %s\n", country->is_need_visa? "Yes": "No");
    fprintf(output, "Flight time: %d:%d\n", country->flight_time.hours, country->flight_time.minute);
    fprintf(output, "Min cost: %d\n", country->min_rest_cost);
    fprintf(output, "Tourism type: ");
    switch (country->tourism_type)
    {
    case EXCURSION:
        fprintf(output, "excursion\n");
        print_excursion(&country->tourism.excursion, output);
        break;
    case BEACH:
        fprintf(output, "beach\n");
        print_beach(&country->tourism.beach, output);
        break;
    case SPORTS:
        fprintf(output, "sports\n");
        print_sports(&country->tourism.sport_type, output);
        break;
    }
}

int cmp_country_cost(const void *p, const void *q)
{
    const country_t *a = p;
    const country_t *b = q;
    return a->min_rest_cost - b->min_rest_cost;
}
