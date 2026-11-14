// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562B10 rf_model_handle_start_action_or_scene
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 forwards actionIndex,floatValue,byteFlag to character start_action. Tag3 ignores action index; float0 only sets instance bit4. Nonzero clears scene draining low bit via helper, clears bits4and2, assigns bit8 from byteFlag&1, resets clocks12/16. Actual nonzero float magnitude not used as scene speed/blend. Other tags unchanged; no common return/status.
void __thiscall rf_model_handle_start_action_or_scene(int *this, int a2, float a3, char a4)
{
  if ( *this == 2 )
  {
    rf_character_instance_start_action(*(this + 1), a2, a3, a4);
  }
  else if ( *this == 3 )
  {
    if ( a3 == 0.0 )
    {
      *(_DWORD *)*(this + 1) |= 4u;
    }
    else
    {
      rf_scene_instance_set_draining_low_bit((unsigned int *)*(this + 1), 0);
      *(_DWORD *)*(this + 1) &= ~4u;
      *(_DWORD *)*(this + 1) &= ~2u;
      *(_DWORD *)*(this + 1) = (8 * (a4 & 1)) | *(_DWORD *)*(this + 1) & 0xFFFFFFF7;
      *(float *)(*(this + 1) + 16) = 0.0;
      *(float *)(*(this + 1) + 12) = 0.0;
    }
  }
}

