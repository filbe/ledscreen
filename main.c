/* Ledscreen driver library for microcontrollers
 * Author: Ville-Pekka Lahti (C) 2019
 * vp@wdr.fi
 * +358504686300
 * This project is tested with AtMega328P @ 20MHz
 */


#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <util/delay.h>

#include "ledscreen.h"


/*

Jokaisessa tietokoneohjelmassa on main-funktio. Tästä ohjelman suoritus varsinaisesti alkaa, ja mitään muuta ei edes suoriteta.
Idea on siinä, että main-funktiosta voidaan kutsua muita funktioita, jotka voivat olla myös eri tiedostoissa tai kirjastoissa.

Tässä ollaan "includetettu" ledscreen-ohjain (ledscreen.h ja ledscreen.c -tiedostot)
Koodissa tätä .c -tiedostojen includetusta ei suoraan näy, mutta Makefile-tiedostoa tutkimalla se selviäisi.
Ei mennä nyt siihen vaan luotetaan, että Makefile osaa hoitaa homman ja sisällyttää kaikki .c -tiedostot projektiin automaattisesti.

Kun ollaan suoritettu main-funktio, ohjelman suoritus loppuu kokonaan ja siihen mahdollisesti liittyvät sovellusikkunat sulkeutuvat.
Koska nyt ei kuitenkaan koodata tietokoneohjelmaa vaan mikropiirin ohjainta, ohjelma vain "kaatuu" ja mikropiiri jää HALT-tilaan.

Käytännössä ohjelmaa aletaan suorittaa alusta heti, kun laitteeseen kytketään virta.

*/


// ****************
// FUN FACTS
// AtMega328P:ssa on RAM-muistia vain vaivaiset 2 kilotavua, eli siihen voidaan tallentaa maksimissaan 2 048 kpl numeroita, 
// joista kukin voi olla väliltä 0-255. Tämä on naurettavan vähän, ja usein onkin haaste saada järkeviä ohjelmia tehtyä näin pienillä
// resursseilla. Flash-muistia, jonne ohjelmointikoodia ja vain luku -tyyppistä tietoa voidaan tallentaa, löytyy 32 kilotavua.
// Tänne voidaan tallentaa yksinkertaisia kuvia. Huomattavaa on, että yksi kokonainen kuva piirrettynä LED-paneelille vie
// 32 x 8 x 3 = 256 tavua. Koska koodi vie jonkun verran tilaa, voidaan karkeasti sanoa, että laitteelle voidaan tallentaa noin 78 kpl
// 32 x 8 pikselin kokoisia värikuvia täydellä värisyvyydellä (16,7 miljoonaa erilaista väriyhdistelmää)
// ****************


int main() {

	// tehdään muutama tärkeä asetus
	LCD_init();

	// alustetaan pari tärkeää muuttujaa
	x_offset = 0;
	y_offset = 0;
	z_offset = 0;


	// Koska halutaan, että ohjelmaa suoritetaan jatkuvasti eikä se ikinä pysähdy, tehdään "ikuinen silmukka".
	// Kaikkia while(1) { ja sitä vastaavan } välissä oleva suoritetaan ikuisesti


	while(1) {
		// tyhjennetään näyttöpuskuri, jotta aloitetaan joka kierroksella aina "puhtaalta pöydältä"
		LCD_clearscreen();

		// Piirretään H käyttäen viivanpiirtofunktiota.
		// Ensimmäinen parametri kertoo viivan lähtöpisteen x-koordinaatin, toinen y-koordinaatin.
		// Kolmas ja neljäs ovat päätepisteen x- ja y-koordinaatit.
		// Niitä seuraa väri, joka muodostuu punaisesta, vihreästä ja sinisestä värikomponentista
		LCD_drawline(3,0,0,3,255,0,0);
		LCD_drawline(7,0,4,3,255,0,0);
		LCD_drawline(2,1,5,2,255,0,0);

		// Y
		LCD_drawline(8,3,11,0,255,0,0);
		LCD_drawline(9,2,9,0,255,0,0);

		// V
		LCD_drawline(13,0,12,3,255,0,0);
		LCD_drawline(15,0,12,3,255,0,0);

		// Ä
		LCD_drawline(18,3,18,0,255,0,0);
		LCD_drawline(15,3,18,0,255,0,0);
		LCD_drawline(17,0,19,0,255,0,0);
		LCD_drawpixel(17,2,255,0,0);

		// Ä
		LCD_drawline(22,3,22,0,255,0,0);
		LCD_drawline(19,3,22,0,255,0,0);
		LCD_drawline(21,0,23,0,255,0,0);
		LCD_drawpixel(21,2,255,0,0);


		// J
		LCD_drawline(10,4,7,7,255,0,0);
		LCD_drawline(7,7,6,6,255,0,0);

		// O
		LCD_drawline(12,7,9,7,255,0,0);
		LCD_drawline(12,4,15,4,255,0,0);
		LCD_drawline(12,7,15,4,255,0,0);
		LCD_drawline(9,7,12,4,255,0,0);

		// U
		LCD_drawline(17,7,14,7,255,0,0);
		LCD_drawline(17,7,20,4,255,0,0);
		LCD_drawline(14,7,17,4,255,0,0);

		// L
		LCD_drawline(21,7,19,7,255,0,0);
		LCD_drawline(19,7,22,4,255,0,0);

		// U
		LCD_drawline(26,7,23,7,255,0,0);
		LCD_drawline(26,7,29,4,255,0,0);
		LCD_drawline(23,7,26,4,255,0,0);

		// A
		LCD_drawline(31,7,31,4,255,0,0);
		LCD_drawline(28,7,31,4,255,0,0);
		LCD_drawpixel(30,6,255,0,0);

		// HUOM! Tässä piirrettiin vain yksittäinen pikseli LCD_drawpixel -funktiolla.
		// Se sai parametrikseen vain yhden pisteen x- ja y-koordinaatit sekä värikomponentit.


		// Tähän mennessä ollaan piirretty viivoja ja pisteitä vain virtuaalisesti ohjelman muistiin.
		// Seuraava funktio vasta oikeasti lähettää tiedot LED-paneelille.
		// Se tehdään sen takia, että pikselit pitää lähettää paneelille järjestyksessä, mutta tietyn
		// pikselin muistiin kirjoittamisen aikana emme tiedä, onko muita pikseleitä tulossa ennen
		// nyt kirjoitettavaa pikseliä. Siksi "valmistelemme" ensin näyttöön piirrettävän kuvan
		// mikrokontrollerin muistiin ja vasta sitten kun kaikki on valmista, lähetämme tiedon eteenpäin.
		LCD_drawscreen();

		// x_offset ja y_offset -muuttujat lisäävät x- tai y-koordinaatteihin kiinteän luvun. Kun näitä arvoja
		// muutetaan jokaisella kierroksella, se saa LED-paneelille piirretyn kuvan liikkumaan vaaka- tai pystysuunnassa.
		// Kokeile poistaa kommentti y_offset -rivin alusta. Miten toiminta muuttui?
		x_offset = x_offset - 1;
		//y_offset = y_offset + 1;
		_delay_ms(100);
	}
	return 0;
}
