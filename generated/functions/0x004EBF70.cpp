// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBF70 rf_player_leave_custom_fpgun_action
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Same local-global equality and mesh assignment path asBF20 but dispatch semantic action11 custom_leave, then BD20 randomized deadline raw20000..40000 atplayer60. No matching prior custom_start or model validity check. Unequal returns input player; taken path returns timer delegate EAX. Equal NULL is not protected.
_DWORD *__cdecl rf_player_leave_custom_fpgun_action(_DWORD *a1, unsigned int a2)
{
  _DWORD *result; // eax

  result = a1;
  if ( a1 == (_DWORD *)rf_local_fpgun_player )
  {
    a1[13] = rf_fpgun_selected_mesh_resolve(a1, a2);
    rf_fpgun_dispatch_semantic_action((int)a1, 0xBu);
    return (_DWORD *)sub_4EBD20((int)a1);
  }
  return result;
}

