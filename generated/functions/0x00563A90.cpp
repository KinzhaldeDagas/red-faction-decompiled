// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00563A90 rf_model_handle_set_scene_node_hidden
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Corrected thiscall(handle,index,hiddenByte,propagateByte), RET12. Only tag3:sets mesh/point/dummy bit31 from hidden&1, effect kind4 bit30. Copies runtime record name into local76byte buffer without length check. Point pool release(index at record56) occurs only when hiddenByte EXACTLY1, not every odd value; does not clear index here. Propagate EXACTLY1 recursively visits all other flat objects whose parent-name strcmp equals copied name, using same flags. Kind1/default does not initialize copied name but still can enter propagation. No cycle guard, null checks or child-name case folding.
unsigned int __thiscall rf_model_handle_set_scene_node_hidden(
        void *this,
        int a2,
        unsigned __int8 a3,
        unsigned __int8 a4)
{
  unsigned int result; // eax
  char v5; // [esp+17h] [ebp-A9h]
  char *v6; // [esp+1Ch] [ebp-A4h]
  char *v7; // [esp+20h] [ebp-A0h]
  char v8; // [esp+27h] [ebp-99h]
  char *v9; // [esp+2Ch] [ebp-94h]
  char *v10; // [esp+30h] [ebp-90h]
  char v11; // [esp+37h] [ebp-89h]
  char *v12; // [esp+3Ch] [ebp-84h]
  char *v13; // [esp+40h] [ebp-80h]
  char v14; // [esp+47h] [ebp-79h]
  char *v15; // [esp+4Ch] [ebp-74h]
  char *v16; // [esp+50h] [ebp-70h]
  int i; // [esp+5Ch] [ebp-64h]
  signed int v19; // [esp+60h] [ebp-60h]
  char v20[4]; // [esp+64h] [ebp-5Ch] BYREF
  char v21[76]; // [esp+68h] [ebp-58h] BYREF
  int v22; // [esp+B8h] [ebp-8h] BYREF
  unsigned int v23; // [esp+BCh] [ebp-4h] BYREF

  result = (unsigned int)this;
  if ( *(_DWORD *)this == 3 )
  {
    rf_scene_definition_decode_flat_object_index(*((_DWORD **)this + 2), a2, &v23, &v22, v20);
    result = v23;
    switch ( v23 )
    {
      case 0u:
        v16 = *(char **)(152 * v22 + *(_DWORD *)(*((_DWORD *)this + 1) + 20));
        v15 = v21;
        do
        {
          v14 = *v16;
          *v15++ = *v16++;
        }
        while ( v14 );
        result = *(_DWORD *)(*((_DWORD *)this + 1) + 20);
        *(_DWORD *)(result + 152 * v22 + 28) = ((a3 & 1) << 31) | *(_DWORD *)(result + 152 * v22 + 28) & 0x7FFFFFFF;
        break;
      case 2u:
        v13 = *(char **)(60 * v22 + *(_DWORD *)(*((_DWORD *)this + 1) + 24));
        v12 = v21;
        do
        {
          v11 = *v13;
          *v12++ = *v13++;
        }
        while ( v11 );
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24) + 60 * v22 + 8) = ((a3 & 1) << 31)
                                                                            | *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24)
                                                                                        + 60 * v22
                                                                                        + 8)
                                                                            & 0x7FFFFFFF;
        result = a3;
        if ( a3 == 1 )
          result = rf_scene_point_pool_release_index(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24) + 60 * v22 + 56));
        break;
      case 3u:
        v7 = *(char **)(40 * v22 + *(_DWORD *)(*((_DWORD *)this + 1) + 32));
        v6 = v21;
        do
        {
          v5 = *v7;
          *v6++ = *v7++;
        }
        while ( v5 );
        result = *(_DWORD *)(*((_DWORD *)this + 1) + 32);
        *(_DWORD *)(result + 40 * v22 + 8) = ((a3 & 1) << 31) | *(_DWORD *)(result + 40 * v22 + 8) & 0x7FFFFFFF;
        break;
      case 4u:
        v10 = *(char **)(164 * v22 + *(_DWORD *)(*((_DWORD *)this + 1) + 28));
        v9 = v21;
        do
        {
          v8 = *v10;
          *v9++ = *v10++;
        }
        while ( v8 );
        result = 164 * v22;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 28) + 164 * v22 + 20) = ((a3 & 1) << 30)
                                                                              | *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 28)
                                                                                          + 164 * v22
                                                                                          + 20)
                                                                              & 0xBFFFFFFF;
        break;
      default:
        break;
    }
    if ( a4 == 1 )
    {
      result = rf_scene_definition_get_flat_object_count(*((_DWORD **)this + 2));
      v19 = result;
      for ( i = 0; i < v19; ++i )
      {
        if ( i != a2 && !strcmp(v21, rf_model_handle_get_parent_name(this, i)) )
          rf_model_handle_set_scene_node_hidden(this, i, a3, a4);
        result = i + 1;
      }
    }
  }
  return result;
}

