#include "engine.hpp"

std::string Engine::load(std::string path)
{
    std::string data;
    std::fstream file;
    file.open(path);

    std::string line;
    
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            data += line + '\n';
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file\n";
    }

    return data;
}

int Engine::start()
{
    std::cout << "TBE Starting..." << std::endl;
    // Start the Clock
    Engine::tp1 = std::chrono::system_clock::now();
    return 0;
}

void Engine::close(int exit)
{
    // Reset Console Buffer to default buffer
    Engine::set_graphics_mode(Engine::Graphics_Modes::Text);
    std::cout << "Closing..." << std::endl;

    std::cout << std::endl;

    // Will include code to clean up memory and stuff in the future
    
    // exit program and return exit value if exit > -1
    if (exit > -1)
        std::exit(exit);
}

void Engine::restart()
{
    int gm = Engine::get_graphics_mode(); // Current Graphics Mode
    Engine::close(-1);
    std::cout << "Restarting..." << std::endl;
    Engine::start();

    Engine::set_graphics_mode(gm);
    
    // Reset Display Mode Screen Buffer
    if (Engine::ScreenWidth > 0 && Engine::ScreenHeight > 0)
        Engine::create_screen(Engine::ScreenWidth, Engine::ScreenHeight);
}

void Engine::create_screen(int width, int height)
{
    Engine::ScreenWidth = width;
    Engine::ScreenHeight = width;
    Engine::screen = new wchar_t[Engine::ScreenWidth * Engine::ScreenHeight]; // Create wchar_t Array of characters to send to buffer
    Engine::Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Create Console Screen Buffer
    Engine::Default_Buffer = GetStdHandle(STD_OUTPUT_HANDLE); // Store Default Console Buffer Handle

    Engine::ScreenBytesWritten = 0;

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(Console, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(Console, &cursorInfo);
    
    // Clear Screen for use in Display or Render modes
    for (int x = 0; x < Engine::ScreenWidth; x++)
    {
        for (int y = 0; y < Engine::ScreenHeight; y++)
        {
            Engine::screen[y * Engine::ScreenWidth + x] = ' ';
        }
    }
}

void Engine::set_graphics_mode(int mode)
{
    Engine::graphics_mode = mode;
    switch (mode)
    {
        case Engine::Graphics_Modes::Text:
            SetConsoleActiveScreenBuffer(Engine::Default_Buffer);
            break;
        case Engine::Graphics_Modes::Display:
        case Engine::Graphics_Modes::Render:
            SetConsoleActiveScreenBuffer(Engine::Console);
            break;
    }
}

void Engine::set_window_title(std::string title)
{
    SetConsoleTitleA((title).c_str());
}

int Engine::get_graphics_mode()
{
    return Engine::graphics_mode;
}

void Engine::draw()
{
    if (Engine::get_graphics_mode() == Engine::Graphics_Modes::Display || Engine::get_graphics_mode() == Engine::Graphics_Modes::Render)
    {
        // Loop through sprites
        for (Engine::sprite Sprite : Engine::Sprites)
        {
            int x = -1;
            int y = 0;
            for (char c : Sprite.design)
            {
                x++;
                if (x > Sprite.width - 1)
                {
                    x = 0;
                    y++;
                }
                Engine::screen[((int)Sprite.y + y) * Engine::ScreenWidth + ((int)Sprite.x + x)] = c;
            }
        }

        DWORD SBW = Engine::ScreenBytesWritten; // Screen Bytes Written
        Engine::screen[Engine::ScreenWidth * Engine::ScreenHeight - 1] = '\0';
        // Display Buffer
        WriteConsoleOutputCharacterW(Engine::Console, Engine::screen, Engine::ScreenWidth * Engine::ScreenHeight, { 0,0 }, &SBW);
    }
}

int Engine::create_sprite(float x, float y, int width, int height, std::string design)
{
    Engine::sprite new_sprite;

    new_sprite.x = x;
    new_sprite.y = y;
    new_sprite.width = width;
    new_sprite.height = height;
    new_sprite.design = design;
    new_sprite.set_id(Engine::Sprite_id_Counter);

    Engine::Sprite_id_Counter++;

    Engine::Sprites.push_back(new_sprite);
    
    return Engine::Sprites.size() - 1;
}

float Engine::get_elapsed_time()
{
    Engine::tp2 = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedTime = Engine::tp2 - Engine::tp1;
    Engine::tp1 = Engine::tp2;
    return elapsedTime.count();
}