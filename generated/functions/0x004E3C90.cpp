// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E3C90 rf_cockpit_get_life_gauge_frame_and_integer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Cdecl(entity,int framecount,int*frame,int*life). Read LIFE F32 entity+52 divided by class pointer660 F32+68, multiply signed wrapping(framecount-1) in x87, round F32, ceil_float->FTOL->wrapping+1. If frame<1 set1; ELSE if frame>framecount setframecount. This ordered pair is not a universal valid-range clamp when framecount<=0. Then FTOL(entity life+52) to second output and return that same integer EAX. Despite armor texture names reads life, NOT armor+56. No NULL, zero max-life, finite or metadata count validation; ratio is not preclamped.
int __cdecl rf_cockpit_get_life_gauge_frame_and_integer(int a1, int a2, int *a3, int *a4)
{
  int result; // eax
  float v5; // [esp+4h] [ebp-8h]

  v5 = *(float *)(a1 + 52) / *(float *)(*(_DWORD *)(a1 + 660) + 68) * (double)(a2 - 1);
  *a3 = (int)rf_math_ceil_float(v5) + 1;
  if ( *a3 >= 1 )
  {
    if ( *a3 > a2 )
      *a3 = a2;
  }
  else
  {
    *a3 = 1;
  }
  result = (int)*(float *)(a1 + 52);
  *a4 = result;
  return result;
}

