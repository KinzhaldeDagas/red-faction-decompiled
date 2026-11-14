// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCD20 rf_sound_list_select_play_return_asset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Cdecl(object,positionX,positionY,positionZ,list,count,floatA,floatB), eight DWORD slots. count>1 draws shared rand()%count; count<=1 uses index0, including zero/negative count without validation. Predicate0x4BD1F0 tests object type+36==0 before reading entity player+5168. Unless predicate is true and player+196 view-wrapper DWORD8 is zero, invokes positional sound at by-value XYZ, volume1, shared0x17F10B0,flags0 and ignores floatA/B. The alternate path invokes game sound event(asset,0,floatB,floatA). Ignores either play result and rereads/returns selected SOUND ASSET ID, not a voice handle. No null/list/extent guard.
int __cdecl rf_sound_list_select_play_return_asset(
        int a1,
        float a2,
        int a3,
        int a4,
        int a5,
        int a6,
        float a7,
        float a8)
{
  int v9; // [esp+Ch] [ebp-8h]

  if ( a6 <= 1 )
    v9 = 0;
  else
    v9 = rand() % a6;
  if ( !rf_entity_has_player_pointer_if_type0(a1)
    || rf_view_wrapper_get_dword8(*(_DWORD *)(*(_DWORD *)(a1 + 5168) + 196)) )
  {
    rf_gamesound_play_positional_event(*(_DWORD *)(a5 + 4 * v9), &a2, 1.0, (int)flt_17F10B0, 0);
  }
  else
  {
    rf_gamesound_play_event(*(_DWORD *)(a5 + 4 * v9), 0, a8, a7);
  }
  return *(_DWORD *)(a5 + 4 * v9);
}

