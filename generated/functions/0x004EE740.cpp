// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EE740 rf_player_bind_weapon_screen_material
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Enables private material table for player model52 with no own NULL/model guard. Scans signed count of200-byte materials; exact CASE-SENSITIVE screen.tga match at+20. For each match, if pointer188 is nonNULL writes its first float=0.7; stores player bitmap4232 into material DWORD16, including negative values. Does not allocate/validate bitmap. Returns loop index (zero for nonpositive count).
int __cdecl rf_player_bind_weapon_screen_material(int a1)
{
  int result; // eax
  int v2; // [esp+18h] [ebp-Ch] BYREF
  int i; // [esp+1Ch] [ebp-8h]
  int v4; // [esp+20h] [ebp-4h] BYREF

  rf_model_handle_enable_private_materials_get_table(*(_DWORD *)(a1 + 52), &v4, &v2);
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= v4 )
      break;
    if ( !strcmp((const char *)(v2 + 200 * i + 20), "screen.tga") )
    {
      if ( *(_DWORD *)(v2 + 200 * i + 188) )
        **(float **)(v2 + 200 * i + 188) = 0.69999999;
      *(_DWORD *)(v2 + 200 * i + 16) = *(_DWORD *)(a1 + 4232);
    }
  }
  return result;
}

