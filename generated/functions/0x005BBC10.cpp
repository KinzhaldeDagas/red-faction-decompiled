// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BBC10 rf_text_file_read_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Recovered thiscall(receiver,char*destination,unsigned capacity),RET8; function ends5BBE58 before4-entry switch table. Closed stream,NULL destination,or remaining0+EOF returnsNULL without terminator write. Otherwise decrements capacity by1 WITHOUT zero guard; capacity1 returns empty string without consumption,capacity0 wraps to0xFFFFFFFF. Copies at most min(space,remaining) before delimiter: mode0 searches CR followed by LF;mode1 LF;mode2 CR;mode3 earliest CR or LF. Terminators omitted from output, consumes2 bytes in mode0 and1 in other modes. Thus mode3 treats CRLF as two separate delimiters. CRLF lookahead reads byte after CR without checking it stays buffered; spanning-boundary pair is not robustly handled. Advances
// cursor/decrements remaining,refills when exactly0,stops after delimiter/full output/EOF and NUL-terminates,returns original destination. Long lines split across calls when capacity exhausted. Failed fread treated as EOF by refill; no distinct error status. No positive capacity,read-mode or remaining-count validation; zero-size buffers can cause no-progress loop.
char *__thiscall rf_text_file_read_line(void *this, char *a2, unsigned int a3)
{
  _BYTE *v4; // [esp+0h] [ebp-24h]
  size_t v5; // [esp+8h] [ebp-1Ch]
  size_t Size; // [esp+10h] [ebp-14h]
  _BYTE *v8; // [esp+14h] [ebp-10h]
  _BYTE *v9; // [esp+18h] [ebp-Ch]
  char *v10; // [esp+1Ch] [ebp-8h]
  _BYTE *byte; // [esp+20h] [ebp-4h]
  unsigned int v12; // [esp+30h] [ebp+Ch]

  v10 = a2;
  if ( !*(_DWORD *)this || !a2 || !*((_DWORD *)this + 4) && (*((_DWORD *)this + 6) & 1) != 0 )
    return nullptr;
  byte = nullptr;
  v12 = a3 - 1;
  while ( !byte && v12 && (*((_DWORD *)this + 4) || (*((_DWORD *)this + 6) & 1) == 0) )
  {
    if ( v12 <= *((_DWORD *)this + 4) )
      v5 = v12;
    else
      v5 = *((_DWORD *)this + 4);
    Size = v5;
    switch ( (*((_DWORD *)this + 6) >> 2) & 3 )
    {
      case 0:
        byte = *((_BYTE **)this + 3);
        while ( byte )
        {
          byte = rf_memory_find_byte(byte, 13, v5 - (_DWORD)&byte[-*((_DWORD *)this + 3)]);
          if ( byte )
          {
            if ( byte[1] == 10 )
              goto LABEL_32;
            ++byte;
          }
        }
        break;
      case 1:
        byte = rf_memory_find_byte(*((void **)this + 3), 10, v5);
        break;
      case 2:
        byte = rf_memory_find_byte(*((void **)this + 3), 13, v5);
        break;
      case 3:
        v9 = rf_memory_find_byte(*((void **)this + 3), 10, v5);
        v8 = rf_memory_find_byte(*((void **)this + 3), 13, v5);
        if ( v9 )
        {
          if ( v8 )
          {
            if ( v9 >= v8 )
              v4 = v8;
            else
              v4 = v9;
            byte = v4;
          }
          else
          {
            byte = v9;
          }
        }
        else
        {
          byte = v8;
        }
        break;
    }
LABEL_32:
    if ( byte )
      Size = (size_t)&byte[-*((_DWORD *)this + 3)];
    memcpy(a2, *((const void **)this + 3), Size);
    a2 += Size;
    v12 -= Size;
    if ( byte )
      Size += 2 - (((*((_DWORD *)this + 6) >> 2) & 3) != 0);
    *((_DWORD *)this + 3) += Size;
    *((_DWORD *)this + 4) -= Size;
    if ( !*((_DWORD *)this + 4) )
      rf_text_file_refill_buffer((int)this);
  }
  *a2 = 0;
  return v10;
}

