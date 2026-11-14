// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCF80 rf_jpeg_quality_scaling
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:jpeg_quality_scaling matched): Cdecl signed quality. Clamps<=0 to1,>100 to100;quality<50 returns integer5000/quality,otherwise200-2*quality. Thusquality100scale0 produces allones after quant-table clamp;quality75scale50. Pureinteger function,no cinfo/state.
int __cdecl rf_jpeg_quality_scaling(int a1)
{
  if ( a1 <= 0 )
    a1 = 1;
  if ( a1 > 100 )
    a1 = 100;
  if ( a1 >= 50 )
    return 200 - 2 * a1;
  else
    return 5000 / a1;
}

