// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005883D0 rf_character_build_bone_order_by_depth
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Writes byte indices to output in increasing parent depth: for depth0 upward, scans all count primary bones in original index order and appends those whose recursive parent depth equals current depth. Stops once output count reaches count; returns count (or0 for nonpositive input). Caller supplies50-byte order area at character+3876 and76-byte bone array at+76. Stable order within each depth, parents precede descendants for a valid forest. No output capacity, index truncation, parent range or cycle guard; recursive malformed chains can fail before ordering finishes.
int __cdecl rf_character_build_bone_order_by_depth(int a1, int a2, int a3)
{
  int result; // eax
  int i; // [esp+0h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-8h]
  int j; // [esp+8h] [ebp-4h]

  v5 = 0;
  for ( i = 0; ; ++i )
  {
    result = v5;
    if ( v5 >= a2 )
      break;
    for ( j = 0; j < a2; ++j )
    {
      if ( rf_character_bone_parent_depth(a3, j, 0) == i )
      {
        *(_BYTE *)(v5 + a1) = j;
        ++v5;
      }
    }
  }
  return result;
}

