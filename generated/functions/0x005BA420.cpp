// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA420 rf_animation_clip_drop_instance_reference
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Decrements DWORD clip+116; if resulting signed value<0 clamps to0. Returns clip pointer bits. Does not free data when count reaches zero or change name/ownership. Signed wraparound is unchecked. Called before instance action record removal/compaction.
int __cdecl rf_animation_clip_drop_instance_reference(int a1)
{
  int result; // eax

  --*(_DWORD *)(a1 + 116);
  result = a1;
  if ( *(int *)(a1 + 116) < 0 )
    *(_DWORD *)(a1 + 116) = 0;
  return result;
}

