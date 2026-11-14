// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED180 rf_dsound3d_set_emitter_position_velocity_distances
// UNREALRED VERIFIED [wave-codec-20261028]: Five arguments backend buffer index,min-distance float,max-distance float,positionXYZ,velocityXYZ. Index-1 skips all andreturns0. Otherwise loads 3D buffer interface at0x1BA1824+44*index; vtable+76 sets position,+80 velocity,+68 firstdistance,+64 seconddistance,all flags1. Commits deferred listener state via global0x1F670F8 vtable+68. Ignores every HRESULT andreturns0. No index-range,null listener/interface or distance ordering validation.
int __cdecl rf_dsound3d_set_emitter_position_velocity_distances(int a1, float a2, float a3, float *a4, float *a5)
{
  int v6; // [esp+40h] [ebp-4h]

  if ( a1 != -1 )
  {
    v6 = unk_1BA1824[11 * a1];
    (*(void (__thiscall **)(int, int, _DWORD, float, float, int))(*(_DWORD *)v6 + 76))(v6, v6, *a4, a4[1], a4[2], 1);
    (*(void (__stdcall **)(int, _DWORD, float, float, int))(*(_DWORD *)v6 + 80))(v6, *a5, a5[1], a5[2], 1);
    (*(void (__stdcall **)(int, _DWORD, int))(*(_DWORD *)v6 + 68))(v6, LODWORD(a2), 1);
    (*(void (__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v6 + 64))(v6, v6, LODWORD(a3), 1);
    (*(void (__stdcall **)(_DWORD *))(*dword_1F670F8 + 68))(dword_1F670F8);
  }
  return 0;
}

