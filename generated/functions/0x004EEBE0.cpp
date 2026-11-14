// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EEBE0 rf_fplegs_request_state_transition
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Cdecl desired state, float duration. Signed state outside0..5 or animation handle-1 falls back to state0; missing handle0 returns without changes. Only ordered current duration==0 starts idle transition: pending=state,duration=newDuration,elapsed=0, current unchanged. Otherwise t=elapsed/duration rounded to float; only ORDERED t>0.5 promotes current=old pending and sets elapsed=float((1-t)*newDuration); t<=0.5 OR unordered retains current and sets elapsed=float(newDuration*t). Then pending=new state,duration=newDuration. Negative/NaN durations follow active branch; no finite/positive/clamp checks, no animation playback.
void __cdecl rf_fplegs_request_state_transition(unsigned int a1, float a2)
{
  double v2; // st7
  float v3; // [esp+0h] [ebp-4h]

  if ( a1 > 5 || dword_87FBDC[a1] == -1 )
    a1 = 0;
  if ( dword_87FBDC[a1] != -1 )
  {
    if ( flt_87FBF8 == 0.0 )
    {
      dword_663040 = a1;
      flt_87FBF8 = a2;
      flt_87FBFC = 0.0;
    }
    else
    {
      v3 = flt_87FBFC / flt_87FBF8;
      if ( v3 <= 0.5 )
      {
        v2 = a2 * v3;
      }
      else
      {
        dword_66303C = dword_663040;
        v2 = (1.0 - v3) * a2;
      }
      flt_87FBFC = v2;
      dword_663040 = a1;
      flt_87FBF8 = a2;
    }
  }
}

