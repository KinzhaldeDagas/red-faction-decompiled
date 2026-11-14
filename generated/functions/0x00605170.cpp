// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605170 rf_jpeg_master_select_scan_parameters
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmaster.c:select_scan_parameters matched): Selects a single full sequential scan in this build. Requires num_components <=4 (error 26), sets comps_in_scan, fills current component pointers using 84-byte component stride, and sets Ss=0, Se=63, Ah=0, Al=0. Custom scan scripts are rejected by master initialization.
_DWORD *__cdecl rf_jpeg_master_select_scan_parameters(_DWORD *a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( (int)a1[14] > 4 )
  {
    *(_DWORD *)(*a1 + 20) = 26;
    *(_DWORD *)(*a1 + 24) = a1[14];
    *(_DWORD *)(*a1 + 28) = 4;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  a1[60] = a1[14];
  for ( i = 0; i < a1[14]; ++i )
    a1[i + 61] = a1[16] + 84 * i;
  a1[78] = 0;
  a1[79] = 63;
  a1[80] = 0;
  a1[81] = 0;
  return a1;
}

