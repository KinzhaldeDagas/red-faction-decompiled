// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F74D0 rf_scene_key_tracks_sample_vector2
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Track count WORD4,pointer16,stride40. Args destination vector,time signedDWORD. Zero count writes(0,0,0). Nonempty time<=first timestamp copies first key value+4;time>=last copies last value+4. Interior scans first timestamp>time,uses preceding index and fraction float((time-prevTime)/(nextTime-prevTime)),then cubic Bezier evaluator. Assumes sorted timestamps/count-pointer consistency;no duplicate/overflow/pointer guards. Copies three floats to destination,returns destination. No time wrap or interpolation easing.
float *__thiscall rf_scene_key_tracks_sample_vector2(int this, float *a2, int a3)
{
  float v5; // [esp+18h] [ebp-1Ch]
  int v6[3]; // [esp+20h] [ebp-14h] BYREF
  _DWORD *v7; // [esp+2Ch] [ebp-8h]
  int i; // [esp+30h] [ebp-4h]

  if ( *(_WORD *)(this + 4) )
  {
    if ( a3 > **(_DWORD **)(this + 16) )
    {
      if ( a3 < *(_DWORD *)(40 * (*(unsigned __int16 *)(this + 4) - 1) + *(_DWORD *)(this + 16)) )
      {
        for ( i = 0; i < *(unsigned __int16 *)(this + 4) && *(_DWORD *)(40 * i + *(_DWORD *)(this + 16)) <= a3; ++i )
          ;
        v7 = (_DWORD *)(*(_DWORD *)(this + 16) + 40 * (i - 1));
        v5 = (double)(a3 - *v7) / (double)(*(_DWORD *)(*(_DWORD *)(this + 16) + 40 * i) - *v7);
        rf_vector3_default_construct_noop(v6);
        rf_scene_key_tracks_evaluate_vector2_bezier((_DWORD *)this, (float *)v6, i - 1, i, v5);
        rf_vector3_copy_return_destination(a2, (float *)v6);
        return a2;
      }
      else
      {
        rf_vector3_copy_return_destination(
          a2,
          (float *)(*(_DWORD *)(this + 16) + 40 * (*(unsigned __int16 *)(this + 4) - 1) + 4));
        return a2;
      }
    }
    else
    {
      rf_vector3_copy_return_destination(a2, (float *)(*(_DWORD *)(this + 16) + 4));
      return a2;
    }
  }
  else
  {
    rf_vector3_set_components_return_destination(a2, 0.0, 0.0, 0.0);
    return a2;
  }
}

