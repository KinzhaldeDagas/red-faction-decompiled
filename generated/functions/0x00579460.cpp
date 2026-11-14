// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579460 rf_text_parser_read_cr_line_cstring_if_fits
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(destination,capacity),RET8. EOF returns0 with destination/cursor unchanged. Scans until CR-or-NUL;Count>=signed capacity returns0 without copying or moving cursor. Otherwise copiesCount bytes plusNUL,advances cursor,then consumes/counts CR and optional followingLF;returns1. Capacity must exceed text length,including allowance forNUL;does not truncate. LF-only file contents stay in one line,LF does not increment line number. No NULL or stored-size checks.
char __thiscall rf_text_parser_read_cr_line_cstring_if_fits(int this, char *Destination, int a3)
{
  int Count; // [esp+4h] [ebp-4h]

  if ( !**(_BYTE **)(this + 4) )
    return 0;
  for ( Count = 0; *(_BYTE *)(*(_DWORD *)(this + 4) + Count) && *(_BYTE *)(*(_DWORD *)(this + 4) + Count) != 13; ++Count )
    ;
  if ( Count >= a3 )
    return 0;
  strncpy(Destination, *(const char **)(this + 4), Count);
  Destination[Count] = 0;
  *(_DWORD *)(this + 4) += Count;
  if ( **(_BYTE **)(this + 4) == 13 )
  {
    ++*(_DWORD *)(this + 264);
    if ( *(_BYTE *)++*(_DWORD *)(this + 4) == 10 )
      ++*(_DWORD *)(this + 4);
  }
  return 1;
}

