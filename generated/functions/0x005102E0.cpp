// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005102E0 rf_weapon_select_float224_236_248_260
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Argument order: selector byte, weapon index, alternate byte, override byte. Negative index returns ST0 zero; no upper bound. Extended selection iff override byte EXACTLY1 OR (record flags+612 mask10000000 AND alternate byte EXACTLY1). Extended selects F32+236 when first byte EXACTLY1, otherwise+260; normal selects+224 when first byte EXACTLY1, otherwise+248. ONLY first byte EXACTLY0 scales selected value by F32 table661254[difficulty6612A4], rounded to F32; other nonzero bytes select else-field without scaling. Returns stored F32 in ST0. Field source meanings remain unresolved; no finite/clamp/difficulty bounds guard.
double __cdecl rf_weapon_select_float224_236_248_260(char a1, int a2, char a3, char a4)
{
  float v5; // [esp+0h] [ebp-8h]
  float *v6; // [esp+4h] [ebp-4h]

  if ( a2 < 0 )
    return 0.0;
  v6 = (float *)((char *)&rf_weapon_records + 1360 * a2);
  if ( a4 == 1 || ((_DWORD)v6[153] & 0x10000000) != 0 && a3 == 1 )
  {
    if ( a1 == 1 )
      v5 = v6[59];
    else
      v5 = v6[65];
  }
  else if ( a1 == 1 )
  {
    v5 = v6[56];
  }
  else
  {
    v5 = v6[62];
  }
  if ( !a1 )
    return (float)(v5 * flt_661254[dword_6612A4]);
  return v5;
}

