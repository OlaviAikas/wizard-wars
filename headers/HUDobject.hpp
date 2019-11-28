#pragma once

class HUDobject {
    public:
        HUDobject(int x, int y, int sx, int sy);

        void draw();

    private:
        int x;
        int y;
        int sx;
        int sy;
};