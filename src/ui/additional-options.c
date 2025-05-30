#include "./additional-options.h"

#define OPTION_HORIZ_GAP (18)

const char *option_tabs[] = {"Game", "Controls", "UI", "Bank"};

static int mudclient_add_option_panel_label(Panel *panel, char *label, int x,
                                            int y);
static int mudclient_add_option_panel_string(Panel *panel, char *label,
                                             char *default_text, int max_length,
                                             int x, int y);
static int mudclient_add_option_panel_checkbox(Panel *panel, char *label,
                                               int is_checked, int x, int y);

static int mudclient_add_option_panel_label(Panel *panel, char *label, int x,
                                            int y) {
    panel_add_text(panel, x, y, label, 1, 0);

    return surface_text_width(label, 1) + 2;
}

static int mudclient_add_option_panel_string(Panel *panel, char *label,
                                             char *default_text, int max_length,
                                             int x, int y) {
    int label_width = mudclient_add_option_panel_label(panel, label, x, y);

    int control = panel_add_text_input(panel, x + label_width, y,
                                       (ADDITIONAL_OPTIONS_WIDTH / 2) - 10, 15,
                                       FONT_BOLD_12, max_length, 0, 1);

    panel_update_text(panel, control, default_text);

    return control;
}

static int mudclient_add_option_panel_checkbox(Panel *panel, char *label,
                                               int is_checked, int x, int y) {
    int label_width = mudclient_add_option_panel_label(panel, label, x, y);

    int control = panel_add_checkbox(panel, x + label_width, y - 7, 14, 14);
    panel_toggle_checkbox(panel, control, is_checked);

    return control;
}

void mudclient_create_options_panel(mudclient *mud) {
    char formatted_digits[16] = {0};

    for (int i = 0; i < 50; i++) {
        mud->game_option_types[i] = -1;
        mud->control_option_types[i] = -1;
        mud->ui_option_types[i] = -1;
        mud->bank_option_types[i] = -1;
    }

    int ui_x = mud->surface->width / 2 - ADDITIONAL_OPTIONS_WIDTH / 2;

    int ui_y = (mud->surface->height / 2) - ADDITIONAL_OPTIONS_HEIGHT / 2;

    int x = ui_x + 4;
    int y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

    /* game */
    mud->panel_game_options = malloc(sizeof(Panel));
    panel_new(mud->panel_game_options, mud->surface, 50);

    int control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Members (restart): ", mud->options->members, x, y);

    mud->game_options[control] = &mud->options->members;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Idle logout: ", mud->options->idle_logout, x, y);

    mud->game_options[control] = &mud->options->idle_logout;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Remember username:", mud->options->remember_username, x, y);

    mud->game_options[control] = &mud->options->remember_username;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Remember password: ", mud->options->remember_password, x, y);

    mud->game_options[control] = &mud->options->remember_password;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Diversify NPCs: ", mud->options->diversify_npcs, x, y);

    mud->game_options[control] = &mud->options->diversify_npcs;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@3D ground items: ", mud->options->ground_item_models, x, y);

    mud->game_options[control] = &mud->options->ground_item_models;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    if (mud->options->members) {
        control = mudclient_add_option_panel_checkbox(
            mud->panel_game_options,
            "@whi@Rename Herblaw items: ", mud->options->rename_herblaw_items,
            x, y);
    } else {
        control = mudclient_add_option_panel_checkbox(
            mud->panel_game_options,
            "@whi@Show potion dosage: ", mud->options->rename_herblaw_items, x,
            y);
    }

    mud->game_options[control] = &mud->options->rename_herblaw_items;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    x += (ADDITIONAL_OPTIONS_WIDTH - 4) / 2;
    y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

#ifndef RENDER_GL
    if (mud->options->version_entity > 8) {
        control = mudclient_add_option_panel_checkbox(
            mud->panel_game_options,
            "@whi@HQ sprites (restart): ", mud->options->tga_sprites, x, y);

        mud->game_options[control] = &mud->options->tga_sprites;
        mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

        y += OPTION_HORIZ_GAP;
    }
#endif

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options, "@whi@Show roofs: ", mud->options->show_roofs,
        x, y);

    mud->game_options[control] = &mud->options->show_roofs;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Interlace (F1): ", mud->options->interlace, x, y);

    mud->game_options[control] = &mud->options->interlace;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Low memory (restart): ", mud->options->lowmem, x, y);

    mud->game_options[control] = &mud->options->lowmem;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options,
        "@whi@Underground flicker: ", mud->options->flicker, x, y);

    mud->game_options[control] = &mud->options->flicker;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_game_options, "@whi@Fog of war: ", mud->options->flicker, x,
        y);

    mud->game_options[control] = &mud->options->fog_of_war;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    snprintf(formatted_digits, sizeof(formatted_digits), "%d",
             mud->options->field_of_view);

    control = mudclient_add_option_panel_string(
        mud->panel_game_options, "@whi@Field of view: ", formatted_digits, 3, x,
        y);

    mud->game_options[control] = &mud->options->field_of_view;
    mud->game_option_types[control] = ADDITIONAL_OPTIONS_INT;

    y += OPTION_HORIZ_GAP;

    /* controls */
    x = ui_x + 4;
    y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

    mud->panel_control_options = malloc(sizeof(Panel));
    panel_new(mud->panel_control_options, mud->surface, 50);

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Mouse wheel: ", mud->options->mouse_wheel, x, y);

    mud->control_options[control] = &mud->options->mouse_wheel;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    snprintf(formatted_digits, sizeof(formatted_digits), "%d",
             mud->options->middle_click_camera);

    control = mudclient_add_option_panel_string(
        mud->panel_control_options,
        "@whi@Middle click camera: ", formatted_digits, 4, x, y);

    mud->control_options[control] = &mud->options->middle_click_camera;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_INT;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Zoom camera: ", mud->options->zoom_camera, x, y);

    mud->control_options[control] = &mud->options->zoom_camera;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Tab message respond: ", mud->options->tab_respond, x, y);

    mud->control_options[control] = &mud->options->tab_respond;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Option number keys: ", mud->options->option_numbers, x, y);

    mud->control_options[control] = &mud->options->option_numbers;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Compass menu: ", mud->options->compass_menu, x, y);

    mud->control_options[control] = &mud->options->compass_menu;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Transaction menus: ", mud->options->transaction_menus, x, y);

    mud->control_options[control] = &mud->options->transaction_menus;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options, "@whi@Offer-X: ", mud->options->offer_x, x,
        y);

    mud->control_options[control] = &mud->options->offer_x;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Last Offer-X: ", mud->options->last_offer_x, x, y);

    mud->control_options[control] = &mud->options->last_offer_x;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    x += (ADDITIONAL_OPTIONS_WIDTH - 4) / 2;
    y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_control_options,
        "@whi@Hold to buy/sell in shop: ", mud->options->hold_to_buy, x, y);

    mud->control_options[control] = &mud->options->hold_to_buy;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    snprintf(formatted_digits, sizeof(formatted_digits), "%d",
             mud->options->touch_vertical_drag);

    control = mudclient_add_option_panel_string(
        mud->panel_control_options,
        "@whi@Vertical drag (touch): ", formatted_digits, 4, x, y);

    mud->control_options[control] = &mud->options->touch_vertical_drag;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_INT;

    y += OPTION_HORIZ_GAP;

    snprintf(formatted_digits, sizeof(formatted_digits), "%d",
             mud->options->touch_pinch);

    control = mudclient_add_option_panel_string(
        mud->panel_control_options,
        "@whi@Horizontal pinch (touch): ", formatted_digits, 4, x, y);

    mud->control_options[control] = &mud->options->touch_pinch;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_INT;

    y += OPTION_HORIZ_GAP;

    snprintf(formatted_digits, sizeof(formatted_digits), "%d",
             mud->options->touch_menu_delay);

    control = mudclient_add_option_panel_string(
        mud->panel_control_options,
        "@whi@Menu delay (touch): ", formatted_digits, 4, x, y);

    mud->control_options[control] = &mud->options->touch_menu_delay;
    mud->control_option_types[control] = ADDITIONAL_OPTIONS_INT;

    /* ui */
    x = ui_x + 4;
    y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

    mud->panel_ui_options = malloc(sizeof(Panel));
    panel_new(mud->panel_ui_options, mud->surface, 50);

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options, "@whi@Display FPS: ", mud->options->display_fps,
        x, y);

    mud->ui_options[control] = &mud->options->display_fps;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options, "@whi@UI Scale: ", mud->options->ui_scale, x, y);

    mud->ui_options[control] = &mud->options->ui_scale;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options, "@whi@Anti-alias: ", mud->options->anti_alias, x,
        y);

    mud->ui_options[control] = &mud->options->anti_alias;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Number commas: ", mud->options->number_commas, x, y);

    mud->ui_options[control] = &mud->options->number_commas;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Remaining XP: ", mud->options->remaining_experience, x, y);

    mud->ui_options[control] = &mud->options->remaining_experience;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Total XP: ", mud->options->total_experience, x, y);

    mud->ui_options[control] = &mud->options->total_experience;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@XP drops: ", mud->options->experience_drops, x, y);

    mud->ui_options[control] = &mud->options->experience_drops;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Inventory count: ", mud->options->inventory_count, x, y);

    mud->ui_options[control] = &mud->options->inventory_count;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@K/M amounts: ", mud->options->condense_item_amounts, x, y);

    mud->ui_options[control] = &mud->options->condense_item_amounts;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    x += (ADDITIONAL_OPTIONS_WIDTH - 4) / 2;
    y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Wilderness warning: ", mud->options->wilderness_warning, x, y);

    mud->ui_options[control] = &mud->options->wilderness_warning;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    if (mud->options->version_media >= 59) {
        control = mudclient_add_option_panel_checkbox(
            mud->panel_ui_options,
            "@whi@Certificate items: ", mud->options->certificate_items, x, y);

        mud->ui_options[control] = &mud->options->certificate_items;
        mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

        y += OPTION_HORIZ_GAP;
    }

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options, "@whi@Status bars: ", mud->options->status_bars,
        x, y);

    mud->ui_options[control] = &mud->options->status_bars;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Ground item highlight: ", mud->options->ground_item_text, x, y);

    mud->ui_options[control] = &mud->options->ground_item_text;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Hover tooltip: ", mud->options->show_hover_tooltip, x, y);

    mud->ui_options[control] = &mud->options->show_hover_tooltip;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    if (mud->options->version_media > 42) {
        control = mudclient_add_option_panel_checkbox(
            mud->panel_ui_options, "@whi@Wiki lookup: ",
            mud->options->wiki_lookup, x, y);

        mud->ui_options[control] = &mud->options->wiki_lookup;
        mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

        y += OPTION_HORIZ_GAP;
    }

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Style outside combat: ", mud->options->combat_style_always, x, y);

    mud->ui_options[control] = &mud->options->combat_style_always;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    snprintf(formatted_digits, sizeof(formatted_digits), "%d",
             mud->options->ran_target_fps);

    control = mudclient_add_option_panel_string(
        mud->panel_ui_options, "@whi@Text effect FPS: ", formatted_digits, 4, x,
        y);

    mud->ui_options[control] = &mud->options->ran_target_fps;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_INT;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_ui_options,
        "@whi@Keyboard on right: ", mud->options->touch_keyboard_right, x, y);

    mud->ui_options[control] = &mud->options->touch_keyboard_right;
    mud->ui_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    /* bank */
    x = ui_x + 4;
    y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

    mud->panel_bank_options = malloc(sizeof(Panel));
    panel_new(mud->panel_bank_options, mud->surface, 50);

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Always multi-withdraw: ", mud->options->bank_unstackble_withdraw,
        x, y);

    mud->bank_options[control] = &mud->options->bank_unstackble_withdraw;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Search items: ", mud->options->bank_search, x, y);

    mud->bank_options[control] = &mud->options->bank_search;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Show capacity: ", mud->options->bank_capacity, x, y);

    mud->bank_options[control] = &mud->options->bank_capacity;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Show total value: ", mud->options->bank_value, x, y);

    mud->bank_options[control] = &mud->options->bank_value;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Bank expand: ", mud->options->bank_expand, x, y);

    mud->bank_options[control] = &mud->options->bank_expand;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Bank scrollbar: ", mud->options->bank_scroll, x, y);

    mud->bank_options[control] = &mud->options->bank_scroll;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options, "@whi@Bank menus: ", mud->options->bank_menus,
        x, y);

    mud->bank_options[control] = &mud->options->bank_menus;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    y += OPTION_HORIZ_GAP;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Show inventory: ", mud->options->bank_inventory, x, y);

    mud->bank_options[control] = &mud->options->bank_inventory;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;

    x += (ADDITIONAL_OPTIONS_WIDTH - 4) / 2;
    y = ui_y + OPTION_HORIZ_GAP + ADDITIONAL_OPTIONS_TAB_HEIGHT + 4;

    control = mudclient_add_option_panel_checkbox(
        mud->panel_bank_options,
        "@whi@Maintain slot: ", mud->options->bank_maintain_slot, x, y);

    mud->bank_options[control] = &mud->options->bank_maintain_slot;
    mud->bank_option_types[control] = ADDITIONAL_OPTIONS_CHECKBOX;
}

Panel *mudclient_get_active_option_panel(mudclient *mud) {
    Panel *panel = NULL;

    if (mud->options_tab == ADDITIONAL_OPTIONS_CONNECTION) {
        panel = mud->panel_game_options;
    } else if (mud->options_tab == ADDITIONAL_OPTIONS_CONTROL) {
        panel = mud->panel_control_options;
    } else if (mud->options_tab == ADDITIONAL_OPTIONS_DISPLAY) {
        panel = mud->panel_ui_options;
    } else if (mud->options_tab == ADDITIONAL_OPTIONS_BANK) {
        panel = mud->panel_bank_options;
    }

    return panel;
}

void mudclient_get_active_options(mudclient *mud, void ***options,
                                  int **option_types) {
    if (mud->options_tab == ADDITIONAL_OPTIONS_CONNECTION) {
        *options = mud->game_options;
        *option_types = mud->game_option_types;
    } else if (mud->options_tab == ADDITIONAL_OPTIONS_CONTROL) {
        *options = mud->control_options;
        *option_types = mud->control_option_types;
    } else if (mud->options_tab == ADDITIONAL_OPTIONS_DISPLAY) {
        *options = mud->ui_options;
        *option_types = mud->ui_option_types;
    } else if (mud->options_tab == ADDITIONAL_OPTIONS_BANK) {
        *options = mud->bank_options;
        *option_types = mud->bank_option_types;
    }
}

void mudclient_sync_options_panel(Panel *panel, void **options,
                                  int *option_types) {
    for (int i = 0; i < panel->control_count; i++) {
        if (option_types[i] == ADDITIONAL_OPTIONS_CHECKBOX) {
            int option = *(int *)options[i];
            panel_toggle_checkbox(panel, i, option);
        } else if (option_types[i] == ADDITIONAL_OPTIONS_INT) {
            int option = *(int *)options[i];
            char formatted_option[12] = {0};
            snprintf(formatted_option, sizeof(formatted_option), "%d", option);
            panel_update_text(panel, i, formatted_option);
        } else if (option_types[i] == ADDITIONAL_OPTIONS_STRING) {
            char *option = (char *)options[i];
            panel_update_text(panel, i, option);
        }
    }
}

void mudclient_sync_options_panels(mudclient *mud) {
    mudclient_sync_options_panel(mud->panel_game_options, mud->game_options,
                                 mud->game_option_types);

    mudclient_sync_options_panel(mud->panel_control_options,
                                 mud->control_options,
                                 mud->control_option_types);

    mudclient_sync_options_panel(mud->panel_ui_options, mud->ui_options,
                                 mud->ui_option_types);

    mudclient_sync_options_panel(mud->panel_bank_options, mud->bank_options,
                                 mud->bank_option_types);
}

void mudclient_draw_additional_options(mudclient *mud) {
    mud->surface->draw_string_shadow = 1;

    int ui_x = mud->surface->width / 2 - ADDITIONAL_OPTIONS_WIDTH / 2;

    int ui_y = mud->surface->height / 2 - ADDITIONAL_OPTIONS_HEIGHT / 2;

    surface_draw_box(mud->surface, ui_x, ui_y, ADDITIONAL_OPTIONS_WIDTH, 12,
                     TITLE_BAR_COLOUR);

    surface_draw_string(mud->surface, "Additional options", ui_x + 1, ui_y + 10,
                        1, WHITE);

    surface_draw_box_alpha(mud->surface, ui_x, ui_y + 12,
                           ADDITIONAL_OPTIONS_WIDTH,
                           ADDITIONAL_OPTIONS_HEIGHT - 12, GREY_98, 224);

    int text_colour = WHITE;

    if (mud->mouse_x > ui_x + ADDITIONAL_OPTIONS_WIDTH - 88 &&
        mud->mouse_y >= ui_y &&
        mud->mouse_x < ui_x + ADDITIONAL_OPTIONS_WIDTH &&
        mud->mouse_y < ui_y + 12) {
        text_colour = RED;
    }

    surface_draw_string_right(mud->surface, "Close window",
                              ui_x + ADDITIONAL_OPTIONS_WIDTH - 2, ui_y + 10, 1,
                              text_colour);

    surface_draw_tabs(mud->surface, ui_x, ui_y + 12, ADDITIONAL_OPTIONS_WIDTH,
                      ADDITIONAL_OPTIONS_TAB_HEIGHT, option_tabs, 4,
                      mud->options_tab);

    surface_draw_line_horizontal(mud->surface, ui_x + 8,
                                 ui_y + ADDITIONAL_OPTIONS_HEIGHT - 20,
                                 ADDITIONAL_OPTIONS_WIDTH - 16, BLACK);

    char formatted_reset[64] = {0};
    char default_colour[4] = "whi";
    char vanilla_colour[4] = "whi";

    if (mud->mouse_y > ui_y + ADDITIONAL_OPTIONS_HEIGHT - 20 &&
        mud->mouse_y < ui_y + ADDITIONAL_OPTIONS_HEIGHT) {
        if (mud->mouse_x >= ui_x + 58 && mud->mouse_x <= ui_x + 100) {
            strcpy(default_colour, "red");
        } else if (mud->mouse_x >= ui_x + 102 && mud->mouse_x <= ui_x + 140) {
            strcpy(vanilla_colour, "red");
        }
    }

    snprintf(formatted_reset, sizeof(formatted_reset),
             "Reset to: @%s@default @whi@/ @%s@vanilla", default_colour,
             vanilla_colour);

    surface_draw_string(mud->surface, formatted_reset, ui_x + 4,
                        ui_y + ADDITIONAL_OPTIONS_HEIGHT - 5, 1, WHITE);

    text_colour = WHITE;

    if (mud->mouse_x > ui_x + ADDITIONAL_OPTIONS_WIDTH - 90 &&
        mud->mouse_y >= ui_y + ADDITIONAL_OPTIONS_HEIGHT - 12 &&
        mud->mouse_x < ui_x + ADDITIONAL_OPTIONS_WIDTH &&
        mud->mouse_y < ui_y + ADDITIONAL_OPTIONS_HEIGHT) {
        text_colour = RED;
    }

    surface_draw_string(mud->surface, "Save and close",
                        ui_x + ADDITIONAL_OPTIONS_WIDTH - 90,
                        ui_y + ADDITIONAL_OPTIONS_HEIGHT - 5, 1, text_colour);

    Panel *panel = mudclient_get_active_option_panel(mud);

    if (panel != NULL) {
        panel_draw_panel(panel);
    }

    mud->surface->draw_string_shadow = mud->logged_in ? 1 : 0;
}

void mudclient_handle_additional_options_input(mudclient *mud) {
    int ui_x = mud->surface->width / 2 - ADDITIONAL_OPTIONS_WIDTH / 2;
    int ui_y = mud->surface->height / 2 - ADDITIONAL_OPTIONS_HEIGHT / 2;

    /* tabs */
    if (mud->last_mouse_button_down == 1 && mud->mouse_x >= ui_x &&
        mud->mouse_x < ui_x + ADDITIONAL_OPTIONS_WIDTH &&
        mud->mouse_y >= ui_y + 12 &&
        mud->mouse_y <= ui_y + 12 + ADDITIONAL_OPTIONS_TAB_HEIGHT) {
        mud->options_tab =
            (mud->mouse_x - ui_x) / (ADDITIONAL_OPTIONS_WIDTH / 4);
    }

    Panel *panel = mudclient_get_active_option_panel(mud);

    if (panel != NULL) {
        panel_handle_mouse(panel, mud->mouse_x, mud->mouse_y,
                           mud->last_mouse_button_down, mud->mouse_button_down,
                           mud->mouse_scroll_delta);
    }

    if (mud->last_mouse_button_down == 1) {
        /* close window */
        if (mud->mouse_x > ui_x + ADDITIONAL_OPTIONS_WIDTH - 88 &&
            mud->mouse_y >= ui_y &&
            mud->mouse_x < ui_x + ADDITIONAL_OPTIONS_WIDTH &&
            mud->mouse_y < ui_y + 12) {
            mud->show_additional_options = 0;
        }

        /* save and close */
        if (mud->mouse_x > ui_x + ADDITIONAL_OPTIONS_WIDTH - 90 &&
            mud->mouse_y >= ui_y + ADDITIONAL_OPTIONS_HEIGHT - 12 &&
            mud->mouse_x < ui_x + ADDITIONAL_OPTIONS_WIDTH &&
            mud->mouse_y < ui_y + ADDITIONAL_OPTIONS_HEIGHT) {
            options_save(mud->options);
            mud->show_additional_options = 0;
        }

        /* reset */
        if (mud->mouse_y > ui_y + ADDITIONAL_OPTIONS_HEIGHT - 20 &&
            mud->mouse_y < ui_y + ADDITIONAL_OPTIONS_HEIGHT) {
            mud->confirm_text_top = "Are you sure you wish to reset the";

            if (mud->mouse_x >= ui_x + 58 && mud->mouse_x <= ui_x + 100) {
                mud->confirm_text_bottom = "options to defaults?";
                mud->confirm_type = CONFIRM_OPTIONS_DEFAULT;
                mud->show_dialog_confirm = 1;
            } else if (mud->mouse_x >= ui_x + 102 &&
                       mud->mouse_x <= ui_x + 140) {
                mud->confirm_text_bottom = "options to vanilla?";
                mud->confirm_type = CONFIRM_OPTIONS_VANILLA;
                mud->show_dialog_confirm = 1;
            }
        }

        if (panel != NULL) {
            void **options = NULL;
            int *option_types = NULL;

            mudclient_get_active_options(mud, &options, &option_types);

            if (options != NULL && option_types != NULL) {
#if defined(RENDER_GL) || defined(RENDER_3DS_GL)
                int old_field_of_view = mud->options->field_of_view;
#endif
#ifdef RENDER_GL
                int old_ui_scale = mud->options->ui_scale;
#endif

                for (int i = 0; i < panel->control_count; i++) {
                    if (option_types[i] == ADDITIONAL_OPTIONS_CHECKBOX) {
                        int *option = (int *)options[i];
                        *option = panel_is_activated(panel, i);
                    } else if (option_types[i] == ADDITIONAL_OPTIONS_INT) {
                        int *option = (int *)options[i];
                        *option = atoi(panel_get_text(panel, i));
                    } else if (option_types[i] == ADDITIONAL_OPTIONS_STRING) {
                        char *option = (char *)options[i];
                        strcpy(option, panel_get_text(panel, i));
                    }
                }

#if defined(RENDER_GL) || defined(RENDER_3DS_GL)
                if (old_field_of_view != mud->options->field_of_view) {
                    mudclient_update_fov(mud);
                }
#endif
#ifdef RENDER_GL
                if (old_ui_scale != mud->options->ui_scale) {
#ifdef SDL12
                    mudclient_sdl1_on_resize(mud, mud->game_width,
                                             mud->game_height);
#else
                    mudclient_on_resize(mud);
#endif
                }
#endif
            }
        }
    }

    mud->last_mouse_button_down = 0;
}
