// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F65B0 rf_ui_staticbox_copy_text_unbounded
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Copies NUL-terminated source into inline text628..883 (256bytes) without NULL/length guard. Long text overwrites draw geometry884 and later members. Return EAX has AL0 mixed with final source pointer,not length/status. No remeasure,events or image update.
char *__thiscall rf_ui_staticbox_copy_text_unbounded(char *this, char *a2)
{
  char *result; // eax
  char *v3; // [esp+8h] [ebp-Ch]

  v3 = this + 628;
  do
  {
    result = a2;
    LOBYTE(result) = *a2;
    *v3++ = *a2++;
  }
  while ( (_BYTE)result );
  return result;
}

