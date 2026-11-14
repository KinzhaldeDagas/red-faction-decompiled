// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E8A0 sub_43E8A0
// UNREALRED VERIFIED [combat-burn-owner-erratum-20261104]: Clears free head6E650C and active head6E6508; visits slots0..7, calls43EFD0(record,1), and appends each to the free circular list in ascending slot order via record+56/+60 links. Finally disarms shared6E6710 deadline. This is reset/free-ring reconstruction, distinct from43E740 static initialization.
void __cdecl sub_43E8A0()
{
  int *v0; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  unk_6E650C = 0;
  unk_6E6508 = 0;
  for ( i = 0; i < 8; ++i )
  {
    v0 = &unk_6E6510[16 * i];
    rf_burn_effect_release_record((float *)v0, 1u);
    if ( unk_6E650C )
    {
      v0[15] = *(_DWORD *)(unk_6E650C + 60);
      v0[14] = unk_6E650C;
      *(_DWORD *)(*(_DWORD *)(unk_6E650C + 60) + 56) = v0;
      *(_DWORD *)(unk_6E650C + 60) = v0;
    }
    else
    {
      v0[14] = (int)v0;
      v0[15] = (int)v0;
      unk_6E650C = &unk_6E6510[16 * i];
    }
  }
  rf_replicator_reset(&unk_6E6710);
}

