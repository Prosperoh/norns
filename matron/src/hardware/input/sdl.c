#include <SDL2/SDL.h>

#include "events.h"
#include "event_types.h"
#include "hardware/io.h"
#include "hardware/input.h"
#include "hardware/input/inputs.h"
#include "watch.h"

typedef struct _input_sdl_priv {
} input_sdl_priv_t;

static int input_sdl_config(matron_io_t* io, lua_State *l);
static int input_sdl_setup(matron_io_t* io);
static void input_sdl_destroy(matron_io_t* io);
static void* input_sdl_poll(void* data);

input_ops_t input_sdl_ops = {
    .io_ops.name      = "input:sdl",
    .io_ops.type      = IO_INPUT,
    .io_ops.data_size = sizeof(input_sdl_priv_t),
    .io_ops.config    = input_sdl_config,
    .io_ops.setup     = input_sdl_setup,
    .io_ops.destroy   = input_sdl_destroy,
    .poll             = input_sdl_poll,
};

int input_sdl_config(matron_io_t *io, lua_State *l) {
    (void)io;
    (void)l;
    return 0;
}

int input_sdl_setup(matron_io_t *io) {
    return input_setup(io);
}

void input_sdl_destroy(matron_io_t *io) {
    input_destroy(io);
}

static void* input_sdl_poll(void* data) {
    (void)data;

    SDL_Event event;
    union event_data *ev;
    fprintf(stderr, "starting SDL input loop\n");
    while (true) {
        SDL_WaitEvent(&event);

        int z = event.type == SDL_KEYDOWN ? 1 : 0;

        // K1, K2, K3 (buttons to press, need to update pressed/unpressed state)
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                    ev = event_data_new(EVENT_KEY);
                    ev->key.n = 1;
                    ev->key.val = z;
                    event_post(ev);
                    watch_key(ev->key.n, ev->key.val);
                    break;
                case SDL_SCANCODE_A:
                    ev = event_data_new(EVENT_KEY);
                    ev->key.n = 2;
                    ev->key.val = z;
                    event_post(ev);
                    watch_key(ev->key.n, ev->key.val);
                    break;
                case SDL_SCANCODE_Z:
                    ev = event_data_new(EVENT_KEY);
                    ev->key.n = 3;
                    ev->key.val = z;
                    event_post(ev);
                    watch_key(ev->key.n, ev->key.val);
                    break;
                default:
                    break;
            }
        }

        // E1, E2, E3 (buttons to turn, only count keydown input)
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    ev = event_data_new(EVENT_ENC);
                    ev->enc.n = 1;
                    ev->enc.delta = -1;
                    event_post(ev);
                    break;
                case SDL_SCANCODE_E:
                    ev = event_data_new(EVENT_ENC);
                    ev->enc.n = 1;
                    ev->enc.delta = 1;
                    event_post(ev);
                    break;
                case SDL_SCANCODE_S:
                    ev = event_data_new(EVENT_ENC);
                    ev->enc.n = 2;
                    ev->enc.delta = -1;
                    event_post(ev);
                    break;
                case SDL_SCANCODE_D:
                    ev = event_data_new(EVENT_ENC);
                    ev->enc.n = 2;
                    ev->enc.delta = 1;
                    event_post(ev);
                    break;
                case SDL_SCANCODE_X:
                    ev = event_data_new(EVENT_ENC);
                    ev->enc.n = 3;
                    ev->enc.delta = -1;
                    event_post(ev);
                    break;
                case SDL_SCANCODE_C:
                    ev = event_data_new(EVENT_ENC);
                    ev->enc.n = 3;
                    ev->enc.delta = 1;
                    event_post(ev);
                    break;
                default:
                    break;
            }
        }
    }

    return NULL;
}
