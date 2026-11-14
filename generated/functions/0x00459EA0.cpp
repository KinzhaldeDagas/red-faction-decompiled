// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459EA0 rf_main_menu_show_quit_game_dialog
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Two XOR-register/JZ pairs always select localized pointer globals88E20C(message) and88E1A8(title); embedded English-literal assignment arms are
// unreachable from normal entry. Calls46F2A0(title,message,callback459030,0,0), removes20 bytes, forwards EAX. Callback is registered/passed, NOT invoked here. No own active-session
// test, modal admission check or teardown; modal helper owns refusal behavior.
int rf_main_menu_show_quit_game_dialog()
{
  return rf_ui_show_yes_no_modal(unk_88E1A8, unk_88E20C, (int)rf_main_menu_quit_current_game_yes, 0, 0);
}

