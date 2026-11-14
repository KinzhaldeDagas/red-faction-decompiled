// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00588450 rf_character_bone_parent_depth
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Recursive helper over76-byte primary-bone array: reads parent index at bone[index]+72. Any signed parent<=-1 terminates and returns supplied accumulator; otherwise recurses on parent with accumulator+1. No bone count, parent range, cycle or recursion-depth validation.
int __cdecl rf_character_bone_parent_depth(int a1, int a2, int a3)
{
  if ( *(int *)(a1 + 76 * a2 + 72) <= -1 )
    return a3;
  else
    return rf_character_bone_parent_depth(a1, *(_DWORD *)(a1 + 76 * a2 + 72), a3 + 1);
}

