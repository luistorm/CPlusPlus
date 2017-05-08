#include <iostream.h>
template<class Data>
class NodoPila{
        private:
                Data X;
                NodoPila *Suc;
        public:
                NodoPila(){Suc=NULL;}
                NodoPila(Data X);
                Data getX(){return X;}
                void setX(Data X){this->X=X;}
                NodoPila *getSuc(){return Suc;}
                void *setSuc(NodoPila *Suc){this->Suc=Suc;}
};
template<class Data>
NodoPila<Data>::NodoPila(Data X){
        Suc=NULL;
        this->X=X;
}
template<class Data>
class Pila{
        private:
                NodoPila<Data> *Tope;
        public:
                Pila(){Tope=NULL;}
                void Push(Data X);
                void Pop();
                NodoPila<Data> *getTope(){return Tope;}
};
template<class Data>
void Pila<Data>::Push(Data X){
        NodoPila<Data> *e;
        e=new NodoPila<Data>(X);
        if(e){
                e->setSuc(Tope);
                Tope=e;
        }
        else
                cout<<"No hay memoria!"<<endl;
}

template<class Data>
void Pila<Data>::Pop(){
        if(!Tope)
                cout<<"Pila Vacia"<<endl;
        else{
                NodoPila<Data> *Aux;
                Aux=Tope;
                Tope=Tope->getSuc();
                delete Aux;
        }
}
template<class Data>
class NodoCola{
        private:
                Data X;
                NodoCola *Suc;
        public:
                NodoCola(Data X){Suc=NULL;this->X=X;}
                Data getX(){return X;}
                NodoCola *getSuc(){return Suc;}
                void setSuc(NodoCola *Suc){this->Suc=Suc;}
};
template<class Data>
class Cola{
        private:
                NodoCola<Data> *Fte;
                NodoCola<Data> *Fin;
        public:
                Cola(){Fte=NULL;Fin=NULL;}
                NodoCola<Data> *getFte(){return Fte;}
                NodoCola<Data> *getFin(){return Fin;}
                void Push(Data X);
                void Pop();
};
template<class Data>
void Cola<Data>::Push(Data X){
        NodoCola<Data> *e;
        e=new NodoCola<Data>(X);
        if(e){
                if(!Fte)
                        Fte=e;
                else
                        Fin->setSuc(e);
                Fin=e;
        }
        else
                cout<<"No hay memoria!"<<endl;
}
template<class Data>
void Cola<Data>::Pop(){
        if(!Fte)
                cout<<"Cola vacia"<<endl;
        else{
                NodoCola<Data> *Aux;
                Aux=Fte;
                Fte=Fte->getSuc();
                delete Aux;
        }

}
template<class Data>
class NodoBiCola{
        private:
                Data X;
                NodoBiCola *Suc,*Pre;
        public:
                NodoBiCola(Data X){Pre=NULL;Suc=NULL;this->X=X;}
                Data getX(){return X;}
                NodoBiCola *getSuc(){return Suc;}
                void setSuc(NodoBiCola *Suc){this->Suc=Suc;}
                NodoBiCola *getPre(){return Pre;}
                void setPre(NodoBiCola *Pre){this->Pre=Pre;}
};
template<class Data>
class BiCola{
        private:
                NodoBiCola<Data> *FteI;
                NodoBiCola<Data> *FteD;
        public:
                BiCola(){FteI=NULL;FteD=NULL;}
                NodoBiCola<Data> *getFteI(){return FteI;}
                NodoBiCola<Data> *getFteD(){return FteD;}
                void Push(Data X,int r);
                void Pop(int r);
};
template<class Data>
void BiCola<Data>::Push(Data X,int r){
        NodoBiCola<Data> *e;
        e=new NodoBiCola<Data>(X);
        if(e){
                if(!FteD)
                        FteD=FteI=e;
                else{
                        if(r==1){
                                e->setSuc(FteI);
                                FteI->setPre(e);
                                FteI=e;
                        }
                        else{
                                e->setPre(FteD);
                                FteD->setSuc(e);
                                FteD=e;
                        }
                }
        }
        else
                cout<<"No hay memoria!"<<endl;
}
template<class Data>
void BiCola<Data>::Pop(int r){
        NodoBiCola<Data> *Aux;
        if(!FteI)
                cout<<"Bicola vacia"<<endl;
        else{
                if(FteI==FteD){
                        Aux=FteI;
                        FteI=FteD=NULL;
                }
                else{
                        if(r==1){
                                Aux=FteI;
                                FteI=FteI->getSuc();
                                FteI->setPre(NULL);
                        }
                        else{
                                Aux=FteD;
                                FteD=FteD->getPre();
                                FteD->setSuc(NULL);
                        }
                }
                delete Aux;
        }
}
template<class Data>
class NodoColaP{
        private:
                Data X;
                NodoColaP *Suc;
                NodoCola<Data> *Fte,*Fin;
                int Pri;
        public:
                NodoColaP(Data X,int Pri){Suc=NULL;Fte=Fin=NULL;this->Pri=Pri;this->X=X;}
                Data getX(){return X;}
                int getPri(){return Pri;}
                NodoColaP *getSuc(){return Suc;}
                void setSuc(NodoColaP *Suc){this->Suc=Suc;}
                NodoCola<Data> *getFte(){return Fte;}
                NodoCola<Data> *getFin(){return Fin;}
                void setFte(NodoCola<Data> *Fte){this->Fte=Fte;}
                void setFin(NodoCola<Data> *Fin){this->Fin=Fin;}
};
template<class Data>
class ColaPrioridad{
        private:
                NodoColaP<Data> *FteP,*FinP;
        public:
                NodoColaP<Data> *getFteP(){return FteP;}
                NodoColaP<Data> *getFinP(){return FinP;}
                ColaPrioridad(){FteP=FinP=NULL;}
                void Push(Data X,int Pri);
                void Pop();
};
template<class Data>
void ColaPrioridad<Data>::Push(Data X,int Pri){
        if(Pri<0){
                cout<<"Prioridad no puede ser negativa"<<endl;
                return;
        }
        NodoColaP<Data> *R;
        bool b=false;
        R=FteP;
        while(R){
                if(R->getPri()==Pri){
                        b=true;
                        NodoCola<Data> *e;
                        e=new NodoCola<Data>(X);
                        if(e){
                                if(!R->getFte())
                                        R->setFte(e);
                                else
                                        R->getFin()->setSuc(e);
                                R->setFin(e);

                        }
                        else
                                cout<<"No hay memoria para subcola!"<<endl;
                        break;
                }
                R=R->getSuc();
        }
        if(!b){
                NodoColaP<Data> *e;
                e=new NodoColaP<Data>(X,Pri);
                if(e){
                        if(!FteP)
                                FteP=e;
                        else
                                FinP->setSuc(e);
                        FinP=e;
                }
                else
                        cout<<"No hay memoria para cola principal!"<<endl;
        }
}
template<class Data>
void ColaPrioridad<Data>::Pop(){
        if(!FteP){
                cout<<"Cola Principal Vacia"<<endl;
                return;
        }
        NodoColaP<Data> *AuxP;
        NodoCola<Data> *Aux;
        if(FteP->getFte()){//Si hay SubCola por eliminar
                Aux=FteP->getFte();
                FteP->setFte(FteP->getFte()->getSuc());
                delete Aux;
        }
        else{
                AuxP=FteP;
                FteP=FteP->getSuc();
                delete AuxP;
        }
}
template<class Data>
class NodoLista{
        private:
                Data X;
                NodoLista *Suc;
        public:
                NodoLista(Data X){this->X=X;Suc=NULL;}
                NodoLista<Data> *getSuc(){return Suc;}
                void setSuc(NodoLista<Data> *Suc){this->Suc=Suc;}
                Data getX(){return X;}
                void setX(Data X){this->X=X;}
};
template<class Data>
class Lista{
        private:
                NodoLista<Data> *Cab;
        public:
                Lista(){Cab=NULL;}
                void Insertar(Data X);
                NodoLista<Data> *getCab(){return Cab;}
                void Eliminar(Data X);
                NodoLista<Data> *Buscar(Data X);
};
template<class Data>
NodoLista<Data> *Lista<Data>::Buscar(Data X){
        NodoLista<Data> *R;
        R=Cab;
        while(R){
                if(X==R->getX())
                        return R;
                R=R->getSuc();
        }
        return NULL;
}
template<class Data>
void Lista<Data>::Insertar(Data X){
        NodoLista<Data> *e,*Anterior,*R;
        e=new NodoLista<Data>(X);
        bool b=false;
        if(e){
                if(!Cab)
                        Cab=e;
                else{
                        if(e->getX()<Cab->getX()){
                                e->setSuc(Cab);
                                Cab=e;
                        }
                        else{
                                b=false;
                                R=Cab->getSuc();
                                Anterior=Cab;
                                while(R && !b){
                                        if(e->getX()<R->getX())
                                                b=true;
                                        else{
                                                Anterior=R;
                                                R=R->getSuc();
                                        }
                                }
                                if(b){
                                        e->setSuc(R);
                                        Anterior->setSuc(e);
                                }
                                else{
                                        Anterior->setSuc(e);
                                }
                        }
                }
        }
        else
                cout<<"No hay memoria!"<<endl;
}
template<class Data>
void Lista<Data>::Eliminar(Data X){
        NodoLista<Data> *R,*Anterior;
        bool b=false;
        if(Cab){
                R=Cab;
                if(X==Cab->getX()){
                        Cab=Cab->getSuc();
                        delete R;
                }
                else{
                        R=Cab->getSuc();
                        Anterior=Cab;
                        b=false;
                        while(R && !b){
                                if(X==R->getX())
                                        b=true;
                                else{
                                        Anterior=R;
                                        R=R->getSuc();
                                }
                        }
                        if(b){
                                if(!R->getSuc())
                                        Anterior->setSuc(NULL);
                                else
                                        Anterior->setSuc(R->getSuc());
                                delete R;
                        }
                        else
                                cout<<"Dato no encontrado"<<endl;
                }
        }
        else
                cout<<"Lista vacia"<<endl;
}
template<class Data>
class ListaCircular{
        private:
                NodoLista<Data> *Fin;
        public:
                ListaCircular(){Fin=NULL;}
                void Insertar(Data X);
                NodoLista<Data> *getFin(){return Fin;}
                void Eliminar(Data X);

};
template<class Data>
void ListaCircular<Data>::Insertar(Data X){
        NodoLista<Data> *e,*R,*Anterior;
        bool b=false;
        e=new NodoLista<Data>(X);
        if(e){
                Anterior=Fin;
                if(Fin)
                        R=Fin->getSuc();
                else
                        R=NULL;
                while(R && !b){
                        if(e->getX()<R->getX())
                                b=1;
                        else{
                                Anterior=R;
                                R=R->getSuc();
                                if(R==Fin->getSuc())
                                        break;
                        }
                }
                if(!R)
                        Anterior=R=e;
                e->setSuc(R);
                Anterior->setSuc(e);
                if(!b)
                        Fin=e;
        }
        else
                cout<<"No hay memoria!"<<endl;
}
template<class Data>
void ListaCircular<Data>::Eliminar(Data X){
        NodoLista<Data> *R,*Anterior;
        bool b=false;
        if(Fin){
                Anterior=Fin;
                if(Fin)
                        R=Fin->getSuc();
                else
                        R=NULL;
                while(R && !b){
                        if(R->getX()==X)
                                b=true;
                        else{
                                Anterior=R;
                                R=R->getSuc();
                                if(R==Fin->getSuc())
                                        break;
                        }
                }
                if(b){
                        Anterior->setSuc(R->getSuc());
                        if(Fin==Fin->getSuc()){
                                Fin=NULL;
                        }
                        if(R==Fin)
                                Fin=Anterior;
                        delete R;
                }
                else
                        cout<<"El dato no existe!"<<endl;
        }
        else
                cout<<"Lista vacia!"<<endl;
}
template<class Data>
class NodoListaDoble{
        private:
                Data X;
                NodoListaDoble *Suc,*Pre;
        public:
                NodoListaDoble(Data X){this->X=X;Suc=Pre=NULL;}
                NodoListaDoble<Data> *getSuc(){return Suc;}
                void setSuc(NodoListaDoble<Data> *Suc){this->Suc=Suc;}
                NodoListaDoble<Data> *getPre(){return Pre;}
                void setPre(NodoListaDoble<Data> *Pre){this->Pre=Pre;}
                Data getX(){return X;}
};
template<class Data>
class ListaDoble{
        private:
                NodoListaDoble<Data> *Cab;
        public:
                ListaDoble(){Cab=NULL;}
                NodoListaDoble<Data> *getCab(){return Cab;}
                void Insertar(Data X);
                void Eliminar(Data X);
};
template<class Data>
void ListaDoble<Data>::Insertar(Data X){
        NodoListaDoble<Data> *e,*R,*A;
        bool b=false;
        e=new NodoListaDoble<Data>(X,Cod);
        if(e){
                A=NULL;
                R=Cab;
                while(R && !b){
                        if(e->getX()<R->getX())
                                b=true;
                        else{
                                A=R;
                                R=R->getSuc();
                        }
                }
                e->setSuc(R);
                e->setPre(A);
                if(A)
                        A->setSuc(e);
                else
                        Cab=e;
                if(R)
                        R->setPre(e);
        }
        else
                cout<<"No hay memoria!"<<endl;
}
template<class Data>
void ListaDoble<Data>::Eliminar(Data X){
        NodoListaDoble<Data> *R,*A;
        bool b=false;
        if(Cab){
                R=Cab;
                while(R && !b){
                        if(R->getX()==X)
                                b=1;
                        else
                                R=R->getSuc();
                }
                if(b){
                        if(R->getPre())
                                R->getPre()->setSuc(R->getSuc());
                        else
                                Cab=Cab->getSuc();
                        if(R->getSuc())
                                R->getSuc()->setPre(R->getPre());
                        delete R;
                }
                else
                        cout<<"El dato no existe!"<<endl;
        }
        else
                cout<<"Lista vacia!"<<endl;
}
template<class Data>
class ListaDobleCircular{
        private:
                NodoListaDoble<Data> *Cab;
        public:
                ListaDobleCircular(){Cab=NULL;}
                NodoListaDoble<Data> *getCab(){return Cab;}
                void Insertar(Data X);
                void Eliminar(Data X);
};
template<class Data>
void ListaDobleCircular<Data>::Insertar(Data X){
        NodoListaDoble<Data> *e,*R,*A;
        bool b=false;
        e=new NodoListaDoble<Data>(X);
        if(e){
                R=Cab;
                while(R && !b){
                        if(e->getX()<R->getX())
                                b=true;
                        else{
                                R=R->getSuc();
                                if(R==Cab)
                                        break;
                        }
                }
                if(!R)
                        R=A=Cab=e;
                else
                        A=R->getPre();
                e->setSuc(R);
                e->setPre(A);
                A->setSuc(e);
                R->setPre(e);
                if(R==Cab && b)
                        Cab=e;
        }
        else
                cout<<"No hay memoria!"<<endl;
}
template<class Data>
void ListaDobleCircular<Data>::Eliminar(Data X){
        NodoListaDoble<Data> *R,*A;
        bool b=false;
        if(Cab){
                R=Cab;
                while(R && !b){
                        if(X==R->getX())
                                b=true;
                        else{
                                R=R->getSuc();
                                if(R==Cab)
                                        break;
                        }
                }
                if(b){
                        R->getPre()->setSuc(R->getSuc());
                        R->getSuc()->setPre(R->getPre());
                        if(Cab==Cab->getSuc())
                                Cab=NULL;
                        if(Cab==R)
                                Cab=Cab->getSuc();
                        delete R;
                }
                else
                        cout<<"El dato no existe!"<<endl;
        }
        else
                cout<<"Lista vacia!"<<endl;
}
template<class Data,class SubData>
class NodoMulti{
        private:
                NodoMulti *Suc;
                Data X;
                Lista<SubData> *SubLista;
        public:
                NodoMulti(Data X){Suc=NULL;this->X=X;SubLista=new Lista<SubData>();}
                NodoMulti<Data,SubData> *getSuc(){return Suc;}
                void setSuc(NodoMulti<Data,SubData> *Suc){this->Suc=Suc;}
                Lista<SubData> *getSubLista(){return SubLista;}
                Data getX(){return X;}
                void AgregarSubData(SubData Y){SubLista->Insertar(Y);}
                void EliminarSubData(SubData Y);

};
template<class Data,class SubData>
void NodoMulti<Data,SubData>::EliminarSubData(SubData Y){
        if(!SubLista.getCab())
                cout<<"SubLista Vacia"<<endl;
        else
                SubLista.Eliminar(Y);
}
template<class Data,class SubData>
class MultiLista{
        private:
                NodoMulti<Data,SubData> *Cab;
        public:
                MultiLista(){Cab=NULL;}
                void Insertar(Data X);
                NodoMulti<Data,SubData> *getCab(){return Cab;}
                void Eliminar(Data X);
                NodoMulti<Data,SubData> *Buscar(Data X);
};
template<class Data,class SubData>
NodoMulti<Data,SubData> *MultiLista<Data,SubData>::Buscar(Data X){
        NodoMulti<Data,SubData> *R;
        R=Cab;
        while(R){
                if(X==R->getX())
                        return R;
                R=R->getSuc();
        }
        return NULL;
}
template<class Data,class SubData>
void MultiLista<Data,SubData>::Insertar(Data X){
        NodoMulti<Data,SubData> *e,*Anterior,*R;
        e=new NodoMulti<Data,SubData>(X);
        bool b=false;
        if(e){
                if(!Cab)
                        Cab=e;
                else{
                        if(e->getX()<Cab->getX()){
                                e->setSuc(Cab);
                                Cab=e;
                        }
                        else{
                                b=false;
                                R=Cab->getSuc();
                                Anterior=Cab;
                                while(R && !b){
                                        if(e->getX()<R->getX())
                                                b=true;
                                        else{
                                                Anterior=R;
                                                R=R->getSuc();
                                        }
                                }
                                if(b){
                                        e->setSuc(R);
                                        Anterior->setSuc(e);
                                }
                                else{
                                        Anterior->setSuc(e);
                                }
                        }
                }
        }
        else
                cout<<"No hay memoria para lista principal!"<<endl;
}
template<class Data,class SubData>
void MultiLista<Data,SubData>::Eliminar(Data X){
        NodoMulti<Data,SubData> *R,*Anterior;
        bool b=false;
        if(Cab){
                R=Cab;
                if(X==Cab->getX()){
                        Cab=Cab->getSuc();
                        delete R;
                }
                else{
                        R=Cab->getSuc();
                        Anterior=Cab;
                        b=false;
                        while(R && !b){
                                if(X==R->getX())
                                        b=true;
                                else{
                                        Anterior=R;
                                        R=R->getSuc();
                                }
                        }
                        if(b){
                                if(!R->getSuc())
                                        Anterior->setSuc(NULL);
                                else
                                        Anterior->setSuc(R->getSuc());
                                delete R;
                        }
                        else
                                cout<<"Dato no encontrado"<<endl;
                }
        }
        else
                cout<<"Lista principal vacia"<<endl;
}
