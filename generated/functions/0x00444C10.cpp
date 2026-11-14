// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00444C10 rf_prepare_savegame_level_and_request_panel5
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void. Call4F35B0(filename890400,local level-name output,NULL float output,NULL title output); ANY nonzero AL
// success admits, AL0 skips all own RFString/global/panel operations. Success constructs local level RFString from returned level name and local save RFString from890400.
// Copy-construct TWO8-byte by-value arguments (save pushed first, level second), then4798E0 assigns level6FC300/save6FC2F8 and destroys argument copies.
// Request446100(panel5,forceBYTE0), ignoring result; then destroy local save string before local level string. No4494C0 initialization helper, world load or second save validation
// here. Validator can write its local output before eventual failure, but this body does not consume it on AL0. Native caller cleans16 argument bytes; both chunks contain matching
// RFString unwind/cookie/C++ handling. No filename/length guard, failure message, pending-request override or rollback after global assignment.
void rf_prepare_savegame_level_and_request_panel5()
{
  int v0; // eax
  int v1; // eax
  int v2[2]; // [esp-10h] [ebp-14Ch] BYREF
  int v3[8]; // [esp-8h] [ebp-144h] BYREF
  char *v4[2]; // [esp+18h] [ebp-124h] BYREF
  char level_buffer[8]; // [esp+20h] [ebp-11Ch] BYREF
  char Source[260]; // [esp+28h] [ebp-114h] BYREF
  int v7; // [esp+138h] [ebp-4h]

  if ( rf_savegame_validate_headers_and_read_info(&unk_890400, Source, nullptr, nullptr) )
  {
    rf_string_construct_from_cstr(v4, Source);
    v7 = 0;
    rf_string_construct_from_cstr(level_buffer, &unk_890400);
    LOBYTE(v7) = 1;
    v3[7] = (int)v3;
    rf_string_copy_construct_from_object(v3, (char **)level_buffer);
    v3[5] = v0;
    v3[4] = v0;
    LOBYTE(v7) = 2;
    v3[6] = (int)v2;
    rf_string_copy_construct_from_object(v2, v4);
    v3[3] = v1;
    LOBYTE(v7) = 1;
    rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
    rf_ui_request_panel_immediate(5, 0);
    LOBYTE(v7) = 0;
    rf_string_destroy_buffer(level_buffer);
    v7 = -1;
    rf_string_destroy_buffer(v4);
  }
}

