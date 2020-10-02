#ifndef WINDOW_H_
#define WINDOW_H_

class Window {
    public:
        int lowX, lowY, upX, upY;

        // Window();
        // Window(int dim[]);
        // Window(float dim[]);
        void loadDim(int lowX, int lowY, int upX, int upY);
};

#endif