// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004706C0 rf_ui_edit_set_text_bounded
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(source,ignoredSecondStackArgument), RET8. strncpy(this+64,source,31), then this[95]=NUL. Returns destination pointer from strncpy. Second
// argument is NEVER read: despite callers supplying a font, stored font+100 is unchanged. Does not measure, enforce30-character append limit/pixel width, rebuild bitmap or reset
// caret timer; drawing does that later. No source-null guard.
char *__thiscall rf_ui_edit_set_text_bounded(char *this, char *Source, int a3)
{
  char *result; // eax

  result = strncpy(this + 64, Source, 0x1Fu);
  *(this + 95) = 0;
  return result;
}

