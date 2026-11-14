// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487DC0 rf_mover_release_keys_arrays_and_unlink
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl mover common-object pointer; object_delete_dispatch invokes for type8. Walks pointer vector668 with dynamic signed count and raw operator-deletes EACH key pointer, then
// releases backing storage of vectors668,680,692,704,716. Only668 payloads are freed here; latter vectors are not element-owning in this body. Unlinks common next652/prev656 by
// prev.next=next,next.prev=prev, then zeros both own links. Does not free receiver, stop voices, clear linked-object flags, delete linked children or reset other scalar fields here.
// No duplicate-key or NULL/corrupt-link guard. Native normal EAX retains receiver pointer.
int __cdecl rf_mover_release_keys_arrays_and_unlink(int a1)
{
  void **v1; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 668)); ++i )
  {
    v1 = (void **)sub_552200((_DWORD *)(a1 + 668), i);
    operator delete(*v1);
  }
  rf_pointer_array_release_storage((void **)(a1 + 668));
  rf_pointer_array_release_storage((void **)(a1 + 680));
  rf_pointer_array_release_storage((void **)(a1 + 692));
  rf_pointer_array_release_storage((void **)(a1 + 704));
  rf_pointer_array_release_storage((void **)(a1 + 716));
  *(_DWORD *)(*(_DWORD *)(a1 + 656) + 652) = *(_DWORD *)(a1 + 652);
  *(_DWORD *)(*(_DWORD *)(a1 + 652) + 656) = *(_DWORD *)(a1 + 656);
  *(_DWORD *)(a1 + 652) = 0;
  *(_DWORD *)(a1 + 656) = 0;
  return a1;
}

