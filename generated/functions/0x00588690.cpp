// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00588690 rf_animation_trigger_ensure
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): CORRECTION to earlier update description: scans two nonempty clip trigger names for exact case-sensitive equality. If found, RETURNS WITHOUT WRITING ITS TICK; supplied frame is ignored. Only when absent calls append5885D0 (which silently does nothing if full). This is ensure-existing-or-append, not update/set. Same unchecked handle indexing as append; return incidental.
int __thiscall rf_animation_trigger_ensure(_DWORD *this, int a2, char *a3, float a4)
{
  int result; // eax
  int v5; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  result = a2;
  v5 = *(this + a2 + 983);
  for ( i = 0; i < 2; ++i )
  {
    if ( *(_BYTE *)(v5 + 20 * i + 64) )
    {
      result = strcmp((const char *)(v5 + 20 * i + 64), a3);
      if ( !result )
        break;
    }
    result = i + 1;
  }
  if ( i == 2 )
    return rf_animation_trigger_append(this, a2, a3, a4);
  return result;
}

