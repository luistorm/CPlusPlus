#include <iostream.h>
#include <iomanip.h>
#include "EdDL.h"
/**Plantilla de nodo de un arbol, donde:
	X es la informacion a guardar
	Hi representa el puntero del hijo izquierdo del nodo
	Hd representa el puntero del hijo derecho del nodo
	FactorEquilibrio es lo dicho
	@note el nodo solo posee metodos set y get*/
template <class Data>
class NodoArbol{
        private:
                Data X;
                NodoArbol *Hi;
                NodoArbol *Hd;
                int FactorEquilibrio;
        public:
                NodoArbol(Data X){this->X=X;Hi=NULL;Hd=NULL;FactorEquilibrio;}
                void setHi(NodoArbol *Hi){this->Hi=Hi;}
                void setHd(NodoArbol *Hd){this->Hd=Hd;}
                void setX(Data X){this->X=X;}
                NodoArbol *getHi(){return Hi;}
                NodoArbol *getHd(){return Hd;}
                Data getX(){return X;}
                void setFactorEquilibrio(int FactorEquilibrio){this->FactorEquilibrio=FactorEquilibrio;}
                int getFactorEquilibrio(){return FactorEquilibrio;}
};
template <class Data>
class ArbolBB{
        private:
                NodoArbol<Data> *Raiz;
                int H;
        public:
                ArbolBB(){Raiz=NULL;}
                void setH(int H){this->H=H;}
                int getH(){return H;}
                NodoArbol<Data> *getRaiz(){return Raiz;}
                NodoArbol<Data> *Buscar(Data Bus,NodoArbol<Data> **q=NULL);
                virtual int Agregar(Data Ele);
                void Imprimir_Pre(NodoArbol<Data> *P=NULL,int Nivel=0);
                void AgregarLista(Data X){L.Insertar(X);}
                int Altura(NodoArbol<Data> *p);
                int Nivel(Data Bus);
                int CuentaNodos(int nivel);
                void CalcularFactor(NodoArbol<Data> *p);
                int Eliminar(Data X,NodoArbol<Data> **p=&Raiz);
                NodoArbol<Data> *Mayormenores(NodoArbol<Data> *p);
                NodoArbol<Data> *menorMayores(NodoArbol<Data> *p);
                int Mayores(NodoArbol<Data> *p);
                int menores(NodoArbol<Data> *p);
                bool Balanceado(NodoArbol<Data> *p=Raiz);
                NodoArbol<Data> *Padre(NodoArbol<Data> *h,NodoArbol<Data> *p);
                void Imprimir_InOrden(NodoArbol<Data> *p,int Nivel=0);
                void ImprimirArbol();
        protected:
                void setRaiz(NodoArbol<Data> *Raiz){this->Raiz=Raiz;}
};
template <class Data>
int ArbolBB<Data>::CuentaNodos(int nivel){
        int cont=0;
        int n=Nivel(Raiz,Raiz->getX());
        NodoArbol<Data> *p,*i,*d;
        Cola<NodoArbol<Data>*> c;
        c.Push(Raiz);
        while(c.getFte()){
                p=c.getFte()->getX();
                if(Nivel(p,p->getX())!=n){
                        if(n==nivel) return cont;
                        cout<<endl;
                        n=Nivel(p,p->getX());
                        cont=0;
                }
                if(p->getHi()){
                        i=p->getHi();
                        c.Push(i);
                }
                if(p->getHd()){
                        d=p->getHd();
                        c.Push(d);
                }
                cont++;
                c.Pop();
        }
        return cont;
}
template <class Data>
int ArbolBB<Data>::Nivel(Data Bus){
        int n=0;
        NodoArbol<Data> *R;
        R=Raiz;
        while(R){
                if(R->getX()==Bus)
                        return n;
                if(Bus<R->getX())
                        R=R->getHi();
                else
                        R=R->getHd();
                n++;
        }
        return -1;
}
template <class Data>
void ArbolBB<Data>::ImprimirArbol(){
        NodoArbol<Data> *p,*i,*d,*a;
        Cola<NodoArbol<Data>*> c;
        c.Push(Raiz);
        int n=Nivel(Raiz,Raiz->getX());
        int cont=CuentaNodos(n);
        while(c.getFte()){
                p=c.getFte()->getX();
                if(Nivel(p->getX())!=n){
                        cout<<endl;
                        n=Nivel(p->getX());
                        cont=CuentaNodos(n);
                }
                a=Padre(p,Raiz);
                if(a && a->getHi() && p->getX()==a->getHi()->getX()) for(int i=0;i<50/cont;i++) cout<<"-";
                if(a && a->getHd() && p->getX()==a->getHd()->getX()) for(int i=0;i<100/cont;i++) cout<<"-";
                if(!a)  for(int i=0;i<50/cont;i++) cout<<"-";
                if(a && !a->getHi() && !a->getHd()) for(int i=0;i<150/cont;i++) cout<<"-";
                cout<<p->getX();
                if(p->getHi()){
                        i=p->getHi();
                        c.Push(i);
                }
                if(p->getHd()){
                        d=p->getHd();
                        c.Push(d);
                }
                c.Pop();
        }
}
template <class Data>
NodoArbol<Data> *ArbolBB<Data>::Padre(NodoArbol<Data> *h,NodoArbol<Data> *p){
        NodoArbol<Data> *a;
        if((p->getHi() && p->getHi()==h) || (p->getHd() && p->getHd()==h))
                return p;
        if(p->getHi()){
                a=Padre(h,p->getHi());
                if(a) return a;
        }
        if(p->getHd()){
                a=Padre(h,p->getHd());
                if(a) return a;
        }
        return NULL;
}
template <class Data>
bool ArbolBB<Data>::Balanceado(NodoArbol<Data> *p){
        if(!p) return true;
        if(p->getFactorEquilibrio()>=-1 && p->getFactorEquilibrio()<=1)
                return Balanceado(p->getHi()) && Balanceado(p->getHd());
        return false;
}
template <class Data>
int ArbolBB<Data>::Mayores(NodoArbol<Data> *p){
        if(!p->getHd()) return 1;
        else return 1+Mayores(p->getHd());
}
template <class Data>
int ArbolBB<Data>::menores(NodoArbol<Data> *p){
        if(!p->getHi()) return 1;
        else return 1+menores(p->getHi());
}
template<class Data>
NodoArbol<Data> *ArbolBB<Data>::Buscar(Data Bus,NodoArbol<Data> **q){
        NodoArbol<Data> *R;
        R=Raiz;
        while(R){
                *q=R;
                if(Bus==R->getX())
                        return R;
                else if(Bus<R->getX())
                        R=R->getHi();
                else
                        R=R->getHd();
        }
        return NULL;
}
template <class Data>
NodoArbol<Data> *ArbolBB<Data>::menorMayores(NodoArbol<Data> *p){
        if(!p->getHi()) return p;
        else return menorMayores(p->getHi());
}
template <class Data>
NodoArbol<Data> *ArbolBB<Data>::Mayormenores(NodoArbol<Data> *p){
        if(!p->getHd()) return p;
        else return Mayormenores(p->getHd());
}
template <class Data>
int ArbolBB<Data>::Agregar(Data Ele){
        NodoArbol<Data> *n,*p,*q;
        p=Buscar(Ele,&q);
        if(p)
                return 0;//Ya esta en el arbol
        n=new NodoArbol<Data>(Ele);
        if(!n) return -1;//No hay memoria
        if(!Raiz)
                Raiz=n;
        else if(Ele<q->getX())
                q->setHi(n);
        else
                q->setHd(n);
        return 1;
}
template <class Data>
int ArbolBB<Data>::Eliminar(Data X,NodoArbol<Data> **p){
        NodoArbol<Data> *a,*M;
        if(!Raiz) return -1;//Arbol vacio
        if((*p)->getX()==X){
                if(!(*p)->getHi() && !(*p)->getHd()){
                        a=*p;
                        a=Padre(a,Raiz);
                        if(a->getHi() && a->getHi()->getX()==X)
                                a->setHi(NULL);
                        else
                                a->setHd(NULL);
                        delete (*p);
                        return 1;
                }
                if((*p)->getHi() && !(*p)->getHd()){
                        M=Mayormenores((*p)->getHi());
                        (*p)->setX(M->getX());
                        M->setX(X);
                        a=(*p)->getHi();
                        return Eliminar(X,&a);
                }
                if(!(*p)->getHi() && (*p)->getHd()){
                        M=menorMayores((*p)->getHd());
                        (*p)->setX(M->getX());
                        M->setX(X);
                        a=(*p)->getHd();
                        return Eliminar(X,&a);
                }
                else{
                        int m,n;
                        m=Mayores((*p)->getHi());
                        n=menores((*p)->getHd());
                        if(m<n){
                                M=Mayormenores((*p)->getHi());
                                (*p)->setX(M->getX());
                                M->setX(X);
                                a=(*p)->getHi();
                                return Eliminar(X,&a);
                        }
                        else{
                                M=menorMayores((*p)->getHd());
                                (*p)->setX(M->getX());
                                M->setX(X);
                                a=(*p)->getHd();
                                return Eliminar(X,&a);
                        }
                }
        }
        if(X<(*p)->getX() && (*p)->getHi()){
                a=(*p)->getHi();
                return Eliminar(X,&a);
        }
        else if((*p)->getHd()){
                a=(*p)->getHd();
                return Eliminar(X,&a);
        }
        return 0;
}
template <class Data>
void ArbolBB<Data>::Imprimir_Pre(NodoArbol<Data> *P,int Nivel){
        if(Nivel==0) P=Raiz;
        for(int i=0;i<Nivel;i++) cout<<" |";
        cout<<P->getX()<<"("<<P->getFactorEquilibrio()<<")"<<endl;
        if(P->getHi())Imprimir_Pre(P->getHi(),Nivel+1);
        if(P->getHd())Imprimir_Pre(P->getHd(),Nivel+1);
}
template <class Data>
void ArbolBB<Data>::Imprimir_InOrden(NodoArbol<Data> *p,int Nivel){
        if (p->getHi()) Imprimir_InOrden(p->getHi(),Nivel+1);
        for (int i=0; i<Nivel; i++) cout <<"       ";
        cout <<p->getX()<<"("<<p->getFactorEquilibrio()<<")"<<endl;
        if (p->getHd()) Imprimir_InOrden(p->getHd(),Nivel+1);
}
template <class Data>
int ArbolBB<Data>::Altura(NodoArbol<Data> *p){
        int Ri,Rd;
        if(!p) return 0;
        Ri=1+Altura(p->getHi());
        Rd=1+Altura(p->getHd());
        if(Ri>Rd)
                return Ri;
        else
                return Rd;
}
template <class Data>
void ArbolBB<Data>::CalcularFactor(NodoArbol<Data> *p){
        p->setFactorEquilibrio(Altura(p->getHd())-Altura(p->getHi()));
        if(p->getHi()) CalcularFactor(p->getHi());
        if(p->getHd()) CalcularFactor(p->getHd());
}
template<class Data>
class ArbolAVL:public ArbolBB<Data>{
        public:
                ArbolAVL(){setRaiz(NULL);}
                void Rotacion_SD(NodoArbol<Data> **h);
                void Rotacion_CD(NodoArbol<Data> **h);
                void Rotacion_SI(NodoArbol<Data> **h);
                void Rotacion_CI(NodoArbol<Data> **h);
                int Agregar(Data Ele);
                void Equilibrar(NodoArbol<Data> **p);
                void Revisar(NodoArbol<Data> *p);
                void Perfeccionar();
                void BuscarPila(Data X);
};
template <class Data>
void ArbolAVL<Data>::BuscarPila(Data X){
        NodoArbol<Data> *q;
        if(Buscar(X,&q)){
                NodoArbol<Data> *R;
                Data Aux;
                R=getRaiz();
                Pila<Data> P;
                Pila<int> P2;
                while(R){
                        Aux=R->getX();
                        P.Push(Aux);
                        P2.Push(Nivel(Aux));
                        if(R->getX()==X) break;
                        if(X<R->getX())
                                R=R->getHi();
                        else
                                R=R->getHd();
                }
                while(P.getTope()){
                        cout<<"Clave: "<<P.getTope()->getX()<<" Nivel: "<<P2.getTope()->getX()<<endl;
                        P.Pop();
                        P2.Pop();
                }
        }
        else
                cout<<"No se encontro la clave buscada"<<endl;
}
template <class Data>
void ArbolAVL<Data>::Perfeccionar(){
        while(!Balanceado(getRaiz())){
                CalcularFactor(getRaiz());
                Revisar(getRaiz());
                CalcularFactor(getRaiz());
        }
}
template <class Data>
void ArbolAVL<Data>::Revisar(NodoArbol<Data> *p){
        if(p->getFactorEquilibrio()<-1 || p->getFactorEquilibrio()>1)
                Equilibrar(&p);
        if(p->getHi()) Revisar(p->getHi());
        if(p->getHd()) Revisar(p->getHd());
}
template <class Data>
void ArbolAVL<Data>::Equilibrar(NodoArbol<Data> **p){
        Data X;
        X=(*p)->getX();
        if((*p)->getHi() && (*p)->getHd()){
                int m,n;
                n=Altura((*p)->getHi());
                m=Altura((*p)->getHd());
                if(n>m){
                        NodoArbol<Data> *M,*M2,*a;
                        M=Mayormenores((*p)->getHi());
                        M2=menorMayores((*p)->getHd());
                        (*p)->setX(M->getX());
                        M->setX(X);
                        a=(*p)->getHi();
                        Eliminar(X,&a);
                        M2->setHi(new NodoArbol<Data>(X));
                }
                else{
                        NodoArbol<Data> *M,*M2,*a;
                        M=menorMayores((*p)->getHd());
                        M2=Mayormenores((*p)->getHi());
                        (*p)->setX(M->getX());
                        M->setX(X);
                        a=(*p)->getHd();
                        Eliminar(X,&a);
                        M2->setHd(new NodoArbol<Data>(X));
                }
        }
        if((*p)->getHd() && !(*p)->getHi()){
                NodoArbol<Data> *M,*a;
                M=menorMayores((*p)->getHd());
                (*p)->setX(M->getX());
                M->setX(X);
                a=(*p)->getHd();
                Eliminar(X,&a);
                (*p)->setHi(new NodoArbol<Data>(X));
        }
        if(!(*p)->getHd() && (*p)->getHi()){
                NodoArbol<Data> *M,*a;
                M=Mayormenores((*p)->getHi());
                (*p)->setX(M->getX());
                M->setX(X);
                a=(*p)->getHi();
                Eliminar(X,&a);
                (*p)->setHd(new NodoArbol<Data>(X));
        }
}
template <class Data>
void ArbolAVL<Data>::Rotacion_SD(NodoArbol<Data> **h){
        NodoArbol<Data> *q;//Abuelo
        NodoArbol<Data> *p;//Padre
        p=Padre((*h),getRaiz());
        q=Padre(p,getRaiz());
        q->setHd(new NodoArbol<Data>(q->getX()));
        q->setX(p->getX());
        p->setX((*h)->getX());
        p->setHi(NULL);
        delete (*h);
}
template <class Data>
void ArbolAVL<Data>::Rotacion_SI(NodoArbol<Data> **h){
        NodoArbol<Data> *q;//Abuelo
        NodoArbol<Data> *p;//Padre
        p=Padre((*h),getRaiz());
        q=Padre(p,getRaiz());
        q->setHi(new NodoArbol<Data>(q->getX()));
        q->setX(p->getX());
        p->setX((*h)->getX());
        p->setHd(NULL);
        delete (*h);
}
template <class Data>
void ArbolAVL<Data>::Rotacion_CD(NodoArbol<Data> **h){
        NodoArbol<Data> *q;//Abuelo
        NodoArbol<Data> *p;//Padre
        p=Padre((*h),getRaiz());
        q=Padre(p,getRaiz());
        q->setHd(new NodoArbol<Data>(q->getX()));
        q->setX((*h)->getX());
        p->setHd(NULL);
        delete (*h);
}
template <class Data>
void ArbolAVL<Data>::Rotacion_CI(NodoArbol<Data> **h){
        NodoArbol<Data> *q;//Abuelo
        NodoArbol<Data> *p;//Padre
        p=Padre((*h),getRaiz());
        q=Padre(p,getRaiz());
        q->setHi(new NodoArbol<Data>(q->getX()));
        NodoArbol<Data> *Aux;
        Aux=q->getHi();
        Aux->setX(q->getX());
        q->setX((*h)->getX());
        p->setHi(NULL);
        delete (*h);
}
template <class Data>
int ArbolAVL<Data>::Agregar(Data Ele){
        NodoArbol<Data> *n,*p,*q;
        p=Buscar(Ele,&q);
        if(p)
                return 0;//Ya esta en el arbol
        n=new NodoArbol<Data>(Ele);
        if(!n) return -1;//No hay memoria
        if(!getRaiz())
                setRaiz(n);
        else if(Ele<q->getX())
                q->setHi(n);
        else
                q->setHd(n);
        p=Padre(n,getRaiz());
        q=Padre(p,getRaiz());
        if(q){
                CalcularFactor(q);
                if(q->getFactorEquilibrio()==2 && p->getFactorEquilibrio()==1) Rotacion_SI(&n);
                if(q->getFactorEquilibrio()==-2 && p->getFactorEquilibrio()==-1) Rotacion_SD(&n);
                if(q->getFactorEquilibrio()==2 && p->getFactorEquilibrio()==-1) Rotacion_CI(&n);
                if(q->getFactorEquilibrio()==-2 && p->getFactorEquilibrio()==1) Rotacion_CD(&n);
        }
        return 1;
}
template<class Data>
class Arista{
        Data X;
        float Peso;
        public:
                Arista(Data X,float Peso){this->X=X;this->Peso=Peso;}
                Data getX(){return X;}
                float getPeso(){return Peso;}
};
template<class Data>
class Grafo{
        MultiLista<Data,Arista<Data>*> Adyacencia;
        float **Matriz;
        int Tam;
        bool Dirigido;
        Cola<Data> *Camino;
        Lista<Cola<Data>*> *Caminos;
        public:
                Grafo(bool Dirigido=false){Tam=0;this->Dirigido=Dirigido;Camino=new Cola<Data>;Caminos=new Lista<Cola<Data>*>;}
                float **getMatriz(){return Matriz;}
                float getPeso(int i,int j){return Matriz[i][j];}
                Data getVertice(int Posicion);
                int getTam(){return Tam;}
                MultiLista<Data,Arista<Data>*> getAdyacencia(){return Adyacencia;}
                void CrearMatriz();
                void AgregarVertice(Data X);
                void AgregarArista(Data Origen,Data Destino,float Peso=1);
                int Posicion(Data X);
                void Imprimir_Matriz();
                bool **Multiplicar(int n);
                bool ConstruirCamino(Data Origen,Data Destino);
                void ImprimirCamino();
                bool Visitado(Data X);
                bool YaRecorrido(Cola<Data> *C);
                void NuevosCaminos(){Caminos=new Lista<Cola<Data>*>;Camino=new Cola<Data>;}
                Lista<Cola<Data>*> *getCaminos(){return Caminos;}
                float PesoArista(Data Origen,Data Destino);
                void Prim();
                float **Floyd();//Retorna Matriz de pesos minimos
                void CaminosMinimos(Data Origen,Data Destino);
                void CaminosMaximos(Data Origen,Data Destino);
                void MasVertices(Data Origen,Data Destino);
                void MenosVertices(Data Origen,Data Destino);
                void CaminosMinimosSinPasar(Data Origen,Data Destino,Data NoPasar);
                void CaminosMaximosSinPasar(Data Origen,Data Destino,Data NoPasar);
};
template <class Data>
void Grafo<Data>::CaminosMaximosSinPasar(Data Origen,Data Destino,Data NoPasar){
        NuevosCaminos();
        ConstruirCamino(Origen,Destino);
        NodoLista<Cola<Data>*> *R;
        Cola<Data> *C;
        NodoCola<Data> *R2;
        R=Caminos->getCab();
        bool b=false;
        float acum=0,mayor=-999;
        while(R){
                C=R->getX();
                R2=C->getFte();
                b=false;
                while(R2){
                        if(R2->getX()==NoPasar){
                                b=true;
                                break;
                        }
                        R2=R2->getSuc();
                }
                if(!b){
                        acum=0;
                        C=R->getX();
                        R2=C->getFte();
                        while(R2){
                                if(R2->getSuc()) acum+=PesoArista(R2->getX(),R2->getSuc()->getX());
                                R2=R2->getSuc();
                        }
                        if(acum>mayor) mayor=acum;
                }
                R=R->getSuc();
        }
        cout<<"Caminos Maximos ["<<mayor<<"] desde "<<Origen<<" hasta "<<Destino<<" sin pasar por "<<NoPasar<<":"<<endl;
        R=Caminos->getCab();
        while(R){
                b=false;
                C=R->getX();
                R2=C->getFte();
                while(R2){
                        if(R2->getX()==NoPasar){
                                b=true;
                                break;
                        }
                        R2=R2->getSuc();
                }
                if(!b){
                        acum=0;
                        C=R->getX();
                        R2=C->getFte();
                        while(R2){
                                if(R2->getSuc()) acum+=PesoArista(R2->getX(),R2->getSuc()->getX());
                                R2=R2->getSuc();
                        }
                        if(acum==mayor){
                                C=R->getX();
                                R2=C->getFte();
                                while(R2){
                                        cout<<R2->getX();
                                        if(R2->getSuc()) cout<<"->";
                                        R2=R2->getSuc();
                                }
                                cout<<endl;
                        }
                }
                R=R->getSuc();
        }
}
template <class Data>
void Grafo<Data>::CaminosMinimosSinPasar(Data Origen,Data Destino,Data NoPasar){
        NuevosCaminos();
        ConstruirCamino(Origen,Destino);
        NodoLista<Cola<Data>*> *R;
        Cola<Data> *C;
        NodoCola<Data> *R2;
        R=Caminos->getCab();
        bool b=false;
        float acum=0,menor=999;
        while(R){
                C=R->getX();
                R2=C->getFte();
                b=false;
                while(R2){
                        if(R2->getX()==NoPasar){
                                b=true;
                                break;
                        }
                        R2=R2->getSuc();
                }
                if(!b){
                        acum=0;
                        C=R->getX();
                        R2=C->getFte();
                        while(R2){
                                if(R2->getSuc()) acum+=PesoArista(R2->getX(),R2->getSuc()->getX());
                                R2=R2->getSuc();
                        }
                        if(acum<menor) menor=acum;
                }
                R=R->getSuc();
        }
        cout<<"Caminos Minimos ["<<menor<<"] desde "<<Origen<<" hasta "<<Destino<<" sin pasar por "<<NoPasar<<":"<<endl;
        R=Caminos->getCab();
        while(R){
                b=false;
                C=R->getX();
                R2=C->getFte();
                while(R2){
                        if(R2->getX()==NoPasar){
                                b=true;
                                break;
                        }
                        R2=R2->getSuc();
                }
                if(!b){
                        acum=0;
                        C=R->getX();
                        R2=C->getFte();
                        while(R2){
                                if(R2->getSuc()) acum+=PesoArista(R2->getX(),R2->getSuc()->getX());
                                R2=R2->getSuc();
                        }
                        if(acum==menor){
                                C=R->getX();
                                R2=C->getFte();
                                while(R2){
                                        cout<<R2->getX();
                                        if(R2->getSuc()) cout<<"->";
                                        R2=R2->getSuc();
                                }
                                cout<<endl;
                        }
                }
                R=R->getSuc();
        }
}
template <class Data>
void Grafo<Data>::MasVertices(Data Origen,Data Destino){
        NuevosCaminos();
        ConstruirCamino(Origen,Destino);
        NodoLista<Cola<Data>*> *R;
        Cola<Data> *C;
        NodoCola<Data> *R2;
        R=Caminos->getCab();
        int c=0,Mayor=-1;
        while(R){
                C=R->getX();
                R2=C->getFte();
                c=0;
                while(R2){
                        c++;
                        R2=R2->getSuc();
                }
                if(c>Mayor) Mayor=c;
                R=R->getSuc();
        }
        cout<<"Caminos con mas vertices ["<<Mayor<<"] desde "<<Origen<<" hasta "<<Destino<<":"<<endl;
        R=Caminos->getCab();
        while(R){
                C=R->getX();
                R2=C->getFte();
                c=0;
                while(R2){
                        c++;
                        R2=R2->getSuc();
                }
                if(c==Mayor){
                        R2=C->getFte();
                        while(R2){
                                cout<<R2->getX();
                                if(R2->getSuc()) cout<<"->";
                                R2=R2->getSuc();
                        }
                        cout<<endl;
                }
                R=R->getSuc();
        }
}
template <class Data>
void Grafo<Data>::MenosVertices(Data Origen,Data Destino){
        NuevosCaminos();
        ConstruirCamino(Origen,Destino);
        NodoLista<Cola<Data>*> *R;
        Cola<Data> *C;
        NodoCola<Data> *R2;
        R=Caminos->getCab();
        int c=0,menor=999;
        while(R){
                C=R->getX();
                R2=C->getFte();
                c=0;
                while(R2){
                        c++;
                        R2=R2->getSuc();
                }
                if(c<menor) menor=c;
                R=R->getSuc();
        }
        cout<<"Caminos con menos vertices ["<<menor<<"] desde "<<Origen<<" hasta "<<Destino<<":"<<endl;
        R=Caminos->getCab();
        while(R){
                C=R->getX();
                R2=C->getFte();
                c=0;
                while(R2){
                        c++;
                        R2=R2->getSuc();
                }
                if(c==menor){
                        R2=C->getFte();
                        while(R2){
                                cout<<R2->getX();
                                if(R2->getSuc()) cout<<"->";
                                R2=R2->getSuc();
                        }
                        cout<<endl;
                }
                R=R->getSuc();
        }
}
template <class Data>
void Grafo<Data>::CaminosMaximos(Data Origen,Data Destino){
        NuevosCaminos();
        ConstruirCamino(Origen,Destino);
        NodoLista<Cola<Data>*> *R;
        Cola<Data> *C;
        NodoCola<Data> *R2;
        R=Caminos->getCab();
        float acum,Mayor=-999;
        while(R){
                C=R->getX();
                R2=C->getFte();
                acum=0;
                while(R2){
                        if(R2->getSuc()){
                                acum+=PesoArista(R2->getX(),R2->getSuc()->getX());
                        }
                        R2=R2->getSuc();
                }
                if(acum>Mayor) Mayor=acum;
                R=R->getSuc();
        }
        cout<<"Caminos de Peso Maximos ["<<Mayor<<"] desde "<<Origen<<" hasta "<<Destino<<":"<<endl;
        R=Caminos->getCab();
        while(R){
                C=R->getX();
                R2=C->getFte();
                acum=0;
                while(R2){
                        if(R2->getSuc()){
                                acum+=PesoArista(R2->getX(),R2->getSuc()->getX());
                        }
                        R2=R2->getSuc();
                }
                if(acum==Mayor){
                        R2=C->getFte();
                        while(R2){
                                cout<<R2->getX();
                                if(R2->getSuc()) cout<<"->";
                                R2=R2->getSuc();
                        }
                        cout<<endl;
                }
                R=R->getSuc();
        }
}
template <class Data>
void Grafo<Data>::CaminosMinimos(Data Origen,Data Destino){
        NuevosCaminos();
        ConstruirCamino(Origen,Destino);
        NodoLista<Cola<Data>*> *R;
        Cola<Data> *C;
        NodoCola<Data> *R2;
        R=Caminos->getCab();
        float acum=0;
        float **min=Floyd();
        cout<<"Caminos de Peso Minimo ["<<min[Posicion(Origen)][Posicion(Destino)]<<"] desde "<<Origen<<" hasta "<<Destino<<":"<<endl;
        while(R){
                C=R->getX();
                R2=C->getFte();
                acum=0;
                while(R2){
                        if(R2->getSuc()){
                                acum+=PesoArista(R2->getX(),R2->getSuc()->getX());
                        }
                        R2=R2->getSuc();
                }
                if(min[Posicion(Origen)][Posicion(Destino)]==acum){
                        R2=C->getFte();
                        while(R2){
                                cout<<R2->getX();
                                if(R2->getSuc()) cout<<"->";
                                R2=R2->getSuc();
                        }
                        cout<<endl;
                }
                R=R->getSuc();
        }
}
template <class Data>
float **Grafo<Data>::Floyd(){
        float **min;
        min=new float*[Tam];
        for(int i=0;i<Tam;i++) min[i]=new float[Tam];
        for(int i=0;i<Tam;i++){
                for(int j=0;j<Tam;j++){
                        if(Matriz[i][j]!=0) min[i][j]=Matriz[i][j];
                        else min[i][j]=999;
                        if(i==j) min[i][j]=Matriz[i][j];
                }
        }
        NodoMulti<Data,Arista<Data>*> *R;
        R=Adyacencia.getCab();
        int k;
        while(R){
                k=Posicion(R->getX());
                for(int i=0;i<Tam;i++){
                        if(i==k) continue;
                        for(int j=0;j<Tam;j++){
                                if(j==k) continue;
                                if(i!=j){
                                        if(min[i][j]>(min[k][i]+min[k][j])){
                                                min[i][j]=min[k][i]+min[k][j];
                                        }
                                }
                        }
                }
                R=R->getSuc();
        }
        return min;
}
template <class Data>
void Grafo<Data>::Prim(){
        NodoMulti<Data,Arista<Data>*> *R;
        R=Adyacencia.getCab();
        float menor=999;
        int p;
        Data o,d;
        Lista<Data> M,V;
        while(R){
                o=R->getX();
                p=Posicion(o);
                for(int i=0;i<Tam;i++){
                        if(getPeso(p,i)!=0){
                                if(getPeso(p,i)<menor){
                                        menor=getPeso(p,i);
                                        d=getVertice(i);
                                }
                        }
                }
                R=R->getSuc();
        }
        float acum=0;
        R=Adyacencia.getCab();
        while(R){
                o=R->getX();
                V.Insertar(o);
                R=R->getSuc();
        }
        ofstream salida("Salida.txt");
        cout<<"Aristas de minimo recubrimiento: "<<endl;
        Data d2,o2;
        o2=o;
        d2=d;
        while(V.getCab()){
                NodoLista<Data> *R2;
                R2=M.getCab();
                menor=999;
                while(R2){
                        o=R2->getX();
                        p=Posicion(o);
                        for(int i=0;i<Tam;i++){
                                if(getPeso(p,i)!=0){
                                        d=getVertice(i);
                                        if(!M.Buscar(d) && getPeso(p,i)<menor){
                                                menor=getPeso(p,i);
                                                o2=o;
                                                d2=getVertice(i);
                                        }
                                }
                        }
                        R2=R2->getSuc();
                }
                M.Insertar(d2);
                V.Eliminar(d2);
                if(menor!=999){
                        acum+=menor;
                        cout<<o2<<" "<<d2<<" "<<PesoArista(o2,d2)<<endl;
                        salida<<o2<<" "<<d2<<" "<<PesoArista(o2,d2)<<endl;
                }
        }
        cout<<"Peso minimo: "<<acum;
        salida<<"Peso minimo: "<<acum;
}
template<class Data>
Data Grafo<Data>::getVertice(int p){
        NodoMulti<Data,Arista<Data>*> *R;
        int c=0;
        R=Adyacencia.getCab();
        while(R){
                if(p==c)
                        return R->getX();
                R=R->getSuc();
                c++;
        }
        return NULL;
}
template<class Data>
float Grafo<Data>::PesoArista(Data Origen,Data Destino){
        int i,j;
        i=Posicion(Origen);
        j=Posicion(Destino);
        return Matriz[i][j];
}
template<class Data>
bool Grafo<Data>::YaRecorrido(Cola<Data> *C){
        NodoLista<Cola<Data>*> *R;
        R=Caminos->getCab();
        bool b=0;
        int c=0,c2=0;
        while(R){
                NodoCola<Data> *R2;
                NodoCola<Data> *R3;
                R2=R->getX()->getFte();
                R3=C->getFte();
                b=1;
                while(R2 && R3){
                        if(R2->getX()!=R3->getX()) b=0;
                        R2=R2->getSuc();
                        R3=R3->getSuc();
                }
                if(b==0) c++;
                c2++;
                R=R->getSuc();
        }
        if(c==c2)
                return false;
        return true;
}
template<class Data>
bool Grafo<Data>::Visitado(Data X){
        NodoCola<Data> *R;
        R=Camino->getFte();
        while(R){
                if(R->getX()==X) return true;
                R=R->getSuc();
        }
        return false;
}
template<class Data>
void Grafo<Data>::ImprimirCamino(){
        NodoCola<Data> *R;
        NodoLista<Cola<Data>*> *R2;
        R2=Caminos->getCab();
        while(R2){
                R=R2->getX()->getFte();
                while(R){
                        cout<<R->getX();
                        if(R->getSuc())
                                cout<<"->";
                        R=R->getSuc();
                }
                cout<<endl;
                R2=R2->getSuc();
        }
}
template<class Data>
bool Grafo<Data>::ConstruirCamino(Data Origen,Data Destino){
        NodoMulti<Data,Arista<Data>*> *V;
        V=Adyacencia.Buscar(Origen);
        Camino->Push(V->getX());
        NodoLista<Arista<Data>*> *R;
        if(Destino==V->getX()) return true;
        R=V->getSubLista()->getCab();
        while(R){
                NodoCola<Data> *R2;
                Cola<Data> Copia;
                R2=Camino->getFte();
                while(R2){
                        Copia.Push(R2->getX());
                        if(R2->getX()==Origen) break;
                        R2=R2->getSuc();
                }
                Camino=new Cola<Data>;
                R2=Copia.getFte();
                while(R2){
                        Camino->Push(R2->getX());
                        R2=R2->getSuc();
                }

                if(Dirigido){
                        if(ConstruirCamino(R->getX()->getX(),Destino)) Caminos->Insertar(Camino);
                }
                if(!Dirigido){
                        if(!Visitado(R->getX()->getX())){
                                if(ConstruirCamino(R->getX()->getX(),Destino)){
                                        if(!YaRecorrido(Camino))
                                                Caminos->Insertar(Camino);
                                }
                        }
                }
                R=R->getSuc();
        }
        return false;
}
template<class Data>
bool **Grafo<Data>::Multiplicar(int n){
        bool **M,**Aux;
        M=new bool*[Tam];
        Aux=new bool*[Tam];
        bool A=0;
        if(!M || !Aux){
                cout<<"No hay memoria para generar la matriz de productos"<<endl;
                return 0;
        }
        for(int i=0;i<Tam;i++){
                M[i]=new bool[Tam];
                Aux[i]=new bool[Tam];
                if(!M[i] || !Aux[i]){
                        cout<<"No hay memoria para generar la matriz de productos"<<endl;
                        return 0;
                }
        }
        for(int p=0;p<n-1;p++){
                if(p==0){
                        for(int i=0;i<Tam;i++){
                                for(int j=0;j<Tam;j++){
                                        if(Matriz[i][j]==0)
                                                M[i][j]=0;
                                        else
                                                M[i][j]=1;
                                }
                        }
                        for(int i=0;i<Tam;i++){
                                for(int j=0;j<Tam;j++){
                                        Aux[i][j]=M[i][j];
                                }
                        }
                }
                for(int i=0;i<Tam;i++){
                        for(int j=0;j<Tam;j++){
                                A=0;
                                for(int k=0;k<Tam;k++)
                                        A|=Aux[i][k]&M[k][j];
                                M[i][j]=A;
                        }
                }
        }
        return M;
}
template<class Data>
void Grafo<Data>::Imprimir_Matriz(){
        NodoMulti<Data,Arista<Data>*> *R;
        cout<<"Vertices del Grafo:"<<endl;
        R=Adyacencia.getCab();
        for(int i=0;i<Tam;i++){
                cout<<R->getX()<<endl;
                R=R->getSuc();
        }
        cout<<endl;
        cout<<"Matriz de adyacencia:"<<endl;
        for(int i=0;i<Tam;i++){
                for(int j=0;j<Tam;j++){
                        cout<<setiosflags(ios::fixed)<<setprecision(2)<<Matriz[i][j]<<" ";
                }
                cout<<endl;
        }
}
template<class Data>
int Grafo<Data>::Posicion(Data X){
        NodoMulti<Data,Arista<Data>*> *R;
        R=Adyacencia.getCab();
        int i=0;
        while(R){
                if(X==R->getX())
                        return i;
                R=R->getSuc();
                i++;
        }
        return -1;
}
template<class Data>
void Grafo<Data>::AgregarVertice(Data X){
        Adyacencia.Insertar(X);
        Tam++;
}
template<class Data>
void Grafo<Data>::AgregarArista(Data Origen,Data Destino,float Peso){
        NodoMulti<Data,Arista<Data>*> *p;
        p=Adyacencia.Buscar(Origen);
        if(!p)//El Nodo Origen no esta en el Grafo (Aun)
                AgregarVertice(Origen);
        p=Adyacencia.Buscar(Destino);
        if(!p)//El Nodo Destino no esta en el Grafo (Aun)
                AgregarVertice(Destino);
        Arista<Data> *A;
        A=new Arista<Data>(Destino,Peso);
        p=Adyacencia.Buscar(Origen);
        p->AgregarSubData(A);
}
template<class Data>
void Grafo<Data>::CrearMatriz(){
        Matriz=new float*[Tam];
        if(!Matriz){
                cout<<"No hay memoria para generar la matriz de adyacencia"<<endl;
                return;
        }
        for(int i=0;i<Tam;i++){
                Matriz[i]=new float[Tam];
                if(!Matriz[i]){
                        cout<<"No hay memoria para generar la matriz de adyacencia"<<endl;
                        return;
                }
        }
        for(int i=0;i<Tam;i++)
                for(int j=0;j<Tam;j++)
                        Matriz[i][j]=0;
        int o=0,d;
        NodoMulti<Data,Arista<Data>*> *R;
        R=Adyacencia.getCab();
        while(R){
                NodoLista<Arista<Data>*> *R2;
                Lista<Arista<Data>*> *L;
                L=R->getSubLista();
                R2=L->getCab();
                while(R2){
                        d=Posicion(R2->getX()->getX());
                        Matriz[o][d]=R2->getX()->getPeso();
                        if(!Dirigido){
                                Matriz[d][o]=Matriz[o][d];
                                AgregarArista(R2->getX()->getX(),R->getX(),Matriz[o][d]);
                        }
                        R2=R2->getSuc();
                }
                o++;
                R=R->getSuc();
        }
}
 
