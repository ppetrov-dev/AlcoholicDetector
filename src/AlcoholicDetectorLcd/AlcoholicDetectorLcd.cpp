#include "AlcoholicDetectorLcd.h"

AlcoholicDetectorLcd::AlcoholicDetectorLcd() : _lcd(PIN_Lcd_Rs, PIN_Lcd_En, PIN_Lcd_D4, PIN_Lcd_D5, PIN_Lcd_D6, PIN_Lcd_D7)
{
}

void AlcoholicDetectorLcd::Init()
{
    _lcd.begin(16, 2);
}

void AlcoholicDetectorLcd::PrintOnRow(int rowIndex, String string)
{
    _lcd.setCursor(0, rowIndex);
    auto extendedString = ExtendInputedText(string);
    _lcd.print(extendedString);
}
String AlcoholicDetectorLcd::ExtendInputedText(String inputedText)
{
    auto lenght = inputedText.length();
    for (auto i = 0; i < _columnCount - lenght; i++)
        inputedText.concat(" ");

    return inputedText;
}
String AlcoholicDetectorLcd::ConstrainInputedText(String inputedText, String separator)
{
    auto lenght = inputedText.length();

    if (lenght < _columnCount)
    {
        auto indexOfFirstSpace = inputedText.indexOf(separator);
        if (indexOfFirstSpace != -1)
        {
            auto firstSubstring = inputedText.substring(0, indexOfFirstSpace);
            auto secondSubstring = inputedText.substring(indexOfFirstSpace, lenght);

            for (auto i = 0; i < _columnCount - lenght; i++)
                firstSubstring.concat(" ");
            inputedText = firstSubstring + secondSubstring;
        }
        else
        {
            for (auto i = 0; i < _columnCount - lenght; i++)
                inputedText.concat(" ");
        }
    }
    return inputedText;
}