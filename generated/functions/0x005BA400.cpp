// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA400 rf_animation_clip_add_instance_reference
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Increments signed DWORD reference counter at clip+116 and returns clip pointer bits. No load, allocation, NULL guard or overflow protection. Called when an instance action record successfully acquires clip data; distinct from field+112 cleared by clip release.
int __cdecl rf_animation_clip_add_instance_reference(int a1)
{
  ++*(_DWORD *)(a1 + 116);
  return a1;
}

