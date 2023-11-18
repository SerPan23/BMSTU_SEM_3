// Вар №7
#include "my_menu.h"

#include "queue_list.h"
#include "queue_array.h"

int main(void)
{
    int rc = menu();
    return rc;

    // int rc;
    // size_t n = 5;

    // printf("-----LIST QUEUE-----\n\n");
    // queue_list_t queue_list;
    // rc = queue_list_init(&queue_list);
    // if (rc != EXIT_SUCCESS)
    // {
    //     printf("ERROR: err num is %d\n", rc);
    //     return rc;
    // }

    // for (size_t i = 0; i < n; i++)
    // {
        // list_node_t *tmp;
        // list_node_init(&tmp);
        // rc = queue_list_push(&queue_list, tmp);
        // if (rc != EXIT_SUCCESS)
        // {
        //     printf("ERROR: err num is %d\n", rc);
        //     return rc;
        // }
    // }

    // printf("%zu\n", queue_list.size);
    // queue_list_print(&queue_list);
    // printf("\n");

    // queue_list_pop(&queue_list, NULL);

    
    // printf("*%zu\n", queue_list.size);
    // queue_list_print(&queue_list);
    // printf("\n");



    // list_node_t *tmp_list;
    // list_node_init(&tmp_list);
    // rc = queue_list_push(&queue_list, tmp_list);
    // if (rc != EXIT_SUCCESS)
    // {
    //     printf("ERROR: err num is %d\n", rc);
    //     return rc;
    // }

    // printf("*%zu\n", queue_list.size);
    // queue_list_print(&queue_list);
    // printf("\n");

    

    // queue_list_free(&queue_list);






    // printf("\n\n-----ARRAY QUEUE-----\n\n");

    // queue_array_t queue_arr;
    // queue_array_init(&queue_arr);

    // for (size_t i = 0; i < n; i++)
    // {
        // array_element_t tmp;
        // array_el_init(&tmp);
        // rc = queue_array_push(&queue_arr, &tmp);
        // if (rc != EXIT_SUCCESS)
        // {
        //     printf("ERROR: err num is %d\n", rc);
        //     return rc;
        // }
    // }

    // printf("*%zu\n", queue_arr.size);
    // // printf("Pin: %zu | Pout: %zu\n", queue_arr.pin, queue_arr.pout);
    // queue_array_print(&queue_arr);


    // queue_array_pop(&queue_arr, NULL);
    // printf("\nPOP!\n");


    // printf("\n");
    // printf("*%zu\n", queue_arr.size);
    // // printf("Pin: %zu | Pout: %zu\n", queue_arr.pin, queue_arr.pout);
    // queue_array_print(&queue_arr);



    // array_element_t tmp_arr;
    // array_el_init(&tmp_arr);
    // rc = queue_array_push(&queue_arr, &tmp_arr);
    // if (rc != EXIT_SUCCESS)
    // {
    //     printf("ERROR: err num is %d\n", rc);
    //     return rc;
    // }


    // printf("\n");
    // printf("*%zu\n", queue_arr.size);
    // // printf("Pin: %zu | Pout: %zu\n", queue_arr.pin, queue_arr.pout);
    // queue_array_print(&queue_arr);

    // queue_array_pop(&queue_arr, NULL);
    // printf("\nPOP!\n");


    // printf("\n");
    // printf("*%zu\n", queue_arr.size);
    // // printf("Pin: %zu | Pout: %zu\n", queue_arr.pin, queue_arr.pout);
    // queue_array_print(&queue_arr);

    // array_element_t tmp_arr2;
    // array_el_init(&tmp_arr2);
    // rc = queue_array_push(&queue_arr, &tmp_arr2);
    // if (rc != EXIT_SUCCESS)
    // {
    //     printf("ERROR: err num is %d\n", rc);
    //     return rc;
    // }

    // printf("\n");
    // printf("*%zu\n", queue_arr.size);
    // // printf("Pin: %zu | Pout: %zu\n", queue_arr.pin, queue_arr.pout);
    // queue_array_print(&queue_arr);

    // return 0;
}
