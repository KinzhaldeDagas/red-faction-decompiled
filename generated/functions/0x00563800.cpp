// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00563800 rf_model_handle_set_scene_node_payload_flags
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Corrected false fastcall:ECX handle plus(index,payloadDWORD,flagsDWORD), RET12; no incoming EDX arg. Only tag3 acts. Decodes flat scene index:kind0 mesh152 sets dirty bit20000000 at28,payload24,merges caller low29flags preserving high3. Kinds1/4 effect164 set dirty10000000 at20,payload24,merge low28flags preserving high4. Kind2 point60 same dirty/mask at8,payload4. Kind3 dummy40 dirty20000000 at8,payload4,low29flags. Unsupported tags/kinds no change; decoded subindex ignored, no index/state checks; EAX incidental.
unsigned int __thiscall rf_model_handle_set_scene_node_payload_flags(void *this, int a2, int a3, unsigned int a4)
{
  unsigned int result; // eax
  _DWORD *v5; // kr00_4
  int v7; // [esp+8h] [ebp-Ch] BYREF
  int v8; // [esp+Ch] [ebp-8h] BYREF
  int v9; // [esp+10h] [ebp-4h] BYREF

  result = (unsigned int)this;
  if ( *(_DWORD *)this == 3 )
  {
    v5 = rf_scene_definition_decode_flat_object_index(*((_DWORD **)this + 2), a2, &v9, &v8, &v7);
    switch ( v9 )
    {
      case 0:
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 20) + 152 * v8 + 28) |= 0x20000000u;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 20) + 152 * v8 + 24) = a3;
        result = a4 & 0x1FFFFFFF | *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 20) + 152 * v8 + 28) & 0xE0000000;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 20) + 152 * v8 + 28) = result;
        break;
      case 1:
      case 4:
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 28) + 164 * v8 + 20) |= 0x10000000u;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 28) + 164 * v8 + 24) = a3;
        result = *(_DWORD *)(*((_DWORD *)this + 1) + 28);
        *(_DWORD *)(result + 164 * v8 + 20) = a4 & 0xFFFFFFF | *(_DWORD *)(result + 164 * v8 + 20) & 0xF0000000;
        break;
      case 2:
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24) + 60 * v8 + 8) |= 0x10000000u;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24) + 60 * v8 + 4) = a3;
        result = 60 * v8;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24) + 60 * v8 + 8) = a4 & 0xFFFFFFF
                                                                           | *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24)
                                                                                       + 60 * v8
                                                                                       + 8)
                                                                           & 0xF0000000;
        break;
      case 3:
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 32) + 40 * v8 + 8) |= 0x20000000u;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 32) + 40 * v8 + 4) = a3;
        result = a4 & 0x1FFFFFFF | *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 32) + 40 * v8 + 8) & 0xE0000000;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 32) + 40 * v8 + 8) = result;
        break;
      default:
        result = (unsigned int)v5;
        break;
    }
  }
  return result;
}

