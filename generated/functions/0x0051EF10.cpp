// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EF10 rf_world_queue_see_through_room_faces
// UNREALRED VERIFIED [room-render-20261028]: If pending batch count>0 and solid/context differs from arg2, flushes existing batch. Stores arg2 as batch context0xA420B8. Traverses owner room face list+40; includes only see-through faces with rawflags0x1000 OR passing0x581910 visibility predicate. Before append, count>=16384 flushes batch; appends face pointer to0x930A40 and increments0xA420B4. No draw of current partial batch at return; later dispatcher/explicit flush handles it. Return incidental traversal value.
int __cdecl rf_world_queue_see_through_room_faces(int a1, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  if ( dword_A420B4 > 0 && dword_A420B8 != a2 )
    rf_world_flush_see_through_face_batch();
  dword_A420B8 = a2;
  result = rf_receiver_get_first_dword((void *)(a1 + 40));
  for ( i = result; i; i = result )
  {
    if ( rf_face_is_see_through((_DWORD *)(i + 40))
      && ((*(_DWORD *)(i + 40) & 0x1000) != 0 || rf_renderer_face_passes_view_test(i)) )
    {
      if ( dword_A420B4 >= 0x4000 )
        rf_world_flush_see_through_face_batch();
      unk_930A40[dword_A420B4++] = i;
    }
    result = rf_face_next_room_link(i);
  }
  return result;
}

