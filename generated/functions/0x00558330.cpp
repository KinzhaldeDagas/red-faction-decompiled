// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558330 rf_lightmap_update_record_timed_if_enabled
// UNREALRED VERIFIED [renderer-lighting-20261028]: Arguments solidcontext,lightmaprecord. Does work only if BOTH globals0x17F109C and0x663E64 nonzero. Captures timer0x5673A0(1000000),calls0x54D990(lightmaprecord,solidcontext,1),captures same timeragain,and accumulates delta at0x17F10A0. Does not itself test recorddirtyflag; caller0x5DDD80 tests byte+8. Return either gatingglobal or finaltimer value,not lightingresult. Callee performs active-light queries and RGB/16-bit bitmapupdates; no broad calleecontract inferred here.
int __cdecl rf_lightmap_update_record_timed_if_enabled(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-8h]

  result = unk_17F109C;
  if ( unk_17F109C )
  {
    if ( dword_663E64 )
    {
      v3 = rf_performance_clock_elapsed_scaled(1000000);
      rf_lightmap_update_lighting_and_upload_rgb555(a2, a1, 1);
      result = rf_performance_clock_elapsed_scaled(1000000);
      dword_17F10A0 += result - v3;
    }
  }
  return result;
}

