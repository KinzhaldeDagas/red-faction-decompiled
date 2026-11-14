// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005937F0 rf_vfile_get_readonly_archive_attribute_mask
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile, optional filename, resolver context (RET8). Optional re-resolution failure returns-4; existing packed-member pointer yields CONSTANT3 without OS call. Loose source GetFileAttributesA failure returns-99999; otherwise maps readonly OS1 to result2 and archive OS0x20 to result4, discards all other attributes. NULL filename uses existing resolved path. No FILE open needed and no slot validation.
int __thiscall rf_vfile_get_readonly_archive_attribute_mask(void *self, const char *filename, int context)
{
  DWORD FileAttributesA; // [esp+4h] [ebp-8h]
  int v6; // [esp+8h] [ebp-4h]

  v6 = 0;
  if ( filename && !rf_vfile_resolve_open_source((int)self, (char *)filename, context) )
    return -4;
  if ( *((_DWORD *)self + 66) )
    return 3;
  FileAttributesA = GetFileAttributesA((LPCSTR)self + 5);
  if ( FileAttributesA == -1 )
    return -99999;
  if ( (FileAttributesA & 1) != 0 )
    v6 = 2;
  if ( (FileAttributesA & 0x20) != 0 )
    return v6 | 4;
  return v6;
}

