#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "imageManager.h"
#include "Bloque.h"

Bloque::Bloque() { //Constructor.

	numero = rand() % 999 + 1; //Genera un número del 1 al 999.

	img_mgr.addResourceDirectory("Recursos/Imagenes/"); //Carga el directorio de la Textura del bloque.

	bloque.setTexture(img_mgr.getImage("bloque_pared.png")); //Carga la Textura del Bloque

	font.loadFromFile("GILB.ttf"); //Carga la fuente

		Stringnumero = to_string(numero); //Me deposita el número en el String.
		textoNumero.setFont(font); //Define la fuente a utilizar.
		textoNumero.setScale(1.2, 1.2); //Define el tamaño del texto.
		textoNumero.setColor(sf::Color::Yellow); //Define el color del texto.
		textoNumero.setString(Stringnumero); //Define qué va a mostrar el texto.
		textoNumero.setOutlineThickness(2); //Define el grosor del borde del texto.
		textoNumero.setOutlineColor(sf::Color::Black); //Define el color del borde del texto.

}

