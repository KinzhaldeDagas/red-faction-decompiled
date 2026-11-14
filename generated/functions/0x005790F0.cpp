// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005790F0 rf_text_parser_load_owned_cstring
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus NUL source string,RET4. malloc(strlen(source)+1),assigns buffer0 and copies includingNUL,then5791D0 resets cursor=buffer and line1. Does NOT close old allocation or update filename8/stored size268. Newly constructed parser therefore still has uninitialized size for578BF0 offset check. No NULL/malloc/length/ownership guard. Returns0 unconditionally;global-cache close suppression579190 also applies to this owned allocation.
int __thiscall rf_text_parser_load_owned_cstring(void **this, const char *a2)
{
  char v3; // [esp+3h] [ebp-21h]
  _BYTE *v4; // [esp+8h] [ebp-1Ch]
  const char *v5; // [esp+Ch] [ebp-18h]

  *this = malloc(strlen(a2) + 1);
  v5 = a2;
  v4 = *this;
  do
  {
    v3 = *v5;
    *v4++ = *v5++;
  }
  while ( v3 );
  rf_memory_text_parser_reset_cursor_if_loaded(this);
  return 0;
}

