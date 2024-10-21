#include <TinyLib.h>


int main()
{
    tl::Window window({ 800, 600 }, "Tiny Window");

    while (window.isOpen())
    {
        if (window.checkEvent(tl::Event::Closed))
            window.close();

        window.clear();
        window.display();
    }

    return 0;
}