//e1

/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>


// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile. ex: 1 - restaurantul 1 si tot asa   
typedef struct Node{
    int data;
    struct Node *next;
} NODE;


//graf
typedef struct g{
    int v; //nr noduri
    int *vis; //noduri vizitate?
    NODE **alst; 
} GPH;

//stiva!!!
typedef struct s{
    int t; //top
    int scap; // maxim elem in stiva
    int *arr; //stiva
} STK; 


NODE *create_node(int v){
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g,int src,int dest){
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v){
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v=v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(sizeof(int) * v);

    //se initializeaza graful gol
    for (int i = 0; i < v ; i++){
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }   
    return g;
}

STK *create_s(int scap){
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s){
    s->t = (s->t) + 1;
    s->arr[s->t] = pshd;
}


//se adauga nodurile in stiva s in ordinea dfs
void DFS(GPH *g, STK *s, int v_nr){
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;

    push(v_nr,s);
    
    while (aux != NULL){
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS( g, s, con_ver);
        aux=aux->next;
    }
}

void insert_edges(GPH *g,int edg_nr,int nrv){

    int src, dest, i;
    printf("Adauga %d munchii (de la 0 la %d)\n", edg_nr,nrv-1);

    for (i = 0; i < edg_nr; i++){
        scanf("%d  %d", &src, &dest);
        add_edge(g,src,dest);
    }
}

void wipe(GPH *g, int nrv){
    for (int i = 0; i < nrv; i++){
        g->vis[i] = 0;
    }
}


// 0 sau 1 daca poate fi sau nu ajuns
void canbe(GPH *g, int nrv, STK *s1, STK *s2, int *ans){
    // aici i tine loc de numar adica de restaurant
    int *canBe = calloc(nrv, sizeof(int)); 

    for (int i = 0; i < nrv - 1; i++){
        for (int j = i + 1 ; j < nrv; j++){

            wipe(g, nrv);
            s1->t = -1; // reset stiva 1
            DFS(g, s1, i); //drumurile din i
            wipe(g, nrv);
            s2->t = -1; //reset stiva 2
            DFS(g, s2, j); //drumurile din j
            for (int k = 0; k < nrv; k++)
                for (int l = 0; l < nrv; l++)
                    if ((s1->arr[k] == l) || (s2->arr[l] == k)) { //verifica daca exista drum direct intre 2 restaurante???
                        canBe[k] = 1;
                        }  
        }  
    }  

    for(int i = 0 ; i < nrv; i++){
        if(canBe[i] == 1) {
            *ans = 1;
            return;
        }
    }

}

int main()
{
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int ans = 0;

    //nr noduri
    printf("Cate noduri are graful?");
    scanf("%d", &nrv);

    //nr muchii
    printf("Cate muchii are graful?");
    scanf("%d", &edg_nr);

    //se creaza graful
    GPH *g = create_g(nrv);

    
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2, &ans);
    if(ans == 1){
        printf("DA.");
    }
    else{
        printf("NU.");
    }
}