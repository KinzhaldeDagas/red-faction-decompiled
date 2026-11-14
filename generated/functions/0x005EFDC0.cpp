// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EFDC0 rf_ui_button_copy_label_unbounded
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Copies NUL-terminated input byte-by-byte into object+636. No source NULL/length/capacity guard. Label occupies256 bytes before deadline+892;long text overwrites later members. EAX mixes source pointer with final AL=0;not a useful copied-length/success value.
char *__thiscall rf_ui_button_copy_label_unbounded(char *this, char *a2)
{
  char *result; // eax
  char *v3; // [esp+8h] [ebp-Ch]

  v3 = this + 636;
  do
  {
    result = a2;
    LOBYTE(result) = *a2;
    *v3++ = *a2++;
  }
  while ( (_BYTE)result );
  return result;
}

