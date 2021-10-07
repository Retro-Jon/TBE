/*
MIT License

Copyright (c) 2021 Jonathan Buckel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "..\engine\engine.hpp"

int main(int argc, char *argv[])
{
    // argc and *argv[] will be used in the future to enter debug modes
    Engine engine;

    engine.start();
    engine.set_window_title("Test");
    engine.create_screen(120, 40); // Create Display Buffer with a 120x40 resolution

    int player_index = engine.create_sprite(20, 20, 5, 4, "  O   -|- / | \\ / \\ ");

    engine.set_graphics_mode(Engine::Graphics_Modes::Display);

    std::cout << "Running..." << std::endl;
    
    /*
    Press A to quit
    Press T to switch to Text mode
    Press D to switch to Display mode
    */

    while (true)
    {
        engine.set_window_title("Test " + std::to_string(engine.get_elapsed_time()) + " player_index: " + std::to_string(player_index));
        engine.draw();
        if (GetAsyncKeyState((unsigned char)'A')) break;
        else if (GetAsyncKeyState((unsigned char)'T')) engine.set_graphics_mode(Engine::Graphics_Modes::Text);
        else if (GetAsyncKeyState((unsigned char)'D')) engine.set_graphics_mode(Engine::Graphics_Modes::Display);
    }

    engine.close(0);
    return 0;
}