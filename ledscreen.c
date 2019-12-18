/* Ledscreen driver library for microcontrollers
 * Author: Ville-Pekka Lahti (C) 2019
 * vp@wdr.fi
 * +358504686300
 * This project is tested with AtMega328P @ 20MHz
 */


/*
Heidin joululahja 2019

KK  KK    OOO     OOO    DDDDDD        A      RRRRRR   II  NNNN    NN
KK KK    O   O   O   O   DD   DDD     AAA     RR   RR  II  NN NN   NN
KKKK    O     O O     O  DD    DD    AA AA    RRRRRRR  II  NN  NN  NN
KKK     O     O O     O  DD    DD   AA   AA   RRR      II  NN   NN NN
KK KK    O   O   O   O   DD    DD  AAAAAAAAA  RR RR    II  NN    NNNN
KK  KKK   OOO     OOO    DDDDDD   AA       AA RR   RR  II  NN     NNN


  SSSSS  TTTTTTTTTT     A       RRRRRR   TTTTTTTTTTTTTTTTTTTTTTT  II
SS           TT        AAA      RR   RR      TT        TT         II
  SSSSS      TT       AA AA     RRRRRRR      TT        TT         II
     SS      TT      AA   AA    RRR          TT        TT         II
     SS      TT     AAAAAAAAA   RR RR        TT        TT         II
SSSSSSS      TT    AA       AA  RR   RR      TT        TT         II
        

Tämä tiedosto (ledscreen.c) on tekemäni ledscreen-kirjasto lahjassa
mukana tulleelle LED-paneelille. Kirjasto tarkoittaa kooditiedosto-
kokoelmaa, jossa on tarvittavia funktioita (aliohjelmia) yksinker-
taisten toimintojen suorittamiseksi.

Ohjelmointi on ohjeiden antamista tietokoneelle. Ohjeiden
antamisessa pätee sama kuin normaalissa elämässäkin, eli ohjeet tulee
olla mahdollisimman yksinkertaisia. Tietokone on vain laskukone.
Ennen kuin tietokoneelle voi kertoa ohjeita helpolla tavalla, se
pitää opettaa ymmärtämään abstrakteja rakenteita.

Siksipä ohjeet asioiden, kuten LED-valon sytyttämiseen, koostuvat
sarjasta pienempiä palasia. Tämä kirjasto on tehty tulkkkaamaan
tietokoneen sisäisen maailman juttuja vähän helpommin ymmärrettävään
muotoon, jotta koodaamisen aloittaminen olisi hieman helpompaa.
Koodaus itsessään voi olla joko helppoa tai vaikeaa, ja se riippuu
myös siitä, kuinka abstraktilla tasolla liikutaan.

***Funktio*** on ohjelman osanen, joka suorittaa pienen tehtävän.
Sille voidaan antaa parametreina tietoa ja se voi myös antaa tuloksena
tietoa. Se voi myös vain suorittaa jonkin toiminnon. Funktioita
sopivasti ketjuttamalla sisäkkäin voidaan rakentaa monimutkaisia
kokonaisuuksia, jotka on koodarin helppo ymmärtää. Jokaisesta pienestä
yksityiskohdasta onkin hyvä tehdä ensin oma funktio, jotta sitä voi
sitten uudelleenkäyttää monissa eri ohjelman kohdissa.

Esimerkiksi jos halutaan piirtää kuva, niin ei yritetä piirtää koko
kuvaa kerralla vaan piirretään yksi pikseli yhdellä funktiolla.
Sen jälkeen kun yhden pikselin piirto toimii, voidaan tehdä toinen
funktio, joka osaa piirtää kuvan pikselifunktiota käyttäen. 
Kun tämä toimii, voidaan tehdä animaation toistamiseen kykenevä 
funktio, joka käyttää kuvanpiirtämisfunktiota (jne).

Tämä kirjasto sisältää juuri tällaisia funktioita, joita esittelen alla.


Alta löytyy huomattava määrä tietoa tämän kirjaston funktioista, joihin kannattaa
tutustua huolellisesti. Tähän tiedostoon ei parane kirjoittaa omia ohjelmia,
mutta pieniä muokkauksia voi kokeilla tehdä asetuksiin, lukuihin jne...

Avaa sublimeen main.c -tiedosto. Tämä on varsinainen suoritettava ohjelma, 
jota voi muokata. Palaa kuitenkin tänne aina hakemaan vinkkiä, jos haluat tietää,
kuinka joku tietty funktio toimii tai mitä se parametrikseen haluaa.
*/




// Tämäkin kirjasto hyödyntää muiden aikaisemmin tekemää koodia. Kirjastot
// liitetään ohjelmakoodiin #include -avainsanaa käyttäen, kuten alla

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Tämä on header-tiedosto. Sen tarkoitus on kertoa kääntäjälle, mitä
// funktioita tämä kirjasto sisältää, jotta niitä voi hyödyntää muualla.
// Etsi tiedosto vasemmalta ja katso sen sisälle
#include "ledscreen.h"


// Täällä on taas laitekohtaisia ajureita juuri AtMega328P -mikrokontrollerille
#include "drivers/atmega328p.h"
// Tästä kirjastosta olisikin suhteellisen helposti tehtävissä LED-paneelin 
// ajuri myös monelle muulle laitteelle, tarvitsisi vain kirjoittaa
// tuossa tiedostossa oleva koodi uudestaan.
// Avaa kyseinen tiedosto vasemmasta reunasta ja katso, mitä siellä on


// Tässä on ensimmäinen funktio.
// void-avainsana kertoo, että funktio ei palauta arvoa, se vain suorittaa 
// jonkin komentosarjan.
// void-avainsanaa seuraa funktion nimi ja sulut. Tyhjät sulut tarkoittavat,
// että funktio ei tarvitse mitään pohjatietoa (parametreja) suorittaakseen
// sille määritellyt toiminnot.
void LCD_init() {
	// funktio kutsuu toista funktiota.
	// Vie hiiren kursori funktion päälle. Sublime kertoo, missä funktio on
	// määritelty. Voit klikata linkkiä ja avata tiedoston katsoaksesi, miltä
	// siellä näyttää.

	// Tämän funktion tarkoitus on alustaa (initialize, init) LED-paneelia 
	// ohjaava yksikkö alkutilaan niin, että se on valmiina vastaanottamaan komentoja 
	__LCD_DRIVER_INIT();
}

// Tämä kirjoittaa LCD-paneelille nollan
inline void _LCD_write_zero() {
	__LCD_DRIVER_WRITE_ZERO_SIG_UP();
	__LCD_DRIVER_WRITE_ZERO_SIG_UP_AFTER();
	__LCD_DRIVER_WRITE_ZERO_SIG_DOWN();
	__LCD_DRIVER_WRITE_ZERO_SIG_DOWN_AFTER();
}

// Tämä kirjoittaa LCD-paneelille ykkösen
inline void _LCD_write_one() {
	__LCD_DRIVER_WRITE_ONE_SIG_UP();
	__LCD_DRIVER_WRITE_ONE_SIG_UP_AFTER();
	__LCD_DRIVER_WRITE_ONE_SIG_DOWN();
	__LCD_DRIVER_WRITE_ONE_SIG_DOWN_AFTER();
}

// Tämä resetoi LCD_paneelin eli kertoo sille, että
// ennen tätä piirretty pikseli oli viimeinen ennen kuin aloitetaan alusta
inline void _LCD_write_reset() {
	__LCD_DRIVER_WRITE_RESET();
	__LCD_DRIVER_WRITE_RESET_AFTER();
}

// Tämä lähettää LCD-paneelille yhden värikomponentin; punaisen, vihreän tai sinisen.
// Nyt funktiolle on määritelty parametri nimeltä "val" (value, arvo).
// Tämän parametrin tietotyyppi on uint8_t.
// Se on lyhenne sanoista unsigned integer 8-bit, eli etumerkitön kokonaisluku, 8 bittiä.
// Tämä tarkoittaa, että val voi olla jokin luku väliltä 0-255
// Lisätietoa ja lisää tietotyyppejä löytyy 
// googlaamalla "C tietotyypit" tai "C data types". https://en.wikipedia.org/wiki/C_data_types
inline void _LCD_send_component(uint8_t val) {
	// tässä alla on "kommentoituna" koodirivi,
	// joka jakaa jokaisen pikseliarvon 8:lla.
	// LED-paneeli on niin tehokas, että virta ei välttämättä aina riitä. Tällöin voidaan
	// himmentää näyttöä jakamalla pikseliarvo luvulla, jolloin sähköä ei kulu niin paljoa.

	// poista tarvittaessa kauttaviivat allaolevasta rivistä, jos LED-paneeli ei toimi tai
	// väri on punaiseen taittuva. Se on merkki liian vähäisestä sähkönsaannista.
	// Kokeile myös muuttaa lukua (alkuperäinen on 8)

	val = val / 8;

	// tässä on for-loop (silmukka), jossa muutetaan val-muuttujaan tallennettu luku
	// nolliksi ja ykkösiksi ja kirjoitetaan ne LCD-paneelille ajurifunktioiden avulla
	for (uint8_t i=0;i<8;i++) {
		if ((val >> (7-i)) & 1) {
			_LCD_write_one();
		} else {
			_LCD_write_zero();
		}
	}
}

// Tämä lähettää LCD_paneelille yhden värin
// Komponentit lähetetään GRB (vihreä-punainen-sininen) -järjestyksessä
inline void _LCD_send_color(uint8_t r, uint8_t g, uint8_t b) {
	_LCD_send_component(g);
	_LCD_send_component(r);
	_LCD_send_component(b);
}

// Tämä osaa piirtää yhden pikselin virtuaaliselle LED-paneelille.
// Parametrina funktiolle annetaan x- ja y-koordinaatit sekä väri (r,g,b)
void LCD_drawpixel(int8_t _x, int8_t _y, uint8_t r, uint8_t g, uint8_t b) {

	// käsitellään koordinaatteja seuraavasti:
	// Jos piirretään LED-paneelin ulkopuolelle, pikseli hyppääkin reunoilta
	// yli samaan tapaan kuin Nokian puhelinten vanhoissa matopeleissä ;)
	// Lisäksi on olemassa x_offset ja y_offset -muuttujat.
	// Niiden avulla piirrettävää kuvaa voi helposti liikuttaa yhtenä
	// kokonaisuutena LED-paneelissa ilman, että kuvaa tarvitsee "piirtää"
	// uudelleen
	int8_t x=(_x + x_offset) % SCREEN_W;
	int8_t y=(_y + y_offset) % SCREEN_H;


	// Jos käytössä on kaksi LED-paneelia allekkain, tehdään pieni muutos
	// koordinaattien laskentaan, jotta piirtäminen toimii loogisesti
	#ifdef SECOND_PANEL_ON_BOTTOM
		if (y >= PANEL_H) {
			y-=PANEL_H;
			x+=PANEL_W;
		}
	#endif /* SECOND_SCREEN_ON_BOTTOM */

	// Jos LED-paneelin pikselit on ketjutettu siksakmaisesti (katso paneelin pohja),
	// se vaatii muutoksia myös koordinaattien käsittelyyn, jotta siksak voidaan
	// "oikaista"
	#ifdef PANEL_LAYOUT_ZIGZAG
		if (x % 2) {
			y = 7-y;
		}
	#endif

	// kirjoitetaan virtuaaliselle näytölle oikeisiin koordinaatteihin oikeat väriarvot
	screen[x*PANEL_H+y][0] = r;
	screen[x*PANEL_H+y][1] = g;
	screen[x*PANEL_H+y][2] = b;
}

// Tämä piirtää etukäteen muistiin ohjelmoidun värikuvan näytölle. Monimutkaisempi juttu!
void LCD_draw_color_image(const uint8_t data[], uint16_t w, uint16_t h) {
	// käydään läpi kuvan kaikki rivit
	for (uint16_t y=0;y<h;y++) {
		// käydään jokaisen rivin sisällä läpi kuvan kaikki sarakkeet
		for (uint16_t x=0;x<w;x++) {
			// piirretään yksi pikseli kuvasta.
			LCD_drawpixel(
				x,
				y,
				#ifdef AVR_PGMMEM
				pgm_read_byte(&data[(uint16_t)(y*w*3+x*3+0)]),
				pgm_read_byte(&data[(uint16_t)(y*w*3+x*3+1)]),
				pgm_read_byte(&data[(uint16_t)(y*w*3+x*3+2)])
				#else
				data[(uint16_t)(y*w*3+x*3+0)],
				data[(uint16_t)(y*w*3+x*3+1)],
				data[(uint16_t)(y*w*3+x*3+2)]
				#endif
			);

			// jos käytössä on AVR_PROGMEM eli mikrokontrollerin flash-muistialueelta
			// piirtäminen, osataan käyttää tästä muistista lukemiseen tarkoitettuja
			// funktioita, kun koodi tehdään näin.

			// Huomattavaa on, että LCD_drawpixel -funktion funktiokutsu on jaettu monelle riville!
		}
	}
}

// Piirretään virtuaalinäyttö oikeasti LCD-paneelille lähettämällä väriarvot peräkkäin sille.
// Lopuksi resetoidaan LCD-paneeli, jotta seuraavaksi lähetettävä väri menee ensimmäiselle pikselille
void LCD_drawscreen() {
	for (uint16_t i=0;i<SCREEN_SIZE;i++) {
		_LCD_send_color(screen[i][0],screen[i][1],screen[i][2]);
	}
	_LCD_write_reset();
}

// tyhjennetään virtuaalinen näyttö. Tämä ei yksin sammuta LCD-paneelin pikseleitä, vaan tämän
// jälkeen pitää vielä kutsua LCD_drawscreen -funktiota
void LCD_clearscreen() {
	memset(&screen, 0, SCREEN_SIZE);
}

// Tämä pimentää virtuaalisen näytön pikseleitä vähitellen. Voi käyttää hienojen fade-efektien tekoon,
// kun kutsuu tätä funktiota yhdessä LCD_drawscreenin kanssa
void LCD_clearscreen_fade() {
	for (int i=0;i<SCREEN_SIZE;i++) {
		if (screen[i][0]) {
			screen[i][0] /= 1.15;
		}
		if (screen[i][1]) {
			screen[i][1] /= 1.15;
		}
		if (screen[i][2]) {
			screen[i][2] /= 1.15;
		}
	}
}

// Tämä piirtää viivan annetuista X0,Y0 -koordinaateista X1,Y1 -koordinaatteihin käyttäen väriä r,g,b
// Algoritmi on napattu netistä ja on melko tarpeetonta selittää sitä tarkemmin auki, se on vaikea
// koodarillekin :)
void LCD_drawline(int8_t X0, int8_t Y0, int8_t X1, int8_t Y1,uint8_t r, uint8_t g, uint8_t b)
{
	if (X0 == X1) {
		if (Y0 > Y1) {
			int8_t t = Y0;
			Y0 = Y1;
			Y1 = t;
		}
		while(Y1 > Y0) {
			LCD_drawpixel(X0,Y1,r,g,b);
			Y1--;
		}
		LCD_drawpixel(X0,Y1,r,g,b);
		return;
	} else if (Y0 == Y1) {
		if (X0 > X1) {
			int8_t t = X0;
			X0 = X1;
			X1 = t;
		}
		while(X1 > X0) {
			LCD_drawpixel(X1,Y0,r,g,b);
			X1--;
		}
		LCD_drawpixel(X1,Y0,r,g,b);
		return;
	} else {
		// calculate dx , dy
		float dx = X1 - X0;
		float dy = Y1 - Y0;

		// Depending upon absolute value of dx & dy
		// choose number of steps to put pixel as
		// steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy)
		float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

		// calculate increment in x & y for each steps
		float Xinc = dx / steps;
		float Yinc = dy / steps;

		// Put pixel for each step
		float X = X0;
		float Y = Y0;
		for (int i = 0; i <= steps; i++)
		{
		    LCD_drawpixel(X,Y,r,g,b);
		    X += Xinc;
		    Y += Yinc;
		}
	}
}

// Tässä lasketaan 2d-koordinaatti x käyttäen hyväksi annettuja 3d-koordinaatteja
int c_3d_to_2d_x(int x, int y, float z) {
	return ((x) / (float)((float)z));
}

// Tässä lasketaan 2d-koordinaatti y käyttäen hyväksi annettuja 3d-koordinaatteja
int c_3d_to_2d_y(int x, int y, float z) {
	return ((y) / (float)((float)z));
}

// Tässä piirretään taulukoituja 3d-viivoja LED-paneelille
void LCD_draw_voxel_lineset(int8_t lineset[], uint8_t len, uint8_t r, uint8_t g, uint8_t b) {
	for (uint8_t i=0;i<len;i++) {
		int8_t x1 = c_3d_to_2d_x(lineset[i*6+0],lineset[i*6+1],lineset[i*6+2]);
		int8_t y1 = c_3d_to_2d_y(lineset[i*6+0],lineset[i*6+1],lineset[i*6+2]);
		int8_t x2 = c_3d_to_2d_x(lineset[i*6+3],lineset[i*6+4],lineset[i*6+5]);
		int8_t y2 = c_3d_to_2d_y(lineset[i*6+3],lineset[i*6+4],lineset[i*6+5]);
		LCD_drawline(x1,y1,x2,y2,r,g,b);
	}
}