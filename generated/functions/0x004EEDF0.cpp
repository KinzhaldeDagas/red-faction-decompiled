// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EEDF0 rf_fplegs_render_model
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Recovered original99-byte closed function4EEDF0..4EEE53; no current code callers. Constructs model render options; position=global entity position60 minus its orientation forward row96 times float0.30000001. Renders leg model663038 with this position and entity orientation72; returns AL1 after delegate regardless of render outcome. No eligibility/NULL/asset checks or state writes.
bool __cdecl rf_fplegs_render_model()
{
  float *v0; // eax
  float scaled_result[3]; // [esp+4h] [ebp-68h] BYREF
  float out_vector[3]; // [esp+10h] [ebp-5Ch] BYREF
  char v4[80]; // [esp+1Ch] [ebp-50h] BYREF

  rf_model_render_options_construct(v4);
  v0 = rf_vector_multiply_scalar((const float *)(dword_681E38 + 96), scaled_result, 0.30000001);
  rf_vector_subtract((const float *)(dword_681E38 + 60), out_vector, v0);
  rf_model_handle_render_all_adapter(dword_663038, (int)out_vector, dword_681E38 + 72, (int)v4);
  return 1;
}

