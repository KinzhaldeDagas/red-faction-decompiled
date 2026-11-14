// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B500 rf_vfile_copy_registered_subdirectory_cstring_unbounded
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl root id and destination. Clears destination[0]; nonzero id unbounded-copies registered-root cstring at1897490+12*id including NUL. Root0 therefore returns empty string. Returns destination base; does not include data-root prefix, allocate output, validate id or accept a capacity.
char *__cdecl rf_vfile_copy_registered_subdirectory_cstring_unbounded(int root_id, char *out_text)
{
  char v2; // dl
  char *v4; // [esp+8h] [ebp-8h]
  char *v5; // [esp+Ch] [ebp-4h]

  *out_text = 0;
  if ( root_id )
  {
    v5 = (char *)dword_1897490[3 * root_id];
    v4 = out_text;
    do
    {
      v2 = *v5;
      *v4++ = *v5++;
    }
    while ( v2 );
  }
  return out_text;
}

