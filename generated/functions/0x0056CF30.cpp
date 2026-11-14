// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056CF30 rf_frame_clock_reset_defaults
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Writes raw delta663EC4 and effective delta663EC8=float(1/30),smoothed FPS663ECC=30,divisor663ED4=1,min duration663ED8=float(1/120),max663EDC=.25. Resets frameCounter18092E0,accumulated scaled ms18092E4,lastQpcSample18092E8 and ringSum18092EC to0;ring index663ED0=-1 defers clearing16-entry history18092A0 until next update. Does NOT clear lazy-init byte18092F0,pause depth18092F4,accumulator-suspend depth18092F8 or saved limit pair18092FC/1809300. No QPC sample/init here and no return result.
void rf_frame_clock_reset_defaults()
{
  flt_663EC4 = 0.033333335;
  rf_frame_delta_seconds = 0.033333335;
  flt_663ECC = 30.0;
  flt_18092A0[16] = 0.0;
  unk_18092E4 = 0;
  flt_663ED4 = 1.0;
  flt_663ED8 = 0.0083333338;
  flt_663EDC = 0.25;
  dword_18092E8 = 0;
  dword_663ED0 = -1;
  unk_18092EC = 0.0;
}

