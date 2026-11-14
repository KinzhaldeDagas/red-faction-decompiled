// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6860 rf_positional_sound_destroy_all
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Walks the circular live-instance list headed at 1DB2458. Caches next before destroying each current instance with fade=0; computes index as (node-1DAEE58)/108. Assumes intact list links. Does not itself clear the initialized flag; shutdown wrapper does.
int rf_positional_sound_destroy_all()
{
  int result; // eax
  _BYTE *i; // [esp+0h] [ebp-8h]
  _BYTE *v2; // [esp+4h] [ebp-4h]

  result = dword_1DB2458;
  for ( i = (_BYTE *)dword_1DB2458; i != (_BYTE *)&dword_1DB2458; i = v2 )
  {
    v2 = *(_BYTE **)i;
    result = rf_positional_sound_destroy_instance((i - (_BYTE *)unk_1DAEE58) / 108, 0);
  }
  return result;
}

