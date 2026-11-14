// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E090 rf_int_max
// UNREALRED VERIFIED [hud-status-tint-general] Returns the greater of its two signed integer arguments. On-foot and supported vehicle HUD health formatting call it with a minimum value of one.
int __cdecl rf_int_max(int a1, int a2)
{
  if ( a1 <= a2 )
    return a2;
  else
    return a1;
}

