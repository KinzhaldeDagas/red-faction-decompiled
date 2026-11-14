// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573530 rf_renderer_set_bump_environment_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl six floats(luminanceScale,luminanceOffset,matrix00,matrix01,matrix10,matrix11),returnsBYTE. Selector102 loads each float through x87 and stores outgoing single-precision stack slot before calling5D4270;no numeric float-to-int conversion. Backend capability byte0 makes callee return0;otherwise writes six stage0 bump/luminance states and returns1 regardless HRESULT. Selectors104/others returnAL0 without touching arguments/device. No validation,texture bind,mode enable or cache invalidation added;exceptional FP load/store behavior inherited.
unsigned __int8 __cdecl rf_renderer_set_bump_environment_backend_dispatch(
        float luminance_scale,
        float luminance_offset,
        float matrix00,
        float matrix01,
        float matrix10,
        float matrix11)
{
  if ( dword_187CC9C == 102 )
    return rf_d3d8_set_bump_environment_states(
             luminance_scale,
             luminance_offset,
             matrix00,
             matrix01,
             matrix10,
             matrix11);
  else
    return 0;
}

