#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

typedef struct arv* AVL;

struct arv{
    int info;
    int altura;
    struct arv* esq;
    struct arv* dir;
};

AVL* raiz;

AVL* avl_criar(){
    
    AVL* arvore = new AVL;
    if(arvore != nullptr)
        *arvore = nullptr;
    return arvore;

}

int avl_altura_no(struct arv* no){
    
    if(no == nullptr)
        return -1;
    else
        return no->altura;

}

int avl_balanco(struct arv* no){

    return labs(avl_altura_no(no->esq) - avl_altura_no(no->dir));

}

int avl_maior(int a, int b){
    
    return max(a,b);

}

void avl_rotacao_dupla_esquerda(AVL *raiz){
    
    struct arv* no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    
    (*raiz)->altura = avl_maior(avl_altura_no((*raiz)->esq),avl_altura_no((*raiz)->dir)) + 1;
    no->altura = avl_maior(avl_altura_no(no->esq),avl_altura_no(no->dir)) + 1;
    (*raiz) = no;

}

void avl_rotacao_dupla_direita(AVL *raiz){
    
    struct arv* no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);

    (*raiz)->altura = avl_maior(avl_altura_no((*raiz)->esq),avl_altura_no((*raiz)->dir)) + 1;
    no->altura = avl_maior(avl_altura_no(no->esq),avl_altura_no(no->dir)) + 1;

    (*raiz) = no;

}

bool empty(AVL *raiz){

    return (raiz == nullptr || *raiz == nullptr);

}

void avl_rotacao_simples_direita(AVL *raiz){
    
    avl_rotacao_dupla_direita(&(*raiz)->esq);
    avl_rotacao_dupla_esquerda(raiz);

}

void avl_rotacao_simples_esquerda(AVL *raiz){

    avl_rotacao_dupla_esquerda(&(*raiz)->dir);
    avl_rotacao_dupla_direita(raiz);

}

bool avl_procura(AVL *raiz, int v){
    
    if(!empty(raiz)){
        if(v == (*raiz)->info)
            return true;
        else if(v > (*raiz)->info)
            raiz = &(*raiz)->dir;
        else
            raiz = &(*raiz)->esq;
    }
    return false;

}

bool avl_insere(AVL *raiz, int v){
    
    bool var_aux;

    if(avl_procura(raiz,v))
        return false;

    if(empty(raiz)){
        struct arv* no = new arv;
        no->altura = 0;
        no->esq = nullptr;
        no->dir = nullptr;
        no->info = v;
        *raiz = no;
        return true;
    }

    struct arv *atual = (*raiz);
    if(v < atual->info){
        if(var_aux = avl_insere(&(atual)->esq,v) == true){
            if(avl_balanco(atual) >= 2){
                if(v < (*raiz)->esq->info)
                    avl_rotacao_dupla_esquerda(raiz);
                else
                    avl_rotacao_simples_esquerda(raiz);
            }
        }
    }else if(v > atual->info){
        if(var_aux = avl_insere(&(atual)->dir,v) == true){
            if(avl_balanco(atual) >= 2){
                if((*raiz)->dir->info < v)
                    avl_rotacao_dupla_direita(raiz);
                else
                    avl_rotacao_simples_direita(raiz);
            }
        }
    }else{
        return false;
    }

    atual->altura = avl_maior(avl_altura_no(atual->esq),avl_altura_no(atual->dir)) + 1;
    return var_aux;

}

int avl_minimo(AVL *raiz){

    if(empty(raiz) || (*raiz)->esq == nullptr)
        return (*raiz)->info;
    return avl_minimo(&(*raiz)->esq);

}

int avl_maximo(AVL *raiz){

    if(empty(raiz) || (*raiz)->dir == nullptr)
        return (*raiz)->info;
    return avl_maximo(&(*raiz)->dir);

}

void avl_pre_ordem(AVL *raiz){
    
    if(!empty(raiz)){
        cout << (*raiz)->info << " ";
        avl_pre_ordem(&(*raiz)->esq);
        avl_pre_ordem(&(*raiz)->dir);
    }

}

void avl_inordem(AVL *raiz){

    if(!empty(raiz)){
        avl_inordem(&(*raiz)->esq);
        cout << (*raiz)->info << " ";
        avl_inordem(&(*raiz)->dir);
    }

}

void avl_pos_ordem(AVL *raiz){
    
    if(!empty(raiz)){
        avl_pos_ordem(&(*raiz)->esq);
        avl_pos_ordem(&(*raiz)->dir);
        cout << (*raiz)->info << " ";
    }

}

int avl_quant_folhas(AVL *raiz){

    if(empty(raiz))
        return 0;
    if((*raiz)->esq == nullptr && (*raiz)->dir == nullptr)
        return avl_quant_folhas(&(*raiz)->esq) + avl_quant_folhas(&(*raiz)->dir) + 1;
    else
        return avl_quant_folhas(&(*raiz)->esq) + avl_quant_folhas(&(*raiz)->dir);

}

int avl_altura_arvore(AVL *raiz){
    
    int esq = 0, dir = 0;
    if(empty(raiz))
        return 0;
    esq = avl_altura_arvore(&(*raiz)->esq);
    dir = avl_altura_arvore(&(*raiz)->dir);
    if(esq > dir)
        return esq + 1;
    else
        return dir + 1;

}

void menu(){
    
    cout << endl <<"--------------" << endl;
    cout << "1. Inserir elemento na árvore" << endl;
    cout << "2. Percurso em pre-ordem" << endl;
    cout << "3. Percurso em in-ordem" << endl;
    cout << "4. Percurso em pos-ordem" << endl;
    cout << "5. Altura da árvore" << endl;
    cout << "6. Número de folhas da árvore" << endl;
    cout << "7. Valor máximo e mínimo da árvore" << endl;
    cout << "0. Sair" << endl;
    cout << "Entre sua escolha:" << endl;

}


int main(void){

    int escolha;

    AVL* arvore;
    arvore = avl_criar();

    while(1){
        menu();
        cin >> escolha;

        if(escolha == 1){
            int valor;
            cout << "Qual valor deseja-se inserir?" << endl;
            cin >> valor;
            int conf = avl_insere(arvore,valor);
            if(conf == 1)
                cout << "inserido com sucesso" << endl;
            else
                cout << "nao foi possivel inserir" << endl;
        }
        else if(escolha == 2){
            avl_pre_ordem(arvore);
        }
        else if(escolha == 3){
            avl_inordem(arvore);
        }
        else if(escolha == 4){
            avl_pos_ordem(arvore);
        }
        else if(escolha == 5){
            cout << "altura da arvore: " << avl_altura_arvore(arvore) << endl;
        }
        else if(escolha == 6){
            cout << "numero de folhas: " << avl_quant_folhas(arvore) << endl;
        }
        else if(escolha == 7){
            cout << "numero maximo: " << avl_maximo(arvore) << ", numero minimo: " << avl_minimo(arvore) << endl; 
        }
        else{
            exit(1);
        }
    }

    return 0;

}