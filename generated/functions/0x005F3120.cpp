// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F3120 rf_ui_container_copy_label_unbounded
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Copies NUL-terminated source into inline label+628 bytewise. No NULL/capacity check;256-byte label ends before flags884. EAX ends with AL0 mixed into source pointer,not a useful length/status.
char *__thiscall rf_ui_container_copy_label_unbounded(char *this, char *a2)
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

