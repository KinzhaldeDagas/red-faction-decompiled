// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EECB0 rf_fplegs_update_transition_and_animation
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Recovered original312-byte closed function4EECB0..4EEDE8; no current code callers. Selects desired movement state. Only ordered duration>0 adds global frame delta to elapsed (float rounding); ordered duration<=elapsed commits current=pending,duration=0,pending=-1. Resets cyclic model mix. Ordered duration==0 uses current handle at unchecked current index, setting weight1 only if handle!=-1. Otherwise (including negative/NaN duration) reads unchecked pending index; if pending handle!=-1 sets current weight=float(1-elapsed/duration), EVEN if current handle==-1, and pending weight=float(elapsed/duration). Always advances leg model with frame delta, byte flag0,NULL position,NULL orientation,extra1. No range/NULL/weight-clamp
// checks.
void __cdecl rf_fplegs_update_transition_and_animation()
{
  float v0; // [esp+14h] [ebp-10h]
  float v1; // [esp+18h] [ebp-Ch]
  int v2; // [esp+1Ch] [ebp-8h]
  int v3; // [esp+20h] [ebp-4h]

  rf_fplegs_select_movement_state();
  if ( flt_87FBF8 > 0.0 )
  {
    flt_87FBFC = flt_87FBFC + rf_frame_delta_seconds;
    if ( flt_87FBF8 <= (double)flt_87FBFC )
    {
      dword_66303C = dword_663040;
      flt_87FBF8 = 0.0;
      dword_663040 = -1;
    }
  }
  rf_model_handle_reset_cyclic_adapter(dword_663038);
  v3 = dword_87FBDC[dword_66303C];
  if ( flt_87FBF8 == 0.0 )
  {
    if ( v3 != -1 )
      rf_model_handle_set_cyclic_mix_adapter((int *)dword_663038, v3, 1.0);
  }
  else
  {
    v2 = dword_87FBDC[dword_663040];
    if ( v2 != -1 )
    {
      v1 = flt_87FBFC / flt_87FBF8;
      v0 = 1.0 - v1;
      rf_model_handle_set_cyclic_mix_adapter((int *)dword_663038, v3, v0);
      rf_model_handle_set_cyclic_mix_adapter((int *)dword_663038, v2, v1);
    }
  }
  rf_vfx_update_instance((int *)dword_663038, rf_frame_delta_seconds, 0, 0, 0, 1);
}

