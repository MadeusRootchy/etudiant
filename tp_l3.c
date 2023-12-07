#include <stdio.h>
#include <stdlib.h>

typedef struct etudiant{
    int age;
    struct etudiant* suiv;
} Etudiant;

Etudiant* creer_liste() {
    int nb;
    char rep;
    int compteur=0;
    Etudiant* tete;
    Etudiant* nouv;
    Etudiant* dernier;
    tete = NULL;
    do {
         if (compteur >= 106) {
            printf("Limite d'etudiants atteinte (106).\n");
            break; 
        }

        printf("Entrer l'age de l'etudiant :\n");
        scanf("%d", &nb);
        nouv = malloc(sizeof(Etudiant));
        nouv->age = nb;
        nouv->suiv = NULL;
        if (tete == NULL) {
            tete = nouv;
            dernier = nouv;
        } else {
            dernier->suiv = nouv;
            dernier = nouv;
        }
         compteur++;
     printf("Voulez-vous continuer? (O pour Oui, N pour Non): ");
    scanf(" %c", &rep); 
    while (rep !='O' && rep != 'o' && rep != 'n' && rep != 'N') {
        printf("Vous devez rentrer O ou N: ");
        scanf(" %c", &rep); 
    }

    } while (rep == 'O' || rep == 'o');
    return tete;
}


Etudiant* trier_liste_decroissant(Etudiant* tete) {
    Etudiant *p, *q;
    int temp;

    for (p = tete; p != NULL; p = p->suiv) {
        for (q = p->suiv; q != NULL; q = q->suiv) {
            if (p->age < q->age) {
                
                temp = p->age;
                p->age = q->age;
                q->age = temp;
            }
        }
    }

    return tete;
}

Etudiant* afficher_liste(Etudiant* tete) {
    Etudiant* p;
    p = tete;
    if (tete == NULL) {
        printf("Liste vide\n");
    } else {
        printf("Tete->");
        while (p != NULL) {
            printf("%d->", p->age);
            p = p->suiv;
        }
        printf("End");
    }
    return 0;
}

void afficher_liste_ordre_decroissant(Etudiant* tete) {
    Etudiant* p;
    p = tete;
    if (tete == NULL) {
        printf("Liste vide\n");
    } else {
        printf("Tete->");
        while (p != NULL) {
            printf("%d->", p->age);
            p = p->suiv;
        }
        printf("End");
    }
}

int CalculSomme(Etudiant* tete) {
    int somme = 0;
    Etudiant* p = tete;

    while (p != NULL) {
        somme += p->age;
        p = p->suiv;
    }

    return somme;
}

int AfficherElementPositionR(Etudiant* tete, int position) {
    Etudiant* p = tete;
    int index = 0;

    while (p != NULL) {
        if (index == position) {
            printf("\nl'element a la position %d : %d\n", position, p->age);
            return p->age;
        }
        p = p->suiv;
        index++;
    }

    printf("\nelement innexistant.\n");
    return -1;
}

Etudiant* SupprimerElementPositionR(Etudiant* tete, int position) {
    Etudiant* courant = tete;
    Etudiant* precedent = NULL;
    int index = 0;

    while (courant != NULL && index != position) {
        precedent = courant;
        courant = courant->suiv;
        index++;
    }

    if (courant == NULL) {
        printf("\nPosition invalide.\n");
        return tete;
    }

    if (precedent == NULL) {
        tete = courant->suiv;
    } else {
        precedent->suiv = courant->suiv;
    }

    free(courant);

    printf("\nElement a la position %d supprime.\n", position);

    return tete;
}

Etudiant* InsererElementPositionR(Etudiant* tete, int position, int age) {
    Etudiant* nouvel_element = malloc(sizeof(Etudiant));
    nouvel_element->age = age;
    nouvel_element->suiv = NULL;

    if (position == 0) {
        nouvel_element->suiv = tete;
        tete = nouvel_element;
    } else {
        Etudiant* courant = tete;
        Etudiant* precedent = NULL;
        int index = 0;

        while (courant != NULL && index != position) {
            precedent = courant;
            courant = courant->suiv;
            index++;
        }

        if (courant == NULL && index != position) {
            printf("\nPosition invalide.\n");
            free(nouvel_element);
            return tete;
        }

        nouvel_element->suiv = courant;
        precedent->suiv = nouvel_element;
    }

    printf("\nElement a la position %d insere.\n", position);

    return tete;
}

int CompterOccurrenceV(Etudiant* tete, int valeur) {
    Etudiant* p = tete;
    int occurrences = 0;

    while (p != NULL) {
        if (p->age == valeur) {
            occurrences++;
        }
        p = p->suiv;
    }

    return occurrences;
}

void LibererListe(Etudiant* tete) {
    Etudiant* courant = tete;
    Etudiant* suivant;

    while (courant != NULL) {
        suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }
}

int CompterEtudiantsMoins18(Etudiant* tete) {
    int count = 0;
    Etudiant* p = tete;

    while (p != NULL) {
        if (p->age < 18) {
            count++;
        }
        p = p->suiv;
    }

    return count;
}


int main() {
   Etudiant* liste;
    Etudiant* liste_decroissant;
    liste = creer_liste();
    liste_decroissant = trier_liste_decroissant(liste);
    afficher_liste_ordre_decroissant(liste_decroissant);
    int choix_menu;
    int position; 
    do {
        printf("\nMenu :\n");
        printf("1. Calculer la somme des ages\n");
        printf("2. Afficher l'element a la position R\n");
        printf("3. Supprimer l'element a la position R\n");
        printf("4. Inserer un nouvel element a la position R\n");
        printf("5. Compter les occurrences d'une valeur V\n");
         printf("6. Compter le nombre d'etudiants ayant moins de 18 ans\n");
        printf("7. Liberer la liste\n");

        printf("Choix : ");
        scanf("%d", &choix_menu);

        switch (choix_menu) {
            case 1:
                printf("\nSomme des ages : %d\n", CalculSomme(liste_decroissant));
                break;

            case 2:
                printf("\nEntrer la position R : ");
                scanf("%d", &position);
                AfficherElementPositionR(liste_decroissant, position-1);
                break;

            case 3:
                printf("\nEntrer la position R : ");
                scanf("%d", &position);
                liste = SupprimerElementPositionR(liste_decroissant, position-1);
                afficher_liste(liste);
                break;

            case 4:
                printf("\nEntrer la position R : ");
                scanf("%d", &position);
                int nouvel_age;
                printf("Entrer l'age du nouvel element : ");
                scanf("%d", &nouvel_age);
                liste = InsererElementPositionR(liste_decroissant, position-1, nouvel_age);
                afficher_liste(liste);
                break;

            case 5:
                int valeur;
                printf("Entrer la valeur V : ");
                scanf("%d", &valeur);
                int occurrences = CompterOccurrenceV(liste_decroissant, valeur);
                printf("Occurrences de la valeur %d : %d\n", valeur, occurrences);
                break;

            
            case 6:
                printf("\nNombre d'etudiants ayant moins de 18 ans : %d\n", CompterEtudiantsMoins18(liste_decroissant));
                break;

            case 7:
                break;


            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 7.\n");
                break;
        }

    } while (choix_menu != 7);

    LibererListe(liste_decroissant);

    return 0;
}
