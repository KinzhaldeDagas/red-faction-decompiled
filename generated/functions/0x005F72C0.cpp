// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F72C0 rf_scene_key_tracks_sample_quaternion
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args destination float4,time signedDWORD,unused BYTE;callee pops12. Count WORD2,pointer12,stride20. No keys ->(0,0,0,1). time<=first forces from0,to1,t0;time>=last forces from=count-2,to=count-1,t1;interior scans first timestamp>time and float fraction between neighbors. Calls eased packed-quaternion evaluator0x5F7410 then copies float4. With ONE key,time<=first still reads key index1 out of range;time>first uses from=-1,to0 direct-copy path. Assumes sorted timestamps,valid count/pointer and no signed subtraction overflow;unused flag never changes branch. Does not wrap time or directly copy endpoints as vector samplers do.
float *__thiscall rf_scene_key_tracks_sample_quaternion(int this, float *a2, int a3, char a4)
{
  _DWORD *v6; // [esp+20h] [ebp-1Ch]
  float v7; // [esp+24h] [ebp-18h]
  int v8[4]; // [esp+28h] [ebp-14h] BYREF
  int i; // [esp+38h] [ebp-4h]

  if ( *(_WORD *)(this + 2) )
  {
    i = 0;
    if ( a3 > **(_DWORD **)(this + 12) )
    {
      if ( a3 < *(_DWORD *)(20 * (*(unsigned __int16 *)(this + 2) - 1) + *(_DWORD *)(this + 12)) )
      {
        for ( i = 0; i < *(unsigned __int16 *)(this + 2) && *(_DWORD *)(20 * i + *(_DWORD *)(this + 12)) <= a3; ++i )
          ;
        v6 = (_DWORD *)(*(_DWORD *)(this + 12) + 20 * (i - 1));
        v7 = (double)(a3 - *v6) / (double)(*(_DWORD *)(*(_DWORD *)(this + 12) + 20 * i) - *v6);
      }
      else
      {
        i = *(unsigned __int16 *)(this + 2) - 1;
        v7 = 1.0;
      }
    }
    else
    {
      i = 1;
      v7 = 0.0;
    }
    rf_float4_construct_zero_zero_zero_one((float *)v8);
    rf_scene_key_tracks_evaluate_quaternion_eased(this, (float *)v8, i - 1, i, v7);
    rf_float4_assign_components_return_this(a2, (float *)v8);
    return a2;
  }
  else
  {
    rf_float4_construct_components(a2, 0.0, 0.0, 0.0, 1.0);
    return a2;
  }
}

