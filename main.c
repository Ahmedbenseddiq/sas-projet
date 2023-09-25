#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int count ;
typedef struct{
    int jour;
    int mois;
    int annee;
}dead;

int complete = 0, incomplete = 0;
 typedef struct {
    int id;
    char statut[30];
    char title[100];
    char description[200];
    dead deadline;

} task;



int z,i,j;
task LIST[100];

int choix;
int joursrestant(dead deadline) {
    struct tm now;
    time_t currentTime;
    time(&currentTime);
    now = *localtime(&currentTime);

    struct tm dueDate;
    dueDate.tm_year = deadline.annee - 1900;
    dueDate.tm_mon = deadline.mois - 1;
    dueDate.tm_mday = deadline.jour;
    dueDate.tm_hour = 0;
    dueDate.tm_min = 0;
    dueDate.tm_sec = 0;

    time_t timeRemaining = difftime(mktime(&dueDate), mktime(&now));
    return (int)(timeRemaining / (60 * 60 * 24));
}


void une_tache() {
    if (count >= 100) {
        printf("\t\tvotre liste est pleine!\n");
        return;
    }

    task temp;
    temp.id = count + 1;
    printf("\nID : %d\n",temp.id);
    printf("Entrez un Titre : ");
    scanf(" %[^\n]",temp.title);
        printf("description: ");
        scanf(" %[^\n]", temp.description);


    printf("Entrez un Deadline au Format (JJ/MM/AAAA): ");
    scanf("%d/%d/%d", &temp.deadline.jour, &temp.deadline.mois, &temp.deadline.annee);

      printf("Entrez le statut de la Tache:\n1: to do\n2: doing\n3: done -> ");
    int statut;

     scanf("%d",&statut);

        switch (statut) {
            case 1:
                strcpy(temp.statut,"to do");
                incomplete++;
                break;
            case 2:
                strcpy(temp.statut,"doing");
                incomplete++;
                break;
            case 3:
                strcpy(temp.statut,"done");
                complete++;
                break;
            default:
                printf("statut invalide , entrez 1, 2, or 3.\n");}


    LIST[count] = temp;
    count++;

    printf("Tache ajoutee avec succes!\n");
}



void plus_taches(){
    int key ;
    do
    {
        une_tache();
        printf("Pour continuer (1), pour sortir (0) ");
        scanf("%d", &key);
    } while (key != 0);
}

void affichage() {
    printf("\n--------------------AFFICHAGE--------------------\n");
    for (int i = 0; i < count; i++) {
        printf("\nID : %d", LIST[i].id);
        printf("\nTitre : %s",LIST[i].title);
        printf("\nDescription : %s",LIST[i].description);
        printf("\nDeadline : %d/%d/%d",LIST[i].deadline.jour, LIST[i].deadline.mois, LIST[i].deadline.annee);
        printf("\nStatut : %s",LIST[i].statut);


}}


void list_taches() {
    int trie;

    printf("\n\n-----------------Choisir un Affichage--------------\n\n");
    printf("\n 1.Trier les taches par ordre alphabetique   \n");
    printf("\n 2.Trier les taches par deadline   \n");
    printf("\n 3.Afficher les taches dont le deadline est dans 3 jours ou moins  \n");
    printf("\n 4.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &trie);

    switch(trie){
    case 1: tri_alpha();
           break;
    case 2: tri_deadline();
           break;
    case 3: affich_3jdead();
           break;
    case 4:break;
    default:
    printf("Choix Invalide. Ressayer.\n");
    }



}

void tri_alpha(){
    int i,j;
    task temp ;

    for (i=0;i<count-1;i++){
        for (j=i+1;j<count;j++){
            if  (strcmp(LIST[i].title,LIST[j].title)>0){
                temp=LIST[i];
                LIST[i]=LIST[j];
                LIST[j]=temp ;

            }

        }

    }
       affichage();
}

void tri_deadline(){
    task temp;
    for (i=0;i<count-1;i++){
        for (j=i+1;j<count;j++){
            if  (LIST[i].deadline.annee>LIST[j].deadline.annee || LIST[i].deadline.annee ==LIST[j].deadline.annee && LIST[i].deadline.mois>LIST[j].deadline.mois || LIST[i].deadline.mois ==LIST[j].deadline.mois && LIST[i].deadline.jour>LIST[j].deadline.jour || LIST[i].deadline.jour == LIST[j].deadline.jour)
                {
                temp=LIST[i];
                LIST[i]=LIST[j];
                LIST[j]=temp ;
                }

        }
    }
    affichage();
}

void affich_3jdead(){

    time_t currentTime;
    struct tm *localTimeInfo;
    currentTime = time(NULL);

    localTimeInfo = localtime(&currentTime);

    int year = localTimeInfo->tm_year + 1900;
    int month = localTimeInfo->tm_mon + 1;
    int day = localTimeInfo->tm_mday;
    printf("Les taches qui ont un dealai moins de 3 jours  :\n");
    for(i=0;i<count;i++){
        if(LIST[i].deadline.annee == year && LIST[i].deadline.mois == month && (LIST[i].deadline.jour - day)<= 3 && (LIST[i].deadline.jour - day)>=0){
        printf("\nID : %d",LIST[i].id);
        printf("\ntitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%s",LIST[i].statut);
    } }
}


void modification() {
    int modifier;

    printf("\n\n------------------Modification-----------------\n\n");
    printf("\n 1.Modifier la description d'une tache   \n");
    printf("\n 2.Modifier le statut d une tache   \n");
    printf("\n 3.Modifier le deadline d une tache  \n");
    printf("\n 4.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &modifier);

    switch(modifier){
    case 1:  modifier_description();
           break;
    case 2:  modifier_statut();
          break;
    case 3:  modifier_deadline();
           break;
    case 4: break;
    default:
    printf("Choix Invalide. Ressayez.\n");
    }



}

void  modifier_description() {
    int i, v_id;
    printf("Entrer l'ID du tache :");
    scanf("%d", &v_id);

    for (i = 0; i < count; i++) {
        if (LIST[i].id == v_id) {
            printf("Entrer votre nouvelle description  :");
            scanf(" %[^\n]", LIST[i].description);
            printf("Description modifie avec succes\n");
            break;
        }
    }
}

void modifier_statut() {
    int i, v_id;
    char new_stat[15];
    printf("Entrer l'ID de la tache : ");
    scanf("%d", &v_id);

    for (i = 0; i < count; i++) {
        if (LIST[i].id == v_id) {
            printf("Entrer le statut de la Tache:\n1:to do\n2: doing\n3: done\n-> ");
            int stat;
            scanf("%d", &stat);

            switch (stat) {
                case 1:
                    strcpy(LIST[i].statut, "to do");
                    break;
                case 2:
                    strcpy(LIST[i].statut, "doing");
                    break;
                case 3:
                    strcpy(LIST[i].statut, "done");
                    break;
                default:
                    printf("Statut invalide, veuillez entrer 1, 2 ou 3.\n");
                    return;
            }
            printf("Statut modifie avec succes\n");
            return;
        }
    }
    printf("Tache avec l'ID %d non trouvee.\n", v_id);
}

void modifier_deadline() {
    int i, v_id;
    printf("Entrer l'ID du tache :");
    scanf("%d", &v_id);

    for (i = 0; i < count; i++) {
        if (LIST[i].id == v_id) {
            printf("Entrer votre nouveau deadline (JJ MM AAAA) -> :");
            scanf("%d/%d/%d", &LIST[i].deadline.jour, &LIST[i].deadline.mois, &LIST[i].deadline.annee);
            printf("Deadline modifie avec succes\n");
            break;
        }
    }
}


void supprimer_tache() {
    int i, j, x, conf;


    for (i = 0; i < count; i++) {
        printf("ID %d\n Titre : %s\n", LIST[i].id, LIST[i].title);
    }

    printf("Entrer l'ID de la tache que vous voulez supprimer ->:");
    scanf("%d", &x);

    for (i = 0; i < count; i++) {
        if (x == LIST[i].id) {

            for (j = i; j < count - 1; j++) {
                LIST[j] = LIST[j + 1];
            }
            count--;

            /*for (j = i; j < count; j++) {
                LIST[j].id = j + 1;
            }*/
            printf("Tache supprimee avec succes\n");
            break;
        }
    }
}




void recherche_tache() {
    int recherche;

    printf("\n\n--------------Recherche une tache------------\n\n");
    printf("\n 1.Rechercher une tache par son Identifiant   \n");
    printf("\n 2.Rechercher une tache par son Titre   \n");
    printf("\n 3.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &recherche);

    switch(recherche){
    case 1:
    rechercher_par_id();
           break;

    case 2:
    rechercher_par_titre();
           break;

    case 3:
    break;
    default:
    printf("Choix Invalide. Ressayer.\n");
    }}

 void rechercher_par_id(){
    int i, v_id;
    printf("Entrer l'ID du tache:");
    scanf("%d",&v_id);
    for(i=0;i<count;i++){
            if(LIST[i].id == v_id){
        printf("\nVous avez chercher :\n");
        printf("\nID : %d",LIST[i].id);
        printf("\nTitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%d",LIST[i].statut);

            }


    }

}

void rechercher_par_titre() {
    int i;
    char titv[100];
    printf("Entrer le titre de votre tache :");
    scanf("%s", titv);

    for (i = 0; i < count; i++) {
        if (strcmp(LIST[i].title, titv) == 0) {
            printf("vous avez cherche :");
        printf("\nID : %d",LIST[i].id);
        printf("\nTitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%d",LIST[i].statut);
        }
    }
}

void afficher_les_statistiques() {
    int statistique;

    printf("\n\n-------------------STATISTIQUES-----------------\n\n");
    printf("\n 1.Afficher le nombre total des taches   \n");
    printf("\n 2.Afficher le nombre de taches completes et incompletes  \n");
    printf("\n 3.Afficher le nombre de jours restants jusqu au delai de chaque tache \n  ");
    printf("\n 4.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &statistique);

    switch(statistique){
    case 1:  nombres_des_taches();
           break;

    case 2:  t_completes_et_incompletes();
           break;

    case 3:  t_jours_restants();
           break;

    case 4: break;
    default:

    printf("Choix Invalide. Ressayer.\n");
    }}



    void nombres_des_taches(){
    printf("L'ensemble total des taches est: %d\n",count);
    }



     void t_completes_et_incompletes(){

                printf("L'ensemble total des taches incomplete est:   %d\n",incomplete);
                printf("L'ensemble total des taches complete est:: %d\n",complete);
     }

void t_jours_restants() {
    printf("\nListe des Taches avec les Jours Restants:\n");
    for (int i = 0; i < count; i++) {
        int daysLeft = joursrestant(LIST[i].deadline);
        printf("\nID : %d",LIST[i].id);
        printf("\ntitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%s",LIST[i].statut);

        printf("\nJours Restants: %d\n", daysLeft);
        printf("------------------------\n");
    }
}

int main()
{
    int choice;
    do
    {
        printf("\n\n------------------M E N U-----------------\n");
        printf("1. Ajouter une nouvelle tache \n");
        printf("2. Ajouter plusieurs nouvelles taches\n");
        printf("3. Afficher la liste de toutes les taches\n");
        printf("4. Modifier une tache\n");
        printf("5. Supprimer une tache par identifiant.\n");
        printf("6. Rechercher les Taches \n");
        printf("7. Statistiques \n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: une_tache();
            break;

        case 2: plus_taches();
            break;

        case 3: list_taches();
            break;

        case 4: modification();
            break;

        case 5: supprimer_tache();
            break;

        case 6: recherche_tache();
            break;

        case 7:afficher_les_statistiques();
            break;

        case 8:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Choix Invalide. Ressayer.\n");
        }
    } while (choice != 8);

    return 0;
}
