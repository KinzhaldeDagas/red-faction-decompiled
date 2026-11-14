// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587210 rf_character_instance_find_action_record
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Scans instance action count+4816,12-byte records at+4820. Exact integer animation index at record+0 matches input; returns first record index, else-1. Does not resolve names or create a record; no bounds/count validation.
int __thiscall rf_character_instance_find_action_record(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *(this + 1204); ++i )
  {
    if ( *(this + 3 * i + 1205) == a2 )
      return i;
  }
  return -1;
}

