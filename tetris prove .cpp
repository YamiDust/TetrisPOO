#include<bits/stdc++.h>

using namespace std;

  bool gamePlace[8][16];                // matriz principal, el "Tablero de juego"

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
      void turnRight(){                                 //funcion para girar la pieza
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
      }

      void showPiece_forC(){
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<4 ; j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
      }
      void clearPiece(){
        clearMatrix();
        posX=0;
        posX=0;
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
  };

int main(){
    CyanPiece C1;
    C1.clearPiece();
    for(int i=0;i<4;i++){
        C1.clearMatrix();
        C1.generate1();
        C1.showPiece_forC();
        C1.turnRight();
        cout << endl;
    }

//    return 0;
}