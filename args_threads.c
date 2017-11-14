//
// Created by Alessandro Iori on 14/11/2017.
//

/**
 * args_thread.c sample project to give args to start_routine function
 */

#include <stdio.h>
#include <pthread.h>


/* Parameters to print_function.  */
struct char_print_parms {
    char character; // char to printgit
    int count;      // number of times to print it.
};

/* Prints a number of characters to stderr, as given by
   PARAMETERS, which is a pointer to a
   struct char_print_parms.  */
void* char_print (void* parameters) {
    /* Cast the cookie pointer to the right type.  */
    struct char_print_parms* p;
    p = (struct char_print_parms*)parameters;

    int i;
    for (i = 0; i < p->count; ++i)
        fputc (p->character, stderr);
    return NULL;
}

int main(void)
{
    pthread_t thread1_id, thread2_id;
    struct char_print_parms thread1_args, thread2_args;

    /* Create a new thread to print 30000 x's. */
    thread1_args.character = 'x';
    thread1_args.count = 30;
    pthread_create(&thread1_id,NULL,&char_print,&thread1_args);

    /* Create a new thread to print 20000 o's. */
    thread2_args.character = 'o';
    thread2_args.count = 20;
    pthread_create(&thread2_id,NULL,&char_print,&thread2_args);

    /* Make sure the first thread has finished.  */
    pthread_join (thread1_id, NULL);
    /* Make sure the second thread has finished.  */
    pthread_join (thread2_id, NULL);
    return 0; /* Now we can safely return.  */
}
