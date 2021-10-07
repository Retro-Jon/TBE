#include "include.hpp"

class Engine
{
    public:
        class sprite
        {
            private:
                int id = 0;
            public:
                float x;
                float y;
                int width;
                int height;
                std::string design;

                int get_id()
                {
                    return id;
                }

                void set_id(int new_id)
                {
                    id = new_id;
                }

                void move(float new_x, float new_y)
                {
                    x = new_x;
                    y = new_y;
                }
        };

        class UI : sprite {}; // Still figuring out how to handle this

        std::vector<sprite> Sprites;
    
    private:
        int ScreenWidth = 0;
        int ScreenHeight = 0;
        wchar_t *screen; // Screen Buffer for Display and Render modes

        HANDLE Console; // Custom Buffer Handle for Engine
        HANDLE Default_Buffer; // Default Console Handle Text Buffer
        DWORD ScreenBytesWritten = 0; // # of Bytes written to screen

        int graphics_mode = 0;

        int Sprite_id_Counter = 0;

        float ElapsedTime;
        std::chrono::system_clock::time_point tp1;
        std::chrono::system_clock::time_point tp2;

    public:
        enum Graphics_Modes {
            Text, // Standard Text Output with iostream
            Display, // 2D Output
            Render // 3D Output
        };

        std::string load(std::string path);
        int start();
        void close(int exit = -1);
        void restart();
        void create_screen(int width, int height);
        void draw();
        void set_graphics_mode(int mode);
        int get_graphics_mode();
        void set_window_title(std::string title = "Engine");
        float get_elapsed_time();
        int create_sprite(float x, float y, int width, int height, std::string design);
};