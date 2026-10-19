package dev.mf.android;

import org.libsdl.app.SDLActivity;

/**
 * Entry point: SDL's activity loads libSDL3.so and libmain.so (the game +
 * port, built from the repository's CMakeLists.txt) and calls SDL_main.
 */
public class MfActivity extends SDLActivity {
    @Override
    protected String[] getLibraries() {
        return new String[] { "SDL3", "main" };
    }
}
