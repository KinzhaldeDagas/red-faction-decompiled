// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B3220 rf_motion_sample_buffer_advance_playback_cursor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX buffer plus entity stackarg,RET4. Flags1320 bit1 set returns bufferEAX immediately. Otherwise resolves entityUID44 toplayer,calls scaled performance clock(1000000),delta=SIGNED32 current-last1328;milliseconds increment=int(ceil(float(delta/1000.0)));stores current1328 BEFORE deciding whether to advance cursor. Reads last sample timestamp at1280+2*(count1332-1) WITHOUT count check. Uses same asymmetric D(q,s) as3570 on(lastTimestamp,cursor1324). Advances16-bit cursor by increment only ORDERED globalF32 7B4DD4<=D;unordered threshold skips advance. Recomputes D after possible wrapping WORD addition;if D<0,clamps cursor to lastTimestamp and increments player-net-data[player4608]
// DWORD544 when bothplayer/netdata nonNULL. Does not reset lastclock when increment suppressed,cap negative/large increments,update physics position or interpolate directly. Return may beplayer pointer on counter-update path,otherwise buffer/incidentalEAX;not a boolean.
_DWORD *__thiscall rf_motion_sample_buffer_advance_playback_cursor(int this, int a2)
{
  _DWORD *result; // eax
  float v3; // [esp+4h] [ebp-1Ch]
  int v5; // [esp+10h] [ebp-10h]
  int v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+14h] [ebp-Ch]
  _DWORD *v8; // [esp+18h] [ebp-8h]
  int v9; // [esp+1Ch] [ebp-4h]

  result = (_DWORD *)this;
  if ( (*(_DWORD *)(this + 1320) & 1) == 0 )
  {
    v8 = sub_4DD720(*(_DWORD *)(a2 + 44));
    v7 = rf_performance_clock_elapsed_scaled(1000000);
    v3 = (double)(v7 - *(_DWORD *)(this + 1328)) / 1000.0;
    v9 = (int)rf_math_ceil_float(v3);
    *(_DWORD *)(this + 1328) = v7;
    if ( 0xFFFF - *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278) >= 5000
      || *(unsigned __int16 *)(this + 1324) >= 0x1388u )
    {
      if ( 0xFFFF - *(unsigned __int16 *)(this + 1324) >= 5000
        || *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278) >= 0x1388u )
      {
        v5 = *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278) - *(unsigned __int16 *)(this + 1324);
      }
      else
      {
        v5 = *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278)
           + 0xFFFF
           - *(unsigned __int16 *)(this + 1324);
      }
    }
    else
    {
      v5 = *(unsigned __int16 *)(this + 1324)
         + *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278)
         - 0xFFFF;
    }
    if ( unk_7B4DD4 <= (double)v5 )
      *(_WORD *)(this + 1324) += v9;
    if ( 0xFFFF - *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278) >= 5000
      || *(unsigned __int16 *)(this + 1324) >= 0x1388u )
    {
      if ( 0xFFFF - *(unsigned __int16 *)(this + 1324) >= 5000
        || *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278) >= 0x1388u )
      {
        result = (_DWORD *)this;
        v6 = *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278) - *(unsigned __int16 *)(this + 1324);
      }
      else
      {
        result = (_DWORD *)this;
        v6 = *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278)
           + 0xFFFF
           - *(unsigned __int16 *)(this + 1324);
      }
    }
    else
    {
      result = (_DWORD *)this;
      v6 = *(unsigned __int16 *)(this + 1324)
         + *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278)
         - 0xFFFF;
    }
    if ( v6 < 0 )
    {
      result = (_DWORD *)this;
      *(_WORD *)(this + 1324) = *(_WORD *)(this + 2 * *(_DWORD *)(this + 1332) + 1278);
      if ( v8 )
      {
        if ( v8[1152] )
        {
          ++*(_DWORD *)(v8[1152] + 544);
          return v8;
        }
      }
    }
  }
  return result;
}

