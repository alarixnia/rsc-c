#ifndef _H_CLIENT_OPCODES
#define _H_CLIENT_OPCODES

#ifdef REVISION_177
#define CLIENT_APPEARANCE 236
#define CLIENT_APPEARANCE_FRIEND 65
#define CLIENT_BANK_CLOSE 207
#define CLIENT_BANK_CLOSE_FRIEND 886
#define CLIENT_BANK_DEPOSIT 205
#define CLIENT_BANK_DEPOSIT_FRIEND 523
#define CLIENT_BANK_WITHDRAW 206
#define CLIENT_BANK_WITHDRAW_FRIEND 655
#define CLIENT_CAST_GROUND 221
#define CLIENT_CAST_GROUND_FRIEND 545
#define CLIENT_CAST_GROUNDITEM 224
#define CLIENT_CAST_GROUNDITEM_FRIEND 821
#define CLIENT_CAST_INVITEM 220
#define CLIENT_CAST_INVITEM_FRIEND 567
#define CLIENT_CAST_NPC 225
#define CLIENT_CAST_NPC_FRIEND 824
#define CLIENT_CAST_OBJECT 222
#define CLIENT_CAST_OBJECT_FRIEND 555
#define CLIENT_CAST_PLAYER 226
#define CLIENT_CAST_PLAYER_FRIEND 117
#define CLIENT_CAST_SELF 227
#define CLIENT_CAST_SELF_FRIEND 411
#define CLIENT_CAST_WALLOBJECT 223
#define CLIENT_CAST_WALLOBJECT_FRIEND 596
#define CLIENT_CHANGE_PASSWORD 25
#define CLIENT_CHANGE_PASSWORD_FRIEND 551
#define CLIENT_CHAT 3
#define CLIENT_CHAT_FRIEND 643
#define CLIENT_CHOOSE_OPTION 237
#define CLIENT_CHOOSE_OPTION_FRIEND 3
#define CLIENT_CLOSE_CONNECTION 1
#define CLIENT_CLOSE_CONNECTION_FRIEND 325
#define CLIENT_COMBAT_STYLE 231
#define CLIENT_COMBAT_STYLE_FRIEND 700
#define CLIENT_COMMAND 7
#define CLIENT_COMMAND_FRIEND 293
#define CLIENT_DUEL_ACCEPT 199
#define CLIENT_DUEL_ACCEPT_FRIEND 564
#define CLIENT_DUEL_CONFIRM_ACCEPT 198
#define CLIENT_DUEL_CONFIRM_ACCEPT_FRIEND 198
#define CLIENT_DUEL_DECLINE 203
#define CLIENT_DUEL_DECLINE_FRIEND 266
#define CLIENT_DUEL_ITEM_UPDATE 201
#define CLIENT_DUEL_ITEM_UPDATE_FRIEND 53
#define CLIENT_DUEL_OPTIONS 200
#define CLIENT_DUEL_OPTIONS_FRIEND 285
#define CLIENT_FRIEND_ADD 26
#define CLIENT_FRIEND_ADD_FRIEND 622
#define CLIENT_FRIEND_REMOVE 27
#define CLIENT_FRIEND_REMOVE_FRIEND 707
#define CLIENT_GROUNDITEM_TAKE 252
#define CLIENT_GROUNDITEM_TAKE_FRIEND 634
#define CLIENT_IGNORE_ADD 29
#define CLIENT_IGNORE_ADD_FRIEND 101
#define CLIENT_IGNORE_REMOVE 30
#define CLIENT_IGNORE_REMOVE_FRIEND 511
#define CLIENT_INV_COMMAND 246
#define CLIENT_INV_COMMAND_FRIEND 237
#define CLIENT_INV_DROP 251
#define CLIENT_INV_DROP_FRIEND 664
#define CLIENT_INV_UNEQUIP 248
#define CLIENT_INV_UNEQUIP_FRIEND 466
#define CLIENT_INV_WEAR 249
#define CLIENT_INV_WEAR_FRIEND 267
#define CLIENT_KNOWN_PLAYERS 254
#define CLIENT_KNOWN_PLAYERS_FRIEND 254
#define CLIENT_LOGIN 0
#define CLIENT_LOGIN_FRIEND 625
#define CLIENT_RECONNECT 19
#define CLIENT_RECONNECT_FRIEND  712
#define CLIENT_LOGOUT 6
#define CLIENT_LOGOUT_FRIEND 156
#define CLIENT_NPC_ATTACK 244
#define CLIENT_NPC_ATTACK_FRIEND 754
#define CLIENT_NPC_COMMAND 195
#define CLIENT_NPC_COMMAND_FRIEND 543
#define CLIENT_NPC_TALK 245
#define CLIENT_NPC_TALK_FRIEND 586
#define CLIENT_OBJECT_COMMAND1 242
#define CLIENT_OBJECT_COMMAND1_FRIEND 863
#define CLIENT_OBJECT_COMMAND2 230
#define CLIENT_OBJECT_COMMAND2_FRIEND 67
#define CLIENT_PACKET_EXCEPTION 3
#define CLIENT_PING 5
#define CLIENT_PING_FRIEND 348
#define CLIENT_PLAYER_ATTACK 228
#define CLIENT_PLAYER_ATTACK_FRIEND 414
#define CLIENT_PLAYER_DUEL 204
#define CLIENT_PLAYER_DUEL_FRIEND 273
#define CLIENT_PLAYER_FOLLOW 214
#define CLIENT_PLAYER_FOLLOW_FRIEND 596
#define CLIENT_PLAYER_TRADE 235
#define CLIENT_PLAYER_TRADE_FRIEND 636
#define CLIENT_PM 28
#define CLIENT_PM_FRIEND 185
#define CLIENT_PRAYER_OFF 211
#define CLIENT_PRAYER_ON 212
/*#define CLIENT_RECOVER_CANCEL 196
#define CLIENT_RECOVER_GET_QUESTIONS 233
#define CLIENT_RECOVER_REQUEST 220
#define CLIENT_RECOVER_SET 208
#define CLIENT_RECOVER_SET_REQUEST 213
#define CLIENT_RECOVER_SET_REQUEST_FRIEND 892*/
#define CLIENT_REGISTER 2
#define CLIENT_REGISTER_FRIEND 129
#define CLIENT_REPORT_ABUSE 206
#define CLIENT_SETTINGS_GAME 213
#define CLIENT_SETTINGS_GAME_FRIEND 892
#define CLIENT_SETTINGS_PRIVACY 31
#define CLIENT_SETTINGS_PRIVACY_FRIEND 777
#define CLIENT_SHOP_BUY 217
#define CLIENT_SHOP_BUY_FRIEND 666
#define CLIENT_SHOP_CLOSE 218
#define CLIENT_SHOP_CLOSE_FRIEND 312
#define CLIENT_SHOP_SELL 216
#define CLIENT_SHOP_SELL_FRIEND 665
#define CLIENT_SLEEP_WORD 193
#define CLIENT_SLEEP_WORD_FRIEND 127
#define CLIENT_TRADE_ACCEPT 232
#define CLIENT_TRADE_ACCEPT_FRIEND 277
#define CLIENT_TRADE_CONFIRM_ACCEPT 202
#define CLIENT_TRADE_CONFIRM_ACCEPT_FRIEND 96
#define CLIENT_TRADE_DECLINE 233
#define CLIENT_TRADE_DECLINE_FRIEND 235
#define CLIENT_TRADE_ITEM_UPDATE 234
#define CLIENT_TRADE_ITEM_UPDATE_FRIEND 500
#define CLIENT_USEWITH_GROUNDITEM 250
#define CLIENT_USEWITH_GROUNDITEM_FRIEND 346
#define CLIENT_USEWITH_INVITEM 240
#define CLIENT_USEWITH_INVITEM_FRIEND 377
#define CLIENT_USEWITH_NPC 243
#define CLIENT_USEWITH_NPC_FRIEND 876
#define CLIENT_USEWITH_OBJECT 241
#define CLIENT_USEWITH_OBJECT_FRIEND 772
#define CLIENT_USEWITH_PLAYER 219
#define CLIENT_USEWITH_PLAYER_FRIEND 145
#define CLIENT_USEWITH_WALLOBJECT 239
#define CLIENT_USEWITH_WALLOBJECT_FRIEND 792
#define CLIENT_WALK 194
#define CLIENT_WALK_FRIEND 770
#define CLIENT_WALK_ACTION 215
#define CLIENT_WALK_ACTION_FRIEND 592
#define CLIENT_WALL_OBJECT_COMMAND1 238
#define CLIENT_WALL_OBJECT_COMMAND1_FRIEND 212
#define CLIENT_WALL_OBJECT_COMMAND2 229
#define CLIENT_WALL_OBJECT_COMMAND2_FRIEND 726
#else
#define CLIENT_APPEARANCE 235
#define CLIENT_BANK_CLOSE 212
#define CLIENT_BANK_DEPOSIT 23
#define CLIENT_BANK_WITHDRAW 22
#define CLIENT_CAST_GROUND 158
#define CLIENT_CAST_GROUNDITEM 249
#define CLIENT_CAST_INVITEM 4
#define CLIENT_CAST_NPC 50
#define CLIENT_CAST_OBJECT 99
#define CLIENT_CAST_PLAYER 229
#define CLIENT_CAST_SELF 137
#define CLIENT_CAST_WALLOBJECT 180
#define CLIENT_CHANGE_PASSWORD 25
#define CLIENT_CHAT 216
#define CLIENT_CHOOSE_OPTION 116
#define CLIENT_CLOSE_CONNECTION 31
#define CLIENT_COMBAT_STYLE 29
#define CLIENT_COMMAND 38
#define CLIENT_DUEL_ACCEPT 176
#define CLIENT_DUEL_CONFIRM_ACCEPT 77
#define CLIENT_DUEL_DECLINE 197
#define CLIENT_DUEL_ITEM_UPDATE 33
#define CLIENT_DUEL_OPTIONS 8
#define CLIENT_FRIEND_ADD 195
#define CLIENT_FRIEND_REMOVE 167
#define CLIENT_GROUNDITEM_TAKE 247
#define CLIENT_IGNORE_ADD 132
#define CLIENT_IGNORE_REMOVE 241
#define CLIENT_INV_COMMAND 90
#define CLIENT_INV_DROP 246
#define CLIENT_INV_UNEQUIP 170
#define CLIENT_INV_WEAR 169
#define CLIENT_KNOWN_PLAYERS 163
#define CLIENT_LOGIN 0
#define CLIENT_LOGOUT 102
#define CLIENT_NPC_ATTACK 190
#define CLIENT_NPC_COMMAND 202
#define CLIENT_NPC_TALK 153
#define CLIENT_OBJECT_COMMAND1 136
#define CLIENT_OBJECT_COMMAND2 79
#define CLIENT_PACKET_EXCEPTION 3
#define CLIENT_PING 67
#define CLIENT_PLAYER_ATTACK 171
#define CLIENT_PLAYER_DUEL 103
#define CLIENT_PLAYER_FOLLOW 165
#define CLIENT_PLAYER_TRADE 142
#define CLIENT_PM 218
#define CLIENT_PRAYER_OFF 254
#define CLIENT_PRAYER_ON 60
#define CLIENT_RECOVER_CANCEL 196
#define CLIENT_RECOVER_GET_QUESTIONS 233
#define CLIENT_RECOVER_REQUEST 220
#define CLIENT_RECOVER_SET 208
#define CLIENT_RECOVER_SET_REQUEST 203
#define CLIENT_REGISTER 2
#define CLIENT_REPORT_ABUSE 206
#define CLIENT_SESSION 32
#define CLIENT_SETTINGS_GAME 111
#define CLIENT_SETTINGS_PRIVACY 64
#define CLIENT_SHOP_BUY 236
#define CLIENT_SHOP_CLOSE 166
#define CLIENT_SHOP_SELL 221
#define CLIENT_SLEEP_WORD 45
#define CLIENT_TRADE_ACCEPT 55
#define CLIENT_TRADE_CONFIRM_ACCEPT 104
#define CLIENT_TRADE_DECLINE 230
#define CLIENT_TRADE_ITEM_UPDATE 46
#define CLIENT_USEWITH_GROUNDITEM 53
#define CLIENT_USEWITH_INVITEM 91
#define CLIENT_USEWITH_NPC 135
#define CLIENT_USEWITH_OBJECT 115
#define CLIENT_USEWITH_PLAYER 113
#define CLIENT_USEWITH_WALLOBJECT 161
#define CLIENT_WALK 187
#define CLIENT_WALK_ACTION 16
#define CLIENT_WALL_OBJECT_COMMAND1 14
#define CLIENT_WALL_OBJECT_COMMAND2 127
#endif

#endif