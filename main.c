#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct dPeriodos{
    int semestre,nMaterias;
    char periodo[10];
    float promedio;

    struct dPeriodos *ant;
    struct dPeriodos *sig;

};

struct estudiantes{
    char Est;
    long codigo;
    long long telefono;
    char nombre[30];
    char direccion[20];
    int Cperiodo;
    struct dPeriodos *periodos;

    struct estudiantes *sig;
    struct estudiantes *ant;
};


int comprobar(long cod,struct estudiantes **cabeza);
void periodo(long cod,struct estudiantes **cabeza);


void agregar(struct estudiantes **cabeza){
    struct estudiantes *n;
    n = malloc(sizeof(struct estudiantes));
    long cod;

    printf("Ingresa el codigo: ");
    fflush(stdin);
    scanf("%li",&cod);


    if(comprobar(cod,cabeza)){
        return;
    }

    n->codigo = cod;
    printf("Nombre del estudiante: ");
    fflush(stdin);
    gets(n->nombre);
    printf("Direccion: ");
    fflush(stdin);
    gets(n->direccion);
    printf("Telefono: ");
    fflush(stdin);
    scanf("%lli",&n->telefono);
    n->Cperiodo = 0;
    n->periodos = NULL;
    n->Est = 'A';

    if (*cabeza == NULL){
        n->sig = NULL;
        n->ant = NULL;
        *cabeza = n;


        printf("Se a guardado el estudiante.\n\n");
        printf("Desea anexar el periodo academico (s/n): ");
        fflush(stdin);
        if(getchar() == 's'){
            periodo(cod,cabeza);
        }
        return;
    }

    struct estudiantes *temp;
    temp = *cabeza;

    while(temp->sig != NULL){
        temp = temp->sig;
    }
    temp->sig = n;
    n->ant = temp;
    n->sig = NULL;

    printf("Se a guardado el estudiante.\n\n");
    printf("Desea anexar el periodo academico (s/n): ");
    fflush(stdin);
    if(getchar() == 's'){
        periodo(cod,cabeza);
    }

}

int comprobar(long cod,struct estudiantes **cabeza){

    struct estudiantes *temp,*tempAnt;
    temp = *cabeza;

    while(temp != NULL){

        if(temp->codigo == cod){
            printf("Error ese codigo si esta registrado.\n");
            fflush(stdin);
            getchar();
            return 1;
        }
        tempAnt = temp;
        temp = temp->sig;
    }
    return 0;
}

void periodo(long cod,struct estudiantes **cabeza){
    int np;
    struct estudiantes *temp;
    struct dPeriodos *tempPeriodo,*aux;

    temp = *cabeza;

    while(temp!=NULL){
        if(temp->codigo == cod){
            if(temp->Est == 'I'){
                printf("Error. El estudiante %s se encuentra inactivo");
                fflush((stdin));
                getchar();
                return;
            }

            do{
                system("cls");
                tempPeriodo = malloc(sizeof(struct dPeriodos));
                printf("Periodos vistos: %i\n",temp->Cperiodo);
                printf("Ingrese el semestre: ");
                fflush(stdin);
                scanf("%i",&tempPeriodo->semestre);

                printf("Ingrese el periodo: ");
                fflush(stdin);
                gets(tempPeriodo->periodo);

                printf("Ingrese el Numero de materias: ");
                fflush(stdin);
                scanf("%i",&tempPeriodo->nMaterias);

                printf("Ingrese el promedio: ");
                fflush(stdin);scanf("%f",&tempPeriodo->promedio);

                temp->Cperiodo++;

                if(temp->periodos == NULL){
                    temp->periodos = tempPeriodo;
                    tempPeriodo->sig = NULL;
                    tempPeriodo->ant = NULL;
                }else{
                    aux = temp->periodos;
                    while(aux->sig != NULL){
                        aux = aux->sig;
                    }
                    tempPeriodo->ant = aux;
                    aux->sig = tempPeriodo;
                    tempPeriodo->sig = NULL;

                }


                printf("Quieres continuar anexando periodos? (s/n): ");
                fflush(stdin);
            }while(getchar() == 's');

        }
        temp = temp->sig;
    }


}


float estadoprom(struct dPeriodos *pt,int limit){
    int i;
    float sumaprom = 0;
    while(pt != NULL){

        sumaprom += pt->promedio;
        pt = pt->sig;
    }

    return sumaprom /= limit;

}


void estado(struct estudiantes **cabeza){
    float sumaprom;
    int i;

    struct estudiantes *temp;
    temp = *cabeza;

    while (temp != NULL){

        if(temp->Est == 'A'){
            sumaprom = estadoprom(temp->periodos, temp->Cperiodo);
            if (sumaprom < 2.5) {
                printf("Nombre: %s\tPeriodos vistos: %i\tPromedio: %.2f\tEstado: FUERA\n", temp->nombre, temp->Cperiodo,
                       sumaprom);
            }
            if (sumaprom >= 2.5 && sumaprom <= 2.9) {
                printf("Nombre: %s\tPeriodos vistos: %i\tPromedio: %.2f\tEstado: PRUEBA\n", temp->nombre,
                       temp->Cperiodo, sumaprom);
            }
            if (sumaprom >= 3.0) {
                printf("Nombre: %s\tPeriodos vistos: %i\tPromedio: %.2f\tEstado: NORMAL\n", temp->nombre,
                       temp->Cperiodo, sumaprom);
            }
        }

        temp = temp->sig;
    }
    printf("\nEsos son todos los estados de los estudiantes\n");
    fflush(stdin);
    getchar();

}


void fuera(struct estudiantes **cabeza){
    struct estudiantes *temp;
    struct dPeriodos *temPer;
    temp = *cabeza;
    int i=0;
    while(temp != NULL){
        if(temp->Est == 'A'){
            if (estadoprom(temp->periodos, temp->Cperiodo) < 2.5) {
                printf("Codigo: %li\n", temp->codigo);
                printf("Nombre: %s\n", temp->nombre);
                printf("Direccion: %s\n", temp->direccion);
                printf("Telefono: %lli\n", temp->telefono);
                printf("periodos vistos: %i\n", temp->Cperiodo);
                printf("Estado: FUERA\n\n");
                printf("Periodos vistos: \n");
                temPer = temp->periodos;
                while (temPer != NULL) {
                    printf("Semestre: %i\n", temPer->semestre);
                    printf("Periodo: %s\n", temPer->periodo);
                    printf("Numero de  materias: %i\n", temPer->nMaterias);
                    printf("Promedio: %.2f\n\n", temPer->promedio);
                    temPer = temPer->sig;
                }
            }
        }
        temp = temp->sig;
    }
    printf("\nEsos son todos los estudiantes que estan FUERA\n");
    fflush(stdin);
    getchar();
}


void desactivar(struct estudiantes **cabeza,long cod){
    struct estudiantes *temp;
    temp = *cabeza;

    while(temp != NULL){
        if(temp->codigo == cod){

            temp->Est = 'I';
            printf("Se ha encontrado y ");
            printf("desactivado el estudiante");
            fflush(stdin);
            getchar();
            return;
        }
        temp = temp->sig;
    }

    printf("Ese codigo no esta registrado");
    fflush(stdin);
    getchar();

}


void eliminar(struct estudiantes **cabeza, struct estudiantes **elim) {
    struct estudiantes *temp = *cabeza;

    while (temp != NULL) {
        if (temp->Est == 'I') {
            // Si el estudiante es inactivo, lo movemos a la lista `elim`
            if (*elim == NULL) {
                *elim = temp;
            } else {
                struct estudiantes *tempElim = *elim;
                while (tempElim->sig != NULL) {
                    tempElim = tempElim->sig;
                }
                tempElim->sig = temp;
                temp->ant=tempElim;
            }

            // Eliminamos el estudiante de la lista original
            if (temp == *cabeza) {
                // Si el estudiante es el primer elemento de la lista, actualizamos la cabeza
                *cabeza = temp->sig;
                 if (*cabeza != NULL) {
                    (*cabeza)->ant = NULL;
                }
            } else {
                temp->ant->sig = temp->sig;
                if (temp->sig != NULL) {
                    temp->sig->ant = temp->ant;
                }
            }

            struct estudiantes *temp2 = temp;
            temp = temp->sig;
            temp2->sig = NULL;
            temp2->ant = NULL;
        } else {
            // Si el estudiante es activo, simplemente avanzamos al siguiente
            temp = temp->sig;
        }
    }


    system("cls");
    printf("Estudiantes Eliminados");
    fflush(stdin);
    getchar();
}

void imprimir(struct estudiantes **cabeza){
    struct estudiantes *temp;
    struct dPeriodos *temPer;
    int i;
    temp = *cabeza;

    while(temp != NULL){
        printf("Codigo: %li\n",temp->codigo);
        printf("Nombre: %s\n",temp->nombre);
        printf("Direccion : %s\n",temp->direccion);
        printf("Telefono: %lli\n\n",temp->telefono);
        if(temp->Est == 'A')
            printf("El estudiante esta activo.\n");
        else
            printf("El estudiante esta inactivo\n");
        if(temp->Cperiodo > 0){
            printf("Periodos vistos: \n");
            temPer = temp->periodos;
            while(temPer != NULL){
                printf("Semestre: %i\n",temPer->semestre);
                printf("Periodo: %s\n",temPer->periodo);
                printf("Numero de  materias: %i\n",temPer->nMaterias);
                printf("Promedio: %.2f\n\n",temPer->promedio);
                temPer = temPer->sig;
            }
        }
        printf("\n\n\n");
        temp = temp->sig;

    }
    printf("Todos los estudiantes han sido impresos");
    fflush(stdin);
    getchar();
}

void activar(struct estudiantes **cabeza, struct estudiantes **elim, long cod) {
    struct estudiantes *tempElim, *anterior;

    tempElim = *elim;
    anterior = NULL;

    // Buscar el estudiante en la lista de eliminados
    while (tempElim != NULL) {
        if (tempElim->codigo == cod) {
            break;
        }
        anterior = tempElim;
        tempElim = tempElim->sig;
    }

    // Si se encontró el estudiante, devolverlo a la lista original
    if (tempElim != NULL) {
        if (anterior == NULL) {
            // Si el estudiante es el primero en la lista de eliminados
            *elim = tempElim->sig;
        } else {
                anterior->sig = tempElim->sig;
            if (tempElim->sig != NULL) {
                tempElim->sig->ant = anterior;
            }
        }
        // Insertar al estudiante al final de la lista original
        struct estudiantes *temp = *cabeza;
        tempElim->Est='A';
        if (temp == NULL) {

            *cabeza = tempElim;
        } else {
            while (temp->sig != NULL) {
                temp = temp->sig;
            }
            temp->sig = tempElim;
            tempElim->ant = temp;
        }
        tempElim->sig = NULL;
    } else {
        printf("Estudiante no encontrado en la lista de eliminados.\n");
    }
}

int main(){
    struct estudiantes *cabeza = NULL;
    struct estudiantes *eliminados = NULL;
    int op;
    long cod;

    do{
        system("cls");
        printf("Menu principal.\n");
        printf("1.Agregar estudiante.\n");
        printf("2.Anexar periodo academico.\n");
        printf("3.Estados.\n");
        printf("4.Estudiantes Fuera\n");
        printf("5.Desactivar estudiante\n");
        printf("6.Eliminar estudiante\n");
        printf("7.Lista de estudiantes\n");
        printf("8.Activar un estudiante\n");
        printf("9.Salir\n");
        printf("Opciones: ");
        fflush(stdin);
        scanf("%i",&op);

        switch(op){
            case 1:
                system("cls");
                printf("Agregar estudiante.\n\n");
                agregar(&cabeza);
                break;

            case 2:
                system("cls");
                printf("Anexar periodo.\n\n");
                printf("Ingresa el codigo del estudiante: ");
                scanf("%li",&cod);
                periodo(cod,&cabeza);
                break;

            case 3:
                system("cls");
                printf("Estado de todos los estudiantes \n\n");
                estado(&cabeza);
                break;

            case 4:
                system("cls");
                printf("Lista de los estudiantes que estan FUERA\n\n");
                fuera(&cabeza);
                break;


            case 5:
                system("cls");
                printf("Desactivar estudiante.\n\n");
                printf("Ingrese el codigo del estudiante que dessea eliminar.\n\n");
                fflush(stdin);
                scanf("%li",&cod);
                desactivar(&cabeza,cod);
                break;

            case 6:
                system("cls");
                printf("Eliminando estudiantes.\n\n");
                eliminar(&cabeza,&eliminados);

                break;

            case 7:
                system("cls");
                printf("Escoge una lista:\n");
                printf("1.Lista de estudiantes activos.\n");
                printf("2.lista de estudiantes eliminados.\n");
                printf("Opcion: ");
                fflush(stdin);
                scanf("%i",&op);
                printf("\n\n");
                if(op == 1)
                    imprimir(&cabeza);
                if(op == 2)
                    imprimir(&eliminados);
                break;

            case 8:
                system("cls");
                printf("Escribe el codigo del estudiante que quieres activar: ");
                scanf("%li",&cod);
                activar(&cabeza,&eliminados,cod);
                break;

            case 9:;break;
            default:
                printf("\nError ese opcion no existe.\n");
                break;
        }
    }while(op != 9);

    return 0;
}