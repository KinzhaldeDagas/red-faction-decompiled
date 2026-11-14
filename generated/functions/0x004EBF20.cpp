// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBF20 rf_player_begin_custom_fpgun_action
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Unequal local-global returns input player EAX. Equal pointer: resolve supplied weapon index mesh, store result unchanged in player model52 even0; dispatch semantic action10 custom_start; arm player60 randomized deadline throughBD20(raw20000..40000). No inputNULL, selected weapon/model validity, active-action or dispatch-result gate. Return final timer helper EAX on taken path; not guaranteed player pointer.
_DWORD *__cdecl rf_player_begin_custom_fpgun_action(_DWORD *a1, unsigned int a2)
{
  _DWORD *result; // eax

  result = a1;
  if ( a1 == (_DWORD *)rf_local_fpgun_player )
  {
    a1[13] = rf_fpgun_selected_mesh_resolve(a1, a2);
    rf_fpgun_dispatch_semantic_action((int)a1, 0xAu);
    return (_DWORD *)sub_4EBD20((int)a1);
  }
  return result;
}

