// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD8A0 rf_world_allocate_model_instance_render_data
// UNREALRED VERIFIED [resource-pools-20261028]: Only when global0x662D90 nonzero, traverses clutter and item lists; eligible object has model+128 nonnull, flags+124 mask2 clear and model kind1. Sums per-model storage requirement0x566360. If total>0 operator-news one block0x7B8E14, zeroes bytes, then assigns consecutive slices to each eligible object+636. No free of old block, integer overflow guard or clearing ineligible objects+636. Recomputes size per object in assignment pass.
void rf_world_allocate_model_instance_render_data()
{
  int Size; // [esp+4h] [ebp-14h]
  int j; // [esp+Ch] [ebp-Ch]
  int m; // [esp+Ch] [ebp-Ch]
  int v3; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]
  int k; // [esp+14h] [ebp-4h]

  if ( dword_662D90 )
  {
    Size = 0;
    for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
    {
      if ( *(_DWORD *)(i + 128)
        && (*(_DWORD *)(i + 124) & 2) == 0
        && rf_model_descriptor_get_kind(*(_DWORD *)(i + 128)) == 1 )
      {
        Size += rf_model_instance_render_data_size(*(_DWORD **)(i + 128));
      }
    }
    for ( j = unk_6FB1C4; (_UNKNOWN *)j != &unk_6FAF38; j = *(_DWORD *)(j + 652) )
    {
      if ( *(_DWORD *)(j + 128)
        && (*(_DWORD *)(j + 124) & 2) == 0
        && rf_model_descriptor_get_kind(*(_DWORD *)(j + 128)) == 1 )
      {
        Size += rf_model_instance_render_data_size(*(_DWORD **)(j + 128));
      }
    }
    if ( Size > 0 )
    {
      unk_7B8E14 = operator new(Size);
      if ( unk_7B8E14 )
      {
        memset(unk_7B8E14, 0, Size);
        v3 = 0;
        for ( k = rf_clutter_list_head; (_UNKNOWN *)k != &unk_666D18; k = *(_DWORD *)(k + 652) )
        {
          if ( *(_DWORD *)(k + 128)
            && (*(_DWORD *)(k + 124) & 2) == 0
            && rf_model_descriptor_get_kind(*(_DWORD *)(k + 128)) == 1 )
          {
            *(_DWORD *)(k + 636) = (char *)unk_7B8E14 + v3;
            v3 += rf_model_instance_render_data_size(*(_DWORD **)(k + 128));
          }
        }
        for ( m = unk_6FB1C4; (_UNKNOWN *)m != &unk_6FAF38; m = *(_DWORD *)(m + 652) )
        {
          if ( *(_DWORD *)(m + 128)
            && (*(_DWORD *)(m + 124) & 2) == 0
            && rf_model_descriptor_get_kind(*(_DWORD *)(m + 128)) == 1 )
          {
            *(_DWORD *)(m + 636) = (char *)unk_7B8E14 + v3;
            v3 += rf_model_instance_render_data_size(*(_DWORD **)(m + 128));
          }
        }
      }
    }
  }
}

