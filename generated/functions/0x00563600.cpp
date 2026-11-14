// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00563600 rf_model_handle_get_indexed_record_base
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Tag2 returns character definition8 pointer and IGNORES supplied index. Tag1 returns instance4 DWORD76 +144*index. Tag3 decodes scene flattened index into kind/local/subindex, then returns kind0 base72+292*local,kind1or4 base88+220*local,kind2 base80+180*local,kind3 base96+172*local; other kind/tagNULL. Decoded subindex unused. No independent bounds checks; callers use returned record base as name storage for scene searches.
int __thiscall rf_model_handle_get_indexed_record_base(_DWORD *this, int a2)
{
  int result; // eax
  int v4; // [esp+8h] [ebp-Ch] BYREF
  int v5; // [esp+Ch] [ebp-8h] BYREF
  int v6; // [esp+10h] [ebp-4h] BYREF

  if ( *this == 2 )
    return *(this + 2);
  if ( *this == 1 )
    return *(_DWORD *)(*(this + 1) + 76) + 144 * a2;
  if ( *this != 3 )
    return 0;
  rf_scene_definition_decode_flat_object_index((_DWORD *)*(this + 2), a2, &v6, &v5, &v4);
  switch ( v6 )
  {
    case 0:
      result = *(_DWORD *)(*(this + 2) + 72) + 292 * v5;
      break;
    case 1:
    case 4:
      result = *(_DWORD *)(*(this + 2) + 88) + 220 * v5;
      break;
    case 2:
      result = *(_DWORD *)(*(this + 2) + 80) + 180 * v5;
      break;
    case 3:
      result = *(_DWORD *)(*(this + 2) + 96) + 172 * v5;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

