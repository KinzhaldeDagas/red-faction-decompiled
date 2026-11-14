// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579200 rf_text_parser_fatal_expected_with_context
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus expected-description,RET4,noreturn. Builds40-byte forward snippet from cursor,ALWAYS reads all40 bytes even past firstNUL/remaining allocation;nonzero signed bytes<32 become22,zero retained. Prior snippet starts max(cursor-40,buffer) and copies up tocursor,control bytes<32 mapped22. AddsNUL to both snippets. Formats filename+8,line264,expected,forward/prior snippets with unbounded sprintf into256B diagnostic,then fatal parse.cpp635. No cursor/remaining-length/filename/description bounds;diagnostic itself can overread or overflow. Confirms field264 is CR-based line number.
void __thiscall __noreturn rf_text_parser_fatal_expected_with_context(char **this, const char *a2)
{
  char v2[44]; // [esp+4h] [ebp-164h] BYREF
  char Buffer[256]; // [esp+30h] [ebp-138h] BYREF
  char v4[44]; // [esp+130h] [ebp-38h] BYREF
  char *v5; // [esp+160h] [ebp-8h]
  int i; // [esp+164h] [ebp-4h]

  for ( i = 0; i < 40; ++i )
  {
    if ( (*(this + 1))[i] && (*(this + 1))[i] < 32 )
      v2[i] = 22;
    else
      v2[i] = (*(this + 1))[i];
  }
  v2[i] = 0;
  v5 = *(this + 1) - 40;
  if ( v5 < *this )
    v5 = *this;
  for ( i = 0; i < 40 && v5 != *(this + 1); ++i )
  {
    if ( *v5 >= 32 )
      v4[i] = *v5;
    else
      v4[i] = 22;
    ++v5;
  }
  v4[i] = 0;
  sprintf(
    Buffer,
    "Parsing file \"%s\", at line #%d\nExpected %s but found this text:\n\n[%s]\n\nPrior text was this:\n\n[%s]\n",
    (const char *)this + 8,
    *(this + 66),
    a2,
    v2,
    v4);
  rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\parse\\parse.cpp", 635, Buffer);
}

