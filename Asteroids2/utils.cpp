#include "utils.h"

namespace GraphUtils
{
    float diffWhite[] = { 1.0f, 1.0f, 1.0f };
    float ambiWhite[] = { 0.8f, 0.8f, 0.8f };
    float specWhite[] = { 1.0f, 1.0f, 1.0f };

    float diffBlue[] = { 0.0f, 0.0f, 0.6f };
    float ambiBlue[] = { 0.1f, 0.1f, 0.2f };
    float specBlue[] = { 0.2f, 0.2f, 0.8f };

    float diffGray[] = { 0.6f, 0.6f, 0.6f };
    float ambiGray[] = { 0.2f, 0.2f, 0.2f };
    float specGray[] = { 0.8f, 0.8f, 0.8f };

    float diffRed[] = { 0.6f, 0.0f, 0.0f };
    float ambiRed[] = { 0.2f, 0.1f, 0.1f };
    float specRed[] = { 0.8f, 0.2f, 0.2f };

    float diffYellow[] = { 0.9f, 0.9f, 0 };
    float ambiYellow[] = { 0.2f, 0.2f, 0.1f };
    float specYellow[] = { 1.0f, 1.0f, 0.2f };

    float diffGreen[] = { 0, 0.5f, 0 };
    float ambiGreen[] = { 0.1f, 0.2f, 0.1f };
    float specGreen[] = { 0.2f, 0.7f, 0.2f };

    float diffOrange[] = { 0.9f, 0.2f, 0 };
    float ambiOrange[] = { 0.2f, 0.2f, 0.2f };
    float specOrange[] = { 0.8f, 0.8f, 0.8f };

    float diffLightBlue[] = { 0, 0.6f, 0.9f };
    float ambiLightBlue[] = { 0.2f, 0.2f, 0.2f };
    float specLightBlue[] = { 0.8f, 0.8f, 0.8f };

    float diffViolet[] = { 0.5f, 0, 0.5f };
    float ambiViolet[] = { 0.2f, 0.2f, 0.2f };
    float specViolet[] = { 0.8f, 0.8f, 0.8f };

    void drawString(void* font, const char* text, float x, float y)
    {
        if (!text)
        {
            return;
        }
        glRasterPos2f(x, y);
        while (*text)
        {
            glutBitmapCharacter(font, *text);
            text++;
        }
    }
}