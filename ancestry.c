#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ancestry.h"

struct person_t *make_person(char *first_name, char *last_name, int year_born) {
    // TODO: Allokér plads til en `struct person_t`.
    // TODO: Allokér også plads til kopier af `first_name` og `last_name`.
    // TODO: Kopiér indholdet fra `first_name` og `last_name` over i kopierne.
    // TODO: Husk at gøre plads til både alle tegnene i navnene + 1 NUL-byte.

    struct person_t *person = malloc(sizeof(struct person_t));
    char *firstNameCopy = malloc(strlen(first_name) + 1);
    char *lastNameCopy = malloc(strlen(last_name) + 1);

    person->first_name = strcpy(firstNameCopy,first_name);
    person->last_name = strcpy(lastNameCopy,last_name);
    person->year_born = year_born;
    return person;
}

void free_person(struct person_t *person) {
    // TODO: Der skal være et free()-kald for hver malloc() i make_person().
    // TODO: Du må gerne sætte `first_name` og `last_name` til NULL *EFTER* de er free()'et.
    /// lets emancipate some ram.
    free(person->first_name);
    person->first_name = NULL;
    free(person->last_name);
    person->last_name = NULL;
    free(person);
    person = NULL;

}

struct ancestry_node_t *make_tree(struct person_t *person) {
    // TODO: Allokér plads til en `struct ancestry_node_t`.
    // TODO: Sæt `person` til input-personen.
    // TODO: Sæt `mom` og `dad` til NULL.

    struct ancestry_node_t  *branch = malloc(sizeof(struct ancestry_node_t));
    branch->person = person;
    //hvorfor null ?
    branch->mom = NULL;
    branch->dad = NULL;
    return branch;
}

bool add_mom(struct ancestry_node_t *child_node, struct person_t *mom_person) {
    
    // TODO: Hvis der allerede er en mor-stamtavle, skal funktionen fejle.
    // TODO: Hvis ikke, skal `mom_person` indsættes i en `mom_node` som først skal allokeres.
    if (child_node->mom == NULL) {

        struct ancestry_node_t *mom_node = malloc(sizeof(struct ancestry_node_t));
        struct person_t *mom_copy = malloc(sizeof(struct person_t));

        char *firstNameCopy = malloc(strlen(mom_person->first_name) + 1);
        char *lastNameCopy = malloc(strlen(mom_person->last_name) + 1);

        mom_copy->first_name =  strcpy(firstNameCopy,mom_person->first_name);
        mom_copy->last_name =  strcpy(lastNameCopy,mom_person->last_name);

        mom_copy->year_born = mom_person->year_born;

        mom_node->person = mom_copy;
        //hvorfor null ? 
        mom_node->dad = NULL;
        mom_node->mom = NULL;

        child_node->mom = mom_node;
        return true;
    }
    return false;
}

bool add_dad(struct ancestry_node_t *child_node, struct person_t *dad_person) {
    // TODO: Hvis der allerede er en far-stamtavle, skal funktionen fejle.
    // TODO: Hvis ikke, skal `dad_person` indsættes i en `dad_node` som først skal allokeres.
    if (child_node->dad == NULL) {
        struct ancestry_node_t *dad_node = malloc(sizeof(struct ancestry_node_t));

        struct person_t *dad_copy = malloc(sizeof(struct person_t));
        char *firstNameCopy = malloc(strlen(dad_person->first_name) + 1);
        char *lastNameCopy = malloc(strlen(dad_person->last_name) + 1);


        dad_copy->first_name =  strcpy(firstNameCopy,dad_person->first_name);
        dad_copy->last_name =  strcpy(lastNameCopy,dad_person->last_name);

        dad_copy->year_born = dad_person->year_born;

        dad_node->person = dad_copy;
        dad_node->dad = NULL;
        dad_node->mom = NULL;
        child_node->dad = dad_node;
        return true;
    }
    printf("who's your daddy %s\n",child_node->dad->person->first_name);
    return false;
}

void free_tree(struct ancestry_node_t *node) {
    // TODO: Kald `free_person()` på personen i noden.
    // TODO: Kald `free_tree()` på begge forældre-stamtræer.
    // TODO: Sæt pointerne til NULL efter de er free()'et.
    while (node->dad != NULL) {
        free_tree(node->dad);
        printf("hedder: %s\n", node->dad->person->first_name);
        node->dad = NULL;
    }
    while (node->mom != NULL) {
        free_tree(node->mom);
        printf("hedder: %s\n", node->mom->person->first_name);
        node->mom = NULL;
    }
    free_person(node->person);
    free(node);


}

void print_tree_recursive(struct ancestry_node_t *node, char *prefix, bool is_last) {
    if (node == NULL) {
        return;
    }

    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");
    printf("%s %s\n", node->person->first_name, node->person->last_name);

    char new_prefix[1000];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    if (node->mom != NULL && node->dad != NULL) {
        print_tree_recursive(node->mom, new_prefix, false);
        print_tree_recursive(node->dad, new_prefix, true);
    } else if (node->mom != NULL) {
        print_tree_recursive(node->mom, new_prefix, true);
    } else if (node->dad != NULL) {
        print_tree_recursive(node->dad, new_prefix, true);
    }
}

void print_tree(struct ancestry_node_t *node) {
    print_tree_recursive(node, "", true);
}
