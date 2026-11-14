// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005935E0 rf_vfile_unlink_resolved_loose_source
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Thiscall VFile receiver, optional filename, resolver context/id (RET8). Nonnull filename re-resolves source and returns-4 if resolver false. Null filename skips re-resolve and uses existing receiver fields, as57C700 does. Nonzero packed-member field+264 returns-3 with no unlink. Otherwise _unlink(receiver+5); clears resolved byte+4 whether unlink succeeds/fails, returns0 for CRT success or-99999 for failure. Does not clear readonly attributes, close open stream slots, remove registered lookup entries or validate filename/path before direct unlink.
int __thiscall rf_vfile_unlink_resolved_loose_source(int this, char *String2, int a3)
{
  int v4; // eax

  if ( String2 && !rf_vfile_resolve_open_source(this, String2, a3) )
    return -4;
  if ( *(_DWORD *)(this + 264) )
    return -3;
  v4 = _unlink((const char *)(this + 5));
  *(_BYTE *)(this + 4) = 0;
  if ( v4 )
    return -99999;
  else
    return 0;
}

