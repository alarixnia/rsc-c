#include <stdbool.h>
#include "options-tab.h"

static bool sound_visible(mudclient *mud) {
    return mud->options->members && !mud->options->lowmem;
}

void mudclient_send_privacy_settings(mudclient *mud, int chat, int private_chat,
                                     int trade, int duel) {
    packet_stream_new_packet(mud->packet_stream, CLIENT_SETTINGS_PRIVACY);
    packet_stream_put_byte(mud->packet_stream, chat);
    packet_stream_put_byte(mud->packet_stream, private_chat);
    packet_stream_put_byte(mud->packet_stream, trade);
    packet_stream_put_byte(mud->packet_stream, duel);
    packet_stream_send_packet(mud->packet_stream);
}

void mudclient_draw_change_password(mudclient *mud) {
    int dialog_x = (mud->surface->width / 2) - (CHANGE_PASSWORD_WIDTH / 2);

    int dialog_y =
        (mud->surface->height / 2) - (CHANGE_PASSWORD_HEIGHT / 2) + 7;

    int x = mud->surface->width / 2;
    int y = dialog_y + 22;

    if (mud->mouse_button_click != 0) {
        mud->mouse_button_click = 0;
        return;
    }

    surface_draw_box(mud->surface, dialog_x, dialog_y, CHANGE_PASSWORD_WIDTH,
                     CHANGE_PASSWORD_HEIGHT, BLACK);

    surface_draw_border(mud->surface, dialog_x, dialog_y, CHANGE_PASSWORD_WIDTH,
                        CHANGE_PASSWORD_HEIGHT, WHITE);

    char password_input[PASSWORD_LENGTH + 2] = {0};

    if (mud->show_change_password_step == PASSWORD_STEP_CURRENT) {
        surface_draw_string_centre(mud->surface,
                                   "Please enter your current password", x, y,
                                   FONT_BOLD_14, WHITE);

        y += 25;

        size_t current_length = strlen(mud->input_text_current);

        for (size_t i = 0; i < current_length; i++) {
            password_input[i] = 'X';
        }

        password_input[current_length] = '*';

        surface_draw_string_centre(mud->surface, password_input, x, y,
                                   FONT_BOLD_14, WHITE);

        if (strlen(mud->input_text_final) > 0) {
            strcpy(mud->change_password_old, mud->input_text_final);
            memset(mud->input_text_current, '\0', INPUT_TEXT_LENGTH + 1);
            memset(mud->input_text_final, '\0', INPUT_TEXT_LENGTH + 1);
            mud->show_change_password_step = 1;
        }
    } else if (mud->show_change_password_step == PASSWORD_STEP_NEW) {
        surface_draw_string_centre(mud->surface,
                                   "Please enter your new password", x, y,
                                   FONT_BOLD_14, WHITE);

        y += 25;

        size_t current_length = strlen(mud->input_text_current);

        for (size_t i = 0; i < current_length; i++) {
            password_input[i] = 'X';
        }

        password_input[current_length] = '*';

        surface_draw_string_centre(mud->surface, password_input, x, y,
                                   FONT_BOLD_14, WHITE);

        if (strlen(mud->input_text_final) > 0) {
            strcpy(mud->change_password_new, mud->input_text_final);
            memset(mud->input_text_current, '\0', INPUT_TEXT_LENGTH + 1);
            memset(mud->input_text_final, '\0', INPUT_TEXT_LENGTH + 1);

            if (strlen(mud->change_password_new) >= 5) {
                mud->show_change_password_step = PASSWORD_STEP_CONFIRM;
            } else {
                mud->show_change_password_step = PASSWORD_STEP_SHORT;
            }
        }
    } else if (mud->show_change_password_step == PASSWORD_STEP_CONFIRM) {
        surface_draw_string_centre(mud->surface,
                                   "Enter password again to confirm", x, y,
                                   FONT_BOLD_14, WHITE);

        y += 25;

        size_t current_length = strlen(mud->input_text_current);

        for (size_t i = 0; i < current_length; i++) {
            password_input[i] = 'X';
        }

        password_input[current_length] = '*';

        surface_draw_string_centre(mud->surface, password_input, x, y,
                                   FONT_BOLD_14, WHITE);

        if (strlen(mud->input_text_final) > 0) {
            if (strcasecmp(mud->input_text_final, mud->change_password_new) ==
                0) {
                mud->show_change_password_step = PASSWORD_STEP_FINISHED;

                mudclient_change_password(mud, mud->change_password_old,
                                          mud->change_password_new);
            } else {
                mud->show_change_password_step = PASSWORD_STEP_MISMATCH;
            }
        }
    } else {
        if (mud->show_change_password_step == PASSWORD_STEP_MISMATCH) {
            surface_draw_string_centre(mud->surface, "Passwords do not match!",
                                       x, y, FONT_BOLD_14, WHITE);

            y += 25;

            surface_draw_string_centre(mud->surface, "Press any key to close",
                                       x, y, FONT_BOLD_14, WHITE);
        } else if (mud->show_change_password_step == PASSWORD_STEP_FINISHED) {
            surface_draw_string_centre(mud->surface,
                                       "Ok, your request has been sent", x, y,
                                       FONT_BOLD_14, WHITE);

            y += 25;

            surface_draw_string_centre(mud->surface, "Press any key to close",
                                       x, y, FONT_BOLD_14, WHITE);
        } else if (mud->show_change_password_step == 5) {
            surface_draw_string_centre(mud->surface, "Password must be at", x,
                                       y, FONT_BOLD_14, WHITE);

            y += 25;

            surface_draw_string_centre(mud->surface, "least 5 letters long", x,
                                       y, FONT_BOLD_14, WHITE);
        }
    }
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

    int security_box_height = is_compact ? 15 : 65;

    if (is_touch) {
        security_box_height += OPTIONS_LINE_BREAK - 4;
    }

    surface_draw_box_alpha(mud->surface, ui_x, ui_y + controls_box_height,
                           OPTIONS_WIDTH, security_box_height, GREY_C9, 160);

    int privacy_box_height = is_compact ? 60 : 95;

    if (is_touch) {
        privacy_box_height += OPTIONS_LINE_BREAK - 4;
    }

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
            packet_stream_new_packet(mud->packet_stream, CLIENT_SETTINGS_GAME);
            packet_stream_put_byte(mud->packet_stream, 0);

            packet_stream_put_byte(mud->packet_stream,
                                   mud->settings_camera_auto ? 1 : 0);

            packet_stream_send_packet(mud->packet_stream);
        }

        y += OPTIONS_LINE_BREAK;

        if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
            mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
            mud->mouse_button_click == 1) {
            mud->settings_mouse_button_one = !mud->settings_mouse_button_one;
            packet_stream_new_packet(mud->packet_stream, CLIENT_SETTINGS_GAME);
            packet_stream_put_byte(mud->packet_stream, 2);

            packet_stream_put_byte(mud->packet_stream,
                                   mud->settings_mouse_button_one ? 1 : 0);

            packet_stream_send_packet(mud->packet_stream);
        }

        y += OPTIONS_LINE_BREAK;

        if (sound_visible(mud) && mud->mouse_x > x &&
            mud->mouse_x < x + OPTIONS_WIDTH && mud->mouse_y > y - 12 &&
            mud->mouse_y < y + 4 && mud->mouse_button_click == 1) {
            mud->settings_sound_disabled = !mud->settings_sound_disabled;
            packet_stream_new_packet(mud->packet_stream, CLIENT_SETTINGS_GAME);
            packet_stream_put_byte(mud->packet_stream, 3);

            packet_stream_put_byte(mud->packet_stream,
                                   mud->settings_sound_disabled ? 1 : 0);

            packet_stream_send_packet(mud->packet_stream);
        }

        if (sound_visible(mud)) {
            y += OPTIONS_LINE_BREAK;
        }

        if (mud->options->show_additional_options) {
            if (mud->mouse_x > x && mud->mouse_x < x + OPTIONS_WIDTH &&
                mud->mouse_y > y - 12 && mud->mouse_y < y + 4 &&
                mud->mouse_button_click == 1) {
                mud->show_additional_options = 1;
            }
        }

        mud->mouse_button_click = 0;
    }
}
