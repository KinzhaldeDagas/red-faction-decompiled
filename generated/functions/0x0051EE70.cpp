// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EE70 rf_world_invoke_render_callback_entry
// UNREALRED VERIFIED [room-render-20261028]: Only if enable global0x663B04 nonzero. Unless callback pointer at packet+44 is0x51EF10, flushes pending see-through-face batch through0x51EDD0 before invocation. If packet lighting byte+23 and global light-context0xA42084 nonnull, builds active light list using packet position+4,radius+16,constant1 and byte+24. Invokes callback with caller payload/context arguments, then clears active light list under same lighting condition. Does not update packet drawn/grouped flags itself or null-check callback.
void __thiscall rf_world_invoke_render_callback_entry(int this, int a2, int a3)
{
  if ( dword_663B04 )
  {
    if ( *(int (__cdecl **)(int, int))(this + 44) != rf_world_queue_see_through_room_faces )
      rf_world_flush_see_through_face_batch();
    if ( *(_BYTE *)(this + 23) && unk_A42084 )
      rf_light_build_active_list_for_sphere_query(unk_A42084, this + 4, *(float *)(this + 16), 1, *(_BYTE *)(this + 24));
    (*(void (__cdecl **)(int, int))(this + 44))(a2, a3);
    if ( *(_BYTE *)(this + 23) )
    {
      if ( unk_A42084 )
        rf_light_clear_active_world_list();
    }
  }
}

