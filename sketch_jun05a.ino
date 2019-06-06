//Autores:  Equipo AMLOVE

//codigo para el proyecto de programacion, el todo lo que mueve el juego en si mismo

//agregamos las librerias para el programa, las primeras dos son para matris, y la tercera es para la pantalla


#include <Sprite.h>
#include <Matrix.h>
#include <LiquidCrystal.h>

#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
#define VELOCIDAD 300 // Velocidad a la que se mueve el texto

// Lo primero is inicializar la librería indicando los pins de la interfaz
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //    ( RS, EN, d4, d5, d6, d7)

//puntaje
int puntaje=0,q=0;
String texto_fila = "0";
  
// Definimos los pines del arduino
int data = 11;    // Pin DIN del módulo MAX7219
int load = 10;    // Pin CS del módulo MAX7219
int clock = 13;  // Pin CLK del módulo MAX7219

long bdelay = 0;
short buttondelay = 300;
short btdowndelay = 250;
short btsidedelay = 250;
bool amaterasu=false, art_atack=false, lose = false;





int maxuse = 2; //Definimos cuantas matrices usaremos. En este caso solo se usarán 2
Matrix myLeds = Matrix(data, clock, load, maxuse);




bool gamePlace[18][8];                // matriz principal, el "Tablero de juego"
short delay_ = 500;
long delays = 0;


class Piece {                         // clase principal para las piezas, de aqui se derivan todas las piezasutilizadas en el juego
  public:
    bool matrix[4][4];           // matriz secundaria, donde cada pieza es guardada, solo tiene la pieza que se esta "jugando"
    int posX, posY;                   // donde esta la pieza pos(x,y), algo así
    int relativePosition;             // en que posicion esta de giro, puede ser cero, uno, dos o tres, dependiendo de cuantas veces se haya accionado el botn de "giro"


    virtual void generate1() {
      clearMatrix();
    };          // funcion que sirve para literalmente "dibujar" la pieza sobre la matriz secundaria

    void clearMatrix() {              // funcion que limpia (incializa todo con unos) la matriz donde se guarda la pieza
      for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)     // son dos for anidados para recorrer la matriz de 4 x 4
          matrix[i][j] = 0;
    }

    bool CicleCorrector() {
      for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
          if (matrix[i][j] == 1 && ((posX + j >= 8 || posX + j < 0 || posY + i >= 18 || posY + i < 0) || gamePlace[i+posY][j+posX])==1) {
            return true;
          }
        }
      }
      return false;
    }

    virtual void turnRight() {                                //funcion para girar la pieza
      relativePosition++;
      relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
    }

    //Funcion para ver la pieza en C
    void showPiece_forC() {
      //For´s para recorrer la 
      //matriz interna de la pieza
      for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
          //Imprimir pieza
          //           cout << matrix[i][j] << " ";
        }
        // cout << endl;
      }
    }

    void clearPiece() {
      clearMatrix();
      posX = 3;
      posY = 0;
      relativePosition = 0;
    }
    //void movePiece
};


class CyanPiece : public Piece {      // la pieza de color cyan es la pieza que es una barra alargada  "|", mas o menos así
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[0][2] = 1;
        matrix[1][2] = 1;
        matrix[2][2] = 1;
        matrix[3][2] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[1][3] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[3][1] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[2][0] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 1;
        matrix[2][3] = 1;
      }
    }

    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    

    }
};

class JOANPiece : public Piece {      // la pieza de color cyan es la pieza que es una barra alargada  "|", mas o menos así
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[0][2] = 1;
        matrix[0][3] = 1;
        matrix[1][0] = 1;
        matrix[1][3] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[0][2] = 1;
        matrix[1][2] = 1;
        matrix[2][2] = 1;
        matrix[3][2] = 1;
        matrix[0][1] = 1;
        matrix[3][1] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[1][3] = 1;
        matrix[0][0] = 1;
        matrix[0][3] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[3][1] = 1;
        matrix[0][2] = 1;
        matrix[3][2] = 1;
      }
    }

    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    

    }
};

class TONOZPiece : public Piece {      // la pieza de color cyan es la pieza que es una barra alargada  "|", mas o menos así
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[0][2] = 1;
        matrix[1][0] = 1;
        matrix[2][0] = 1;
        matrix[2][1] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[1][0] = 1;
        matrix[2][0] = 1;
        matrix[2][2] = 1;
        matrix[3][0] = 1;
        matrix[3][1] = 1;
        matrix[3][2] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[0][1] = 1;
        matrix[0][2] = 1;
        matrix[1][2] = 1;
        matrix[2][0] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][0] = 1;
        matrix[2][2] = 1;
        matrix[3][3] = 1;
      }
    }

    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    

    }
};

class ABRAHAMPiece : public Piece {      // la pieza de color Blue/azul es la pieza que es una ele volteada "¬", mas o menos así
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[0][0]=1;
        matrix[1][1]=1;
        matrix[2][2]=1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[0][2] = 1;
        matrix[1][1] = 1;
        matrix[2][0] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[0][0]=1;
        matrix[1][1]=1;
        matrix[2][2]=1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[0][2] = 1;
        matrix[1][1] = 1;
        matrix[2][0] = 1;
      }
    }

    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    }

};
class VENZORPiece : public Piece {      // la pieza de color Purple/purpura es la pieza que parece "_|_" o algo similar
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[2][0] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 1;
        matrix[3][2] = 1;
        matrix[3][3] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[0][3] = 1;
        matrix[1][3] = 1;
        matrix[2][3] = 1;
        matrix[2][2] = 1;
        matrix[3][2] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[2][0] = 1;
        matrix[2][1] = 1;
        matrix[3][1] = 1;
        matrix[3][2] = 1;
        matrix[3][3] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[0][2] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][1] = 1;
        matrix[3][1] = 1;
      }
    }
    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    }
};


class TONOYPiece : public Piece {      // la pieza de color cyan es la pieza que es una barra alargada  "|", mas o menos as・
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][0] = 1;
        matrix[3][0] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][2] = 1;
        matrix[3][2] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[1][2] = 1;
        matrix[2][2] = 1;
        matrix[3][0] = 1;
        matrix[3][1] = 1;
        matrix[3][2] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[1][0] = 1;
        matrix[2][0] = 1;
        matrix[3][0] = 1;
        matrix[3][1] = 1;
        matrix[3][2] = 1;
      }
    }

    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    

    }
};



class BluePiece : public Piece {      // la pieza de color Blue/azul es la pieza que es una ele volteada "¬", mas o menos así
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][2] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[2][0] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[0][0] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[0][2] = 1;
      }
    }

    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    }

};

class OrangePiece : public Piece {      // la pieza de color Orange/naranja es la pieza que es una ele  "L", mas o menos así
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[0][2] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[0][0] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][0] = 1;
      }
    }

    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    }
};

class YellowPiece : public Piece {      // la pieza de color Yellow/amarilla es la pieza que es un cuadro  "[]", mas o menos así
  public:
    void generate1() {
      // Para esta pieza solo se necesita una forma de "dibujar", ya que no gira (o al girarse permanece igual)
      matrix[1][1] = 1;
      matrix[1][2] = 1;
      matrix[2][1] = 1;
      matrix[2][2] = 1;
    }
};

class GreenPiece : public Piece {      // la pieza de color Green/Verde es la pieza que es simila a una S
  public:
    void generate1() {
      if (relativePosition % 2 == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez o cuando se ha girado dos veces, ya que son iguales
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[0][1] = 1;
        matrix[0][2] = 1;
      }
      if (relativePosition % 2 == 1) {    // dibuja la pieza cuando se ha girado 1 vez o cuando se ha girado tres veces, ya que son iguales
        matrix[0][0] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
      }
    }
    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    }
};

class RedPiece : public Piece {      // la pieza de color Red/rojo es la pieza que es simila a una Z
  public:
    void generate1() {
      if (relativePosition % 2 == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez o cuando se ha girado dos veces, ya que son iguales
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
      }
      if (relativePosition % 2 == 1) {    // dibuja la pieza cuando se ha girado 1 vez o cuando se ha girado tres veces, ya que son iguales
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[1][0] = 1;
        matrix[2][0] = 1;
      }
    }
    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    }
};


class PurplePiece : public Piece {      // la pieza de color Purple/purpura es la pieza que parece "_|_" o algo similar
  public:
    void generate1() {
      if (relativePosition == 0) {    // dibuja la pieza cuando no se ha girado ninguna vez
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][1] = 1;
      }
      if (relativePosition == 1) {    // dibuja la pieza cuando se ha girado 1 vez
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[1][2] = 1;
      }
      if (relativePosition == 2) {    // dibuja la pieza cuando se ha girado 2 veces
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[0][1] = 1;
      }
      if (relativePosition == 3) {    // dibuja la pieza cuando se ha girado 3 veces
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[1][0] = 1;
      }
    }
    void turnRight() {
        relativePosition++;
        relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
        clearMatrix();
        generate1();
        bool ark=true;
        while(ark==true){
          ark=false;
          if(CicleCorrector()){
            posX++;
            if(CicleCorrector()){
              posX-=2;
              if(CicleCorrector()){
                posX+=3;
                if(CicleCorrector()){
                  posX-=4;
                  if(CicleCorrector()){
                    posX+=2;
                    relativePosition++;
                    relativePosition = relativePosition % 4;        // cuando se presione el boton para girar, se ejecutara esta funcion, funiona aumentando la variable "posicion relativa"
                    clearMatrix();
                    generate1();
                    ark=true;
                  }
                }
              }
            }
          }
        }
    }
};


Piece *P;
CyanPiece C;///creamos una pieza u objeto de tip cyan
PurplePiece Q;///creamos una pieza u objeto de tipo purple
GreenPiece G;///creamos una pieza u objeto de tipo green
RedPiece R;///creamos una pieza u objeto de tipo red
BluePiece B;///creamos una pieza u objeto de tipo blue
YellowPiece Y;///creamos una pieza u objeto yellow
OrangePiece O;///creamos una pieza u objeto orange
JOANPiece J;
TONOZPiece TZ;
ABRAHAMPiece A;
VENZORPiece V;
TONOYPiece TY;

bool check(Piece P) {
  for (int i = 0 ; i < 4 ; i++) {
    for (int j = 0 ; j < 4 ; j++) {
      if (P.matrix[i][j] == 1) {
        if (i + P.posY >= 18 || i + P.posY < 0 || j + P.posX >= 8 || j + P.posX < 0 || gamePlace[i + P.posY][j + P.posX] == 1) {
          return false;
        }
      }
    }
  }
  return true;
}


void inicialice() {  //funcion para inicializar el tablero
  for (int i = 0; i < 18; i++) { ///Este for inicializa el espacio de juego, y lo llena de ceros
    for (int j = 0; j < 8; j++) {
      gamePlace[i][j] = 0;
    }
  }
}

bool bajar(Piece P) {
  Piece Temp = P;
  Temp.posY += 1;
  if (check(Temp)) {
    return true;
  }
  else {
    return false;
  }
}

bool mov_izq(Piece P) {
  Piece Temp = P;
  Temp.posX -= 1;
  if (check(Temp)) {
    return true;
  }
  else {
    return false;
  }
}

bool mov_der(Piece P) {
  Piece Temp = P;
  Temp.posX += 1;
  if (check(Temp)) {
    return true;
  }
  else {
    return false;
  }
}

//Funcion para fusionar las piezas que van cayendo con la matriz general
void overlap(Piece P) {
  //For's para revisar la matriz interna del objeto P
  for (int i = 0 ; i < 4 ; i++) {
    for (int j = 0 ; j < 4 ; j++) {
      //Actualiza mediante la operacion or la matriz general, ya que solo son 0's y 1's se puede usar esta operacion
      gamePlace[i + P.posY][j + P.posX] |= P.matrix[i][j];
    }
  }
  return;
}


//Funcion que imprime la condicion actual del tablero
void showTime(Piece P) {
  //Imprime la posicion actual de la pieza
  //cout << P.posY << " " << P.posX <<endl;
  //For's que van a recorrer la matriz del tablero de 16x8
  for (int i = 2 ; i < 18 ; i++) {
    for (int j = 0 ; j < 8 ; j++) {
      //revisamos si la pieza se encuentra dentro del rango en el que estamos
      if (j - P.posX > 3 || j - P.posX < 0 || i - P.posY > 3 || i - P.posY < 0) {
        //si es asi se imprime la matriz actual
          if(i<10){
            if(gamePlace[i][j]==true){
                myLeds.write((j+1)%8,i-2, HIGH);
            }
            else {
                myLeds.write((j+1)%8,i-2, LOW);
            }
          }
          else{
            if(gamePlace[i][j]==true){
                myLeds.write((j+1)%8+8,(i-2)%8, HIGH);
            }
            else {
                myLeds.write((j+1)%8+8,(i-2)%8, LOW);
            }
          }
                   //cout << gamePlace[i][j] << " ";
      }
      else {
        //De lo contrario se hace la operacion or y se imprime y si un bloque del objeto se encuentra
        //con la operacion or aparecera
        //           cout << bool(gamePlace[i][j] | P.matrix[i-P.posY][j-P.posX]) << " ";

          
          if(i<10){
            if(bool(gamePlace[i][j] | P.matrix[i-P.posY][j-P.posX])==true){
              myLeds.write((j+1)%8, (i-2), HIGH);
             }
             else {
              myLeds.write((j+1)%8, (i-2), LOW);
            }
          }
          else {
            if(bool(gamePlace[i][j] | P.matrix[i-P.posY][j-P.posX])==true){
              myLeds.write((j+1)%8+8, (i-2)%8, HIGH);
             }
             else {
              myLeds.write((j+1)%8+8, (i-2)%8, LOW);
            }
          }
          
      }
    }
    //   cout << endl;
  }
}


void correction() {
  bool xrl8=false;
  int puntitos=1;
  for (int i = 17; i > 0; i--) {
    bool ax = true;
    for (int j = 0; j < 8; j++) {
      ax &= gamePlace[i][j];
    }
    if (ax == true){ 
    xrl8=true;
    puntitos*=2;
      for (int k = i; k > 0; k--) {
        for (int l = 0; l < 8; l++) {
          gamePlace[k][l] = gamePlace[k - 1][l];
        }
      }
      i++;
    }
  
  }
  
  puntaje+=(puntitos/2)*100;
}


Piece* interacction(int key ) {
  Piece *P;
  switch (key) {
    case 1:
      P = &J; ///asigna al puntero la direccion de memoria de una pieza tipo Cyan, por lo tanto el puntero o pieza se convierte a una pieza tipo cyan
      break;
    case 2:
      P = &A; ///asigna al puntero la direccion de memoria de una pieza tipo purple, por lo tanto el puntero o pieza se convierte a una pieza tipo purple
      break;
    case 3:
      P = &TZ; ///asigna al puntero la direccion de memoria de una pieza tipo green, por lo tanto el puntero o pieza se convierte a una pieza tipo green
      break;
    case 4:
      P = &V; ///asigna al puntero la direccion de memoria de una pieza tipo red, por lo tanto el puntero o pieza se convierte a una pieza tipo red
      break;
    case 5:
      P = &TY; ///asigna al puntero la direccion de memoria de una pieza tipo blue, por lo tanto el puntero o pieza se convierte a una pieza tipo blue
      break;
    case 6:
      P = &Y; ///asigna al puntero la direccion de memoria de una pieza tipo yellow, por lo tanto el puntero o pieza se convierte a una pieza tipo yellow
      break;
    default:
      P = &O; ///asigna al puntero la direccion de memoria de una pieza tipo orange, por lo tanto el puntero o pieza se convierte a una pieza tipo orange
      break;
  }
  return P;
}


Piece* playing_Piece(Piece *P, int key) {

  P->clearPiece();///como p es un puntero se utiliza el apuntador this para acceder al metodo ClearPiece que reinicia o limpia la matriz de la pieza
  P->generate1();///Genera una nueva pieza

  switch (key) {
    case 3:
      if (mov_izq(*P))  {
        P->posX--;
      }
      break;
    case 2: 
      if (mov_der(*P)) {
        P->posX++;
      }
      break;
    case 1:
      P->turnRight();
      P->clearMatrix();
      P->generate1();
      break;
    case 4:
      if (bajar(*P)) {
        P->posY++;
      }
    default:
      
      break;
  }
  return P;
}



void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT); //up
  pinMode(A1, INPUT); //right
  pinMode(A2, INPUT); //left
  pinMode(A3, INPUT); //down 
  pinMode(A4, INPUT); //reset 
// Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
  Serial.begin(9600);
  randomSeed(9600);
  lcd.begin(12, 2); // Fijar el numero de caracteres y de filas
  lcd.setCursor(3, 0);  // set the cursor to column 0, line 1
  lcd.print("  puntos");
}

int readBut()
{
  if (bdelay > millis())
  {
    return 0;
  }
  if (analogRead(A0) > 150)
  {
    //left
    bdelay = millis() + 50;
    delay(50);
    if (analogRead(A0) > 150){
      bdelay = millis() + 100;
      delay(100);
      return 3;
    }
  }
  
  if (analogRead(A1) > 150)
  {
    //down
    bdelay = millis() + 50;
    delay(50);
    if (analogRead(A1) > 150){
      bdelay = millis() + 100;
      delay(100);
      return 4;
    }
  }    
  if (analogRead(A2) > 150)
  {
    //right
    bdelay = millis() + 50;
    delay(50);
    if (analogRead(A2) > 150){
      bdelay = millis() + 100;
      delay(100);
      return 2;  
    }
  }  
  if (analogRead(A3) > 150)
  {
    //up
    bdelay = millis() + 50;
    delay(50);
    if (analogRead(A3) > 150){
      bdelay = millis() + 100;
      delay(100);
      return 1;
    }
  }  

  if (analogRead(A4) > 150)
  {
    //up
    bdelay = millis() + 50;
    delay(50);
    if (analogRead(A4) > 150){
      bdelay = millis() + 100;
      delay(100);
      return 5;
    }
  }
  
  return 0;
}




void loop() {
  //buttun actions
  int a=rand();
  a=rand();
  a=rand();
  a=rand();
  a=rand();
  
  int button = readBut();
  if(amaterasu==false){


  if(q==0){
    int y=rand()%7+1;
    P=interacction(y);
    P->clearPiece();
    P->generate1();
    q++;
  }
  if (button == 1) //up=rotate
    P->turnRight();
  if (button == 2) //right=moveright
    if(mov_der(*P)){
      P->posX++;
    }
  if (button == 3) //left=moveleft
    if(mov_izq(*P)){
      P->posX--;
    }
  if (button == 4) //down=movedown
    if(bajar(*P)){
      P->posY++;
  }
  if (button == 5){ //pause
      art_atack=true;
      amaterasu=true;
  }
  
  
  
  
  showTime(*P);
  if (amaterasu==false){
    if (delays < millis())
    {
        delays = millis()+delay_;
        if(bajar(*P)){
          P->posY++;
        }
        else {
           puntaje+=8;
           
           int z=rand()%7+1;
           overlap(*P);
           correction();
           char cadena[16];
           delay_-=5;
           lcd.setCursor(6, 1);  // set the cursor to column 0, line 1
           sprintf(cadena, "%d", puntaje);
           
           lcd.print(cadena);
           
           showTime(*P);
           P=interacction(z);
           P->clearPiece();
           P->generate1();
           
           if(!bajar(*P)){
            z=rand()%7+1;
            P=interacction(z);
            P->clearPiece();
            P->generate1();
            delay(1000);
            amaterasu = true;
            lose=true;
           }
        }
      //if(delays==0){
        
      
    }
  }  
  }
    else{
      if(lose==true){
           if (button == 5 ){
              inicialice();
              puntaje=0;
              lose=false;
              amaterasu=false;
              char cadena[16]="0    ";
              delay_=500;
              lcd.setCursor(6, 1);  // set the cursor to column 0, line 1
              lcd.print(cadena);
           }
      }
      else if (button == 5 ){ //reinicio
          if(art_atack == true){
            amaterasu=false;
            q=1;
            delay(1000);
            art_atack=false;
          }
        else {
            inicialice();//reto tokio
        }
      }
      else if((button==1 || button==2 || button==3 ||button==4 ) && art_atack == true){
           amaterasu=false;
           art_atack=false;
      }
        
      }
  
  
  }
  
