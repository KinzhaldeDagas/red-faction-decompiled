// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0340 rf_bolt_emitter_try_spawn_and_rearm
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall emitter. Global BYTE662DC8==0 returns without writes/rearm. Otherwise emitter saved identifier8==-1 bypasses lookup; any other value requires nonnull
// object_find_by_saved_identifier4BC680(value), NOT handle resolver. Lookup failure also leaves timer unchanged. Scans four slots emitter+112+68*i for FIRST ordered life<=0; native
// TEST AH41/JP skips positive OR unordered life. At most one slot activated. If none free, still schedules next attempt. No active-byte88 check here; constructor can invoke directly
// while disabled.
// Slot layout: life0, cubic-curve pointer4, point-array(count8,capacity12,backing16), first/second control offsets20/32, drift vectors44/56. Flag92&8 chooses authored vector
// emitter28 for first offset and zero first drift; otherwise random unit directions scaled separately by random[0,length388] and random[length388/2,length388]. Flag92&16 does
// corresponding second offset from emitter52 or length392 randomization. Half-length/random outputs are stored binary32. Copies emitter16 into curve control0 and emitter40 into curve
// control36, then sets slot life=random[emitter76,80] binary32. Does NOT initialize curve interior controls12/24 or point-array vectors; tick/render must populate them.
// After scan, arms timestamp384 with trunc_toward_zero(random[emitter68,72]*1000), passing low EAX signed milliseconds to replicator. No bounds/finite/range/lifetime positivity or
// allocation-pointer validation; negative or zero sampled life remains free, NaN life becomes neither reusable nor ticked. Return EAX incidental timer/lookup/global result, not spawn
// success.
int __thiscall rf_bolt_emitter_try_spawn_and_rearm(int this)
{
  int result; // eax
  double v2; // st7
  double v3; // st7
  float v4; // [esp+4h] [ebp-44h]
  float v5; // [esp+4h] [ebp-44h]
  float v6; // [esp+4h] [ebp-44h]
  float v7; // [esp+4h] [ebp-44h]
  float v8; // [esp+8h] [ebp-40h]
  float v9; // [esp+Ch] [ebp-3Ch]
  float v11[3]; // [esp+14h] [ebp-34h] BYREF
  float v12[3]; // [esp+20h] [ebp-28h] BYREF
  float v13[3]; // [esp+2Ch] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+38h] [ebp-10h] BYREF
  int i; // [esp+44h] [ebp-4h]

  result = (unsigned __int8)byte_662DC8;
  if ( byte_662DC8 )
  {
    if ( *(_DWORD *)(this + 8) == -1 || (result = rf_object_find_by_saved_identifier(*(_DWORD *)(this + 8))) != 0 )
    {
      for ( i = 0; i < 4; ++i )
      {
        if ( *(float *)(this + 68 * i + 112) <= 0.0 )
        {
          if ( (*(_DWORD *)(this + 92) & 8) != 0 )
          {
            rf_vector_copy((float *)(this + 68 * i + 132), copy_result, (const float *)(this + 28));
            rf_vector3_zero_return_destination((float *)(this + 68 * i + 156));
          }
          else
          {
            rf_random_unit_vector_from_z_and_azimuth((float *)(this + 68 * i + 132));
            v4 = rf_random_float_range(0.0, *(float *)(this + 388));
            rf_vector3_scale_in_place_return_self((float *)(this + 68 * i + 132), v4);
            rf_random_unit_vector_from_z_and_azimuth((float *)(this + 68 * i + 156));
            v9 = *(float *)(this + 388) / 2.0;
            v5 = rf_random_float_range(v9, *(float *)(this + 388));
            rf_vector3_scale_in_place_return_self((float *)(this + 68 * i + 156), v5);
          }
          if ( (*(_DWORD *)(this + 92) & 0x10) != 0 )
          {
            rf_vector_copy((float *)(this + 68 * i + 144), v13, (const float *)(this + 52));
            rf_vector3_zero_return_destination((float *)(this + 68 * i + 168));
          }
          else
          {
            rf_random_unit_vector_from_z_and_azimuth((float *)(this + 68 * i + 144));
            v6 = rf_random_float_range(0.0, *(float *)(this + 392));
            rf_vector3_scale_in_place_return_self((float *)(this + 68 * i + 144), v6);
            rf_random_unit_vector_from_z_and_azimuth((float *)(this + 68 * i + 168));
            v8 = *(float *)(this + 392) / 2.0;
            v7 = rf_random_float_range(v8, *(float *)(this + 392));
            rf_vector3_scale_in_place_return_self((float *)(this + 68 * i + 168), v7);
          }
          rf_vector_copy(*(float **)(this + 68 * i + 116), v12, (const float *)(this + 16));
          rf_vector_copy((float *)(*(_DWORD *)(this + 68 * i + 116) + 36), v11, (const float *)(this + 40));
          v2 = rf_random_float_range(*(float *)(this + 76), *(float *)(this + 80));
          *(float *)(this + 68 * i + 112) = v2;
          break;
        }
      }
      v3 = rf_random_float_range(*(float *)(this + 68), *(float *)(this + 72)) * 1000.0;
      return rf_replicator_arm_milliseconds((int *)(this + 384), (int)v3);
    }
  }
  return result;
}

