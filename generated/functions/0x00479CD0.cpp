// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479CD0 rf_liquid_room_level_transition_start
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl(room pointer,target FLOAT,duration FLOAT), returns24-byte transition pointer. Reuses FIRST vector6FC46C record whose room pointer matches; otherwise allocates24 bytes and
// appends pointer BEFORE initializing payload, with no allocation-NULL guard. Record offsets room0,start4,current8,target12,duration16,elapsed20. Start/current=room FLOAT392 if
// BYTE388 ANY nonzero, else0; copies input target/duration and sets elapsed0. Retarget samples current room depth, not old target or newly recomputed interpolation. Does not clamp
// inputs, set room enable/depth, rebuild surface or roll back append.
float *__cdecl rf_liquid_room_level_transition_start(int a1, float a2, float a3)
{
  float *v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v4 = nullptr;
  for ( i = 0; i < rf_receiver_get_first_dword(unk_6FC46C); ++i )
  {
    if ( **(_DWORD **)sub_552200(unk_6FC46C, i) == a1 )
    {
      v4 = *(float **)sub_552200(unk_6FC46C, i);
      break;
    }
  }
  if ( !v4 )
  {
    v4 = (float *)operator new(0x18u);
    rf_pointer_array_append_dword(unk_6FC46C, (int)v4);
  }
  *(_DWORD *)v4 = a1;
  if ( *(_BYTE *)(a1 + 388) )
    v4[1] = *(float *)(a1 + 392);
  else
    v4[1] = 0.0;
  v4[2] = v4[1];
  v4[3] = a2;
  v4[4] = a3;
  v4[5] = 0.0;
  return v4;
}

