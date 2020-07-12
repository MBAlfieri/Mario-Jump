//Universidad Nacional del Litoral
//Programación de Videojuegos I
//Alumna: Micaela B. Alfieri
//Año: 2020 


//He decidido utilizar el código base ofrecido en la sección "Actividad" presente en la Unidad 1 - Plan de Trabajo 3, junto con el Contador/Reloj.
//También le cambié el tamaño al Mario, ya que el tamaño del Sprite original hacía que colisione con dos Bloques al
//mismo tiempo. (Era muy grande originalmente en comparación con los bloques y la cercanía entre ellos).

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "imageManager.h"
#include "Bloque.h"

using namespace std;
using namespace sf;


//--------------------------------------------------------------------------Métodos. (Se encuentran más explicados al final).

void actualizarSalto(); //Verifica las condiciones del salto.
void dibujar();//Dibuja en pantalla todos los Sprites.
void bubbleSortAux(); //Ordena el Array de menor a mayor.
void auxiliarOrdenadoPantalla(); //Muestra el Array ordenado en la pantalla.
void sonidos(); //Carga los sonidos del juego
void detenerPersonaje(); //Detiene el movimiento del personaje
void actualizarContador(); //Es el reloj/contador del juego.


//---------------------------------------------------------------------------Declaraciones.

sf::RenderWindow window(sf::VideoMode(800, 600), "Mario-Jump!"); //Crea la ventana del juego.

const int POSICION_TERRENO_Y = 473; //Posicion del personaje en Y.
const int MAX_ASCENSO_SALTO_Y = 141; //Límite del salto del personaje en Y.
const int TIEMPO_JUEGO = 60; //Tiempo límite del juego.

int auxiliarOrdenado[10]; //Acá se deposita el Array de la Clase "Bloque" y se lo ordena luego.

int indice = 0; //Es el índice que permite saber cuántos bloques se han presionado, y ayuda a detectar
				//Si los números en el Array "Bloques" coincide con el Array Auxiliar Ordenado.

float tiempoInicio; //Es el inicio del tiempo/juego.
float tiempoFin;// Es el fin del tiempo / juego.

bool teclaSaltoPresionada = false; //Maneja los elementos del salto del Personaje
bool enAscenso = false;// Idem.
bool saltoEnProceso = false; //Idem.

sf::Sprite personaje; //Sprite del Personaje
sf::Sprite fondo; //Sprite del Fondo.

Bloque *bloquePuntos[10]; //Objeto de la Clase "Bloque"

sf::Text textoNumero[10]; //Es el texto que muestra los números del Array "Bloques".
sf::Text textoNumeroFinal[10]; //Es el texto que muestra los números del Array Auxiliar Ordenado.
sf::Text textoContador; //Es el texto del contador/reloj.
String Stringnumero[10]; //Es el string que muestra los números del Array "Bloques".
String stringNumeroFinal[10]; //Es el string que muestra los números del Array Auxiliar Ordenado.
Font font; //Es la fuente del texto.

sf::Clock reloj; //Variable del reloj.

sf::SoundBuffer b_Salto; //Buffer del sonido del Salto del Personaje.
sf::Sound s_Salto; //Sonido del salto del Personaje.

sf::SoundBuffer b_bloque; //Buffer del sonido del golpe contra el Bloque.
sf::Sound s_bloque; //Sonido del golpe contra el Bloque.

sf::SoundBuffer b_fanfare; //Buffer del sonido de Victoria.
sf::Sound s_fanfare; //Sonido de Victoria.

Music musica; //Música del juego y Tick-Tock del reloj.


int main() {
	//------------------------------Sonidos
	sonidos(); //Cargo los sonidos.
	s_Salto.setVolume(20); //Cambia el volumen del sonido.
	s_fanfare.setVolume(50);//Idem
	musica.setVolume(20);//Idem
	musica.play();//Reproduce la música/tick-tock del reloj.

	//--------------------------------Texto
	font.loadFromFile("GILB.ttf"); //Cargo la fuente a utilizar.
	textoContador.setFont(font); //Define la fuente a utilizar.
	textoContador.setColor(sf::Color::Yellow);//Define el color del texto.
	textoContador.setCharacterSize(30);//Define el tamaño de la letra.
	textoContador.setOutlineColor(sf::Color::Black);//Define el color del borde del texto.
	textoContador.setOutlineThickness(2);//Define el grosor del borde del texto.


	srand(time(NULL));//Randomizador.


	tiempoInicio = reloj.getElapsedTime().asSeconds() + TIEMPO_JUEGO; //Inicia el reloj.


	for (int i = 0; i < 10; i++) { //Cargo el Array con Bloques.
		bloquePuntos[i] = new Bloque; //Voy creando un bloque nuevo, y los guardo en mi array.
		auxiliarOrdenado[i] = bloquePuntos[i]->getNumeroEntero(); //Deposito los números en mi auxiliar
	}

	bloquePuntos[0]->setPosiblePosicion1(); //Ubico los bloques en la pantalla con sus respectivos números.
	bloquePuntos[1]->setPosiblePosicion2(); //Idem
	bloquePuntos[2]->setPosiblePosicion3(); //Idem
	bloquePuntos[3]->setPosiblePosicion4(); //Idem
	bloquePuntos[4]->setPosiblePosicion5(); //Idem
	bloquePuntos[5]->setPosiblePosicion6(); //Idem
	bloquePuntos[6]->setPosiblePosicion7(); //Idem
	bloquePuntos[7]->setPosiblePosicion8(); //Idem
	bloquePuntos[8]->setPosiblePosicion9(); //Idem
	bloquePuntos[9]->setPosiblePosicion10(); //Idem

	bubbleSortAux(); //Ordeno el Array Auxiliar.


	imageManager img_mgr;//Se crea una instancia del objeto imageManager

	window.setFramerateLimit(60);//Limito los FPS del juego.


	img_mgr.addResourceDirectory("Recursos/Imagenes/");//Se asigna la carpeta relativa donde se alojan nuestras imágenes

	personaje.setTexture(img_mgr.getImage("jumper.png"));//Se carga la textura del Jugador.
	personaje.setPosition(400, 473);//Se define el tamaño del Sprite del Jugador.

	fondo.setTexture(img_mgr.getImage("mundo_fondo.png")); //Cargo la textura del fondo.
	
	

	while (window.isOpen()) {//Detección de eventos de SFML

	//------------------------------Colisiones Pt1.
		FloatRect colisionPersonaje = personaje.getGlobalBounds(); //Obtengo los Bounds del Personaje para realizar las colisiones con los Bloques..

		FloatRect colisionBloques[10];//Creo un Array para guardar todas las colisiones de todos los Bloques.
		for (int i = 0; i < 10; i++) { //Genero las colisiones para todos los bloques.

			colisionBloques[i] = bloquePuntos[i]->getSpritebloque().getGlobalBounds(); //Deposito todas las colisiones de todos los Bloques en el Array.
		}



	//------------------------------Eventos.
		sf::Event event; //Instancia de Evento.
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) { //Permite cerrar la ventana.
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) { //Detecta si se presiona la Barra Espaciadora para saltar.
				teclaSaltoPresionada = true;
				s_Salto.play(); //Reproduce el sonido del Salto.
				
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {//Detecta si no se presiona la Barra Espaciadora para saltar.
				teclaSaltoPresionada = false;}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {//Hace que el personaje se mueva hacia la izquierda.
			personaje.setPosition(personaje.getPosition().x - 6, personaje.getPosition().y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {//Hace que el personaje se mueva hacia la derecha
			personaje.setPosition(personaje.getPosition().x + 6, personaje.getPosition().y);

		}



	//------------------------------Colisiones Pt2.



		for (int i = 0; i < 10; i++) {
			if (indice == i && colisionPersonaje.intersects(colisionBloques[0])) {//Detecta la colisión entre el Personaje y el Bloque y verifica si es el orden correcto. Lo mismo pasa en todos los "for" de esta instancia.
				if (bloquePuntos[0]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[0]->setColorBloque(); //Si se golpeó el Bloque correcto, este cambia de color.
					indice++; //Si se golpea el bloque correcto, se "gana" un punto de indice.
					s_bloque.play();}//Se reproduce el sonido del golpeo del Bloque. Solo se escucha si se golpea el correcto.
				if (((bloquePuntos[0]->getNumeroEntero()) > (auxiliarOrdenado[i]))){ //Si el número en el Bloque es mayor al del Array, se pierde tiempo.
					tiempoInicio -= 10;}
			}
		}
		
		for (int i = 0; i < 10; i++) { //Idem al caso anterior.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[1])) {
				if (bloquePuntos[1]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[1]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[1]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[2])) {
				if (bloquePuntos[2]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[2]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[2]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[3])) {
				if (bloquePuntos[3]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[3]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[3]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[4])) {
				if (bloquePuntos[4]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[4]->setColorBloque();
					indice++;
					s_bloque.play();}				
				if (((bloquePuntos[4]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
						tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[5])) {
				if (bloquePuntos[5]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[5]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[5]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[6])) {
				if (bloquePuntos[6]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[6]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[6]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[7])) {
				if (bloquePuntos[7]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[7]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[7]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[8])) {
				if (bloquePuntos[8]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[8]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[8]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}

		for (int i = 0; i < 10; i++) {//Idem.
			if (indice == i && colisionPersonaje.intersects(colisionBloques[9])) {
				if (bloquePuntos[9]->getNumeroEntero() == auxiliarOrdenado[i]) {
					bloquePuntos[9]->setColorBloque();
					indice++;
					s_bloque.play();}
				if (((bloquePuntos[9]->getNumeroEntero()) > (auxiliarOrdenado[i]))) {
					tiempoInicio -= 10;
				}
			}
		}



	//------------------------------------------------------------------Condicion de victoria
		if (indice == 10) { //Si se golpean todos los bloques correctos, se gana el juego.

			musica.stop(); //Se termina el juego, se detiene la música.

			for (int i = 0; i < 10; i++) {
				bloquePuntos[i]->setPosicionRemover(); //Muevo de lugar el Array de Bloques.
				auxiliarOrdenadoPantalla(); //Reubico el Array ordenado.
				detenerPersonaje();//"Congelo" al Personaje
				tiempoInicio = 0; //Como se ganó el juego, se termina el tiempo también. (No tiene sentido que siga si ya terminó la partida)
			}}
		else {
		s_fanfare.play(); //Se reproduce la música.
		}


		//-------------------------------------------------------SALTO
		actualizarSalto(); //Es el salto del personaje.

		actualizarContador(); //Es el reloj/contador.

		//Limpia lo dibujado en ciclo anterior
        window.clear(); //Limpia la pantalla.

		dibujar(); //Dibuja en la pantalla los elementos.

		//Se muestra en ventana,lo nuevo que se ha dibujado con window.draw
        window.display();
    }

    return 0;
}


void bubbleSortAux() { //He implementado el BubbleSort de los apuntes. Ordena el Array de menor a mayor.
	int auxiliar;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (auxiliarOrdenado[j] > auxiliarOrdenado[j + 1]) {
		
				auxiliar = auxiliarOrdenado[j];
				
				auxiliarOrdenado[j] = auxiliarOrdenado[j + 1];

				auxiliarOrdenado[j + 1] = auxiliar;
			}
		}
	}

}

void auxiliarOrdenadoPantalla(){ //Se encarga de ordenar, colorear y posicionar los números y los bloques, una vez que se terminó el juego.
								 //Basicamente se "esconde" el array original (proveniente de la clase "Bloque"),
								//Y se muestra el array ordenado en su lugar.

	for (int i = 0; i < 10; i++) {
		stringNumeroFinal[i] = to_string(auxiliarOrdenado[i]);//Me deposita el número en el String.
		textoNumeroFinal[i].setFont(font); //Define la fuente a utilizar.
		textoNumeroFinal[i].setScale(1.2, 1.2); //Define el tamaño del texto
		textoNumeroFinal[i].setColor(sf::Color::Yellow); //Define el color del texto.
		textoNumeroFinal[i].setString(stringNumeroFinal[i]); //Define qué va a mostrar el texto.
		textoNumeroFinal[i].setOutlineThickness(2); //Define el grosor del borde del texto.
		textoNumeroFinal[i].setOutlineColor(sf::Color::Black); //Define el color del borde del texto.
	}

	if (indice == 0) { for (int i = 0; i < 10; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Cambia el color del Bloque a verde.
	if (indice == 1) { for (int i = 0; i < 1; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 2) { for (int i = 0; i < 2; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 3) { for (int i = 0; i < 3; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 4) { for (int i = 0; i < 4; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 5) { for (int i = 0; i < 6; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 6) { for (int i = 0; i < 7; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 7) { for (int i = 0; i < 8; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 8) { for (int i = 0; i < 9; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.
	if (indice == 10) { for (int i = 0; i < 10; i++) { textoNumeroFinal[i].setColor(sf::Color::Green); } } //Idem.

	textoNumeroFinal[0].setPosition(10, 263); //Defino la posición del texto del Array Auxiliar Ordenado.
	textoNumeroFinal[1].setPosition(90, 263); //Idem
	textoNumeroFinal[2].setPosition(170, 263); //Idem
	textoNumeroFinal[3].setPosition(250, 263); //Idem
	textoNumeroFinal[4].setPosition(330, 263); //Idem
	textoNumeroFinal[5].setPosition(410, 263); //Idem
	textoNumeroFinal[6].setPosition(490, 263); //Idem
	textoNumeroFinal[7].setPosition(570, 263); //Idem
	textoNumeroFinal[8].setPosition(650, 263); //Idem
	textoNumeroFinal[9].setPosition(730, 263); //Idem

	detenerPersonaje(); //"Congelo" al Personaje.

}

void actualizarSalto(){ //Sacado del material de estudio. Es el salto del personaje.

	if(teclaSaltoPresionada && !saltoEnProceso){
		saltoEnProceso = true;
		enAscenso = true;
	}

	if(saltoEnProceso){

		if(personaje.getPosition().y <= POSICION_TERRENO_Y - MAX_ASCENSO_SALTO_Y){
			enAscenso = false;
		}

		if(enAscenso){
			personaje.setPosition(personaje.getPosition().x, personaje.getPosition().y - 5);
		}else{
			personaje.setPosition(personaje.getPosition().x, personaje.getPosition().y + 5);
		}

		if(personaje.getPosition().y >= POSICION_TERRENO_Y){
			saltoEnProceso = false; 
			personaje.setPosition(personaje.getPosition().x, POSICION_TERRENO_Y); 
		}
	}
	
} 

void dibujar() {//Dibuja los elementos del juego.
	window.draw(fondo);

	for (int i = 0; i < 10; i++) {
		window.draw(bloquePuntos[i]->getSpritebloque());
		window.draw(bloquePuntos[i]->getNumero());
		window.draw(textoNumeroFinal[i]);
	}

	window.draw(textoContador);
	window.draw(personaje);	
} 

void actualizarContador() { //Es el contador/reloj. Presenta adentro la condición de derrota. Sacado de los apuntes a estudiar.
	tiempoFin = reloj.getElapsedTime().asSeconds();

	int seconds = ((int)(tiempoInicio - tiempoFin));

	if (seconds >= 0) {
		char buffer[20];
		sprintf_s(buffer, "Tiempo restante: %i", seconds);
		textoContador.setString(buffer);
	}

	else{ 
		textoContador.setString("¡Se terminó el tiempo!");
		textoContador.setColor(sf::Color::Red);
		textoContador.setOutlineColor(sf::Color::Black);
		textoContador.setOutlineThickness(2);

		if (indice < 10) { //Si se consiguen menos de 10 aciertos antes del tiempo límite, se pierde.
			for (int i = 0; i < 10; i++) {
				musica.stop(); //Se detiene la música.
				detenerPersonaje(); // Se "Congela" al personaje.
				bloquePuntos[i]->setPosicionRemover();// Muevo de lugar al Array desordenado.
				auxiliarOrdenadoPantalla(); //Muestro el Array Auxiliar Ordenado.

			}

		}

	}



}

void sonidos() { //Carga todos los sonidos del juego.

	b_Salto.loadFromFile("MarioJump.WAV"); //Cargo el sonido del salto.
	s_Salto.setBuffer(b_Salto);//Cargo el Buffer.

	b_bloque.loadFromFile("Coin.WAV");//Cargo el sonido del golpe al Bloque.
	s_bloque.setBuffer(b_bloque);//Cargo el Buffer.

	b_fanfare.loadFromFile("Fanfare.WAV");//Cargo el sonido de Victoria.
	s_fanfare.setBuffer(b_fanfare);//Cargo el Buffer.

	musica.openFromFile("Countdown.WAV");//Cargo la musica/tick tock.

}

void detenerPersonaje() { //Detiene al personaje. Basicamente lo "congela" en un lugar, y no se puede mover.

	personaje.setPosition(400, 473);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		personaje.setPosition(400, 473);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		personaje.setPosition(400, 473);

	}

}