#include <stdbool.h>
#include "options-tab.h"

static bool sound_visible(mudclient *mud) {
    return false;
}

void mudclient_draw_ui_tab_options(mudclient *mud, int no_menus) {
    int ui_x = mud->surface->width - OPTIONS_WIDTH - 3;
    int ui_y = UI_BUTTON_SIZE + 1;

    int height = 265;

    int is_touch = mudclient_is_touch(mud);

    int is_compact = is_touch || mud->surface->height <
                                     (height + (OPTIONS_LINE_BREAK * 2)) + ui_y;

    int player_x = mud->region_x + mud->local_region_x;
    int player_y = mud->region_y + mud->local_region_y;

    int show_skip_tutorial =
        mud->options->skip_tutorial && (player_x >= 190 && player_x <= 240 &&
                                        player_y >= 720 && player_y <= 770);

    if (is_compact) {
        height = 152;
    }

    if (mud->options->show_additional_options && sound_visible(mud)) {
        height += OPTIONS_LINE_BREAK;
    }

    if (show_skip_tutorial) {
        height += OPTIONS_LINE_BREAK;
    }

    if (is_touch) {
        height = 198;
        ui_x = UI_TABS_TOUCH_X - OPTIONS_WIDTH - 1;
        ui_y = (UI_TABS_TOUCH_Y + UI_TABS_TOUCH_HEIGHT) - height - 2;
    }

    if (mud->options->version_media >= 59) {
        mudclient_draw_ui_tab_label(mud, OPTIONS_TAB, OPTIONS_WIDTH + !is_touch,
                                    ui_x - !is_touch,
                                    ui_y - UI_TABS_LABEL_HEIGHT);
    }

    mud->ui_tab_min_x = ui_x;
    mud->ui_tab_max_x = mud->surface->width;
    mud->ui_tab_min_y = 0;
    mud->ui_tab_max_y = ui_y + height + 10;

    if (is_touch) {
        mud->ui_tab_max_x = ui_x + OPTIONS_WIDTH;
        mud->ui_tab_min_y = ui_y - UI_TABS_LABEL_HEIGHT;
        mud->ui_tab_max_y = ui_y + height;
    }

    int controls_box_height = is_compact ? 48 : 65;

    if (is_touch) {
        controls_box_height += 9;
    }

    if (mud->options->show_additional_options && sound_visible(mud)) {
        controls_box_height += OPTIONS_LINE_BREAK;
    }

    surface_draw_box_alpha(mud->surface, ui_x, ui_y, OPTIONS_WIDTH,
                           controls_box_height, GREY_B5, 160);

    int security_box_height = 130;

    if (is_touch) {
        security_box_height += OPTIONS_LINE_BREAK - 4;
    }

    surface_draw_box_alpha(mud->surface, ui_x, ui_y + controls_box_height,
                           OPTIONS_WIDTH, security_box_height, GREY_C9, 160);

    int x = ui_x + 3;
    int y = ui_y + OPTIONS_LINE_BREAK;

    if (!is_compact) {
        surface_draw_string(mud->surface, "Game options - click to toggle", x,
                            y, FONT_BOLD_12, BLACK);

        y += OPTIONS_LINE_BREAK;
    } else if (is_touch) {
        y -= 4;

        surface_draw_string(mud->surface, "Game options - tap to toggle", x, y,
                            FONT_BOLD_12, BLACK);

        y += OPTIONS_LINE_BREAK - 3;
    }

    char settings_string[64] = {0};

    sprintf(settings_string, "Camera angle mode - %s",
            (mud->settings_camera_auto ? "@gre@Auto" : "@red@Manual"));

    surface_draw_string(mud->surface, settings_string, x, y, FONT_BOLD_12,
                        WHITE);

    y += OPTIONS_LINE_BREAK;

    sprintf(settings_string, "Mouse buttons - %s",
            (mud->settings_mouse_button_one ? "@red@One" : "@gre@Two"));

    surface_draw_string(mud->surface, settings_string, x, y, FONT_BOLD_12,
                        WHITE);

    y += OPTIONS_LINE_BREAK;

    if (mud->options->show_additional_options) {
        int text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
            text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Additional options...", x, y,
                            FONT_BOLD_12, text_colour);
    }

    if (mud->options->show_additional_options || !sound_visible(mud)) {
        y += OPTIONS_LINE_BREAK;
    }

    if (0) {
        if (!is_compact) {
            y += 5;

            surface_draw_string(mud->surface, "Security settings", x, y,
                                FONT_BOLD_12, BLACK);

            y += OPTIONS_LINE_BREAK;
        }

        if (is_touch) {
            y -= 1;

            surface_draw_string(mud->surface, "Security settings", x, y,
                                FONT_BOLD_12, BLACK);

            y += OPTIONS_LINE_BREAK - 3;
        }

        int text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
            text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Change password", x, y, FONT_BOLD_12,
                            text_colour);

        y += OPTIONS_LINE_BREAK;

        /*text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
            text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Change recovery questions", x, y,
                            FONT_BOLD_12, text_colour);*/

        if (!is_compact) {
            y += OPTIONS_LINE_BREAK * 2;
        }
    } else {
        y += 3;

        surface_draw_string(mud->surface, "Map viewer commands", x,
                            y, FONT_BOLD_12, BLACK);
        y += OPTIONS_LINE_BREAK;

        int text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
            text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Go up level...", x, y,
            FONT_BOLD_12, text_colour);
        y += OPTIONS_LINE_BREAK;

        text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
                text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Go down level...", x, y,
            FONT_BOLD_12, text_colour);
        y += OPTIONS_LINE_BREAK;

        text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
                text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Teleport to Varrock...", x, y,
            FONT_BOLD_12, text_colour);
        y += OPTIONS_LINE_BREAK;

        text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
                text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Teleport to Lumbridge...", x, y,
            FONT_BOLD_12, text_colour);
        y += OPTIONS_LINE_BREAK;

        text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
                text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Teleport to Falador...", x, y,
            FONT_BOLD_12, text_colour);
        y += OPTIONS_LINE_BREAK;

        text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
                text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Teleport to Karamja...", x, y,
            FONT_BOLD_12, text_colour);
        y += OPTIONS_LINE_BREAK;

        text_colour = WHITE;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4) {
                text_colour = YELLOW;
        }

        surface_draw_string(mud->surface, "Teleport to Camelot...", x, y,
            FONT_BOLD_12, text_colour);
        y += OPTIONS_LINE_BREAK;
    }

    if (!no_menus) {
        return;
    }

    int mouse_x = mud->mouse_x - ui_x;
    int mouse_y = mud->mouse_y - ui_y;

    if (mouse_x >= 0 && mouse_y >= 0 && mouse_x < 196 && mouse_y < height) {
        int x = ui_x + 3;

        int y = ui_y + OPTIONS_LINE_BREAK +
                (is_compact ? 0 : OPTIONS_LINE_BREAK) +
                (is_touch ? OPTIONS_LINE_BREAK - 7 : 0);

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mud->settings_camera_auto = !mud->settings_camera_auto;
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mud->settings_mouse_button_one = !mud->settings_mouse_button_one;
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->options->show_additional_options) {
            if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
                mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
                mud->mouse_button_click == 1) {
                mud->show_additional_options = 1;
            }
        }

        y += (OPTIONS_LINE_BREAK * 2) + 3;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mudclient_go_up(mud);
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mudclient_go_down(mud);
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mudclient_teleport(mud, 120, 504);
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mudclient_teleport(mud, 120, 648);
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mudclient_teleport(mud, 312, 552);
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mudclient_teleport(mud, 360, 696);
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mudclient_teleport(mud, 456, 456);
        }

        mud->mouse_button_click = 0;
    }
}
