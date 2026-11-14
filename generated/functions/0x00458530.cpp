// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458530 rf_key_help_draw_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl two C-string pointers. First calls font draw with LIVE(leftX661E24,nextY661E28,left_text,-1,fontDWORD182ABBC). Then REREADS cursor/font,
// draws(rightX=wrapped(leftX661E24+offset661E30),nextY,right_text,-1,font). Finally rereads nextY and adds LIVE step661E2C with32-bit wrap. No clipping, wrapping, text measurement,
// NULL check or coordinate scaling in this helper; blank rows still advance cursor. Preserves second draw EAX through integer cursor writes and returns it, not newY. Caller owns
// shared reset and color.
int __cdecl rf_key_help_draw_row(const char *left_text, const char *right_text)
{
  int result; // eax

  rf_font_draw_text_screen(dword_661E24, dword_661E28, (unsigned __int8 *)left_text, -1, dword_182ABBC);
  result = rf_font_draw_text_screen(
             dword_661E30 + dword_661E24,
             dword_661E28,
             (unsigned __int8 *)right_text,
             -1,
             dword_182ABBC);
  dword_661E28 += dword_661E2C;
  return result;
}

