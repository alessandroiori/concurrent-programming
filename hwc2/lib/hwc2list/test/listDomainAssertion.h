/*
 * Autore: Valter Crescenzi e gli studenti del 
 * Corso di Programmazione Concorrente
 *  
 * listDomainAssertion.h
 *
 * asserzioni di dominio sulle liste
*/

#include "../list.h"
#ifndef LISTDOMAINASSERT_H_
#define LISTDOMAINASSERT_H_

void ASSERT_SINGLETONLIST(list_t *l, void *e);
void ASSERT_LIST_EQUAL2(list_t *l, void *e1, void *e2);

#endif /* LISTDOMAINASSERT_H_ */
