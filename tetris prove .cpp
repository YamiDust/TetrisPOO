#include<bits/stdc++.h>

using namespace std;

  bool gamePlace[16][8];                // matriz principal, el "Tablero de juego"

  class Piece {                         // clase principal para las piezas, de aqui se derivan todas las piezasutilizadas en el juego
    public:
      bool matrix[4][4];           // matriz secundaria, donde cada pieza es guardada, solo tiene la pieza que se esta "jugando"
      int posX, posY;                   // donde esta la pieza pos(x,y), algo así
      int relativePosition;             // en que posicion esta de giro, puede ser cero, uno, dos o tres, dependiendo de cuantas veces se haya accionado el botn de "giro"


      virtual void generate1(){clearMatrix();};          // funcion que sirve para literalmente "dibujar" la pieza sobre la matriz secundaria

       void clearMatrix(){               // funcion que limpia (incializa todo con unos) la matriz donde se guarda la pieza
        for(int i=0 ; i<4 ; i++)
          for(int j=0 ; j<4 ; j++)          // son dos for anidados para recorrer la matriz de 4 x 4
            matrix[i][j] = 0;
      }

      bool CicleCorrector(){
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<4 ; j++){
                if(matrix[i][j]==1 && (posX+j>= 8 || posX+j < 0 || posY+i>= 16 || posY+i < 0)){
                    return true;
                }
            }
        }
        return false;
      }

      virtual void turnRight(){                                 //funcion para girar la pieza
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
      }

      //Funcion para ver la pieza en C
      void showPiece_forC(){
		 //For´s para recorrer la matriz interna de la pieza
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<4 ; j++){
				//Imprimir pieza
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
      }
    
      void clearPiece(){
        clearMatrix();
        posX=3;
        posY=0;
        relativePosition=0;
      }
      //void movePiece
  };

  class CyanPiece : public Piece {      // la pieza de color cyan es la pieza que es una barra alargada  "|", mas o menos así
     public:
      void generate1(){
        if(relativePosition==0){        // dibuja la pieza cuando no se ha girado ninguna vez
          matrix[0][2]=1;
          matrix[1][2]=1;
          matrix[2][2]=1;
          matrix[3][2]=1;
        }
        if(relativePosition==1){        // dibuja la pieza cuando se ha girado 1 vez
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[1][3]=1;
        }
        if(relativePosition==2){        // dibuja la pieza cuando se ha girado 2 veces
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
          matrix[3][1]=1;
        }
        if(relativePosition==3){        // dibuja la pieza cuando se ha girado 3 veces
          matrix[2][0]=1;
          matrix[2][1]=1;
          matrix[2][2]=1;
          matrix[2][3]=1;
        }
      }

      void turnRight(){
        do{
            relativePosition++;
            relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
            clearMatrix();
            generate1();
        }while(CicleCorrector()==true);

      }
  };


  class BluePiece : public Piece {      // la pieza de color Blue/azul es la pieza que es una ele volteada "¬", mas o menos así
     public:
      void generate1(){
        if(relativePosition==0){        // dibuja la pieza cuando no se ha girado ninguna vez
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[2][2]=1;
        }
        if(relativePosition==1){        // dibuja la pieza cuando se ha girado 1 vez
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
          matrix[2][0]=1;
        }
        if(relativePosition==2){        // dibuja la pieza cuando se ha girado 2 veces
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[0][0]=1;
        }
        if(relativePosition==3){        // dibuja la pieza cuando se ha girado 3 veces
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
          matrix[0][2]=1;
        }
      }

      void turnRight(){
        do{
            relativePosition++;
            relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
            clearMatrix();
            generate1();
            //showPiece_forC();
        }while(CicleCorrector());

      }

  };

  class OrangePiece : public Piece {      // la pieza de color Orange/naranja es la pieza que es una ele  "L", mas o menos así
     public:
      void generate1(){
        if(relativePosition==0){        // dibuja la pieza cuando no se ha girado ninguna vez
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
          matrix[2][2]=1;
        }
        if(relativePosition==1){        // dibuja la pieza cuando se ha girado 1 vez
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[0][2]=1;
        }
        if(relativePosition==2){        // dibuja la pieza cuando se ha girado 2 veces
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
          matrix[0][0]=1;
        }
        if(relativePosition==3){        // dibuja la pieza cuando se ha girado 3 veces
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[2][0]=1;
        }
      }

      void turnRight(){
        do{
            relativePosition++;
            relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
            clearMatrix();
            generate1();
            //showPiece_forC();
        }while(CicleCorrector());

      }
  };

  class YellowPiece : public Piece {      // la pieza de color Yellow/amarilla es la pieza que es un cuadro  "[]", mas o menos así
     public:
      void generate1(){
                                          // Para esta pieza solo se necesita una forma de "dibujar", ya que no gira (o al girarse permanece igual)
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[2][1]=1;
          matrix[2][2]=1;
      }
  };

  class GreenPiece : public Piece {      // la pieza de color Green/Verde es la pieza que es simila a una S
     public:
      void generate1(){
        if(relativePosition%2 == 0){        // dibuja la pieza cuando no se ha girado ninguna vez o cuando se ha girado dos veces, ya que son iguales
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[0][1]=1;
          matrix[0][2]=1;
        }
        if(relativePosition%2 == 1){        // dibuja la pieza cuando se ha girado 1 vez o cuando se ha girado tres veces, ya que son iguales
          matrix[0][0]=1;
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
        }
      }
      void turnRight(){
        do{
            relativePosition++;
            relativePosition = relativePosition % 2;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
            clearMatrix();
            generate1();
        }while(CicleCorrector());

      }
  };

  class RedPiece : public Piece {      // la pieza de color Red/rojo es la pieza que es simila a una Z
     public:
      void generate1(){
        if(relativePosition%2 == 0){        // dibuja la pieza cuando no se ha girado ninguna vez o cuando se ha girado dos veces, ya que son iguales
          matrix[0][0]=1;
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
        }
        if(relativePosition%2 == 1){        // dibuja la pieza cuando se ha girado 1 vez o cuando se ha girado tres veces, ya que son iguales
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[1][0]=1;
          matrix[2][0]=1;
        }
      }
      void turnRight(){
        do{
            relativePosition++;
            relativePosition = relativePosition % 2;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
            clearMatrix();
            generate1();
        }while(CicleCorrector());

      }
  };


  class PurplePiece : public Piece {      // la pieza de color Purple/purpura es la pieza que parece "_|_" o algo similar
     public:
      void generate1(){
        if(relativePosition==0){        // dibuja la pieza cuando no se ha girado ninguna vez
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[2][1]=1;
        }
        if(relativePosition==1){        // dibuja la pieza cuando se ha girado 1 vez
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
          matrix[1][2]=1;
        }
        if(relativePosition==2){        // dibuja la pieza cuando se ha girado 2 veces
          matrix[1][0]=1;
          matrix[1][1]=1;
          matrix[1][2]=1;
          matrix[0][1]=1;
        }
        if(relativePosition==3){        // dibuja la pieza cuando se ha girado 3 veces
          matrix[0][1]=1;
          matrix[1][1]=1;
          matrix[2][1]=1;
          matrix[1][0]=1;
        }
      }
      void turnRight(){
        do{
            relativePosition++;
            relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
            clearMatrix();
            generate1();
        }while(CicleCorrector());

      }
  };

bool check(Piece P){
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<4 ; j++){
            if(P.matrix[i][j]==1){
                if(i+P.posY >= 16 || i+P.posY < 0 || j+P.posX >= 8 || j+P.posX < 0 || gamePlace[i+P.posY][j+P.posX]==1){
                    return false;
                }
            }
        }
    }
    return true;
  }

  bool bajar(Piece P){
    Piece Temp=P;
    Temp.posY+=1;
    if(check(Temp)){
        return true;
    }
    else {
        return false;
    }
  }

  bool mov_izq(Piece P){
    Piece Temp=P;
    Temp.posX-=1;
    if(check(Temp)){
        return true;
    }
    else {
        return false;
    }
  }

  bool mov_der(Piece P){
    Piece Temp=P;
    Temp.posX+=1;
    if(check(Temp)){
        return true;
    }
    else {
        return false;
    }
  }




//Funcion para fusionar las piezas que van cayendo con la matriz general
void overlap(Piece P){
	//For's para revisar la matriz interna del objeto P
   for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<4 ; j++){
			//Actualiza mediante la operacion or la matriz general, ya que solo son 0's y 1's se puede usar esta operacion
            gamePlace[i+P.posY][j+P.posX]|= P.matrix[i][j];
        }
    }
    return;
}

//Funcion que imprime la condicion actual del tablero
void showTime(Piece P){
	//Imprime la posicion actual de la pieza
    cout << P.posY << " " << P.posX <<endl;
	//For's que van a recorrer la matriz del tablero de 16x8
    for(int i=0 ; i<16 ; i++){
        for(int j=0 ; j<8 ; j++){
			//revisamos si la pieza se encuentra dentro del rango en el que estamos
            if(j-P.posX > 3 || j-P.posX < 0 || i-P.posY > 3 || i-P.posY < 0){
				//si es asi se imprime la matriz actual
                cout << gamePlace[i][j] << " ";
            }
            else {
				//De lo contrario se hace la operacion or y se imprime y si un bloque del objeto se encuentra
				//con la operacion or aparecera
                cout << bool(gamePlace[i][j] | P.matrix[i-P.posY][j-P.posX]) << " ";
            }
        }
        cout << endl;
    }
}


void correction(){
    for(int i=16;i>=0;i--){
        bool ax=true;
        for(int j=0;j<8;j++){
            ax &= gamePlace[i][j];
        }
        if(ax==true){
            for(int k=i;k>=0;k--){
                for(int l=0;l<8;l++){
                    gamePlace[k][l]=gamePlace[k-1][l];
                }
            }
            i++;
        }
    }
}


int main(){
   for(int i=0;i<16;i++){ ///Este for inicializa el espacio de juego, y lo llena de ceros
        for(int j=0;j<8;j++){
            gamePlace[i][j]=0;
        }
    }
    CyanPiece C;///creamos una pieza u objeto de tip cyan
    PurplePiece Q;///creamos una pieza u objeto de tipo purple
    GreenPiece G;///creamos una pieza u objeto de tipo green
    RedPiece R;///creamos una pieza u objeto de tipo red
    BluePiece B;///creamos una pieza u objeto de tipo blue
    YellowPiece Y;///creamos una pieza u objeto yellow
    OrangePiece O;///creamos una pieza u objeto orange

    Piece *P; ///creamos un puntero de tipo piece que sera el unico objeto o pieza con el que trabajaremos y asignaremos para cada caso el tipo de pieza al que pertenecera
    ///creamos un switch case para crear cada una de las piezas de forma aleatoria
    do{

        int key = rand()%7 +1;///key es el valor con el que asignara el tipo de pieza al puntero
        cout <<"key: "<< key << endl;
        switch (key){
        case 1:
            P=&C;///asigna al puntero la direccion de memoria de una pieza tipo Cyan, por lo tanto el puntero o pieza se convierte a una pieza tipo cyan
            break;
        case 2:
            P=&Q;///asigna al puntero la direccion de memoria de una pieza tipo purple, por lo tanto el puntero o pieza se convierte a una pieza tipo purple
            break;
        case 3:
            P=&G;///asigna al puntero la direccion de memoria de una pieza tipo green, por lo tanto el puntero o pieza se convierte a una pieza tipo green
            break;
        case 4:
            P=&R;///asigna al puntero la direccion de memoria de una pieza tipo red, por lo tanto el puntero o pieza se convierte a una pieza tipo red
            break;
        case 5:
            P=&B;///asigna al puntero la direccion de memoria de una pieza tipo blue, por lo tanto el puntero o pieza se convierte a una pieza tipo blue
            break;
        case 6:
            P=&Y;///asigna al puntero la direccion de memoria de una pieza tipo yellow, por lo tanto el puntero o pieza se convierte a una pieza tipo yellow
            break;
        default:
            P=&O;///asigna al puntero la direccion de memoria de una pieza tipo orange, por lo tanto el puntero o pieza se convierte a una pieza tipo orange
            break;
        }


        P->clearPiece();///como p es un puntero se utiliza el apuntador this para acceder al metodo ClearPiece que reinicia o limpia la matriz de la pieza
        P->generate1();///Genera una nueva pieza


        bool L=true;
        while(L==true){
            P->showPiece_forC();
            cout << endl;
            showTime(*P);
            cout << endl;
            int n;
            cin >> n;
            switch (n){
            case 1:
                if(bajar(*P)){
                    P->posY++;
                }
                else {
                    L=false;
                    overlap(*P);
                    correction();
                }
                break;
            case 2:
                if(mov_izq(*P)){
                    P->posX--;
                }
                break;
            case 3:
                if(mov_der(*P)){
                    P->posX++;
                }
                break;
            default:
                P->turnRight();
                P->clearMatrix();
                P->generate1();
                break;
            }
        }
    }while(1);

}
