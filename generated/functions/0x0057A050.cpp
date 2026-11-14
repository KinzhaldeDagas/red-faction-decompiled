// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A050 rf_text_parser_read_delimited_cstring
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(destination,capacity,openingByte,closingByte),RET16,returns length. Skips full trivia,requires current==opening byte or fatal,string error. Consumes opening,scans toNUL/CR/closing byte. If stopped byte!=closing,fatal string terminator;Count>=signed capacity invokes fatal parse.cpp1242 before destination copy. Otherwise strncpyCount,addsNUL,advances cursor byCount+1 (including closing) and returnsCount. No escaping,case folding,translation or line-counter update for copiedLF/consumed delimiter. Empty body needs capacity>=1;closingByte0 may consumeNUL,closingCR consumes it without counting line. Bounds rely on C-string terminator,not stored file size.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Generic quoted delimiter reader does not process escapes or comments. Payload length<caller capacity, CR/NUL before closing fatal, LF preserved as ordinary body byte. RFString579FB0 passes255 =>max254payload bytes; flag/XSTR caller256=>max255.
size_t __thiscall rf_text_parser_read_delimited_cstring(int this, char *Destination, int a3, char a4, char a5)
{
  char Buffer[256]; // [esp+4h] [ebp-108h] BYREF
  size_t Count; // [esp+108h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  if ( **(char **)(this + 4) != a4 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a string");
  Count = 0;
  ++*(_DWORD *)(this + 4);
  while ( *(_BYTE *)(*(_DWORD *)(this + 4) + Count)
       && *(_BYTE *)(*(_DWORD *)(this + 4) + Count) != 13
       && *(char *)(*(_DWORD *)(this + 4) + Count) != a5 )
    ++Count;
  if ( *(char *)(*(_DWORD *)(this + 4) + Count) != a5 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a string terminator");
  if ( (int)Count >= a3 )
  {
    sprintf(Buffer, "Not enough storage provided (%d) for parsed C string (len=%d)", a3, Count);
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\parse\\parse.cpp", 1242, Buffer);
  }
  strncpy(Destination, *(const char **)(this + 4), Count);
  Destination[Count] = 0;
  *(_DWORD *)(this + 4) += Count + 1;
  return Count;
}

