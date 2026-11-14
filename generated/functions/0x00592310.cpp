// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592310 rf_vfile_copy_vpp_archive_path_and_block_offset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile, destination cstring, DWORD offset output, UNUSED capacity-like third argument (RET12). If packed-member pointer+264 NULL returns AL0 with outputs unchanged. Otherwise unbounded-copies archive path at member.archivePointer(+16)+32, writes member DWORD+8 shifted left11 to offset output (2048-byte block addressing,32-bit wrap), returns1. Does not copy member filename, add member-relative position, open archive or check destination capacity/NULL pointers.
char __thiscall rf_vfile_copy_vpp_archive_path_and_block_offset(_DWORD *this, _BYTE *a2, _DWORD *a3, int a4)
{
  char v5; // al
  char *v7; // [esp+Ch] [ebp-8h]

  if ( !*(this + 66) )
    return 0;
  v7 = (char *)(*(_DWORD *)(*(this + 66) + 16) + 32);
  do
  {
    v5 = *v7;
    *a2++ = *v7++;
  }
  while ( v5 );
  *a3 = *(_DWORD *)(*(this + 66) + 8) << 11;
  return 1;
}

