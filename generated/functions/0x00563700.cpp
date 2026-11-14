// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00563700 rf_model_handle_get_parent_name
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tags1and2 return literal"Scene Root" for every index. Tag3 decodes flat index and returns record+65 from kind0 scene base72 stride292,kind1or4 base88 stride220,kind2 base80 stride180,kind3 base96 stride172. Decoded subindex unused. Unsupported tag/kindNULL. No bounds/NUL validation; returned pointer is borrowed parent-name storage used by transform propagation.
const char *__thiscall rf_model_handle_get_parent_name(_DWORD *this, int a2)
{
  const char *result; // eax
  int v4; // [esp+8h] [ebp-Ch] BYREF
  int v5; // [esp+Ch] [ebp-8h] BYREF
  int v6; // [esp+10h] [ebp-4h] BYREF

  if ( *this == 2 )
    return "Scene Root";
  if ( *this == 1 )
    return "Scene Root";
  if ( *this != 3 )
    return nullptr;
  rf_scene_definition_decode_flat_object_index((_DWORD *)*(this + 2), a2, &v6, &v5, &v4);
  switch ( v6 )
  {
    case 0:
      result = (const char *)(*(_DWORD *)(*(this + 2) + 72) + 292 * v5 + 65);
      break;
    case 1:
    case 4:
      result = (const char *)(*(_DWORD *)(*(this + 2) + 88) + 220 * v5 + 65);
      break;
    case 2:
      result = (const char *)(*(_DWORD *)(*(this + 2) + 80) + 180 * v5 + 65);
      break;
    case 3:
      result = (const char *)(*(_DWORD *)(*(this + 2) + 96) + 172 * v5 + 65);
      break;
    default:
      result = nullptr;
      break;
  }
  return result;
}

