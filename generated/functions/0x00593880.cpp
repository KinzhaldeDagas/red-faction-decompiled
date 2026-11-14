// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593880 rf_vfile_add_readonly_archive_attribute_bits
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile, mask byte, optional filename, resolver context (RET12). Optional resolver failure-4; packed-member pointer returns-3; failed GetFileAttributesA returns-99999. ORs readonly OS1 when mask2 and archive OS0x20 when mask4, preserving all other existing attributes. Calls SetFileAttributesA even for mask0/irrelevant bits, returns0 on success or-99999. Adds bits only, does not replace entire attribute set, close stream or change cached path.
int __thiscall rf_vfile_add_readonly_archive_attribute_bits(
        void *self,
        unsigned __int8 mask,
        const char *filename,
        int context)
{
  DWORD dwFileAttributes; // [esp+4h] [ebp-4h]

  if ( filename && !rf_vfile_resolve_open_source((int)self, (char *)filename, context) )
    return -4;
  if ( *((_DWORD *)self + 66) )
    return -3;
  dwFileAttributes = GetFileAttributesA((LPCSTR)self + 5);
  if ( dwFileAttributes == -1 )
    return -99999;
  if ( (mask & 2) != 0 )
    dwFileAttributes |= 1u;
  if ( (mask & 4) != 0 )
    dwFileAttributes |= 0x20u;
  if ( SetFileAttributesA((LPCSTR)self + 5, dwFileAttributes) )
    return 0;
  else
    return -99999;
}

