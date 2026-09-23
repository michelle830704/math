#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

#include <cmath>
#include <string>
#include <iostream>
#include <limits>
#include <type_traits>
#include <cstdio>
#include <windows.h>



int DISPLAY_WIDTH = 640;
int DISPLAY_HEIGHT = 360;
int DISPLAY_SCALE = 2;


// ============================================================
// PART 1 INPUT VALUES
// ============================================================

double inputX = 3.0;
double inputY = 4.0;
int inputN = 3;
double inputTheta = 1.0;


// ============================================================
// PROGRAM VARIABLES
// ============================================================


int currentPart = 0;

float animationTime = 0.0f;

bool enterWasDown = false;

// Open a Windows console to collect numeric input before Play starts.
template <typename T>
void ReadValue(const char* label, T& value)
{
    while (true)
    {
        std::cout << label << " [" << value << "]: ";
        std::string line;
        if (!std::getline(std::cin, line)) return;
        if (line.empty()) return;

        try
        {
            size_t used = 0;
            T parsed;
            if constexpr (std::is_same_v<T, int>)
                parsed = std::stoi(line, &used);
            else
                parsed = std::stod(line, &used);
            if (used == line.size() && std::isfinite(static_cast<double>(parsed)))
            {
                value = parsed;
                return;
            }
        }
        catch (...) {}
        std::cout << "Please enter a valid number.\n";
    }
}

void GetPart1Inputs()
{
    AllocConsole();
    FILE* consoleFile = nullptr;
    freopen_s(&consoleFile, "CONIN$", "r", stdin);
    freopen_s(&consoleFile, "CONOUT$", "w", stdout);
    std::cout << "PART 1 - Enter values (press Enter to keep the default)\n";
    ReadValue("x", inputX);
    ReadValue("y", inputY);
    do
    {
        ReadValue("n (whole number, 0 or more)", inputN);
        if (inputN < 0) std::cout << "n must be 0 or greater.\n";
    } while (inputN < 0);
    ReadValue("theta (radians)", inputTheta);
    std::cout << "\nValues saved. The Play window will open now.\n";
    FreeConsole();
}


// ============================================================
// PART 1 - MATH -> CODE
// ============================================================


// ------------------------------------------------------------
// 1-1
// l(x,y) = sqrt(x*x + y*y)
// ------------------------------------------------------------

double l(double x, double y)
{
    return sqrt(x * x + y * y);
}


// ------------------------------------------------------------
// 1-2
// s(x) = |x|
// ------------------------------------------------------------

double s(double x)
{
    return abs(x);
}


// ------------------------------------------------------------
// 1-3
// f(n) = sum from i=0 to n of i^2 / n
// ------------------------------------------------------------

double f(int n)
{
    if (n == 0)
        return 0;

    double sum = 0;

    for (int i = 0; i <= n; i++)
    {
        sum += (i * i) / (double)n;
    }

    return sum;
}


// ------------------------------------------------------------
// 1-4
// ------------------------------------------------------------

double g(int n)
{
    double sum = 0;

    for (int i = 1; i <= n; i++)
    {
        double product = 1;

        for (int j = 1; j <= n; j++)
        {
            if (j != i)
            {
                product *= (i * j);
            }
        }

        sum += 3 * i + n * product;
    }

    return sum;
}


// ------------------------------------------------------------
// 1-5
// ------------------------------------------------------------

double h(double theta, double x, double y)
{
    return cos(theta) * (x - (x * y) * x)
        + sin(theta) * (y - x)
        + sqrt(x);
}


// ============================================================
// PART 1 DISPLAY
// ============================================================

void DrawPart1()
{
    Play::DrawDebugText(
        { 320, 25 },
        "PART 1 - MATH -> CODE",
        Play::cWhite
    );

    Play::DrawDebugText(
        { 320, 55 },
        "Input values:",
        Play::cWhite
    );

    std::string inputs =
        "x = " + std::to_string(inputX) +
        "   y = " + std::to_string(inputY) +
        "   n = " + std::to_string(inputN) +
        "   theta = " + std::to_string(inputTheta);

    Play::DrawDebugText(
        { 320, 80 },
        inputs.c_str(),
        Play::cWhite
    );


    std::string answer1 =
        "1-1  l(x,y) = " +
        std::to_string(l(inputX, inputY));

    Play::DrawDebugText(
        { 320, 120 },
        answer1.c_str(),
        Play::cWhite
    );


    std::string answer2 =
        "1-2  s(x) = " +
        std::to_string(s(inputX));

    Play::DrawDebugText(
        { 320, 145 },
        answer2.c_str(),
        Play::cWhite
    );


    std::string answer3 =
        "1-3  f(n) = " +
        std::to_string(f(inputN));

    Play::DrawDebugText(
        { 320, 170 },
        answer3.c_str(),
        Play::cWhite
    );


    std::string answer4 =
        "1-4  g(n) = " +
        std::to_string(g(inputN));

    Play::DrawDebugText(
        { 320, 195 },
        answer4.c_str(),
        Play::cWhite
    );


    if (inputX >= 0)
    {
        std::string answer5 =
            "1-5  h(theta,x,y) = " +
            std::to_string(
                h(inputTheta, inputX, inputY)
            );

        Play::DrawDebugText(
            { 320, 220 },
            answer5.c_str(),
            Play::cWhite
        );
    }
    else
    {
        Play::DrawDebugText(
            { 320, 220 },
            "1-5 x must be >= 0",
            Play::cWhite
        );
    }


    Play::DrawDebugText(
        { 320, 320 },
        "Press ENTER for Part 2-1",
        Play::cWhite
    );
}


// ============================================================
// PART 2-1
// SINE + COSINE FORM A CIRCLE
// ============================================================

void DrawPart2_1()
{
    Play::DrawDebugText(
        { 320, 20 },
        "2-1  SINE + COSINE = CIRCLE",
        Play::cWhite
    );

    float centerX = 320.0f;
    float centerY = 190.0f;

    float radius = 100.0f;

    float oldX = centerX + radius;
    float oldY = centerY;

    for (float angle = 0.0f;
        angle <= 6.28318f;
        angle += 0.01f)
    {
        float x =
            centerX + cos(angle) * radius;

        float y =
            centerY + sin(angle) * radius;

        Play::DrawLine(
            { oldX, oldY },
            { x, y },
            Play::cWhite
        );

        oldX = x;
        oldY = y;
    }

    Play::DrawDebugText(
        { 320, 330 },
        "X = cos(theta)   Y = sin(theta)   ENTER = next",
        Play::cWhite
    );
}


// ============================================================
// PART 2-2
// SINE WAVE
// ============================================================

void DrawPart2_2()
{
    Play::DrawDebugText(
        { 320, 20 },
        "2-2  SINE WAVE",
        Play::cWhite
    );

    float centerY = 180.0f;
    float amplitude = 80.0f;

    // X axis
    Play::DrawLine(
        { 20, centerY },
        { 620, centerY },
        Play::cWhite
    );

    float oldX = 20.0f;
    float oldY = centerY;

    for (float x = 0; x <= 600; x += 1.0f)
    {
        float newX = 20.0f + x;

        float newY =
            centerY +
            sin(x * 0.03f) * amplitude;

        Play::DrawLine(
            { oldX, oldY },
            { newX, newY },
            Play::cGreen
        );

        oldX = newX;
        oldY = newY;
    }

    Play::DrawDebugText(
        { 320, 330 },
        "y = sin(x)   ENTER = next",
        Play::cWhite
    );
}


// ============================================================
// PART 2-3
// AMPLITUDE + PHASE SHIFT
// ============================================================

void DrawPart2_3()
{
    Play::DrawDebugText(
        { 320, 20 },
        "2-3  AMPLITUDE + PHASE SHIFT",
        Play::cWhite
    );

    float centerY = 180.0f;

    // Original sine
    float amplitude1 = 40.0f;

    // Larger amplitude
    float amplitude2 = 80.0f;

    // Phase shift
    float phaseShift = 1.5f;


    float oldX1 = 20.0f;
    float oldY1 = centerY;

    float oldX2 = 20.0f;
    float oldY2 = centerY;

    float oldX3 = 20.0f;
    float oldY3 = centerY;


    for (float x = 0; x <= 600; x += 1.0f)
    {
        float newX = 20.0f + x;

        // Normal sine
        float y1 =
            centerY +
            sin(x * 0.03f) * amplitude1;

        // Larger amplitude
        float y2 =
            centerY +
            sin(x * 0.03f) * amplitude2;

        // Phase shifted sine
        float y3 =
            centerY +
            sin(x * 0.03f + phaseShift)
            * amplitude1;


        Play::DrawLine(
            { oldX1, oldY1 },
            { newX, y1 },
            Play::cWhite
        );

        Play::DrawLine(
            { oldX2, oldY2 },
            { newX, y2 },
            Play::cGreen
        );

        Play::DrawLine(
            { oldX3, oldY3 },
            { newX, y3 },
            Play::cYellow
        );


        oldX1 = newX;
        oldY1 = y1;

        oldX2 = newX;
        oldY2 = y2;

        oldX3 = newX;
        oldY3 = y3;
    }


    Play::DrawDebugText(
        { 320, 300 },
        "White = normal   Green = amplitude   Yellow = phase shift",
        Play::cWhite
    );

    Play::DrawDebugText(
        { 320, 330 },
        "Press ENTER for next",
        Play::cWhite
    );
}


// ============================================================
// PART 2-4
// ROTATING POINT
// ============================================================

void DrawPart2_4()
{
    Play::DrawDebugText(
        { 320, 20 },
        "2-4  ROTATING POINT",
        Play::cWhite
    );

    float centerX = 320.0f;
    float centerY = 180.0f;

    // Configurable distance
    float distance = 100.0f;

    float pointX =
        centerX +
        cos(animationTime) * distance;

    float pointY =
        centerY +
        sin(animationTime) * distance;


    // Draw line from center to point
    Play::DrawLine(
        { centerX, centerY },
        { pointX, pointY },
        Play::cWhite
    );


    // Draw point as small cross
    Play::DrawLine(
        { pointX - 5, pointY },
        { pointX + 5, pointY },
        Play::cGreen
    );

    Play::DrawLine(
        { pointX, pointY - 5 },
        { pointX, pointY + 5 },
        Play::cGreen
    );


    Play::DrawDebugText(
        { 320, 330 },
        "Point continuously rotates - ENTER = next",
        Play::cWhite
    );
}


// ============================================================
// HELPER FUNCTION FOR ROTATED SQUARE
// ============================================================

Play::Point2D RotatePoint(
    float x,
    float y,
    float angle,
    float centerX,
    float centerY)
{
    float rotatedX =
        x * cos(angle) -
        y * sin(angle);

    float rotatedY =
        x * sin(angle) +
        y * cos(angle);

    return
    {
        centerX + rotatedX,
        centerY + rotatedY
    };
}


// ============================================================
// PART 2-5
// ROTATING SQUARE
// ============================================================

void DrawPart2_5()
{
    Play::DrawDebugText(
        { 320, 20 },
        "2-5  ROTATING SQUARE",
        Play::cWhite
    );

    float centerX = 320.0f;
    float centerY = 180.0f;

    // Configurable square size
    float size = 120.0f;

    float half = size / 2.0f;


    Play::Point2D p1 =
        RotatePoint(
            -half, -half,
            animationTime,
            centerX, centerY
        );

    Play::Point2D p2 =
        RotatePoint(
            half, -half,
            animationTime,
            centerX, centerY
        );

    Play::Point2D p3 =
        RotatePoint(
            half, half,
            animationTime,
            centerX, centerY
        );

    Play::Point2D p4 =
        RotatePoint(
            -half, half,
            animationTime,
            centerX, centerY
        );


    Play::DrawLine(p1, p2, Play::cWhite);
    Play::DrawLine(p2, p3, Play::cWhite);
    Play::DrawLine(p3, p4, Play::cWhite);
    Play::DrawLine(p4, p1, Play::cWhite);


    Play::DrawDebugText(
        { 320, 330 },
        "Square continuously rotates - ENTER = next",
        Play::cWhite
    );
}


// ============================================================
// PART 2-6
// MOVING + ROTATING SQUARE
// ============================================================

void DrawPart2_6()
{
    Play::DrawDebugText(
        { 320, 20 },
        "2-6  MOVING + ROTATING SQUARE",
        Play::cWhite
    );

    float centerY = 180.0f;

    // Sine controls horizontal movement
    float centerX =
        320.0f +
        sin(animationTime) * 180.0f;

    float size = 80.0f;

    float half = size / 2.0f;


    Play::Point2D p1 =
        RotatePoint(
            -half, -half,
            animationTime,
            centerX, centerY
        );

    Play::Point2D p2 =
        RotatePoint(
            half, -half,
            animationTime,
            centerX, centerY
        );

    Play::Point2D p3 =
        RotatePoint(
            half, half,
            animationTime,
            centerX, centerY
        );

    Play::Point2D p4 =
        RotatePoint(
            -half, half,
            animationTime,
            centerX, centerY
        );


    Play::DrawLine(p1, p2, Play::cGreen);
    Play::DrawLine(p2, p3, Play::cGreen);
    Play::DrawLine(p3, p4, Play::cGreen);
    Play::DrawLine(p4, p1, Play::cGreen);


    Play::DrawDebugText(
        { 320, 310 },
        "X position = sin(time)",
        Play::cWhite
    );

    Play::DrawDebugText(
        { 320, 335 },
        "ENTER = return to Part 1",
        Play::cWhite
    );
}


// ============================================================
// MAIN GAME ENTRY
// ============================================================

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
    GetPart1Inputs();
    Play::CreateManager(
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT,
        DISPLAY_SCALE
    );
}


// ============================================================
// MAIN GAME UPDATE
// ============================================================

bool MainGameUpdate(float elapsedTime)
{
    // Increase animation timer
    animationTime += elapsedTime;


    // --------------------------------------------------------
    // ENTER KEY
    // --------------------------------------------------------

    bool enterDown =
        Play::KeyDown(KEY_ENTER);

    // Only change once for each key press
    if (enterDown && !enterWasDown)
    {
        currentPart++;

        if (currentPart > 6)
        {
            currentPart = 0;
        }

        animationTime = 0.0f;
    }

    enterWasDown = enterDown;


    // --------------------------------------------------------
    // CLEAR SCREEN
    // --------------------------------------------------------

    Play::ClearDrawingBuffer(
        Play::cBlack
    );


    // --------------------------------------------------------
    // SELECT WHICH PART TO DRAW
    // --------------------------------------------------------

    if (currentPart == 0)
    {
        DrawPart1();
    }
    else if (currentPart == 1)
    {
        DrawPart2_1();
    }
    else if (currentPart == 2)
    {
        DrawPart2_2();
    }
    else if (currentPart == 3)
    {
        DrawPart2_3();
    }
    else if (currentPart == 4)
    {
        DrawPart2_4();
    }
    else if (currentPart == 5)
    {
        DrawPart2_5();
    }
    else if (currentPart == 6)
    {
        DrawPart2_6();
    }


    // Show everything
    Play::PresentDrawingBuffer();


    // ESC closes program
    return Play::KeyDown(KEY_ESCAPE);
}


// ============================================================
// MAIN GAME EXIT
// ============================================================

int MainGameExit(void)
{
    Play::DestroyManager();

    return PLAY_OK;
}
