// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00470910 rf_ui_edit_append_character
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall low-byte character, RET4. Computes strlen(inline text+64); signed length>=30 returns AL0 without writing. Else appends byte and NUL, copies
// text to250-byte-limited local, appends underscore to local at oldLength+1 and NUL at+2, measures candidate WITH caret using stored font+100 and length-1 sentinel. If measured
// width>limitDWORD+96, reverts appended text byte toNUL. Returns AL1 even when pixel-width rejection reverted append; equality fits. No own printable/filter/state check, cursor
// insertion, bitmap update or caret reset. Requires preexisting NUL-terminated text.
char __thiscall rf_ui_edit_append_character(int this, char a2)
{
  int v4; // [esp+14h] [ebp-110h] BYREF
  int v5; // [esp+18h] [ebp-10Ch] BYREF
  char Destination[256]; // [esp+1Ch] [ebp-108h] BYREF
  int v7; // [esp+120h] [ebp-4h]

  v7 = strlen((const char *)(this + 64));
  if ( v7 >= 30 )
    return 0;
  *(_BYTE *)(v7 + this + 64) = a2;
  *(_BYTE *)(v7 + this + 65) = 0;
  strncpy(Destination, (const char *)(this + 64), 0xFAu);
  Destination[250] = 0;
  Destination[v7 + 1] = 95;
  Destination[v7 + 2] = 0;
  rf_font_measure_text_extent(&v4, &v5, (unsigned __int8 *)Destination, -1, *(_DWORD *)(this + 100));
  if ( v4 > *(_DWORD *)(this + 96) )
    *(_BYTE *)(v7 + this + 64) = 0;
  return 1;
}

