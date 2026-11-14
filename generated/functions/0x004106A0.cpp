// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004106A0 rf_path_record_sample_offset_point
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required record pointer,out three-float vector), EAX returns original input record pointer; no explicit status. Writes
// outputY FIRST as float32(record FLOAT+4 - record FLOAT+32*DOUBLE0.5 + DOUBLE2). Then stores float32 radiusLimit=record FLOAT+28-DOUBLE0.5; draws
// rf_random_float_range(0,radiusLimit) and rounds radial distance float32, then independently draws range(0,FLOAT6.2831854820251465) and rounds angle float32. Both random calls
// consume shared RNG even degenerate/reversed limits; unit sample is masked15bitrand/32768 in[0,1), although final range float32 rounding can reach endpoints. Computes
// outputX=float32(float-rounded cos(angle)*radial+record FLOAT+0), then outputZ=float32(float-rounded sin(angle)*radial+record FLOAT+8). No product float32 store between trig result
// and coordinate sum. Angle is radians; radius is sampled linearly, not by area/sqrt. No radius>=0/finite/output guard or rejection/resampling: record radius<0.5 leaves reversed
// radial bounds. Reads record fields as needed after prior writes rather than snapshotting entire record, so overlapping pointers retain native write/read ordering; partial outputY
// precedes all RNG/trig calls. No record marker or queue/count mutation.
float *__cdecl rf_path_record_sample_offset_point(float *a1, float *a2)
{
  double v2; // st7
  float v4; // [esp+8h] [ebp-Ch]
  float v5; // [esp+Ch] [ebp-8h]
  float v6; // [esp+10h] [ebp-4h]

  a2[1] = a1[1] - a1[8] * 0.5 + 2.0;
  v4 = a1[7] - 0.5;
  v5 = rf_random_float_range(0.0, v4);
  v6 = rf_random_float_range(0.0, 6.2831855);
  *a2 = rf_cos_float(v6) * v5 + *a1;
  v2 = rf_sin_float(v6);
  a2[2] = v2 * v5 + a1[2];
  return a1;
}

