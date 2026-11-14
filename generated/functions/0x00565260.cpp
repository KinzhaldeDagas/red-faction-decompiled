// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565260 rf_scene_handle_test_definition_node_flag
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl(handle,flatIndex), NO tag3 guard. Decodes handle.definition8 then reads SOURCE definition flags:kind0 WORD136 bit0,kind1/4 DWORD148 bit31,kind2 DWORD136 bit0,kind3 WORD164 bit15. Unknown kindfalse; decoded subindex unused. Does not query runtime hidden bits set by563A90 or check index/pointers.
unsigned __int8 __cdecl rf_scene_handle_test_definition_node_flag(const void *a1, int a2)
{
  unsigned __int8 result; // al
  int v3; // [esp+8h] [ebp-Ch] BYREF
  int v4; // [esp+Ch] [ebp-8h] BYREF
  int v5; // [esp+10h] [ebp-4h] BYREF

  rf_scene_definition_decode_flat_object_index(*((_DWORD **)a1 + 2), a2, &v5, &v4, &v3);
  switch ( v5 )
  {
    case 0:
      result = (*(_WORD *)(*(_DWORD *)(*((_DWORD *)a1 + 2) + 72) + 292 * v4 + 136) & 1) != 0;
      break;
    case 1:
    case 4:
      result = *(_DWORD *)(*(_DWORD *)(*((_DWORD *)a1 + 2) + 88) + 220 * v4 + 148) >> 31 != 0;
      break;
    case 2:
      result = (*(_DWORD *)(*(_DWORD *)(*((_DWORD *)a1 + 2) + 80) + 180 * v4 + 136) & 1) != 0;
      break;
    case 3:
      result = *(__int16 *)(*(_DWORD *)(*((_DWORD *)a1 + 2) + 96) + 172 * v4 + 164) < 0;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

