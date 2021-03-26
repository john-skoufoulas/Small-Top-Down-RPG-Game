#include "graphics.h"
#include "Game.h"
#include "config.h"
#include "StartScreen.h"

void resize(int w, int h) {
    Game* EscapeRoom = reinterpret_cast<Game*> (graphics::getUserData());
    EscapeRoom->setWindow_x_y((unsigned int) w, (unsigned int)h);
}

void update(float ms)
{
    Game* EscapeRoom = reinterpret_cast<Game*> (graphics::getUserData());
    EscapeRoom->update();
    if (EscapeRoom) {
        if (EscapeRoom->getDestruction_order()) {
            graphics::destroyWindow();
        }
    }

}

void draw()
{
    Game* EscapeRoom = reinterpret_cast<Game*> (graphics::getUserData());
        EscapeRoom->draw();
}

int main()
{
    Game EscapeRoom;

    graphics::createWindow(WINDOW, WINDOW, "My Window");
    graphics::setResizeFunction(resize);


    graphics::setUserData(&EscapeRoom);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS, CANVAS);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    EscapeRoom.init();
    graphics::startMessageLoop();

    return 0;
}