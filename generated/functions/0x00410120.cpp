// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410120 rf_path_record_dimensions_and_flag_admit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(requiredWidthF32,requiredHeightF32,LOWBYTE flag,required record pointer); explicit AL0/1, upper EAX incidental. Rejects
// ONLY ORDERED record FLOAT+28<requiredWidth, then ONLY ORDERED FLOAT+32<requiredHeight. Equality and UNORDERED comparisons pass each dimensional test. After both tests, exact flag
// BYTE1 AND record DWORD+64!=0 rejects; byte0 or any byte other than1 bypasses this field restriction. No positivity/finite/pointer validation and no writes. Fourth argument is
// dereferenced record pointer, not an integer identifier.
bool __cdecl rf_path_record_dimensions_and_flag_admit(float a1, float a2, char a3, int a4)
{
  if ( *(float *)(a4 + 28) < (double)a1 )
    return 0;
  if ( *(float *)(a4 + 32) < (double)a2 )
    return 0;
  return a3 != 1 || !*(_DWORD *)(a4 + 64);
}

