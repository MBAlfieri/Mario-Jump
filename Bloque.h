#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "imageManager.h"

using namespace std;
using namespace sf;

//--------------------------------------------------------------------------Clase "Bloque"
class Bloque {
private:

	int numero; //Es el número al azar que tendrá el Bloque.
	imageManager img_mgr; //Es el Image Manager (Sacado de los apuntes a estudiar).
	Text textoNumero; //Es el texto que muestra los puntos.
	String Stringnumero; //String que contiene el texto.
	Font font; //Es la fuente del texto.
	sf::Sprite bloque; //Sprite del Bloque.

public:

	Bloque(); //Constructor

	int getNumeroEntero() { return numero; } //Me devuelve el número al azar del Bloque.
	Sprite getSpritebloque() { return bloque; }; //Me devuelve el Sprite del Bloque.
	Text getNumero() { return textoNumero; } //Me devuelve el Texto que posee el número al azar del Bloque (para verl en pantalla)

	void setColorBloque() { textoNumero.setColor(sf::Color::Green); }; //Cambia el color del Bloque a verde.

	void setPosiblePosicion1() { bloque.setPosition(0, 250); textoNumero.setPosition(10, 263);}; //Es la posible posición en pantalla que tendrá el bloque.
	void setPosiblePosicion2() { bloque.setPosition(80, 250); textoNumero.setPosition(90, 263);}; //Idem.
	void setPosiblePosicion3() { bloque.setPosition(160, 250); textoNumero.setPosition(170, 263);};//Idem.
	void setPosiblePosicion4() { bloque.setPosition(240, 250); textoNumero.setPosition(250, 263);};//Idem.
	void setPosiblePosicion5() { bloque.setPosition(320, 250); textoNumero.setPosition(330, 263);};//Idem.
	void setPosiblePosicion6() { bloque.setPosition(400, 250); textoNumero.setPosition(410, 263);};//Idem.
	void setPosiblePosicion7() { bloque.setPosition(480, 250); textoNumero.setPosition(490, 263);};//Idem.
	void setPosiblePosicion8() { bloque.setPosition(560, 250); textoNumero.setPosition(570, 263);};//Idem.
	void setPosiblePosicion9() { bloque.setPosition(640, 250); textoNumero.setPosition(650, 263);};//Idem.
	void setPosiblePosicion10() { bloque.setPosition(720, 250); textoNumero.setPosition(730, 263);};//Idem.

	void setPosicionRemover() { textoNumero.setPosition(-100, -100); } //Basicamente "escondo el array", y al final del juego muestro otro.

};

