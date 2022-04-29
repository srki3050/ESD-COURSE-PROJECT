/*
 * @Name: Abijith
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: lcd.c
 * @Description: LCD driver code
 * @Brief: This file has functions that can
 *          1) Initialize the LCD - lcd_init()
 *          2) Pull enable pin high or low - lcd_trigger_en()
 *          3) Write data to LCD - lcd_write_data(unsigned char data)
 *          4) Write a string of data on LCD - lcdSetText(char* text)
 *          5) Clear the LCD screen - lcdClear()
 * @References:
 *          1) https://microdigisoft.com/ti-launchpad-interfacing-lcd-16x2-with-msp432-microcontroller/
 *          2) https://github.com/agaelema/LCD16x2_MSP43x/blob/master/lcd16x2_msp43x.c
 *          3) http://www.ece.utep.edu/courses/web3376/Lab_5_-_LCD_files/lcdLib.c
 *          4) http://www.ece.utep.edu/courses/web3376/Lab_5_-_LCD_files/lcdLib.h
 */



/*
 * Header files
 */
#include <lcd.h>



/*
 * Preprocessor defines
 */
// writes nibble of data to LCD controller via Port 4
#define LOWNIB(x)   P4OUT = (P4OUT & 0xF0) + (x & 0x0F)


/*
 * Check header file for documentation
 */
void lcd_init() {
    // Wait for 100ms after power is applied.
    delay_ms(10000);

    // Make pins outputs
    P4DIR = EN + RS + DATA;
    // Start LCD (send 0x03)
    P4OUT = 0x03;

    // Send 0x03 3 times at 500ms
    lcd_trigger_en();
    delay_ms(500);
    lcd_trigger_en();
    delay_ms(500);
    lcd_trigger_en();
    delay_ms(500);

    // Switch to 4-bit mode
    P4OUT = 0x02;
    lcd_trigger_en();
    delay_ms(500);

    // 4-bit, 2 line, 5x8
    lcd_write_cmd(0x28);
    // Instruction Flow
    lcd_write_cmd(0x08);
    // Clear LCD
    lcd_write_cmd(0x01);
    // Auto-Increment
    lcd_write_cmd(0x06);
    // Display cursor and blink
    lcd_write_cmd(0x0F);
}



/*
 * Check header file for documentation
 */
void lcd_trigger_en() {
    // Enable pin high
    P4OUT |= EN;
    // Enable pin low
    P4OUT &= ~EN;
}



/*
 * Check header file for documentation
 */
void lcd_write_data(unsigned char data) {
    // Set RS to Data
    P4OUT |= RS;
    // Upper nibble
    LOWNIB(data >> 4);
    lcd_trigger_en();
    // Lower nibble
    LOWNIB(data);
    lcd_trigger_en();
    // Delay > 47 us
    delay_ms(1000);
}



/*
 * Check header file for documentation
 */
void lcd_write_cmd(unsigned char cmd) {
    // Set RS to Data
    P4OUT &= ~RS;
    // Upper nibble
    LOWNIB(cmd >> 4);
    lcd_trigger_en();
    // Lower nibble
    LOWNIB(cmd);
    lcd_trigger_en();
    // Delay > 1.5ms
    delay_ms(5);
}



/*
 * Check header file for documentation
 */
void lcd_set_text(char* text) {
    int i = 0;
    // till last character of string
    while (text[i] != '\0') {
        // write character
        lcd_write_data(text[i]);
        i++;
    }
}



/*
 * Check header file for documentation
 */
void lcd_clear() {
    // clear screen
    lcd_write_cmd(CLEAR);
}
