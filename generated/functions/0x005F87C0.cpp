// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F87C0 rf_scene_frame_channel_unlink_cache
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This channel. When cache enabled0x1F67110,walks circular list head0x1F67114 via next136,stops after wrap,looking for pointer identity. Found sole head:zero next136/prev140/globalhead. Found other node:if head,advance globalhead to next;unlink prev.next and next.prev using retained THIS,zero both own links. If disabled/not found,no link changes. Finally calls no-op0x4580D0. Does NOT free shared frame pool,name storage or channel allocation. No malformed-list validation/refcount operation.
void __thiscall rf_scene_frame_channel_unlink_cache(_DWORD *this)
{
  _DWORD *v1; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  if ( unk_1F67110 )
  {
    for ( i = (_DWORD *)unk_1F67114; i; i = v1 )
    {
      if ( i == this )
      {
        if ( (_DWORD *)unk_1F67114 == this )
        {
          if ( (_DWORD *)*(this + 34) == this )
          {
            *(this + 34) = 0;
            *(this + 35) = 0;
            unk_1F67114 = 0;
            break;
          }
          unk_1F67114 = *(this + 34);
        }
        *(_DWORD *)(*(this + 35) + 136) = *(this + 34);
        *(_DWORD *)(*(this + 34) + 140) = *(this + 35);
        *(this + 34) = 0;
        *(this + 35) = 0;
        break;
      }
      if ( i[34] == unk_1F67114 )
        v1 = nullptr;
      else
        v1 = (_DWORD *)i[34];
    }
  }
  rf_shared_noop_destructor_4580d0();
}

