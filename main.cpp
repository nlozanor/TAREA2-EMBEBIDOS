#include <avr/io.h> 
#include <util/delay.h> 
#define F_CPU 8000000 

#define RD5_PIN PC5 
#define START_PIC PC0 

// Gráficos Base
unsigned char signo[8]  = {0x0, 0x04, 0x02, 0x01, 0xB1, 0x0A, 0x04, 0x0};   // "?" Estático
unsigned char PERDER[8] = {0x81, 0xC3, 0x66, 0x18, 0x18, 0x66, 0xC3, 0x81}; // "X" 
unsigned char PORT[8]   = {1, 2, 4, 8, 16, 32, 64, 128}; 

// Gráficos de los 9 Elementos
unsigned char AGUA[8]     = {0x30, 0x78, 0xFC, 0xFE, 0xFC, 0x78, 0x30, 0x00};
unsigned char FUEGO[8]    = {0x30, 0x7C, 0xF8, 0xFC, 0xFE, 0xFC, 0xF8, 0x30};
unsigned char PLANTA[8]   = {0x00, 0x04, 0x4E, 0x76, 0x4E, 0x04, 0x00, 0x00};
unsigned char ELECTRICO[8]= {0x00, 0x08, 0x0C, 0x6E, 0x3B, 0x18, 0x08, 0x00};
unsigned char TIERRA[8]   = {0x70, 0xFC, 0x76, 0x07, 0x76, 0xFC, 0x70, 0x00};
unsigned char ROCA[8]     = {0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7C, 0x00};
unsigned char HIELO[8]    = {0x60, 0x60, 0x18, 0x78, 0x60, 0x18, 0x78, 0x60};
unsigned char ACERO[8]    = {0x38, 0x6C, 0x46, 0x02, 0x02, 0x46, 0x6C, 0x38};
unsigned char DRAGON[8]   = {0x03, 0x46, 0x64, 0x18, 0X18, 0x64, 0x46, 0x03};

void mostrarMatriz(int side, const unsigned char* imagen) { 
    if (side == 8) { 
        for (int k = 0; k < 50; k++) { 
            for (int j = 0; j < 8; j++) { 
                PORTD = PORT[j]; 
                PORTB = ~imagen[j]; 
                _delay_ms(0.05); 
            } 
        } 
    } 
} 

unsigned char binarioADecimal() { 
    return ((PINC & 0x1E) >> 1); 
} 

int main(void) { 
    DDRB = 0xFF; DDRD = 0xFF; DDRC = 0x01; PORTC = 0x00; 
    PORTC |= (1 << START_PIC); 

    while (1) { 
        unsigned char numero = binarioADecimal(); 

        if (numero == 0x0F) {
            // --- MODO ESPERA: Muestra el "?" de forma estática ---
            mostrarMatriz(8, signo); 
        }
        else if (PINC & (1 << RD5_PIN)) { 
            // --- MODO VICTORIA: Muestra el elemento de la CPU ---
            switch (numero) { 
                case 1: mostrarMatriz(8, AGUA);      break; 
                case 2: mostrarMatriz(8, FUEGO);     break; 
                case 3: mostrarMatriz(8, PLANTA);    break; 
                case 4: mostrarMatriz(8, ELECTRICO); break; 
                case 5: mostrarMatriz(8, TIERRA);    break; 
                case 6: mostrarMatriz(8, ROCA);      break; 
                case 7: mostrarMatriz(8, HIELO);     break; 
                case 8: mostrarMatriz(8, ACERO);     break; 
                case 9: mostrarMatriz(8, DRAGON);    break; 
                default: break; 
            } 
        } 
        else if (!(PINC & (1 << RD5_PIN)) && numero != 0) {
            // --- MODO DERROTA O EMPATE: Imprime la "X" (PERDER) ---
            mostrarMatriz(8, PERDER); 
        }
    } 
    return 0; 
}
