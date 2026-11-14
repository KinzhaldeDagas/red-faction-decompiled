// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051ED00 rf_renderer_select_room_clip_aperture
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Cdecl room. Always store room pointer (orNULL) to globalA42084 FIRST, even when global663B00==0; disabled flag then skips ALL backend changes. Enabled plusNULL or authored-sky BYTE1 nonzero invokes5811A0 selector1 and four0.0 values to reset aperture. Enabled ordinary room invokes selector0 with room floats364,368,372,376 in that order. Wrapper dispatches only backend102. No fog setup, viewport reset, rectangle union, clipping validity test or mutation of room visibility flags. Return void; helper backend EAX ignored.
void __cdecl rf_renderer_select_room_clip_aperture(int a1)
{
  if ( !a1 )
  {
    unk_A42084 = 0;
    if ( !dword_663B00 )
      return;
    goto LABEL_7;
  }
  unk_A42084 = a1;
  if ( !dword_663B00 )
    return;
  if ( rf_room_is_authored_sky((_BYTE *)a1) )
  {
LABEL_7:
    rf_renderer_apply_room_clip_aperture_backend_wrapper(1, 0.0, 0.0, 0.0, 0.0);
    return;
  }
  rf_renderer_apply_room_clip_aperture_backend_wrapper(
    0,
    *(float *)(a1 + 364),
    *(float *)(a1 + 368),
    *(float *)(a1 + 372),
    *(float *)(a1 + 376));
}

