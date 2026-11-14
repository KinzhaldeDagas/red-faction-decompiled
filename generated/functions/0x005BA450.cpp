// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA450 rf_animation_clip_pool_reset_names
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): For800 static clip records at1D6DA28,stride124, clears name[0] only. Returns loop count800 incidentally. Does not release buffers or reset ownership/reference count/trigger names/other fields; initialization should not be treated as ownership cleanup.
int rf_animation_clip_pool_reset_names()
{
  int result; // eax
  _BYTE *v1; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v2 = 0;
  v1 = &unk_1D6DA28;
  while ( v2 < 800 )
  {
    *v1 = 0;
    result = ++v2;
    v1 += 124;
  }
  return result;
}

