// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041B9C0 rf_render_instances_set_skin_handle_for_uid
// UNREALRED VERIFIED [switch-clutter-reset] Walks live render instances for one object UID and replaces their resolved skin handle and skin descriptor.
int __cdecl rf_render_instances_set_skin_handle_for_uid(int a1, int a2)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  if ( a2 >= 0 )
  {
    result = a2;
    if ( a2 < dword_680AE0 )
    {
      for ( i = unk_680DA0; (_UNKNOWN *)i != &unk_680AE8; i = result )
      {
        if ( *(_DWORD *)(i + 48) == a1 )
        {
          *(_DWORD *)(i + 688) = a2;
          *(_DWORD *)(i + 684) = &byte_680DD8[52 * a2];
        }
        result = *(_DWORD *)(i + 696);
      }
    }
  }
  return result;
}

