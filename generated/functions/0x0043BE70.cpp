// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043BE70 rf_entity_release_auxiliary_models_and_arrays
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl required entity. In order, model fields2120 then2124 are destroyed via native adapter564280 and only
// SIGNED DWORD>0 admits, followed by zeroing that field after callback. Then loop signed index0 upward over a freshly read array2264 count EACH iteration. Unchecked element
// accessor552200 uses backing DWORD+8; only SIGNED element value>0 calls564280, then recompute the element address and write0. Always release array2264 storage through517F40 after
// loop, even for nonpositive count. Next destroy/zero field5136 only if signed>0. Last read array5144 count and release its storage ONLY if signed>0; zero/negative count leaves its
// storage untouched. This body does not destroy individual5144 elements. Nonpositive model handles are retained, not normalized toNULL. No entity/container/index/duplicate-handle
// guard, callback rollback or object allocation free. Count, backing and slots are deliberately re-read after delegate effects. EAX is final count or release-helper residue, not a
// success Boolean.
void **__cdecl rf_entity_release_auxiliary_models_and_arrays(int a1)
{
  _DWORD **v1; // eax
  void **result; // eax
  int i; // [esp+0h] [ebp-4h]

  if ( *(int *)(a1 + 2120) > 0 )
  {
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 2120));
    *(_DWORD *)(a1 + 2120) = 0;
  }
  if ( *(int *)(a1 + 2124) > 0 )
  {
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 2124));
    *(_DWORD *)(a1 + 2124) = 0;
  }
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 2264)); ++i )
  {
    if ( *(int *)sub_552200((_DWORD *)(a1 + 2264), i) > 0 )
    {
      v1 = (_DWORD **)sub_552200((_DWORD *)(a1 + 2264), i);
      rf_model_handle_destroy_cdecl_adapter(*v1);
      *(_DWORD *)sub_552200((_DWORD *)(a1 + 2264), i) = 0;
    }
  }
  rf_pointer_array_release_storage((void **)(a1 + 2264));
  if ( *(int *)(a1 + 5136) > 0 )
  {
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 5136));
    *(_DWORD *)(a1 + 5136) = 0;
  }
  result = (void **)rf_receiver_get_first_dword((void *)(a1 + 5144));
  if ( (int)result > 0 )
    return rf_pointer_array_release_storage((void **)(a1 + 5144));
  return result;
}

