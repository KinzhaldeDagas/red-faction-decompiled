// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB8E0 rf_text_file_refill_and_detect_newlines
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Refills via5BBA40 then scans FIRST LF and FIRST CR within remaining bytes. Flags bits2..3 encode mode:0=CRLF,1=LF,2=CR,3=mixed/unknown. First CR followed by LF within initial buffer is CRLF candidate; any first LF outside that pair yields mode3, otherwise mode0. With no candidate: LF-only=>1,CR-only=>2,both unrelated or neither=>3. Examines only first occurrences, not all lines/file; later mixed endings can be misclassified. CR at last buffered byte cannot form initial candidate. Returns0 normally; propagates nonzero refill status though current refill always0. Other flag bits preserved.
int __thiscall rf_text_file_refill_and_detect_newlines(int this)
{
  unsigned int v2; // ecx
  _BYTE *byte; // [esp+4h] [ebp-10h]
  _BYTE *v5; // [esp+8h] [ebp-Ch]
  int v6; // [esp+Ch] [ebp-8h]
  _BYTE *v7; // [esp+10h] [ebp-4h]

  v6 = rf_text_file_refill_buffer(this);
  if ( v6 )
    return v6;
  v7 = nullptr;
  byte = rf_memory_find_byte(*(void **)(this + 4), 10, *(_DWORD *)(this + 16));
  v5 = rf_memory_find_byte(*(void **)(this + 4), 13, *(_DWORD *)(this + 16));
  if ( v5 && (int)&v5[-*(_DWORD *)(this + 4)] < *(_DWORD *)(this + 16) - 1 && v5[1] == 10 )
    v7 = v5;
  if ( v7 )
  {
    if ( v5 && (v5 < v7 || v5 > v7 + 1) || byte && (byte > v7 + 1 || byte < v7) )
      *(_DWORD *)(this + 24) |= 0xCu;
    else
      *(_DWORD *)(this + 24) &= 0xFFFFFFF3;
  }
  else if ( byte )
  {
    if ( v5 )
      v2 = *(_DWORD *)(this + 24) | 0xC;
    else
      v2 = *(_DWORD *)(this + 24) & 0xFFFFFFF3 | 4;
    *(_DWORD *)(this + 24) = v2;
  }
  else if ( v5 )
  {
    *(_DWORD *)(this + 24) = *(_DWORD *)(this + 24) & 0xFFFFFFF3 | 8;
  }
  else
  {
    *(_DWORD *)(this + 24) |= 0xCu;
  }
  return 0;
}

