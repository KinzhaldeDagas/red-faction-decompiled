// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527C70 rf_spot_light_set_cone_angles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl handle,innerFullAngleF32,outerFullAngleF32. Unchecked resolve; type!=3 leaves record unchanged. For type3, pre-refresh(mode0) only if category77 nonzero AND OLD innerAngle48 ORDERED>0; NaN/zero/negative old inner skips. Store newinner48, negative F32cos(F32(inner*.5)) to132; store newouter52, negative F32cos(F32(outer*.5)) to136. Endpoint extent140=F32(F32tan(F32(storedOuter*.5))*range60), NOT cosine. Increment serial once, then categorynonzero post-refresh(mode0) irrespective of new angle sign. Angles passed directly to trig (radians), no degree conversion, order/range/finite checks or direction normalization. No list mutation/active-list invalidation; EAX incidental resolved
// pointer,categorybyte or last coverage result. Corrects old repeatable/instruction cosine-extent claim.
int __cdecl rf_spot_light_set_cone_angles(int a1, float a2, float a3)
{
  int result; // eax
  float v4; // [esp+4h] [ebp-10h]
  float v5; // [esp+8h] [ebp-Ch]
  float v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  result = (int)rf_renderer_light_resolve_handle(a1);
  v7 = result;
  if ( *(_DWORD *)(result + 8) == 3 )
  {
    if ( *(_BYTE *)(result + 77) && *(float *)(result + 48) > 0.0 )
      rf_light_refresh_receiver_coverage(result, 0);
    *(float *)(v7 + 48) = a2;
    v6 = a2 * 0.5;
    *(float *)(v7 + 132) = -rf_cos_float(v6);
    *(float *)(v7 + 52) = a3;
    v5 = a3 * 0.5;
    *(float *)(v7 + 136) = -rf_cos_float(v5);
    v4 = *(float *)(v7 + 52) * 0.5;
    *(float *)(v7 + 140) = rf_tan_float(v4) * *(float *)(v7 + 60);
    ++rf_renderer_light_change_serial;
    result = *(unsigned __int8 *)(v7 + 77);
    if ( *(_BYTE *)(v7 + 77) )
      return rf_light_refresh_receiver_coverage(v7, 0);
  }
  return result;
}

