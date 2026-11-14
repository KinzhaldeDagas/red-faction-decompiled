// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592390 rf_vfile_find_first_unused_stream_slot
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl scans four32832-byte global stream slots189CEB0; first slot DWORD0==0 returns index0..3, none returns-1. Does not reserve/initialize slot, check FILE/member pointers or grow pool.
int rf_vfile_find_first_unused_stream_slot()
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    if ( !unk_189CEB0[8208 * i] )
      return i;
  }
  return -1;
}

