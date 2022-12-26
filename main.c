#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

void show_caps_state(unsigned char);

int main(void) {
    Display *display;
    XkbStateRec state, prev_state;
    Bool status;

    // Open a connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Error: Unable to open display.\n");
        return 1;
    }

    // Get the initial state of the caps lock key
    status = XkbGetState(display, XkbUseCoreKbd, &state);
    show_caps_state(state.locked_mods);
    if (status != Success) {
        fprintf(stderr, "Error: Unable to get keyboard state.\n");
        return 1;
    }

    // Print the initial state of the caps lock key
    show_caps_state(state.locked_mods);

    // Listen to the caps lock key state
    for (;;) {
        // Get the current state of the caps lock key
        status = XkbGetState(display, XkbUseCoreKbd, &state);
        if (status != Success) {
            fprintf(stderr, "Error: Unable to get keyboard state.\n");
            return 1;
        }

        // Check if the state of the caps lock key has changed
        if (state.locked_mods != prev_state.locked_mods) {
            // Print the current state of the caps lock key
            show_caps_state(state.locked_mods);

            // Update the previous state of the caps lock key
            prev_state = state;
        }

        // Sleep for 0.5 second before checking again
        usleep(500000);
    }

    return 0;
}

// Print the state of the caps lock key
void show_caps_state(unsigned char mods) {
    if (mods & 2) {
        system("qdbus org.kde.plasmashell /org/kde/osdService showText \"keyboard-caps-enabled\" \"Caps enabled\"");
    } else {
        system("qdbus org.kde.plasmashell /org/kde/osdService showText \"keyboard-caps-disabled\" \"Caps disabled\"");
    }
}
