// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BBE70 rf_text_file_write_normalized_newlines
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Thiscall(receiver,C string),returns0 on success/1 on failed fwrite. Splits input at first CR/LF; consumes adjacent CRLF as one newline, otherwise each CR or LF separately. Writes text spans unchanged and substitutes string pointed by global66493C for every newline. Pointer and original PE literal at644100 verify CRLF bytes0D0A00. Empty string returns0 without I/O; final unterminated text written as one item. Does not append extra newline,flush,check FILE* or validate input. No read-mode/flag gate; newline selection is global, not detected input mode.
BOOL __thiscall rf_text_file_write_normalized_newlines(FILE **this, const char *Buffer)
{
  char v4; // [esp+27h] [ebp-Dh]
  char *v5; // [esp+28h] [ebp-Ch]
  const char *v6; // [esp+2Ch] [ebp-8h]
  char *v7; // [esp+30h] [ebp-4h]

  while ( *Buffer )
  {
    v5 = strchr(Buffer, 13);
    v7 = strchr(Buffer, 10);
    if ( !v5 && !v7 )
      return fwrite(Buffer, strlen(Buffer), 1u, *this) != 1;
    v4 = 0;
    if ( v5 && v7 )
    {
      if ( v7 == v5 + 1 )
      {
        v4 = 1;
        v6 = v7;
      }
      else if ( v5 >= v7 )
      {
        v6 = v7;
      }
      else
      {
        v6 = v5;
      }
    }
    else if ( v5 )
    {
      v6 = v5;
    }
    else
    {
      v6 = v7;
    }
    if ( v6 != Buffer )
    {
      if ( v4 )
      {
        if ( v5 != Buffer && fwrite(Buffer, v6 - Buffer - 1, 1u, *this) != 1 )
          return 1;
      }
      else if ( fwrite(Buffer, v6 - Buffer, 1u, *this) != 1 )
      {
        return 1;
      }
    }
    if ( fwrite(off_66493C, strlen((const char *)off_66493C), 1u, *this) != 1 )
      return 1;
    Buffer = v6 + 1;
  }
  return 0;
}

