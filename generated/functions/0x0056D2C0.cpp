// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D2C0 rf_frame_clock_save_limits_and_set_wide_range
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Copies current min663ED8/max663EDC into single global backup pair18092FC/1809300,then calls56D250(10.0,float1e-5),yielding minimum9.999999747378752e-6 and maximum10seconds. This is a single overwriteable backup,not a stack or nesting counter; repeated call loses original saved limits. Does not disable frame updates or set divisor.
void __cdecl rf_frame_clock_save_limits_and_set_wide_range()
{
  flt_18092FC = flt_663ED8;
  flt_1809300 = flt_663EDC;
  rf_frame_clock_set_duration_limits_sorted(10.0, 0.0000099999997);
}

