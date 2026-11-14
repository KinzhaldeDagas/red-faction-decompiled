// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CAF00 sub_4CAF00
// UNREALRED VERIFIED [combat-particle-vbm-lifetime-20261104]: Level-load47C6C0 calls thispoolreset at47CE62. It clearsglobalparticleflags/activecounts and reinitializes free/active links (pool0capacity500,pool1capacity1100), plus emitter reset4CE240. Old room-scoped particles do not continue into the next loaded RFworld. Unreal multi-import-level adapter should retire boundlevel presentation before reimport, preserving unrelated level owners.
_DWORD *__cdecl sub_4CAF00(int a1)
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-8h]
  int j; // [esp+0h] [ebp-8h]

  rf_particle_detached_list_reset_empty();
  unk_866604 = 500;
  unk_866600 = &unk_857BA0;
  unk_866608 = &unk_866608;
  dword_86660C[0] = (int)&unk_866608;
  dword_866680 = &dword_866680;
  unk_866684 = &dword_866680;
  unk_8666F8 = 0;
  for ( i = 0; i < unk_866604; ++i )
  {
    *(_DWORD *)(unk_866600 + 120 * i + 88) = 0;
    *(_WORD *)(unk_866600 + 120 * i + 78) = 0;
    *(_DWORD *)(unk_866600 + 120 * i + 4) = dword_86660C[0];
    *(_DWORD *)(120 * i + unk_866600) = &unk_866608;
    *(_DWORD *)dword_86660C[0] = unk_866600 + 120 * i;
    dword_86660C[0] = unk_866600 + 120 * i;
  }
  dword_866700 = 1100;
  unk_8666FC[0] = &unk_837800;
  unk_866704 = &unk_866704;
  unk_866708 = &unk_866704;
  unk_86677C[0] = unk_86677C;
  result = unk_8666FC;
  unk_866780 = unk_86677C;
  unk_8667F4 = 0;
  for ( j = 0; j < dword_866700; ++j )
  {
    *(_DWORD *)(unk_8666FC[0] + 120 * j + 88) = 0;
    *(_WORD *)(unk_8666FC[0] + 120 * j + 78) = 0;
    *(_DWORD *)(unk_8666FC[0] + 120 * j + 4) = unk_866708;
    *(_DWORD *)(120 * j + unk_8666FC[0]) = &unk_866704;
    *unk_866708 = unk_8666FC[0] + 120 * j;
    unk_866708 = unk_8666FC[0] + 120 * j;
    result = (_DWORD *)(j + 1);
  }
  unk_8377D8 = a1;
  unk_8377E0 = 0;
  unk_8377E8 = 0.0;
  dword_662DF0 = 1;
  return result;
}

