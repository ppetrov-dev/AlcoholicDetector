#ifndef AlcoholicDetectorLcdH
#define AlcoholicDetectorLcdH

#include <LiquidCrystal.h>
#include "settings.h"
#include "enums.h"

class AlcoholicDetectorLcd
{
private:
    const unsigned int _columnCount = 16;
    const unsigned int _rowCount = 2;
    LiquidCrystal _lcd;
    String ExtendInputedText(String inputedText);
public:
    AlcoholicDetectorLcd();
    void PrintOnRow(int rowIndex, String string);
    void Init();
    String ConstrainInputedText(String inputedText, String separator = " ");
};
#endif //AlcoholicDetectorLcdH
