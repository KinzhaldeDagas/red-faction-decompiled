// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CDFF0 rf_scene_definition_decode_flat_object_index
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Maps flat index using definition counts/pools: first modelCount+76 =>type0/model index; then walks emitterCount+92 and subtracts each maxParticles+152 =>type1/emitter index plus particle slot; next pointCount+84=>type2;next transformCount+100=>type3;remaining=>type4/emitter-definition index. Only type1 writes third output slot. Negative input can become negative model index; final type4 has NO upper bound check. Return register varies between index and output-pointer bits,not status. Callers must use explicit output type/index/slot.
_DWORD *__thiscall rf_scene_definition_decode_flat_object_index(
        _DWORD *this,
        int a2,
        _DWORD *a3,
        _DWORD *a4,
        _DWORD *a5)
{
  int v6; // [esp+4h] [ebp-4h]
  int v7; // [esp+10h] [ebp+8h]
  int v8; // [esp+10h] [ebp+8h]

  if ( a2 >= *(this + 19) )
  {
    v7 = a2 - *(this + 19);
    v6 = 0;
    if ( !*(this + 23) )
      goto LABEL_8;
    do
    {
      if ( v7 < *(_DWORD *)(*(this + 22) + 220 * v6 + 152) )
        break;
      v7 -= *(_DWORD *)(*(this + 22) + 220 * v6++ + 152);
    }
    while ( v6 != *(this + 23) );
    if ( v6 < *(this + 23) )
    {
      *a3 = 1;
      *a4 = v6;
      *a5 = v7;
      return (_DWORD *)v7;
    }
    else
    {
LABEL_8:
      if ( v7 >= *(this + 21) )
      {
        v8 = v7 - *(this + 21);
        if ( v8 >= *(this + 25) )
        {
          *a4 = v8 - *(this + 25);
          *a3 = 4;
          return a4;
        }
        else
        {
          *a4 = v8;
          *a3 = 3;
          return a3;
        }
      }
      else
      {
        *a4 = v7;
        *a3 = 2;
        return a4;
      }
    }
  }
  else
  {
    *a3 = 0;
    *a4 = a2;
    return a4;
  }
}

