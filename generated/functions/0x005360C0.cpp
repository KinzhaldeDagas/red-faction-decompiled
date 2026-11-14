// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005360C0 rf_geomod_spatial_node_face_list_remove
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall counted-list receiver(head0,count4),targetFace,RET4. Decrements count BEFORE any membership check, without underflow guard. If target equals head, head=target.next88 and returns targetEAX WITHOUT clearing target.next88. Else search predecessors through next88; on first matching successor, splice target.next88 and clear target.next88=0, return targetEAX. Missing target leaves links untouched but count already decremented; EAX remains original head. Does not clear target.spatialOwner72 or touch solid84/room92/decal76 links, free face, or validate cycles. Requires nonnull target when empty head equals NULL; NULL/NULL path dereferences target+88.
int __thiscall rf_geomod_spatial_node_face_list_remove(int *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  --*(this + 1);
  if ( *this == a2 )
  {
    *this = *(_DWORD *)(a2 + 88);
    return a2;
  }
  else
  {
    result = *this;
    for ( i = *this; i; i = *(_DWORD *)(i + 88) )
    {
      if ( *(_DWORD *)(i + 88) == a2 )
      {
        *(_DWORD *)(i + 88) = *(_DWORD *)(a2 + 88);
        *(_DWORD *)(a2 + 88) = 0;
        return a2;
      }
    }
  }
  return result;
}

